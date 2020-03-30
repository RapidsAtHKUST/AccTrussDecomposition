from data_analysis.util.read_file_utils_updated import *
from config import *
from data_analysis.common.common_utils import *

gpu23_config_lst = ['exp-03-21-study-all-edge-counting', '03-21-gro-exp.json', '03-21-gro-exp.md']
gpu_other_config_lst = ['exp-01-22-study-reordering-gpu-other', '01-22-gro-exp.json', '01-22-gro-exp.md']
knl_config_lst = ['exp-01-22-study-reordering-non-hbw', '01-22-gro-exp.json', '01-22-gro-exp.md']


def generate_statistics(platform_tag):
    if platform_tag is knl_tag:
        my_config_lst = knl_config_lst
    elif platform_tag is gpu_other_tag:
        my_config_lst = gpu_other_config_lst
    else:
        my_config_lst = gpu23_config_lst

    config_dict = get_config_dict(platform_tag, '../..')
    json_file_dir = '../data-json/' + platform_tag
    md_file_dir = '../data-md/' + platform_tag

    root_dir = config_dict[exp_res_root_mount_path_tag] + os.sep + my_config_lst[0]
    json_file_name = my_config_lst[1]
    md_file_name = my_config_lst[2]
    exec_lst = config_dict[exec_lst_tag]

    data_set_lst = []
    reorder_method_lst = ['gro', 'org', 'deg', 'kcore']
    for reorder_method in reorder_method_lst:
        data_set_lst = data_set_lst + list(map(lambda data_name: data_name + os.sep + reorder_method,
                                               config_dict[data_set_lst_tag]))
    output_data_set_lst = []
    for data_set in config_dict[data_set_lst_tag]:
        for reorder_method in reorder_method_lst:
            output_data_set_lst.append(data_set + os.sep + reorder_method)

    def fetch_data_to_json():
        os.system('mkdir -p ' + json_file_dir)

        my_dict = {}
        for data_set in data_set_lst:
            my_dict[data_set] = {}
            for thread_num in [config_dict[thread_num_tag]]:
                my_dict[data_set][thread_num] = {}
                for algorithm in exec_lst:
                    parameter_lst = [data_set, '0.2', '5', str(thread_num)]
                    test_file_path = os.sep.join([root_dir] + parameter_lst + [algorithm + '.txt'])
                    my_dict[data_set][thread_num][algorithm] = get_all_edge_cnt_time_mem_info(test_file_path)

        with open(os.sep.join([json_file_dir, json_file_name]), 'w') as ofs:
            ofs.write(json.dumps(my_dict, indent=4))

    def convert_json_to_md():
        with open(os.sep.join([json_file_dir, json_file_name])) as ifs:
            my_dict = json.load(ifs)
        lines = ['# O(E) intersection count time', '\n\nUnit: seconds']

        for data_set in output_data_set_lst:
            cols = ['file-name', 'Pre-Reorder', 'Pre-Layout', 'All-Edge-Comp',
                    'All-Edge-Total', 'S4 (Output) (KB)']
            lines.extend(['\n\n### ' + data_set + '\n',
                          ' | '.join(cols),
                          ' | '.join(['---' for _ in range(len(cols))]),
                          ])
            sort_tmp_lst = []
            for algorithm in exec_lst:
                # with fixed thread number
                thread_num = str(config_dict[thread_num_tag])

                single_stat_dict = my_dict[data_set][thread_num][algorithm]
                if single_stat_dict[is_correct_tag] is True and single_stat_dict[is_time_out_tag] is False:
                    time_lst = list(map(lambda tag: str(single_stat_dict[tag][time_tag]) if
                    single_stat_dict[tag] is not None else None, all_edge_cnt_time_tag_lst[:-1]))

                    value_lst = list(map(transform, time_lst)) + [
                        transform(str(single_stat_dict[output_cores_non_cores_tag][mem_tag]))]
                    elapsed_time = 999999 if time_lst[2] is None else float(time_lst[2])
                    algo_name = all_edge_cnt_exec_alias_dict[algorithm]
                    if 'bsr' in algorithm or 'emptyheaded' in algorithm or 'roaring' in algorithm:
                        sort_tmp_lst.append(
                            (' | '.join(['**' + algo_name + '**'] + value_lst),
                             elapsed_time))
                    elif algorithm in ["scan-xp-naive-galloping-single",
                                       "scan-xp-sse-hybrid",
                                       "scan-xp-sse-merge",
                                       "scan-xp-naive-bitvec",
                                       "scan-xp-naive-bitvec-2d",
                                       "scan-xp-avx2-hybrid",
                                       "scan-xp-avx2-merge",
                                       ]:
                        sort_tmp_lst.append(
                            (' | '.join(['`' + algo_name + '`'] + value_lst),
                             elapsed_time))
                    else:
                        sort_tmp_lst.append(
                            (' | '.join([all_edge_cnt_exec_alias_dict[algorithm]] + value_lst), elapsed_time))
            sort_tmp_lst = sorted(sort_tmp_lst, key=lambda t: t[1])
            for line, cmp_val in sort_tmp_lst:
                lines.append(line)

        os.system('mkdir -p ' + md_file_dir)
        with open(os.sep.join([md_file_dir, md_file_name]), 'w') as ofs:
            ofs.write('\n'.join(lines))

    fetch_data_to_json()
    convert_json_to_md()


if __name__ == '__main__':
    generate_statistics(platform_tag=gpu23_tag)
    # generate_statistics(platform_tag=lccpu12_tag)
    # generate_statistics(platform_tag=knl_tag)
    # generate_statistics(platform_tag=gpu_other_tag)
