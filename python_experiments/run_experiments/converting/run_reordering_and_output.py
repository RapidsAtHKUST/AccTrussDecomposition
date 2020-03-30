import time

from exec_utilities import time_out_util
from config import *
from run_experiments.acc_tri_cnt.run_our_executables import my_splitter
import socket


def convert(env_tag):
    with open('config.json') as ifs:
        my_config_dict = json.load(ifs)[env_tag]

    data_set_path = my_config_dict[data_set_path_tag]
    data_set_lst = filter(lambda name: 'rmat' in name, my_config_dict[data_set_lst_tag])
    han_exec_path = my_config_dict[han_order_exec_path_tag]
    # reordering_method = rev_deg_order_tag
    converter_path = my_config_dict[reordering_to_ppscan_input_exec_path_tag]

    root_path = my_config_dict[exp_res_root_path_tag] + '/log/'
    os.system('mkdir -p ' + root_path)

    def one_round():
        for data_set_name in data_set_lst:
            # assume already have all the edge list binaries
            reorder_dict = dict(zip(
                ['gpu15', 'gpu16', 'gpu17', 'gpu21', 'gpu22'],
                ['hybrid', 'slashburn', 'bfsr', 'dfs', 'gro']
            ))
            order_tag = reorder_dict[hostname]
            # for order_tag in [
            #     'hybrid',
            #     'slashburn',
            #     'bfsr',
            #     'dfs',
            #     'gro'
            # ]:
            time_out = 7200000 if order_tag is 'gro' else 3600000
            statistics_file_path = root_path + 'han-' + order_tag + '.log'

            params_lst = map(str, [han_exec_path, os.sep.join([data_set_path, data_set_name]), '-order', order_tag])
            cmd = ' '.join(params_lst)
            # print cmd
            tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out)
            with open(statistics_file_path, 'a+') as ifs:
                ifs.write(info)
                ifs.write(correct_info)
                ifs.write('\nis_time_out:' + str(tle_flag))
                ifs.write(my_splitter + time.ctime() + my_splitter)
                ifs.write('\n\n\n\n')

            # params_lst = map(str, [converter_path, data_set_path + os.sep + data_set_name, order_tag,
            #                        statistics_file_path])
            # cmd = ' '.join(params_lst)
            # print cmd
            #
            # tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out)
            # with open(statistics_file_path, 'a+') as ifs:
            #     ifs.write(correct_info)
            #     ifs.write('\nis_time_out:' + str(tle_flag))
            #     ifs.write(my_splitter + time.ctime() + my_splitter)
            #     ifs.write('\n\n\n\n')

            # print 'finish:', cmd

    one_round()


if __name__ == '__main__':
    hostname = socket.gethostname()
    if hostname.startswith('lccpu12'):
        convert(env_tag=lccpu12_tag)
    elif hostname.startswith('gpu23'):
        convert(env_tag=gpu23_tag)
    elif hostname.startswith('gpu'):
        convert(env_tag=gpu_other_tag)
    else:
        convert(env_tag=knl_tag)
