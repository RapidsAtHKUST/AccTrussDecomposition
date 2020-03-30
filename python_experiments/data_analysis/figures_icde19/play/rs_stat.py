from data_analysis.aec_algorithm.local_config.ktruss_exec_tags import *
from data_analysis.util.parsing_helpers import parse_lines, union
from data_analysis.util.read_file_utils_updated import *
from config import *

from exec_utilities.exec_utils import get_logger
from data_analysis.figures_icde19.play.common import *


def parse_rs():
    mount_dir = '{}/workspace/yche/git-repos/OutOfCoreSCAN/python_experiments/exp_results/exp-2019-10-06-parameters' \
                '/ustgpu2/{}/org/40/{}/'. \
        format('/home/yche/mnt/ustgpu2', 'webgraph_eu', 'range-size')
    data = dict()
    for gc in [2 ** i for i in range(9)]:
        file_path = '{}/pkt-varying-{}.log'.format(mount_dir, gc)
        lines = get_file_lines(file_path)
        time_dict = parse_lines(lines, local_tag_lst, total_time_tag, total_tag_lst)
        print(time_dict)
        data[gc] = time_dict

    with open('{}/rs.json'.format(varying_parameter_json_dir), 'w') as ofs:
        ofs.write(json.dumps(data, indent=4))


if __name__ == '__main__':
    base_dir = '/home/yche/'
    os.system('mkdir -p {}logs/'.format(base_dir))
    logger = get_logger('/home/yche/tmp.log', __name__)

    parse_rs()
