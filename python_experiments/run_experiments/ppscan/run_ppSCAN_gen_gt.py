import subprocess
import socket
import sys
import time
from exec_utilities import time_out_util
from config import *

my_splitter = '-'.join(['*' for _ in range(20)])


def kill_all():
    exec_name_lst = []
    for exec_name in exec_name_lst:
        err_code, output = subprocess.getstatusoutput("ps -ef | grep " + exec_name + " | awk '{print $2}'")
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
    # print my_config_dict
    data_set_path = my_config_dict[data_set_path_tag]
    data_set_lst = filter(lambda name: 'rmat' in name, my_config_dict[data_set_lst_tag])
    # print data_set_path, data_set_lst
    # eps_lst = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]
    # mu_lst = [2, 5, 10, 15]

    eps_lst = [0.2]
    mu_lst = [5]
    root_path = my_config_dict[exp_res_root_path_tag] + '/log/'

    def one_round(reorder_method='.'):
        statistics_file_path = root_path + 'han-' + reorder_method + '.log'
        for data_set_name in data_set_lst:
            for eps in eps_lst:
                for mu in mu_lst:
                    algorithm_path = my_config_dict[ppSCAN_exec_path_tag]
                    params_lst = map(str,
                                     [algorithm_path, os.sep.join([data_set_path, data_set_name, reorder_method]),
                                      eps, mu, 'output', '> /dev/null 2>&1'])
                    cmd = ' '.join(params_lst)
                    # print cmd
                    time_out = 7000
                    tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out)

                    with open(statistics_file_path, 'a+') as ifs:
                        ifs.write(info)
                        ifs.write(correct_info)
                        ifs.write('\nis_time_out:' + str(tle_flag))
                        ifs.write(my_splitter + time.ctime() + my_splitter)
                        ifs.write('\n\n\n\n')

    # for reorder_method in ['cache', 'gro']:
    # for reorder_method in ['hybrid', 'slashburn', 'bfsr', 'dfs']:
    # for reorder_method in ['cache', 'rcm-cache']:
    # for reorder_method in ['slashburn']:
    for reorder_method in ['.']:
        one_round(reorder_method)


if __name__ == '__main__':
    hostname = socket.gethostname()

    if hostname.startswith('lccpu12'):
        run_exp(env_tag=lccpu12_tag)
    elif hostname.startswith('gpu23'):
        run_exp(env_tag=gpu23_tag)
    elif hostname.startswith('gpu'):
        run_exp(env_tag=gpu_other_tag)
    else:
        run_exp(knl_tag)
