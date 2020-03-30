from data_analysis.util.read_file_utils_updated import *
from config import *

# my_config_lst = ['exp-03-11-study-tri-cnt-deg', '03-15-tri-cnt-reorder.json', '03-15-tri-cnt-reorder.md']
my_config_lst = ['exp-03-25-study-tri-cnt', '03-25-study-tri-cnt.json', '03-25-study-tri-cnt.md']


def generate_statistics(platform_tag):
    assert platform_tag is gpu23_tag
    config_dict = get_config_dict(platform_tag, '../..')
    json_file_dir = '../data-json/' + platform_tag
    md_file_dir = '../data-md/' + platform_tag

    root_dir = config_dict[exp_res_root_mount_path_tag] + os.sep + my_config_lst[0]
    json_file_name = my_config_lst[1]
    md_file_name = my_config_lst[2]
    exec_lst = config_dict[triangle_exec_lst_tag]

    data_set_lst = config_dict[data_set_lst_tag]
    total_data_set_lst = []
    reorder_method_lst = ['gro', 'org', 'deg', 'kcore']
    for reorder_method in reorder_method_lst:
        total_data_set_lst += [os.sep.join([d, reorder_method]) for d in data_set_lst]

    output_data_set_lst = []
    for data_set in config_dict[data_set_lst_tag]:
        for reorder_method in reorder_method_lst:
            output_data_set_lst.append(os.sep.join([data_set, reorder_method]))

    def fetch_data_to_json():
        os.system('mkdir -p ' + json_file_dir)

        my_dict = {}
        for data_set in total_data_set_lst:
            my_dict[data_set] = {}
            for thread_num in [config_dict[thread_num_tag]]:
                my_dict[data_set][thread_num] = {}
                for algorithm in exec_lst:
                    parameter_lst = [data_set, str(thread_num)]
                    test_file_path = os.sep.join([root_dir] + parameter_lst + [algorithm + '.txt'])
                    my_dict[data_set][thread_num][algorithm] = get_triangle_cnt_time_mem_info_updated(test_file_path)

        with open(os.sep.join([json_file_dir, json_file_name]), 'w') as ofs:
            ofs.write(json.dumps(my_dict, indent=4))

    def convert_json_to_md():
        with open(os.sep.join([json_file_dir, json_file_name])) as ifs:
            my_dict = json.load(ifs)
        lines = ['# O(E) tri count time', '\n\nUnit: seconds']

        columns = ['file-name', 'Pre-Reorder', 'Pre-Layout', 'TriCnt', 'Max-Deg', 'Res']
        for data_set in output_data_set_lst:
            lines.extend(['\n\n### ' + data_set + '\n',
                          ' | '.join(columns),
                          ' | '.join(['---' for _ in range(len(columns))]),
                          ])
            sort_tmp_lst = []
            for algorithm in exec_lst:
                # with fixed thread number
                thread_num = str(config_dict[thread_num_tag])
                single_stat_dict = my_dict[data_set][thread_num][algorithm]

                time_lst = list(map(lambda tag: str(single_stat_dict[tag][time_tag]) if \
                    single_stat_dict[tag] is not None else None, tri_cnt_time_lst))
                tri_cnt_time = time_lst[-1]
                tri_cnt_time = float(tri_cnt_time) if tri_cnt_time is not None else 0
                time_lst = list(map(lambda time: str(time) if time is not None else '/', time_lst))

                abrr_name = tri_cnt_exec_alias_dict[algorithm]
                content = [abrr_name] + time_lst + list(map(str, [single_stat_dict[max_d_tag],
                                                                  single_stat_dict[triangle_cnt_tag]]))
                if 'bsr' in algorithm or 'eh' in algorithm or 'roaring' in algorithm:
                    content = ['**' + string + '**' for string in content]
                elif 'bitvec' in algorithm:
                    content = ['`' + string + '`' for string in content]
                sort_tmp_lst.append((' | '.join(content), tri_cnt_time))
            sort_tmp_lst = sorted(sort_tmp_lst, key=lambda t: t[1])
            for line, cmp_val in sort_tmp_lst:
                lines.append(line)

        os.system('mkdir -p ' + md_file_dir)
        with open(os.sep.join([md_file_dir, md_file_name]), 'w') as ofs:
            ofs.write('\n'.join(lines))

    # fetch_data_to_json()
    convert_json_to_md()


if __name__ == '__main__':
    generate_statistics(platform_tag=gpu23_tag)
