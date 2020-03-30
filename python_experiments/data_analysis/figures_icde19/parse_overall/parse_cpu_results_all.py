from data_analysis.util.read_file_utils_updated import *
from data_analysis.util.parsing_helpers import *
from data_analysis.aec_algorithm.local_config.ktruss_exec_tags import *

from config import *
from exec_utilities import exec_utils
import json


def fetch_statistics(root_dir, dataset_lst, reorder_tag, t_num, algorithm, json_file_path):
    # Dataset -> Detailed Time Info
    my_dict = dict()
    for dataset in dataset_lst:
        file_path = os.sep.join([root_dir, dataset, reorder_tag, t_num, algorithm + '.log'])
        logger.info(file_path)
        lines = get_file_lines(file_path)
        my_dict[dataset] = parse_lines(lines, local_tag_lst, total_time_tag, total_tag_lst)
    with open(json_file_path, 'w') as ofs:
        ofs.write(json.dumps(my_dict, indent=4))


if __name__ == '__main__':
    # base_dir = '/Users/cheyulin/'

    base_dir = '/home/yche/'
    os.system('mkdir -p {}logs/'.format(base_dir))
    my_res_log_file_folder = 'exp-2019-10-05-best'
    log_path = my_res_log_file_folder + '.log'
    logger = exec_utils.get_logger('{}logs/'.format(base_dir) + log_path, __name__)

    hostname = 'ustgpu2'
    varying_cpu_tag = 'varying_cpu'
    os.system('mkdir -p ./{}/{}'.format(varying_cpu_tag, my_res_log_file_folder))
    root_dir = '{}mnt/ustgpu2/workspace/yche/git-repos/' \
               'OutOfCoreSCAN/python_experiments/exp_results/{}/ustgpu2'.format(base_dir, my_res_log_file_folder)

    os.system('mkdir -p ./{}/{}'.format(varying_cpu_tag, my_res_log_file_folder))
    for my_md_algorithm_name in ['pkt-bmpf', 'pkt-inter-shrink', 'pkt-legacy']:
        json_file_path = './{}/{}/{}.json'.format(varying_cpu_tag, my_res_log_file_folder, my_md_algorithm_name)
        # Dataset ->  Detailed Time Info
        dataset_lst = [
            'snap_orkut', 'webgraph_uk', 'webgraph_webbase',
            'webgraph_eu', 'webgraph_it', 'webgraph_twitter']
        reorder_tag = 'org'
        fetch_statistics(root_dir=root_dir, dataset_lst=dataset_lst, reorder_tag=reorder_tag, t_num='40',
                         algorithm=my_md_algorithm_name, json_file_path=json_file_path)
