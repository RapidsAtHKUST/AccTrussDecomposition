from data_analysis.util.read_file_utils_updated import *
from config import *
from data_analysis.util.data_set_names import *

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
    root_dir = config_dict[exp_res_root_mount_path_tag] + os.sep + my_config_lst[0]

    data_set_lst = []
    reorder_method_lst = ['gro', 'org', 'deg', 'kcore']
    for reorder_method in reorder_method_lst:
        data_set_lst = data_set_lst + map(lambda data_name: data_name + os.sep + reorder_method,
                                          config_dict[data_set_lst_tag])
    output_data_set_lst = []
    for data_set in config_dict[data_set_lst_tag]:
        for reorder_method in reorder_method_lst:
            output_data_set_lst.append(data_set + os.sep + reorder_method)

    def save_stat_to_md():
        algorithm = 'scan-xp-compact-forward-bmp'
        cols = ['Dataset', 'Order', 'Time', 'Mis', 'Total', 'Ratio']
        splitter = ['---' for _ in range(len(cols))]
        stat_res = [' | '.join(cols), ' | '.join(splitter)]
        for data_set in output_data_set_lst:
            for thread_num in [config_dict[thread_num_tag]]:
                test_file_path = os.sep.join(
                    [root_dir, data_set, '0.2', '5', str(thread_num)] + [algorithm + '.txt'])
                lines = get_file_lines(test_file_path)
                t = get_time_mem_info_updated(lines, all_edge_cnc_comp_tag, lambda x: x[-1])
                filtered = list(filter(lambda l: 'MisMatch' in l, lines))

                def get_info():
                    return ' '.join(filtered[-1].split(' ')[get_log_header_col() + 1:]).split(', ')

                lst = map(str, [get_data_set_name(data_set.split('/')[0]),
                                data_set.split('/')[1], t[time_tag]] + get_info()) \
                    if len(filtered) > 0 else ['/'] * 6
                stat_res.append(' | '.join(lst))
        print('\n'.join(stat_res))
        with open('../data-md/cf-stat.md', 'w') as ofs:
            ofs.write('\n'.join(stat_res))

    save_stat_to_md()


if __name__ == '__main__':
    generate_statistics(platform_tag=gpu23_tag)
    # generate_statistics(platform_tag=lccpu12_tag)
    # generate_statistics(platform_tag=knl_tag)
    # generate_statistics(platform_tag=gpu_other_tag)
