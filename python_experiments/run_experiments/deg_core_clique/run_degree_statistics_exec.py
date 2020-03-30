import socket
from exec_utilities import time_out_util
from config import *
from exec_utilities.exec_utils import *


def run(env_tag=knl_tag):
    with open('config.json') as ifs:
        my_config_dict = json.load(ifs)[env_tag]

    data_set_path = my_config_dict[data_set_path_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]
    # print data_set_lst
    exp_res_root_name = 'exp_results'
    folder_name = 'exp-03-08-degree-stat'

    def one_round():
        for data_set_name in data_set_lst:
            statistics_dir = os.sep.join(
                map(str,
                    ['.',
                     exp_res_root_name, folder_name]))
            os.system('mkdir -p ' + statistics_dir)
            statistics_file_path = statistics_dir + os.sep + data_set_name + '.txt'

            # 1st: write header
            os.system(
                ' '.join(
                    ['echo', my_splitter + time.ctime() + my_splitter, '>>', statistics_file_path]))

            # 2nd: run exec cmd
            algorithm_path = '/mnt/nfs/var/nfsshare/yche/git-repos/OutOfCoreSCAN/degree-statistics/build/' \
                             'statistics_deg_ordered_directed_graph'
            params_lst = map(str,
                             [algorithm_path, os.sep.join([data_set_path, data_set_name]), statistics_file_path])

            cmd = ' '.join(params_lst)
            # print cmd
            time_out = 1000
            tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out)

            # 3rd: append outputs
            write_split(statistics_file_path)
            with open(statistics_file_path, 'a+') as ifs:
                ifs.write(correct_info)
                ifs.write('\nis_time_out:' + str(tle_flag))
                ifs.write(my_splitter + time.ctime() + my_splitter)
                ifs.write('\n\n\n\n')
            # print 'finish:', cmd

    one_round()


if __name__ == '__main__':
    hostname = socket.gethostname()
    if hostname.startswith('lccpu12'):
        run(env_tag=lccpu12_tag)
    elif hostname.startswith('gpu23'):
        run(env_tag=gpu23_tag)
    elif hostname.startswith('gpu'):
        run(env_tag=gpu_other_tag)
