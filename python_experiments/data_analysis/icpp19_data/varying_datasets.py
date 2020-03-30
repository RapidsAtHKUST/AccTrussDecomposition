from data_analysis.util.read_file_utils import *
from config import *
from data_analysis.common.common_utils import *

folder_name_09_18_cpu_knl = ['overview-09-18-cpu-knl', '09-18-cpu-knl-overview.json', '09-18-cpu-knl-overview.md']
knl_non_hbw = ['overview-09-23-knl-non-hbw', '09-23-knl-non-hbw.json', '09-23-knl-non-hbw.md']
filtered_09_18_cpu_knl = ['overview-09-18-cpu-knl', '09-18-filtered-cpu-overview.json',
                          '09-18-filtered-cpu-knl-overview.md']
filtered_09_29_cpu_knl = ['overview-09-29-non-sym', '09-29-non-sym.json',
                          '09-29-non-sym.md', lambda name: name + '-non-sym-assign']
my_config_lst = ['exp-01-09-study', '01-10-exp.json', '01-10-exp.md']
knl_config_lst = ['exp-01-09-study-non-hbw', '01-10-exp-non-hbw.json', '01-10-exp-non-hbw.md']


def generate_statistics(platform_tag):
    if platform_tag is knl_tag:
        global my_config_lst
        my_config_lst = knl_config_lst
    config_dict = get_config_dict(platform_tag, '../..')
    json_file_dir = '../data-json/' + platform_tag
    md_file_dir = '../data-md/' + platform_tag

    root_dir = config_dict[exp_res_root_mount_path_tag] + os.sep + my_config_lst[0]
    json_file_name = my_config_lst[1]
    md_file_name = my_config_lst[2]
    exec_lst = filter(lambda name: 'cuda' not in name, config_dict[exec_lst_tag])
    exec_lst += [my_config_lst[3](name) for name in exec_lst] if len(my_config_lst) >= 4 else []
    data_set_lst = config_dict[data_set_lst_tag] + map(lambda data_name: data_name + os.sep + rev_deg_order_tag,
                                                       config_dict[data_set_lst_tag])
    output_data_set_lst = []
    for data_set in config_dict[data_set_lst_tag]:
        output_data_set_lst.append(data_set)
        output_data_set_lst.append(data_set + os.sep + rev_deg_order_tag)

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
                    my_dict[data_set][thread_num][algorithm] = get_overview_time_mem_info(test_file_path)

        with open(os.sep.join([json_file_dir, json_file_name]), 'w') as ofs:
            ofs.write(json.dumps(my_dict, indent=4))

    def convert_json_to_md():
        with open(os.sep.join([json_file_dir, json_file_name])) as ifs:
            my_dict = json.load(ifs)
        lines = ['# O(E) intersection count time', '\n\nUnit: seconds']

        for data_set in output_data_set_lst:
            lines.extend(['\n\n### ' + data_set + '\n',
                          ' | '.join(
                              ['file-name', 'LayoutTransform', 'SetInterTime', 'SimCal',
                               'TotalCoreCheck']),
                          ' | '.join(['---' for _ in range(5)]),
                          ])
            sort_tmp_lst = []
            for algorithm in filter(lambda name: 'bitvec' in name if 'rev_deg' in data_set else 'bitvec' not in name,
                                    exec_lst):
                # with fixed thread number
                thread_num = str(config_dict[thread_num_tag])
                time_lst = list(map(lambda tag: str(my_dict[data_set][thread_num][algorithm][tag][time_tag]) if
                my_dict[data_set][thread_num][algorithm][tag] is not None else None,
                                    time_tag_lst + [core_checking_sim_cal_cost_tag]))

                core_checking_time = time_lst[1]
                sim_cal_time = time_lst[-1]
                preprocess_time = time_lst[0] if time_lst[0] is not None else 0
                elapsed_time = float(core_checking_time) - float(sim_cal_time) - float(preprocess_time) \
                    if no_body_is_none([core_checking_time, sim_cal_time]) else None
                value_lst = map(lambda x: format_str(x) if x is not None else '/',
                                [preprocess_time, elapsed_time, sim_cal_time, core_checking_time])

                sort_tmp_lst.append((' | '.join([algorithm.replace('scan-xp-', '')] + value_lst), elapsed_time))
            sort_tmp_lst = sorted(sort_tmp_lst, key=lambda t: t[1])
            for line, cmp_val in sort_tmp_lst:
                lines.append(line)

        os.system('mkdir -p ' + md_file_dir)
        with open(os.sep.join([md_file_dir, md_file_name]), 'w') as ofs:
            ofs.write('\n'.join(lines))

    fetch_data_to_json()
    convert_json_to_md()


if __name__ == '__main__':
    generate_statistics(platform_tag=lccpu12_tag)
    generate_statistics(platform_tag=gpu23_tag)
    generate_statistics(platform_tag=knl_tag)
