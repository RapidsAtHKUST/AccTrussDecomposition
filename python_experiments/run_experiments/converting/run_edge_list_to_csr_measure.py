import commands
import socket
import sys
import time
from exec_utilities import time_out_util
from config import *

my_splitter = '-'.join(['*' for _ in range(20)])


def kill_all():
    exec_name_lst = []
    for exec_name in exec_name_lst:
        err_code, output = commands.getstatusoutput("ps -ef | grep " + exec_name + " | awk '{print $2}'")
        for pid in output.strip().split('\n'):
            os.system('kill -9 ' + pid)
    time.sleep(5)


def write_split(statistics_file_path):
    with open(statistics_file_path, 'a+') as ifs:
        ifs.write(my_splitter + my_splitter + '\n')
        ifs.write(my_splitter + my_splitter + '\n')


def signal_handler(signal, frame):
    # print 'You pressed Ctrl+C!'
    kill_all()
    sys.exit(0)


def run_exp(env_tag=knl_tag):
    with open('config.json') as ifs:
        my_config_dict = json.load(ifs)[env_tag]
    ######################
    our_exec_path = my_config_dict[edge_lst_to_csr_exec_path_tag]
    data_set_path = my_config_dict[data_set_path_tag]
    ######################

    our_exec_name_lst = my_config_dict[to_csr_exec_lst_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]

    exp_res_root_name = 'exp_results'
    folder_name = 'edge-list-to-csr-performance'

    thread_num = my_config_dict[thread_num_tag]
    my_env = os.environ.copy()
    my_env["OMP_NUM_THREADS"] = str(thread_num)

    def one_round(is_rev_deg=False):
        for data_set_name in data_set_lst:
            # should use using the user `root`
            if env_tag == knl_tag:
                os.system('echo 3 > /proc/sys/vm/drop_caches')
            # avoid page-cache influence on
            for _ in range(3 if env_tag == lccpu12_tag else 1):
                if is_rev_deg:
                    data_set_name = data_set_name + os.sep + rev_deg_order_tag
                for our_algorithm in our_exec_name_lst:
                    statistics_dir = os.sep.join(
                        map(str, ['.', exp_res_root_name, folder_name, data_set_name, normal_no_reorder_tag, ]))
                    os.system('mkdir -p ' + statistics_dir)
                    statistics_file_path = statistics_dir + os.sep + our_algorithm + '.txt'

                    # 1st: write header
                    os.system(
                        ' '.join(
                            ['echo', my_splitter + time.ctime() + my_splitter, '>>', statistics_file_path]))

                    # 2nd: run exec cmd
                    algorithm_path = our_exec_path + os.sep + our_algorithm
                    params_lst = map(str,
                                     [algorithm_path, data_set_path + os.sep + data_set_name, statistics_file_path])
                    cmd = ' '.join(params_lst)
                    time_out = 1200
                    tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out, env=my_env)

                    # 3rd: append outputs
                    write_split(statistics_file_path)
                    with open(statistics_file_path, 'a+') as ifs:
                        ifs.write(correct_info)
                        ifs.write('\nis_time_out:' + str(tle_flag))
                        ifs.write(my_splitter + time.ctime() + my_splitter)
                        ifs.write('\n\n\n\n')
                    # print 'finish:', cmd

    # normal case
    for i in range(5):
        one_round()


if __name__ == '__main__':
    hostname = socket.gethostname()
    if hostname.startswith('lccpu12'):
        run_exp(env_tag=lccpu12_tag)
    else:
        run_exp(env_tag=knl_tag)
