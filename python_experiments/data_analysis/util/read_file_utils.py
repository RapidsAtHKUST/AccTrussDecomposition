import decimal
import os

# Tri-Cnt Related.
from functools import reduce

reorder_tag = 'PreProcess Reordering Cost'
preprocess_tag2 = 'PreProcess-'

forward_tag = 'Forward cost'
tri_cnt_time_lst = [reorder_tag, preprocess_tag2, forward_tag]

# SCAN-XP Related.
check_core_tag = 'Step1 - CheckCore:'
cluster_core_tag = 'Step2 - ClusterCore'
label_non_core_tag = 'Step3 - LabelNonCore'
init_cluster_id_tag = 'Step4 - cluster id initialization cost'
cluster_id_assign_tag = 'Step4 - prepare results'
output_cores_non_cores_tag = 'Step4 - output to the disk cost'

all_edge_cnc_comp_tag = 'All-Edge Computation'
all_edge_cnc_total_tag = 'All-Edge CN-Cnt Cost'
preprocess_tag = 'PreProcess'
time_tag_lst = [preprocess_tag,
                check_core_tag, cluster_core_tag, label_non_core_tag, init_cluster_id_tag,
                cluster_id_assign_tag,
                output_cores_non_cores_tag]

bin_search_cost_tag = 'bin-search cost'
core_checking_sim_cal_cost_tag = 'core-checking sim-core-comp cost'
cpu_side_cost_tag_lst = [bin_search_cost_tag, core_checking_sim_cal_cost_tag]
cpu_side_task_range_init_tag = 'task range init by filtered accumulated degree cost'
cpu_corountine_time_tag = 'CPU corountine time'

deg_lst_init_time_tag = 'before csr transform time'
scatter_time_tag = 'before sort time'
edge_list_to_csr_time_tag = 'edge list to csr time'
edge_lst_to_csr_time_tag_lst = [deg_lst_init_time_tag, scatter_time_tag, edge_list_to_csr_time_tag]
mem_usage_tag = 'Mem Usage'
time_tag = 'time'
mem_tag = 'mem'

cuda_kernel_elapsed_time_tag = 'CUDA Kernel Time'
cuda_kernel_lauch_time_tag = 'CUDA kernel lauch cost'
cuda_driver_and_malloc_tag = 'CUDA driver and malloc cost'
is_correct_tag = 'is_correct'
is_time_out_tag = 'is_time_out'

func = lambda x: x[-1]

all_edge_cnt_exec_alias_dict = {
    "scan-xp-naive-merge": "M",
    "scan-xp-avx2-merge": "VBM",
    "scan-xp-tetzank-avx2-asm": "VASM-M",
    "scan-xp-avx2-lemire": "VPS-V3",
    "scan-xp-naive-hybrid": "MPS",
    "scan-xp-avx2-hybrid": "VMPS",
    "scan-xp-sse-han-qfilter": "VQF",
    "scan-xp-sse-han-bmiss-sttni": "VBMISS",
    "scan-xp-sse-emptyheaded-layout-uint": "EH-UI",
    "scan-xp-sse-emptyheaded-layout-hybrid": "EH-HY",
    "scan-xp-sse-han-bsr-qfilter": "BSR-VQF",
    "scan-xp-sse-han-bsr-scalar-merge": "BSR-M",
    "scan-xp-sse-han-bsr-scalar-galloping": "BSR-GAL",
    "scan-xp-avx2-roaring": "VROAR",
    "scan-xp-naive-bitvec": "BMP",
    "scan-xp-naive-bitvec-2d": "BMP-2D",
    "scan-xp-naive-bitvec-adv": "BMP-HY",
    "scan-xp-naive-bitvec-op": "BMP-OP",
    "scan-xp-compact-forward-reorder": "CF-VPS-SSE",
    "scan-xp-compact-forward-avx2-lemire": "CF-VPS",
    "scan-xp-compact-forward-bmp": "CF-BMP",
    "scan-xp-compact-forward-avx2-asm-tetzank": "CF-VASM-M",
    "scan-xp-compact-forward-qfilter": "CF-VQF",
    "scan-xp-compact-forward-bmiss-sttni": "CF-VBMISS",
    "scan-xp-cf-hybrid": "CF-HY"
}

