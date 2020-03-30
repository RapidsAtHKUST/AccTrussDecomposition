from data_analysis.util.read_file_utils import *
from config import *
from data_analysis.common.common_utils import *

config_09_20_lb_gpu_wildcarid = ['overview-09-23-lb-gpu-', '09-23-lb-gpu-wildcard.json', '09-23-lb-gpu-wildcard.md',
                                 lambda algorithm_name: 'multi-pass' in algorithm_name]

stat_config_lst = config_09_20_lb_gpu_wildcarid
my_config_lst = [config_09_20_lb_gpu_wildcarid]


def generate_statistics(platform_tag):
    config_dict = get_config_dict(platform_tag, '../..')
    json_file_dir = '../data-json/' + platform_tag
    md_file_dir = '../data-md/' + platform_tag

    root_dir = config_dict[exp_res_root_mount_path_tag] + os.sep + stat_config_lst[0]
    json_file_name = stat_config_lst[1]
    md_file_name = stat_config_lst[2]
    algorithm_lst = config_dict[exec_lst_tag]

    filtered_data_set_lst = list(filter(lambda name: 'small' not in name, config_dict[data_set_lst_tag]))
    rev_deg_order_data_set_lst = list(map(lambda name: name + os.sep + rev_deg_order_tag,
                                          filtered_data_set_lst))
    num_of_gpus_lst = map(str, [1, 2, 4, 8])

    def fetch_data_to_json():
        os.system('mkdir -p ' + json_file_dir)

        global_dict = {}
        for num_of_gpus in num_of_gpus_lst:
            my_dict = {}

            for data_set in filtered_data_set_lst + rev_deg_order_data_set_lst:
                my_dict[data_set] = {}
                for thread_num in [config_dict[thread_num_tag]]:
                    my_dict[data_set][thread_num] = {}
                    for algorithm in filter(stat_config_lst[-1], algorithm_lst):
                        parameter_lst = [data_set, '0.2', '5', str(thread_num)]
                        test_file_path = os.sep.join([root_dir + num_of_gpus] + parameter_lst + [algorithm + '.txt'])
                        my_dict[data_set][thread_num][algorithm] = get_overview_time_mem_info_cuda(test_file_path)
            global_dict[num_of_gpus] = my_dict

        with open(os.sep.join([json_file_dir, json_file_name]), 'w') as ofs:
            ofs.write(json.dumps(global_dict, indent=4))

    def convert_json_to_md():
        with open(os.sep.join([json_file_dir, json_file_name])) as ifs:
            my_dict = json.load(ifs)
        lines = ['# O(E) intersection count time', '\n\nUnit: seconds']

        title_lst = ['file-name'] + num_of_gpus_lst
        for data_set_raw in filtered_data_set_lst:
            for data_set in [data_set_raw, data_set_raw + os.sep + rev_deg_order_tag]:
                lines.extend(['\n\n### ' + data_set + '\n',
                              ' | '.join(title_lst),
                              ' | '.join(['---' for _ in range(len(title_lst))]), ])
                for algorithm in filter(stat_config_lst[-1], algorithm_lst):
                    thread_num_str = str(config_dict[thread_num_tag])
                    tmp_lst = []
                    for num_of_gpus in num_of_gpus_lst:
                        algorithm_dict = my_dict[num_of_gpus][data_set][thread_num_str][algorithm]

                        def get_time_if_not_none(usr_tag):
                            return algorithm_dict[usr_tag][time_tag] if usr_tag in algorithm_dict and algorithm_dict[
                                usr_tag] is not None else None

                        time_lst = list(map(
                            lambda tag: get_time_if_not_none(tag) if algorithm_dict[is_correct_tag] == True else None,
                            time_tag_lst))

                        core_checking_time = time_lst[0]
                        sim_cal_time = get_time_if_not_none(core_checking_sim_cal_cost_tag)
                        task_init_time = get_time_if_not_none(cpu_side_task_range_init_tag)
                        tmp_lst.append(float(core_checking_time) - float(sim_cal_time) - float(task_init_time) if
                                       no_body_is_none([core_checking_time, sim_cal_time, task_init_time]) else None)

                    tmp_lst = list(map(lambda ele: format_str(ele) if ele is not None else '/', tmp_lst))
                    lines.append(' | '.join([algorithm.replace('scan-xp-', '')] + tmp_lst))

        os.system('mkdir -p ' + md_file_dir)
        with open(os.sep.join([md_file_dir, md_file_name]), 'w') as ofs:
            ofs.write('\n'.join(lines))

    fetch_data_to_json()
    convert_json_to_md()


if __name__ == '__main__':
    for config in my_config_lst:
        stat_config_lst = config
        generate_statistics(platform_tag=lccpu12_tag)
