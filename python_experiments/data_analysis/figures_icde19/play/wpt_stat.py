from data_analysis.util.read_file_utils_updated import *
from config import *

from exec_utilities.exec_utils import get_logger
from data_analysis.figures_icde19.play.common import *

if __name__ == '__main__':
    base_dir = '/home/yche/'
    os.system('mkdir -p {}logs/'.format(base_dir))
    logger = get_logger('/home/yche/tmp.log', __name__)

    mount_dir = '{}/workspace/yche/git-repos/OutOfCoreSCAN/python_experiments/exp_results/exp-2019-10-06-varying-wpt-all' \
                '/ustgpu2/webgraph_eu/org/40/word-packing/'. \
        format('/home/yche/mnt/ustgpu2')

    pack_lst = []
    overhead_lst = []
    tc_cnt_lst = []
    tc_time_lst = []
    for i in range(65):
        file_path = '{}/pkt-varying-wpt-{}.log'.format(mount_dir, i)
        lines = get_file_lines(file_path)
        line = '\n'.join(lines)

        pack_lst.append(split_val(':', ret_all('Packed#: [0-9,]+', line)[0]))
        overhead_lst.append(split_val(':', ret_all('Memory Overheads: [0-9,]+ KB', line)[0]))
        tc_cnt_lst.append(split_val(':', ret_all('TC Cnt: [0-9,]+', line)[0]))
        tc_time_lst.append(split_val(':', ret_all('TC Time: [0-9,\.]+s', line)[0]))

    data_dict = {
        'Packed#': pack_lst,
        'Memory Overheads': overhead_lst,
        'TC Time': tc_time_lst,
        'TC Cnt': tc_cnt_lst
    }
    with open('{}/wpt.json'.format(varying_parameter_json_dir), 'w') as ofs:
        ofs.write(json.dumps(data_dict, indent=4))
