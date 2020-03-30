import socket
from exec_utilities import time_out_util
from config import *
from exec_utilities.exec_utils import *


def run_exp(env_tag=knl_tag, data_path_tag=exec_path_tag):
    with open('config.json') as ifs:
        my_config_dict = json.load(ifs)[env_tag]
    ######################
    our_exec_path = my_config_dict[data_path_tag]
    data_set_path = my_config_dict[data_set_path_tag]
    ######################

    # our_exec_name_lst = filter(lambda name: 'roaring' in name, my_config_dict[triangle_exec_lst_tag])
    # our_exec_name_lst = filter(lambda name: 'roaring' in name, my_config_dict[triangle_exec_lst_tag])
    our_exec_name_lst = my_config_dict[triangle_exec_lst_tag]

    data_set_lst = my_config_dict[data_set_lst_tag]
    exp_res_root_name = 'exp_results'
    folder_name = 'exp-03-25-study-tri-cnt'
    reorder_method_lst = ['gro', 'org', 'deg', 'kcore']

    # reorder_method_lst = ['org', 'deg', 'kcore']
    # reorder_method_lst = ['gro']

    def one_round():
        for data_set_name in data_set_lst:
            for our_algorithm in our_exec_name_lst:
                thread_num_lst = my_config_dict[thread_num_lst_tag]

                for t_num in thread_num_lst:
                    for reorder_method in reorder_method_lst:
                        statistics_dir = os.sep.join(
                            map(str,
                                ['.',
                                 exp_res_root_name, folder_name, data_set_name, reorder_method, t_num]))
                        os.system('mkdir -p ' + statistics_dir)
                        statistics_file_path = statistics_dir + os.sep + our_algorithm + '.txt'

                        # 1st: write header
                        os.system(
                            ' '.join(
                                ['echo', my_splitter + time.ctime() + my_splitter, '>>', statistics_file_path]))

                        # 2nd: run exec cmd
                        algorithm_path = our_exec_path + os.sep + our_algorithm
                        params_lst = map(str,
                                         [algorithm_path,
                                          data_set_path + os.sep + data_set_name,
                                          t_num, reorder_method, statistics_file_path, '> /dev/null 2>&1'])
                        cmd = ' '.join(params_lst)
                        time_out = 300

                        my_env = os.environ.copy()
                        tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out,
                                                                                      env=my_env)
                        # 3rd: append outputs
                        write_split(statistics_file_path)
                        with open(statistics_file_path, 'a+') as ifs:
                            ifs.write(correct_info)
                            ifs.write('\nis_time_out:' + str(tle_flag) + '\n')
                            ifs.write(my_splitter + time.ctime() + my_splitter)
                            ifs.write('\n\n\n\n')

    # normal case
    one_round()


if __name__ == '__main__':
    hostname = socket.gethostname()
    if hostname.startswith('lccpu12'):
        run_exp(env_tag=lccpu12_tag)
    elif hostname.startswith('gpu23'):
        run_exp(env_tag=gpu23_tag)
    else:
        # run_exp(env_tag=knl_tag, data_path_tag=exec_path_tag)
        run_exp(env_tag=knl_tag, data_path_tag=exec_path_non_hbw_tag)
