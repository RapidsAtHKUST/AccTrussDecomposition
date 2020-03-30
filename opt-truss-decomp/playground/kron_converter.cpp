//
// Created by yche on 12/15/19.
//

#include <cmath>

#include <fstream>

#include <malloc.h>
#include <omp.h>

#include <util/program_options/popl.h>
#include <util/timer.h>
#include <util/util.h>
#include <util/stat.h>

#include <util/graph/graph.h>
#include <util/graph/pre_processing.h>

using namespace popl;
using namespace std;

#define PAGE_SIZE (4096)
#define IO_REQ_SIZE (PAGE_SIZE * 32)
#define IO_QUEUE_DEPTH (16)

template<typename Deg, typename Adj>
void WriteToOutputFiles(string &deg_output_file, string &adj_output_file, Deg &degrees, size_t vertex_num,
                        Adj &dst_vertices, size_t edge_num) {
    ofstream deg_ofs(deg_output_file, ios::binary);

    Timer timer;
    int int_size = sizeof(int);
    deg_ofs.write(reinterpret_cast<const char *>(&int_size), 4);
    deg_ofs.write(reinterpret_cast<const char *>(&vertex_num), 4);
    deg_ofs.write(reinterpret_cast<const char *>(&edge_num), 4);
    deg_ofs.write(reinterpret_cast<const char *>(degrees), vertex_num * 4u);
    log_info("degree file write time: %.3lf s", timer.elapsed_and_reset());

    ofstream adj_ofs(adj_output_file, ios::binary);
    adj_ofs.write(reinterpret_cast<const char *>(dst_vertices), edge_num * 4u);
    log_info("adj file write time: %.3lf s", timer.elapsed_and_reset());
}

int main(int argc, char *argv[]) {
    OptionParser op("Allowed options");
    auto string_option = op.add<Value<std::string>>("f", "file-path", "the graph bin file path");
    auto output_dir_option = op.add<Value<std::string>>("o", "o-file-path", "the graph ouput bin directory path");
    op.parse(argc, argv);

    using Edge = pair<int32_t, int32_t>;
    Timer global_timer;
    if (string_option->is_set() && output_dir_option->is_set()) {
        size_t size = file_size(string_option->value(0).c_str());
        size_t num_edges = size / sizeof(uint32_t) / 2;
        log_info("File size: %zu", size);
        log_info("#of Edges: %zu", num_edges);

        // Load Bin File (DIO).
        auto file_name = string_option->value(0);
        auto output_dir = output_dir_option->value(0);
        auto file_fd = open(file_name.c_str(), O_RDONLY | O_DIRECT, S_IRUSR | S_IWUSR);
//        auto file_fd = open(file_name.c_str(), O_RDONLY, S_IRUSR | S_IWUSR);
        Edge *edge_lst = (Edge *) memalign(PAGE_SIZE, size + IO_REQ_SIZE);
        auto prev = edge_lst;

        auto max_omp_threads = omp_get_max_threads();
        Timer io_timer;
        size_t read_size = 0;
#pragma omp parallel num_threads(IO_QUEUE_DEPTH)
        {
#pragma omp for schedule(dynamic, 1) reduction(+:read_size)
            for (size_t i = 0; i < size; i += IO_REQ_SIZE) {
                auto it_beg = i;
                auto *chars = reinterpret_cast<uint8_t *>(edge_lst);
                auto ret = pread(file_fd, chars + it_beg, IO_REQ_SIZE, it_beg);
                if (ret != IO_REQ_SIZE) {
                    log_error("Err, %zu, %zu, %zu, %d", i, it_beg, IO_REQ_SIZE, ret);
                } else {
                    read_size += ret;
                }
            }
#pragma omp single
            log_info("%zu, %zu", read_size, size);
        }

        log_info("IO Time: %.6lfs, DIO-QPS: %.6lf GB/s", io_timer.elapsed(), size / io_timer.elapsed() / pow(1024, 3));
        log_info("Load File Time: %.9lfs", global_timer.elapsed());

        // 1st: Remove Multi-Edges and Self-Loops.
        auto edge_lst_buffer = (Edge *) memalign(PAGE_SIZE, size + IO_REQ_SIZE);
        auto max_node_id = RemoveDuplicates(edge_lst, num_edges, edge_lst_buffer);
        auto num_vertices = max_node_id + 1;
        free(edge_lst_buffer);

        uint32_t *deg_lst;
        graph_t g{.n=num_vertices, .m = 0, .adj=nullptr, .num_edges=nullptr};
        ConvertEdgeListToCSR((uint32_t) num_edges, edge_lst, num_vertices, deg_lst, g.num_edges, g.adj,
                             max_omp_threads);
        g.m = g.num_edges[num_vertices];
#pragma omp parallel for schedule(dynamic, 1000)
        for (auto u = 0; u < num_vertices; u++) {
            sort(g.adj + g.num_edges[u], g.adj + g.num_edges[u + 1]);
        }
        log_info("Undirected Graph G = (|V|, |E|): %lld, %lld", g.n, g.m);
        log_info("Mem Usage: %s KB", FormatWithCommas(getValue()).c_str());

        auto ret = exec(string("mkdir -p " + output_dir).c_str());
        log_info("ret: %s", ret.c_str());
        string deg_file_path = output_dir + "/" + +"b_degree.bin";
        string reorder_adj_file_path = output_dir + "/"  "/" + "b_adj.bin";

        WriteToOutputFiles(deg_file_path, reorder_adj_file_path, deg_lst, num_vertices, g.adj, g.m);
        // Verification.
        // No duplicates, sorted, no-self loops.
        Graph test_g((char *) output_dir.c_str());
    }
}