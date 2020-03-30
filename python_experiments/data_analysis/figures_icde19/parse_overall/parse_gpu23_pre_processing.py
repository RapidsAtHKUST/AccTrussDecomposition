from config import *
from data_analysis.util.read_file_utils_updated import *
from exec_utilities import exec_utils

gpu23_pp_dir = 'PP-gpu23'


def get_eid_time_lst(line):
    res = re.findall('Init Eid Time: [0-9.]+ s', line)
    return [eval(val.replace('s', '').split(':')[-1]) for val in res]


def fetch_statistics(root_dir, dataset_lst, reorder_tag, t_lst, algorithm, json_file_path):
    # Dataset -> Thread-Num -> Detailed Time Info
    my_dict = dict()
    for dataset in dataset_lst:
        my_dict[dataset] = dict()
        for t_num in t_lst:
            file_path = os.sep.join([root_dir, dataset, reorder_tag, t_num, algorithm + '.log'])
            logger.info(file_path)
            lines = get_file_lines(file_path)
            functor = max if algorithm == 'pkt-eid' else min
            eid_time_lst = get_eid_time_lst('\n'.join(lines))
            my_dict[dataset][t_num] = functor(eid_time_lst)
    with open(json_file_path, 'w') as ofs:
        ofs.write(json.dumps(my_dict, indent=4))


if __name__ == '__main__':
    base_dir = '/home/yche/'
    os.system('mkdir -p {}'.format(gpu23_pp_dir))

    logger = exec_utils.get_logger('{}logs/'.format(base_dir) + 'gpu23-pp.log', __name__)

    my_res_log_file_folder = 'exp-2019-10-07-eid'
    root_dir = '{}mnt/luocpu9/mnt/storage1/yche/git-repos/' \
               'OutOfCoreSCAN/python_experiments/exp_results/{}/gpu23'.format(base_dir, my_res_log_file_folder)
    for name in ['pkt-eid', 'pkt-eid-parallel']:
        fetch_statistics(root_dir, ['webgraph_eu', 'webgraph_it', 'webgraph_twitter'], 'org',
                         [str(i) for i in [1, 2, 4, 8, 16, 32, 40]], name, '{}/{}'.format(gpu23_pp_dir, name + '.json'))