tri_cnt_exec_alias_dict = {
    "tri-cnt-naive-merge": "M",
    "tri-cnt-avx2-bmerge": "VBM",
    "tri-cnt-avx2-asm-tetzank": "VASM-M",
    "tri-cnt-sse-han-qfilter": "VQF",
    "tri-cnt-avx2-lemire": "VPS-V3",
    "tri-cnt-naive-hybrid": "MPS",
    "tri-cnt-avx2-hybrid": "VMPS",
    "tri-cnt-sse-han-bmiss-sttni": "VBMISS",
    "tri-cnt-sse-eh-uint": "EH-UI",
    "tri-cnt-sse-eh-hybrid": "EH-HY",
    "tri-cnt-sse-bsr-qfilter": "BSR-VQF",
    "tri-cnt-naive-bsr-scalar-merge": "BSR-M",
    "tri-cnt-avx2-roaring": "VROAR",
    "tri-cnt-naive-bitvec": "BMP",
    "tri-cnt-naive-bitvec-2d": "BMP-2D",
    "tri-cnt-naive-bitvec-adv": "BMP-HY",
    "tri-cnt-naive-bitvec-op": "BMP-OP"
}


def format_str(float_num):
    if float_num is None:
        return None
    if isinstance(float_num, str):
        return float_num
    # print type(float_num)
    my_str = str(decimal.Decimal.from_float(float_num).quantize(decimal.Decimal('0.000')))
    return my_str


def get_triangle_cnt_time_mem_info(file_path):
    my_time_tag_lst = tri_cnt_time_lst
    my_dict = dict(zip(my_time_tag_lst, [get_time_mem_info(file_path, tag, func) for tag in my_time_tag_lst]))
    my_dict[is_time_out_tag] = get_simple_tag_info(file_path, is_time_out_tag,
                                                   lambda input_lst: reduce(lambda l, r: l or r, input_lst, False))
    return my_dict


def get_overview_time_mem_info(file_path):
    my_time_tag_lst = time_tag_lst + [core_checking_sim_cal_cost_tag]
    # print my_time_tag_lst
    my_dict = dict(zip(my_time_tag_lst, [get_time_mem_info(file_path, tag, func) for tag in my_time_tag_lst]))
    my_dict[is_correct_tag] = \
        my_dict[output_cores_non_cores_tag] is not None and \
        get_simple_tag_info(file_path, is_correct_tag,
                            lambda input_lst: reduce(lambda l, r: l and r, input_lst, True)) == True
    my_dict[is_time_out_tag] = get_simple_tag_info(file_path, is_time_out_tag,
                                                   lambda input_lst: reduce(lambda l, r: l or r, input_lst, False))
    return my_dict


def get_overview_time_mem_info_cuda(file_path):
    extra_cuda_tag_lst = [cuda_kernel_elapsed_time_tag, cuda_kernel_lauch_time_tag, cpu_corountine_time_tag]
    cuda_time_tag_lst = time_tag_lst + extra_cuda_tag_lst + cpu_side_cost_tag_lst
    if 'multi-gpu' in file_path or 'scan-xp-cuda-experimental-bitmap-varying-multi-pass' in file_path \
            or 'scan-xp-cuda-experimental-hybrid-kernels-varying-multi-pass' in file_path or \
            'scan-xp-cuda-experimental-bitmap1D-varying-multi-pass' in file_path \
            or 'scan-xp-cuda-experimental-hybrid-kernels-varying-block-size' in file_path or \
            'scan-xp-cuda-experimental-bitmap-varying-block-size' in file_path:
        cuda_time_tag_lst += [cpu_side_task_range_init_tag]
    my_dict = dict(zip(cuda_time_tag_lst,
                       [get_time_info(file_path, tag, func) if tag in extra_cuda_tag_lst else get_time_mem_info(
                           file_path, tag, func) for tag in cuda_time_tag_lst]))
    my_dict[is_correct_tag] = \
        my_dict[output_cores_non_cores_tag] is not None and \
        get_simple_tag_info(file_path, is_correct_tag,
                            lambda input_lst: reduce(lambda l, r: l and r, input_lst, True)) == True and \
        my_dict[cuda_kernel_elapsed_time_tag] != 0.0
    my_dict[is_time_out_tag] = get_simple_tag_info(file_path, is_time_out_tag,
                                                   lambda input_lst: reduce(lambda l, r: l or r, input_lst, False))

    my_dict[cuda_driver_and_malloc_tag] = my_dict[cuda_kernel_lauch_time_tag] - my_dict[
        cuda_kernel_elapsed_time_tag] if my_dict[is_correct_tag] == True else None
    return my_dict


