from data_analysis.util.read_file_utils_updated import *
from data_analysis.util.parsing_helpers import *
from data_analysis.aec_algorithm.local_config.ktruss_exec_tags import *

from config import *
from exec_utilities import exec_utils
import json

scalability_iep_tag = 'iep-scalability'


def fetch_statistics(root_dir, dataset_lst, reorder_tag, t_lst, algorithm, json_file_path):
    # Dataset -> Thread Num -> Detailed Time Info
    my_dict = dict()
    for dataset in dataset_lst:
        my_dict[dataset] = dict()
        for t_num in t_lst:
            file_path = os.sep.join([root_dir, dataset, reorder_tag, t_num, algorithm + '.log'])
            logger.info(file_path)
            lines = get_file_lines(file_path)

            my_dict[dataset][t_num] = parse_lines(lines, local_tag_lst, total_time_tag, total_tag_lst)
        for t_num in t_lst:
            get_speedup(str(min(t_lst)), t_num, my_dict[dataset], tag_lst=all_tag_lst, speedup_tag=speedup_tag)
    with open(json_file_path, 'w') as ofs:
        ofs.write(json.dumps(my_dict, indent=4))


if __name__ == '__main__':
    base_dir = '/home/yche/'
    os.system('mkdir -p {}logs/'.format(base_dir))
    log_path = 'scalability-iep' + '.log'
    logger = exec_utils.get_logger('{}logs/'.format(base_dir) + log_path, __name__)

    my_res_log_file_folder = 'exp-2019-10-04-eid'

    hostname = 'ustgpu2'
    os.system('mkdir -p ./{}/{}'.format(scalability_iep_tag, my_res_log_file_folder))
    root_dir = '{}mnt/ustgpu2/workspace/yche/git-repos/' \
               'OutOfCoreSCAN/python_experiments/exp_results/{}/ustgpu2'.format(base_dir, my_res_log_file_folder)

    my_md_algorithm_name = 'pkt-inter-shrink'
    json_file_path = './{}/{}/{}.json'.format(scalability_iep_tag, my_res_log_file_folder, my_md_algorithm_name)

    # Dataset ->  Detailed Time Info
    dataset_lst = ['webgraph_eu', 'webgraph_twitter']
    reorder_tag = 'org'
    fetch_statistics(root_dir=root_dir, dataset_lst=dataset_lst, reorder_tag=reorder_tag,
                     t_lst=[str(i) for i in [1, 2, 4, 8, 16, 32, 40]],
                     algorithm=my_md_algorithm_name, json_file_path=json_file_path)
