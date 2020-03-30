import socket
from exec_utilities import time_out_util
from config import *
from exec_utilities.exec_utils import *


def run_exp(env_tag=knl_tag, data_path_tag=exec_path_tag):
    with open('config.json') as ifs:
        my_config_dict = json.load(ifs)[env_tag]
    ##################`####
    our_exec_path = os.sep.join([my_config_dict[data_path_tag], '..', '..', 'truss-decomp',
                                 'build23' if env_tag is gpu23_tag else 'build-12'])
    data_set_path = my_config_dict[data_set_path_tag]
    ######################

    our_exec_name_lst = ['pkc',
                         ]
    # print 'our exec folder', our_exec_path
    # print 'our exec name list', our_exec_name_lst

    data_set_lst = filter(lambda name: 'rmat' in name, my_config_dict[data_set_lst_tag])
    # print data_set_lst
    exp_res_root_name = 'exp_results'
    folder_name = 'exp-03-10-k-core'

    def one_round():
        for data_set_name in data_set_lst:
            for our_algorithm in our_exec_name_lst:
                thread_num_lst = my_config_dict[thread_num_lst_tag]

                for t_num in thread_num_lst:
                    statistics_dir = os.sep.join(
                        map(str,
                            ['.',
                             exp_res_root_name, folder_name, data_set_name, t_num]))
                    os.system('mkdir -p ' + statistics_dir)
                    statistics_file_path = statistics_dir + os.sep + our_algorithm + '.txt'
                    # print statistics_file_path

                    # 1st: write header
                    os.system(
                        ' '.join(
                            ['echo', my_splitter + time.ctime() + my_splitter, '>>', statistics_file_path]))

                    # 2nd: run exec cmd
                    algorithm_path = our_exec_path + os.sep + our_algorithm
                    params_lst = map(str,
                                     [algorithm_path,
                                      data_set_path + os.sep + data_set_name
                                         , statistics_file_path])
                    cmd = ' '.join(params_lst)
                    # print 'cmd: ', cmd
                    time_out = 3600 * 5

                    my_env = os.environ.copy()
                    tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out,
                                                                                  env=my_env)
                    if tle_flag:
                        break

                    # 3rd: append outputs
                    write_split(statistics_file_path)
                    with open(statistics_file_path, 'a+') as ifs:
                        ifs.write(correct_info)
                        ifs.write('\nis_time_out:' + str(tle_flag))
                        ifs.write(my_splitter + time.ctime() + my_splitter)
                        ifs.write('\n\n\n\n')
                    # print 'finish:', cmd

    # normal case
    one_round()


if __name__ == '__main__':
    hostname = socket.gethostname()
    if hostname.startswith('lccpu12'):
        run_exp(env_tag=lccpu12_tag)
    elif hostname.startswith('gpu23'):
        run_exp(env_tag=gpu23_tag)
    elif hostname.startswith('gpu'):
        run_exp(env_tag=gpu_other_tag)
    else:
        # run_exp(env_tag=knl_tag, data_path_tag=exec_path_tag)
        run_exp(env_tag=knl_tag, data_path_tag=exec_path_non_hbw_tag)
