import socket
import time

from exec_utilities import time_out_util
from config import *
from run_experiments.acc_tri_cnt.run_our_executables import my_splitter


# exec_path = my_config_dict[ppSCAN_input_to_edge_lst_unidr_exec_tag] + '_txt'
def convert(env_tag, suffix=''):
    with open('config.json') as ifs:
        my_config_dict = json.load(ifs)[env_tag]

    data_set_path = my_config_dict[data_set_path_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]
    exec_path = my_config_dict[ppSCAN_input_to_edge_lst_unidr_exec_tag] + suffix
    verify_path = my_config_dict[ppSCAN_input_to_edge_lst_unidr_exec_verification_tag]

    root_path = my_config_dict[exp_res_root_path_tag] + '/log/'
    os.system('mkdir -p ' + root_path)
    statistics_file_path = root_path + 'convert-to-edge-list.log'

    def one_round():
        for data_set_name in data_set_lst:
            params_lst = map(str, [exec_path, data_set_path + os.sep + data_set_name, statistics_file_path])
            cmd = ' '.join(params_lst)
            # print cmd
            time_out = 700
            tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out)
            with open(statistics_file_path, 'a+') as ifs:
                ifs.write(correct_info)
                ifs.write('\nis_time_out:' + str(tle_flag))
                ifs.write(my_splitter + time.ctime() + my_splitter)
                ifs.write('\n\n\n\n')

            params_lst = map(str, [verify_path, data_set_path + os.sep + data_set_name, statistics_file_path])
            cmd = ' '.join(params_lst)
            # print 'verify', cmd
            tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out)
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
        convert(env_tag=lccpu12_tag)
    elif hostname.startswith('gpu23'):
        convert(env_tag=gpu23_tag)
    else:
        convert(env_tag=knl_tag)
