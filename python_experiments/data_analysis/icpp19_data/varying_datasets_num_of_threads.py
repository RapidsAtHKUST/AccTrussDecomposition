from data_analysis.util.read_file_utils import *
from config import *
from data_analysis.common.common_utils import *

my_config_lst = ['overview-09-23-cpu-knl-best', '09-23-cpu-knl-best-varying-threads.json',
                 '09-23-cpu-knl-best-varying-threads.md']
my_config_lst_10_13_knl_hbw = ['exp-10-13', '10-13-hbw.json',
                               '10-13-hbw.md']
my_config_lst_10_13_knl_non_hbw = ['exp-10-13-non-hbw', '10-13-non-hbw.json',
                                   '10-13-non-hbw.md']
my_config_lst_10_13_knl_non_hbw_cache_mode = ['exp-10-15-cache-knl-non-hbw', '10-15-cache-knl-non-hbw.json',
                                              '10-15-cache-knl-non-hbw.md']

my_config_lst_10_19_knl_flat_mode = ['exp-10-19-flat-knl', '10-19-knl-flat-hbw.json',
                                     '10-19-knl-flat-hbw.md']
knl_config_lst_lst = [my_config_lst_10_19_knl_flat_mode]

cpu_config_lst_10_13 = ['exp-10-13', '10-13.json', '10-13.md']
cpu_config_lst_10_19 = ['exp-10-19-flat-knl', 'exp-10-19.json', 'exp-10-19.md']
cpu_config_lst_lst = [cpu_config_lst_10_19]


def generate_statistics(platform_tag):
    config_dict = get_config_dict(platform_tag, '../..')
    json_file_dir = '../data-json/' + platform_tag
    md_file_dir = '../data-md/' + platform_tag

    root_dir = config_dict[exp_res_root_mount_path_tag] + os.sep + my_config_lst[0]
    json_file_name = my_config_lst[1]
    md_file_name = my_config_lst[2]

    exec_lst = filter(lambda name: 'cuda' not in name, config_dict[exec_lst_tag])
    # exec_lst = filter(lambda name: 'naive-galloping' not in name, exec_lst)
    # exec_lst = filter(lambda name: 'naive-merge' not in name, exec_lst)
    # exec_lst = filter(lambda name: 'naive-hybrid' not in name, exec_lst)

    data_set_lst = config_dict[data_set_lst_tag] + list(map(lambda data_name: data_name + os.sep + rev_deg_order_tag,
                                                       config_dict[data_set_lst_tag]))
    output_data_set_lst = []
    for data_set in config_dict[data_set_lst_tag]:
        output_data_set_lst.append(data_set)
        output_data_set_lst.append(data_set + os.sep + rev_deg_order_tag)

    thread_lst = map(str, sorted(map(int, config_dict[thread_num_lst_tag])))

    def fetch_data_to_json():
        os.system('mkdir -p ' + json_file_dir)

        my_dict = {}
        for data_set in data_set_lst:
            my_dict[data_set] = {}
            for thread_num in thread_lst:
                my_dict[data_set][thread_num] = {}
                for algorithm in exec_lst:
                    parameter_lst = [data_set, '0.2', '5', str(thread_num)]
                    test_file_path = os.sep.join([root_dir] + parameter_lst + [algorithm + '.txt'])
                    my_dict[data_set][thread_num][algorithm] = get_overview_time_mem_info(test_file_path)

        with open(os.sep.join([json_file_dir, json_file_name]), 'w') as ofs:
            ofs.write(json.dumps(my_dict, indent=4))

    def convert_json_to_md():
        with open(os.sep.join([json_file_dir, json_file_name])) as ifs:
            my_dict = json.load(ifs)
        lines = ['# O(E) intersection count Elapsed time', '\n\nUnit: seconds']

        for data_set in output_data_set_lst:
            lines.extend(['\n\n### ' + data_set + '\n',
                          ' | '.join(['file-name'] + thread_lst),
                          ' | '.join(['---' for _ in range(len(thread_lst) + 1)]),
                          ])
            for algorithm in filter(lambda name: 'bitvec' in name if 'rev_deg' in data_set \
                    else 'bitvec' not in name, exec_lst):
                # with fixed thread number
                value_lst = []
                for thread_num in thread_lst:
                    time_lst = list(map(lambda tag: str(my_dict[data_set][thread_num][algorithm][tag][time_tag]) if
                    my_dict[data_set][thread_num][algorithm][tag] is not None else None,
                                        time_tag_lst + [core_checking_sim_cal_cost_tag]))
                    core_checking_time = time_lst[0]
                    sim_cal_time = time_lst[-1]
                    elapsed_time = float(core_checking_time) - float(sim_cal_time) if no_body_is_none(
                        [core_checking_time, sim_cal_time]) else None
                    value_lst.append(format_str(elapsed_time) if elapsed_time is not None else '/')
                lines.append(' | '.join([algorithm.replace('scan-xp-', '')] + value_lst))

        os.system('mkdir -p ' + md_file_dir)
        with open(os.sep.join([md_file_dir, md_file_name]), 'w') as ofs:
            ofs.write('\n'.join(lines))

    fetch_data_to_json()
    convert_json_to_md()


if __name__ == '__main__':
    for config in knl_config_lst_lst:
        my_config_lst = config
        generate_statistics(platform_tag=knl_tag)
    for config in cpu_config_lst_lst:
        my_config_lst = config
        generate_statistics(platform_tag=lccpu12_tag)
