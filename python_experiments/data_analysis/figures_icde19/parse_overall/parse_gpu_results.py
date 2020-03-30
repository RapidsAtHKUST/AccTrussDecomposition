from data_analysis.util.read_file_utils_updated import *
from data_analysis.util.parsing_helpers import *
from data_analysis.aec_algorithm.local_config.ktruss_exec_tags import *

from config import *
from exec_utilities import exec_utils
import json

varying_gpu_tag = 'varying_gpu'
config_lst = [
    'exp-2019-10-05-cuda-new',
    [
        'cuda-pkt-shrink-all-opt',
        'cuda-pkt-offload-opt',
        'cuda-pkt-offload',
    ]
]
cpu_tag = 'CPU'
gpu_tag = 'GPU'
extra_tag = 'CUDA'
summary_tag = 'Summary'
finish_bsr_time_tag = 'Finish BSR construction'
end_to_end_time_tag = 'End-To-End Time'
si_tag = 'Finish Support Initialization'

off_tc_tag = 'OFF-TC'
off_tc_overhead_tag = 'OFF-TC-Transferring'
off_cpu_iep_tag = 'OFF-RIEP-CPU'
off_gpu_iep_tag = 'OFF-RIEP-GPU'
off_iep_total_tag = 'OFF-IEP-Total'
off_total_tag = 'OFF-TC_IEP-Total'
other_overheads_tag = 'Other-Overheads'
total_overhead_tag = 'Total-Overheads'

gpu_required = []
gpu_extra = [kernel_time_tag, prepare_cpu_time_tag, scan_cpu_time_tag, shrink_cpu_time_tag,
             copy_cpu_time_tag, sub_level_process_cpu_time_tag,
             set_inter_cpu_time_tag, update_processed_cpu_time_tag]


def user_parse_lines_entry(lines, tag_lst):
    local_dict = dict(zip(tag_lst, [None for _ in range(len(tag_lst))]))
    if lines is not None and has_is_time_out(lines):
        # use the last one record
        spliter = get_splitter_line(lines)
        org_lines = lines[spliter[-2]:spliter[-1] + 1]

        for tag in tag_lst:
            lines = list(filter(lambda x: contains([tag], x), org_lines))
            if tag == si_tag:
                local_dict[tag] = None
                if len(lines) > 0:
                    local_dict[tag] = eval(lines[0].split(':')[-1].replace('s.', ''))
            else:
                local_dict[tag] = parse_line(None if len(lines) == 0 else lines[0], [tag])[tag]
        return local_dict
    return local_dict


def all_not_none(lst):
    return len(list(filter(lambda x: x is not None, lst))) == len(lst)


def parse_entry_lines_to_dict(lines):
    my_dict = {
        gpu_tag: user_parse_lines_entry(lines, [end_to_end_time_tag, finish_bsr_time_tag, si_tag, pkt_total_tag,
                                                offload_total_tag, prepare_cpu_time_tag]),
        extra_tag: user_parse_lines_entry(lines, gpu_extra),
        cpu_tag: parse_lines(lines, local_tag_lst, total_time_tag, total_tag_lst)
    }
    gpu_stat = my_dict[gpu_tag]
    cpu_stat = my_dict[cpu_tag]
    summary_dict = {
        pkt_total_tag: gpu_stat[pkt_total_tag],
        off_tc_tag: gpu_stat[si_tag] + gpu_stat[finish_bsr_time_tag]
    }
    summary_dict[off_tc_overhead_tag] = gpu_stat[end_to_end_time_tag] - summary_dict[off_tc_tag]
    summary_dict[prepare_cpu_time_tag] = gpu_stat[prepare_cpu_time_tag]
    summary_dict[off_cpu_iep_tag] = 0
    if all_not_none([v for k, v in cpu_stat.items()]):
        summary_dict[off_cpu_iep_tag] = sum(
            [cpu_stat[sync_time_tag] + cpu_stat[scan_time_tag] + cpu_stat[shrink_time_tag] + cpu_stat[proc_time_tag]])
    if gpu_stat[offload_total_tag] is not None:
        summary_dict[off_gpu_iep_tag] = gpu_stat[offload_total_tag] - gpu_stat[prepare_cpu_time_tag]
    else:
        summary_dict[off_gpu_iep_tag] = gpu_stat[pkt_total_tag] - gpu_stat[prepare_cpu_time_tag] - \
                                        gpu_stat[end_to_end_time_tag]
    summary_dict[off_iep_total_tag] = summary_dict[off_gpu_iep_tag] + summary_dict[off_cpu_iep_tag]
    summary_dict[off_total_tag] = summary_dict[off_iep_total_tag] + summary_dict[off_tc_tag]
    summary_dict[total_overhead_tag] = gpu_stat[pkt_total_tag] - summary_dict[off_total_tag]
    summary_dict[other_overheads_tag] = gpu_stat[pkt_total_tag] - summary_dict[off_total_tag] - summary_dict[
        prepare_cpu_time_tag] - summary_dict[off_tc_overhead_tag]
    my_dict[summary_tag] = summary_dict

    return my_dict


