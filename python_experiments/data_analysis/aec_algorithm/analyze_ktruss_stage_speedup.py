from data_analysis.util.read_file_utils_updated import *
from config import *
from exec_utilities import exec_utils
import json

tri_time_tag = 'Tri time'
shrink_time_tag = 'Shrink Time'
scan_time_tag = 'Scan Time'
proc_time_tag = 'Proc Time'
t_lst = ['1', '20', '40']
speedup_tag = 'speedup'
hyper_threading_tag = 'hyper-threading-speedup'

if __name__ == '__main__':
    logger = exec_utils.get_logger('/home/yche/analyzing_speedup.log', __name__)

    config_dict = get_config_dict(gpu23_tag, '../..')
    hostname = gpu23_tag

    root_dir = os.sep.join(
        [config_dict[exp_res_root_mount_path_tag], 'exp-2019-06-24-k-truss-refactor', hostname, ])

    dataset_lst = config_dict[data_set_lst_tag]


    def fetch_statistics(algorithm, json_file_name):
        def parse_line(line):
            if line is None:
                time_lst = [None for _ in range(4)]
            else:
                lst = line.split()[get_log_header_col():]
                time_lst = [literal.replace('s', '').replace(',', '') for literal in
                            [lst[-10], lst[-7], lst[-4], lst[-1]]]

            return dict(zip([tri_time_tag, shrink_time_tag, scan_time_tag, proc_time_tag],
                            map(lambda ele: None if ele is None else float(ele), time_lst)))

        def user_div(v1, v2):
            if v1 is None or v2 is None:
                return None
            else:
                return v1 / v2

        def get_speedup(k_small, k_large, my_info):
            new_dict = dict()
            for tag in my_info[k_small]:
                new_dict[tag] = user_div(my_info[k_large][tag], my_info[k_small][tag])
            return new_dict

        # Dataset -> Thread Num -> Detailed Time Info
        my_dict = dict()
        for dataset in dataset_lst:
            my_dict[dataset] = dict()
            for t_num in t_lst:
                file_path = os.sep.join([root_dir, dataset, t_num, algorithm + '.log'])
                logger.info(file_path)

                lines = get_file_lines(file_path)

                def has_is_time_out(lines):
                    for line in lines:
                        if 'is_time_out' in line:
                            return True
                    return False

                if lines is not None and has_is_time_out(lines):
                    # use the last one record
                    spliter = get_splitter_line(lines)
                    lines = lines[spliter[-2]:spliter[-1] + 1]

                    lines = filter(lambda x: contains(['Tri time', 'Shrink Time'], x), lines)
                    local_dict = parse_line(None if len(lines) == 0 else lines[0])
                else:
                    local_dict = parse_line(None)
                my_dict[dataset][t_num] = local_dict

            # Generate speedup
            my_dict[dataset][speedup_tag] = get_speedup('40', '1', my_dict[dataset])
            my_dict[dataset][hyper_threading_tag] = get_speedup('40', '20', my_dict[dataset])

        dir = '../data-json/' + hostname
        os.system('mkdir -p {}'.format(dir))
        with open(os.sep.join([dir, json_file_name]), 'w') as ofs:
            ofs.write(json.dumps(my_dict, indent=4))


    fetch_statistics(algorithm='pkt-inter-shrink', json_file_name='2019-06-27-time-info-pkt-inter.json')
    fetch_statistics(algorithm='pkt-mark-shrink', json_file_name='2019-06-27-time-info-pkt-mark.json')
