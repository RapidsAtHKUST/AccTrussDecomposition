from data_analysis.util.read_file_utils import *
from config import *
from data_analysis.common.common_utils import *

config_09_08_large_bitmap_range_lst = ['overview-09-08-cuda-unified-mem-large-bitmap-index-scale',
                                       '09-08-cuda-large-bitmap-index-scale.json',
                                       '09-08-cuda-large-bitmap-index-scale.md',
                                       lambda algorithm_name: 'bitmap' in algorithm_name and 'cuda' in algorithm_name
                                                              and 'multi-gpu' not in algorithm_name]
config_09_08_cuda_unified_mem_lst = ['overview-09-08-cuda-unified-mem',
                                     '09-08-cuda-unified-mem.json',
                                     '09-08-cuda-unified-mem.md',
                                     lambda algorithm_name: 'cuda' in algorithm_name and
                                                            'multi-gpu' not in algorithm_name]

config_09_10_multi_gpu_unified_mem_lst = ['overview-09-10-multi-gpu', '09-10-multi-gpu.json'
    , '09-10-multi-gpu.md', lambda algorithm_name: 'multi-gpu' in algorithm_name]

config_09_11_multi_pass_unified_mem_lst = ['overview-09-11-multi-pass-general', '09-11-multi-pass-general.json'
    , '09-11-multi-pass-general.md', lambda algorithm_name: 'multi-pass' in algorithm_name]

config_09_13_multi_pass_pipeline_lst = ['overview-09-13-co-processing-bin-search', '09-13-co-processing-bin-search.json'
    , '09-13-co-processing-bin-search.md', lambda algorithm_name: 'multi-pass' in algorithm_name]

config_09_17_multi_pass_hybrid_lst = ['overview-09-17-multi-pass-general-num-gpu-single',
                                      '09-17-multi-pass-general-num-gpu-single.json'
    , '09-17-multi-pass-general-num-gpu-single.md', lambda algorithm_name: 'multi-pass' in algorithm_name]

config_09_20_lb_gpu_1 = ['overview-09-20-lb-gpu-1', '09-20-lb-gpu-1.json', '09-20-lb-gpu-1.md',
                         lambda algorithm_name: 'multi-pass' in algorithm_name]
config_09_20_lb_gpu_2 = ['overview-09-20-lb-gpu-2', '09-20-lb-gpu-2.json', '09-20-lb-gpu-2.md',
                         lambda algorithm_name: 'multi-pass' in algorithm_name]
config_09_20_lb_gpu_3 = ['overview-09-20-lb-gpu-3', '09-20-lb-gpu-3.json', '09-20-lb-gpu-3.md',
                         lambda algorithm_name: 'multi-pass' in algorithm_name]
config_09_20_lb_gpu_4 = ['overview-09-20-lb-gpu-4', '09-20-lb-gpu-4.json', '09-20-lb-gpu-4.md',
                         lambda algorithm_name: 'multi-pass' in algorithm_name]
config_09_20_lb_gpu_8 = ['overview-09-23-lb-gpu-8', '09-20-lb-gpu-8.json', '09-20-lb-gpu-8.md',
                         lambda algorithm_name: 'multi-pass' in algorithm_name]

stat_config_lst = config_09_20_lb_gpu_1
my_config_lst = [config_09_20_lb_gpu_1, config_09_20_lb_gpu_2, config_09_20_lb_gpu_3, config_09_20_lb_gpu_4,
                 config_09_20_lb_gpu_8]