def parse_lines_in_a_file(lines):
    dict_lst = []
    if lines is not None and has_is_time_out(lines):
        splitter = get_splitter_line(lines)
        for idx in range(len(splitter) - 1):
            tmp_lines = lines[splitter[idx]:splitter[idx + 1]]
            # logger.info(tmp_lines)
            dict_lst.append(parse_entry_lines_to_dict(tmp_lines))
    return dict_lst


def fetch_statistics(root_dir, dataset_lst, reorder_tag, t_num, algorithm, json_file_path):
    # Dataset -> Detailed Time Info
    my_dict = dict()
    for dataset in dataset_lst:
        file_path = os.sep.join([root_dir, dataset, reorder_tag, t_num, algorithm + '.log'])
        logger.info(file_path)
        lines = get_file_lines(file_path)
        local_data = parse_lines_in_a_file(lines)

        # filter the fewest
        fewest_time = min([tmp[gpu_tag][pkt_total_tag] for tmp in local_data])
        my_dict[dataset] = list(filter(lambda x: x[gpu_tag][pkt_total_tag] == fewest_time, local_data))[0]
        print(fewest_time)
    with open(json_file_path, 'w') as ofs:
        ofs.write(json.dumps(my_dict, indent=4))


if __name__ == '__main__':
    base_dir = '/home/yche/'
    my_res_log_file_folder = config_lst[0]

    log_path = my_res_log_file_folder + '.log'
    os.system('mkdir -p {}logs/'.format(base_dir))
    logger = exec_utils.get_logger('{}logs/'.format(base_dir) + log_path, __name__)

    os.system('mkdir -p ./{}/{}'.format(varying_gpu_tag, my_res_log_file_folder))

    hostname = 'ustgpu2'
    root_dir = '{}mnt/ustgpu2/workspace/yche/git-repos/' \
               'OutOfCoreSCAN/python_experiments/exp_results/{}/ustgpu2'.format(base_dir, my_res_log_file_folder)

    dataset_lst = [
        'webgraph_eu', 'webgraph_it',
        'webgraph_twitter',
        'snap_orkut',
        'webgraph_uk', 'webgraph_webbase'
    ]
    for my_md_algorithm_name in config_lst[1]:
        json_file_path = './{}/{}/{}.json'.format(varying_gpu_tag, my_res_log_file_folder, my_md_algorithm_name)
        # Dataset ->  Detailed Time Info
        reorder_tag = 'org'
        fetch_statistics(root_dir=root_dir, dataset_lst=dataset_lst, reorder_tag=reorder_tag, t_num='40',
                         algorithm=my_md_algorithm_name, json_file_path=json_file_path)
