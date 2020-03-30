from data_analysis.util.read_file_utils_updated import *
from exec_utilities import exec_utils
import json

si_dir = 'si-ustgpu2'


def get_tc_time_lst(line):
    res = re.findall('TC Time: [0-9.]+s', line)
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
            eid_time_lst = get_tc_time_lst('\n'.join(lines))
            my_dict[dataset][t_num] = min(eid_time_lst)
    with open(json_file_path, 'w') as ofs:
        ofs.write(json.dumps(my_dict, indent=4))


if __name__ == '__main__':
    base_dir = '/home/yche/'
    os.system('mkdir -p {}'.format(si_dir))

    logger = exec_utils.get_logger('{}logs/'.format(base_dir) + 'ustgpu2-si.log', __name__)
    root_dir_template = '{}mnt/ustgpu2/workspace/yche/git-repos/' \
                        'OutOfCoreSCAN/python_experiments/exp_results/{}/ustgpu2'
    data_set_lst = ['webgraph_eu', 'webgraph_it', 'webgraph_twitter']

    dtc_wp_root_dir = 'exp-2019-10-05-eid'
    baseline_root_dir = 'exp-2019-10-04-eid'
    for name in ['pkt-eval-tc-wp']:
        fetch_statistics(root_dir_template.format(base_dir, dtc_wp_root_dir), data_set_lst, 'org',
                         [str(i) for i in [1, 2, 4, 8, 16, 32, 40]], name, '{}/{}'.format(si_dir, name + '.json'))
    for name in ['pkt-eval-tc-dtc']:
        fetch_statistics(root_dir_template.format(base_dir, dtc_wp_root_dir), data_set_lst, 'org',
                         [str(i) for i in [40]], name, '{}/{}'.format(si_dir, name + '.json'))
    for name in ['pkt-eval-tc-baseline']:
        fetch_statistics(root_dir_template.format(base_dir, baseline_root_dir), data_set_lst, 'org',
                         [str(i) for i in [40]], name, '{}/{}'.format(si_dir, name + '.json'))