def generate_statistics(platform_tag):
    config_dict = get_config_dict(platform_tag, '../..')
    json_file_dir = '../data-json/' + platform_tag
    md_file_dir = '../data-md/' + platform_tag

    root_dir = config_dict[exp_res_root_mount_path_tag] + os.sep + \
               stat_config_lst[0]
    json_file_name = stat_config_lst[1]
    md_file_name = stat_config_lst[2]
    algorithm_lst = config_dict[exec_lst_tag]

    filtered_data_set_lst = list(filter(lambda name: 'small' not in name, config_dict[data_set_lst_tag]))
    rev_deg_order_data_set_lst = list(map(lambda name: name + os.sep + rev_deg_order_tag,
                                          filtered_data_set_lst))

    def fetch_data_to_json():
        os.system('mkdir -p ' + json_file_dir)

        my_dict = {}
        for data_set in filtered_data_set_lst + rev_deg_order_data_set_lst:
            my_dict[data_set] = {}
            for thread_num in [config_dict[thread_num_tag]]:
                my_dict[data_set][thread_num] = {}
                for algorithm in filter(stat_config_lst[-1], algorithm_lst):
                    parameter_lst = [data_set, '0.2', '5', str(thread_num)]
                    test_file_path = os.sep.join([root_dir] + parameter_lst + [algorithm + '.txt'])
                    my_dict[data_set][thread_num][algorithm] = get_overview_time_mem_info_cuda(test_file_path)

        with open(os.sep.join([json_file_dir, json_file_name]), 'w') as ofs:
            ofs.write(json.dumps(my_dict, indent=4))

    def convert_json_to_md():
        with open(os.sep.join([json_file_dir, json_file_name])) as ifs:
            my_dict = json.load(ifs)
        lines = ['# O(E) intersection count time', '\n\nUnit: seconds']

        title_lst = ['file-name',
                     'Elapsed time (GPU)',
                     'Co-Processing (CPU)',
                     'Core Checking (Both)',
                     'Task-Init (CPU)',
                     'Reverse-Assign (CPU)',
                     'Sim-Cal (CPU)',
                     ]

        for data_set_raw in filtered_data_set_lst:
            for data_set in [data_set_raw, data_set_raw + os.sep + rev_deg_order_tag]:
                lines.extend(['\n\n### ' + data_set + '\n',
                              ' | '.join(title_lst),
                              ' | '.join(['---' for _ in range(len(title_lst))]), ])
                for algorithm in filter(stat_config_lst[-1], algorithm_lst):
                    thread_num_str = str(config_dict[thread_num_tag])
                    algorithm_dict = my_dict[data_set][thread_num_str][algorithm]

                    def get_time_if_not_none(usr_tag):
                        return algorithm_dict[usr_tag][time_tag] if usr_tag in algorithm_dict and algorithm_dict[
                            usr_tag] is not None else None

                    def get_time_if_not_none_direct(usr_tag):
                        return algorithm_dict[usr_tag] if usr_tag in algorithm_dict else None

                    time_lst = list(map(
                        lambda tag: get_time_if_not_none(tag) if algorithm_dict[is_correct_tag] == True else None,
                        time_tag_lst))

                    core_checking_time = time_lst[0]
                    sim_cal_time = get_time_if_not_none(core_checking_sim_cal_cost_tag)
                    bin_search_time = get_time_if_not_none(bin_search_cost_tag)
                    task_init_time = get_time_if_not_none(cpu_side_task_range_init_tag)
                    coroutine_time = get_time_if_not_none_direct(cpu_corountine_time_tag)
                    tmp_lst = [float(core_checking_time) - float(sim_cal_time) - float(task_init_time) if
                               no_body_is_none([core_checking_time, sim_cal_time, task_init_time]) else None,
                               coroutine_time,
                               core_checking_time, task_init_time, bin_search_time, sim_cal_time,
                               ]

                    tmp_lst = list(map(lambda ele: format_str(ele) if ele is not None else '/', tmp_lst))

                    if algorithm.endswith('hybrid') or algorithm.endswith('bitvec') or algorithm.endswith('hbw') \
                            or 'bitmap' in algorithm:
                        lines.append(' | '.join(
                            map(lambda x: '**' + x + '**', [algorithm.replace('scan-xp-', '')] + tmp_lst)))
                    else:
                        lines.append(' | '.join([algorithm.replace('scan-xp-', '')] + tmp_lst))

        os.system('mkdir -p ' + md_file_dir)
        with open(os.sep.join([md_file_dir, md_file_name]), 'w') as ofs:
            ofs.write('\n'.join(lines))

    # fetch_data_to_json()
    convert_json_to_md()


if __name__ == '__main__':
    for config in my_config_lst:
        stat_config_lst = config
        generate_statistics(platform_tag=lccpu12_tag)