def get_edge_lst_to_csr_time_info(file_path):
    return dict(
        zip(edge_lst_to_csr_time_tag_lst,
            [get_time_info(file_path, tag, func) for tag in edge_lst_to_csr_time_tag_lst]))


def get_simple_tag_info(file_path, tag, functor):
    if not os.path.exists(file_path):
        return None
    with open(file_path) as ifs:
        # assume unit seconds
        filtered_tuples = filter(lambda line: tag in line and '*-' not in line, ifs.readlines())
        filtered_tuples = list(map(lambda line:
                              eval(line.strip().split(':')[-1]), filtered_tuples))
        return None if len(filtered_tuples) == 0 else functor(filtered_tuples)


def get_time_info(file_path, tag, functor):
    if not os.path.exists(file_path):
        return None
    with open(file_path) as ifs:
        # assume unit seconds
        tuples = filter(lambda t: len(t) >= 4,
                        map(lambda l: l.strip().split(),
                            filter(lambda l: not l.startswith('*-*-'), ifs.readlines())))
        print('tuples:', tuples)

        filtered_tuples = [' '.join(t[4:]) for t in tuples]
        filtered_tuples = filter(lambda t: t.startswith(tag), filtered_tuples)
        print(tag, 'filtered:', filtered_tuples)

        def get_time(l):
            t = l.split(':')[-1]
            if t.rstrip().endswith('ms'):
                time = float(eval(t.split('ms')[0])) / 1000.0
            else:
                time = eval(t.split('s')[0])
            print('time:', time)
            return time

        filtered_tuples = list(map(get_time, filtered_tuples))
        return None if len(filtered_tuples) == 0 else functor(filtered_tuples)


def get_time_mem_info(file_path, tag, functor):
    print(file_path)
    if not os.path.exists(file_path):
        return None
    with open(file_path) as ifs:
        # assume unit seconds
        print(ifs.readlines())
        tuples = filter(lambda t: len(t) >= 4,
                        map(lambda l: l.strip().split(),
                            filter(lambda l: not l.startswith('*-*-'), ifs.readlines())))
        print('tuple:', tuples)
        filtered_tuples = [' '.join(t[4:]) for t in tuples]
        filtered_tuples = filter(lambda t: t.startswith(tag), filtered_tuples)
        print(tag, 'filtered:', filtered_tuples)

        def get_time_mem(l):
            # print l
            t = l.split('s,')
            time = eval(t[0].split(':')[-1].split()[0])
            if time is not None:
                time = float(format_str(time))
            mem = t[1].split(':')[-1].split()[0]
            return {time_tag: time, mem_tag: mem}

        filtered_tuples = list(map(get_time_mem, filtered_tuples))
        return None if len(filtered_tuples) == 0 else functor(filtered_tuples)


if __name__ == '__main__':
    root_dir = '/home/yche/mnt/luocpu8/nfsshare/share/scan-query-root/' \
               'python_experiments/exp_results/overview-08-08-cmp-hugepage'
    parameter_lst = ['snap_orkut', '0.2', '5', '256']
    algorithm_name = 'scan-xp-avx512-hybrid.txt'
    test_file_path = os.sep.join([root_dir] + parameter_lst + [algorithm_name])
    path = '/home/yche/mnt/wangyue-clu/csproject/biggraph/ywangby/yche/new-git-repos-yche/' \
           'scan-query-root/python_experiments/exp_results/' \
           'edge-list-to-csr-performance/n50_m20_1billion_edge/normal/edge_list_to_csr_performance_measure.txt'

    print(get_time_info(path, edge_lst_to_csr_time_tag_lst[0], func))
    print(get_edge_lst_to_csr_time_info(path))
