from data_analysis.util.read_file_utils import *
from config import *
from data_analysis.common.common_utils import *

config_09_25_lb_gpu = ['overview-09-25-varying-num-pass', '09-25-varying-num-pass.json',
                       '09-25-varying-num-pass.md']
config_10_17_lb_gpu = ['overview-10-17-varying-block-size-1', '10-17-varying-block-size.json',
                       '10-17-varying-block-size.md']
config_10_19_lb_gpu = ['overview-10-19-varying-block-size-for-overall-cmp-1', 'overview-10-19-varying-block-size.json',
                       'overview-10-19-varying-block-size.md']
stat_config_lst = config_09_25_lb_gpu
my_config_lst = [config_10_19_lb_gpu]

algorithm_lst = [
    'scan-xp-cuda-experimental-hybrid-kernels-varying-block-size',
    'scan-xp-cuda-experimental-bitmap-varying-block-size']
algorithm_name_dict = {
    'scan-xp-cuda-experimental-hybrid-kernels-varying-block-size': 'MPS',
    'scan-xp-cuda-experimental-bitmap-varying-block-size': 'BMP-RF'
}


def generate_statistics(platform_tag):
    config_dict = get_config_dict(platform_tag, '../..')
    json_file_dir = '../data-json/' + platform_tag
    md_file_dir = '../data-md/' + platform_tag

    root_dir = config_dict[exp_res_root_mount_path_tag] + os.sep + stat_config_lst[0]
    json_file_name = stat_config_lst[1]
    md_file_name = stat_config_lst[2]

    filtered_data_set_lst = list(filter(lambda name: 'small' not in name, config_dict[data_set_lst_tag]))
    rev_deg_order_data_set_lst = list(map(lambda name: name + os.sep + rev_deg_order_tag,
                                          filtered_data_set_lst))
    num_of_gpus = str(1)
    num_of_pass_lst = map(str, [4, 8, 16, 32])

    def fetch_data_to_json():
        os.system('mkdir -p ' + json_file_dir)
        global_dict = {}
        algo_dict = {}
        for algorithm in algorithm_lst:
            my_dict = {}

            for data_set in filtered_data_set_lst + rev_deg_order_data_set_lst:
                my_dict[data_set] = {}
                for thread_num in [config_dict[thread_num_tag]]:
                    my_dict[data_set][thread_num] = {}
                    for num_pass in num_of_pass_lst:
                        parameter_lst = [data_set, '0.2', '5', str(thread_num)]
                        test_file_path = os.sep.join(
                            [root_dir] + [num_pass] + parameter_lst + [algorithm + '.txt'])
                        my_dict[data_set][thread_num][num_pass] = get_overview_time_mem_info_cuda(test_file_path)
            algo_dict[algorithm] = my_dict
        global_dict[num_of_gpus] = algo_dict
        with open(os.sep.join([json_file_dir, json_file_name]), 'w') as ofs:
            ofs.write(json.dumps(global_dict, indent=4))

    def convert_json_to_md():
        with open(os.sep.join([json_file_dir, json_file_name])) as ifs:
            my_dict = json.load(ifs)
        lines = ['# O(E) intersection count time (Multi-Pass)', '\n\nUnit: seconds']

        title_lst = ['file-name'] + [algorithm_name_dict[algo] for algo in algorithm_lst]

        for data_set in filtered_data_set_lst + rev_deg_order_data_set_lst:
            lines.extend(['\n\n### ' + data_set + '\n',
                          ' | '.join(title_lst),
                          ' | '.join(['---' for _ in range(len(title_lst))]), ])
            thread_num_str = str(config_dict[thread_num_tag])

            for num_of_pass in num_of_pass_lst:
                tmp_lst = []

                for algorithm in algorithm_lst:
                    algorithm_dict = my_dict[num_of_gpus][algorithm][data_set][thread_num_str][num_of_pass]

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
                lines.append(' | '.join([num_of_pass] + tmp_lst))
        os.system('mkdir -p ' + md_file_dir)
        with open(os.sep.join([md_file_dir, md_file_name]), 'w') as ofs:
            ofs.write('\n'.join(lines))

    fetch_data_to_json()
    convert_json_to_md()


if __name__ == '__main__':
    for config in my_config_lst:
        stat_config_lst = config
        generate_statistics(platform_tag=lccpu12_tag)
