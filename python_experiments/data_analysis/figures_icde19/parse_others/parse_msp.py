from data_analysis.util.read_file_utils_updated import *

from config import *
from exec_utilities import exec_utils
import json

others_time_msp = 'msp'


def fetch_statistics(root_dir, dataset_lst, t_num, algorithm, json_file_path):
    my_dict = dict()
    for dataset in dataset_lst:
        file_path = os.sep.join([root_dir, dataset, t_num, algorithm + '.log'])
        logger.info(file_path)
        lines = get_file_lines(file_path)

        beg_ts = list(filter(lambda l: 'kttype: base' in l, lines)) if lines is not None else None
        end_ts = list(filter(lambda l: '#triangles after peeling' in l, lines)) if lines is not None else None
        if beg_ts is None or end_ts is None:
            my_dict[dataset] = 0
        else:
            print(beg_ts)
            print(end_ts)
            lst = re.findall('et: [0-9.]+ s', '\n'.join(beg_ts))
            beg = [eval(x.replace('s', '').split(':')[-1]) for x in lst][0]

            lst = re.findall('et: [0-9.]+ s', '\n'.join(end_ts))
            end = [eval(x.replace('s', '').split(':')[-1]) for x in lst][0]
            my_dict[dataset] = end - beg
    with open(json_file_path, 'w') as ofs:
        ofs.write(json.dumps(my_dict, indent=4))


if __name__ == '__main__':
    base_dir = '/home/yche/'
    os.system('mkdir -p {}logs/'.format(base_dir))
    my_res_log_file_folder = 'exp-2019-10-07-msp'
    log_path = my_res_log_file_folder + '.log'
    logger = exec_utils.get_logger('{}logs/'.format(base_dir) + log_path, __name__)

    hostname = 'ustgpu2'
    root_dir = '{}mnt/ustgpu2/workspace/yche/git-repos/' \
               'OutOfCoreSCAN/python_experiments/exp_results/{}/ustgpu2'.format(base_dir, my_res_log_file_folder)

    os.system('mkdir -p {}'.format(others_time_msp))
    for my_md_algorithm_name in ['ktruss-msp']:
        json_file_path = './{}/{}.json'.format(others_time_msp, my_md_algorithm_name)
        # Dataset ->  Detailed Time Info
        dataset_lst = [
            'snap_orkut', 'webgraph_uk', 'webgraph_webbase',
            'webgraph_eu', 'webgraph_it', 'webgraph_twitter']
        reorder_tag = 'org'
        fetch_statistics(root_dir=root_dir, dataset_lst=dataset_lst, t_num='40',
                         algorithm=my_md_algorithm_name, json_file_path=json_file_path)
