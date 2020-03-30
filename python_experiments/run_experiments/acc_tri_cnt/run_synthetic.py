import socket
from exec_utilities import time_out_util
from config import *
from exec_utilities.exec_utils import *


def run_exp(env_tag=knl_tag):
    with open('config.json') as ifs:
        my_config_dict = json.load(ifs)[env_tag]
    ######################
    data_path_tag = exec_path_tag
    our_exec_path = my_config_dict[data_path_tag] + os.sep + 'experimental'
    data_set_path = my_config_dict[data_set_path_tag]
    ######################

    our_exec_name_lst = filter(lambda exec_name: 'cuda' not in exec_name, my_config_dict[synthetic_exec_lst_tag])

    data_set_lst = my_config_dict[data_set_lst_tag]
    data_set_lst = filter(lambda name: 'webgraph_it' in name, data_set_lst)
    exp_res_root_name = 'exp_results'
    folder_name = 'overview-09-26-synthetic-' + env_tag

    # parameters
    thread_num = my_config_dict[thread_num_tag]

    def one_round():
        for data_set_name in data_set_lst:
            # should use using the user `root`
            if env_tag == knl_tag:
                os.system('echo 3 > /proc/sys/vm/drop_caches')
            data_set_name = data_set_name + os.sep + rev_deg_order_tag
            for our_algorithm in our_exec_name_lst:
                for vid in range(0, 1000, 10):
                    t_num = thread_num
                    statistics_dir = os.sep.join(
                        map(str, ['.', exp_res_root_name, folder_name, data_set_name, t_num]))
                    os.system('mkdir -p ' + statistics_dir)
                    statistics_file_path = statistics_dir + os.sep + our_algorithm + '.txt'

                    # 1st: write header
                    os.system(' '.join(
                        ['echo', my_splitter + time.ctime() + my_splitter, '>>', statistics_file_path]))

                    # 2nd: run exec cmd
                    algorithm_path = our_exec_path + os.sep + our_algorithm
                    params_lst = map(str,
                                     [algorithm_path,
                                      data_set_path + os.sep + data_set_name,
                                      vid,
                                      t_num, statistics_file_path, '> /dev/null 2>&1'])
                    cmd = ' '.join(params_lst)
                    time_out = 20000

                    my_env = os.environ.copy()
                    tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out,
                                                                                  env=my_env)
                    # 3rd: append outputs
                    write_split(statistics_file_path)
                    with open(statistics_file_path, 'a+') as ifs:
                        ifs.write(correct_info)
                        ifs.write('\nis_time_out:' + str(tle_flag))
                        ifs.write(my_splitter + time.ctime() + my_splitter)
                        ifs.write('\n\n\n\n')

    # normal case
    one_round()


if __name__ == '__main__':
    hostname = socket.gethostname()
    if hostname.startswith('lccpu12'):
        run_exp(env_tag=lccpu12_tag)
    else:
        run_exp(env_tag=knl_tag)
