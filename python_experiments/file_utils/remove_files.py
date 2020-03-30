import os, json
from config import *

if __name__ == '__main__':
    with open('../config.json') as ifs:
        my_config_dict = json.load(ifs)[knl_tag]
    our_exec_path = my_config_dict[exec_path_tag]
    data_set_path = my_config_dict[data_set_path_tag]
    our_exec_name_lst = ['scan-xp-avx2-galloping-double', 'scan-xp-avx2-galloping-single', 'scan-xp-avx2-hybrid',
                         'scan-xp-avx2-merge', 'scan-xp-avx2-merge-popcnt', 'scan-xp-avx2-pivot',
                         'scan-xp-naive-galloping-double', 'scan-xp-naive-galloping-single', 'scan-xp-naive-hybrid',
                         'scan-xp-naive-merge', 'scan-xp-naive-pivot',
                         'scan-xp-sse-hybrid', 'scan-xp-sse-merge', 'scan-xp-sse-pivot']
    our_exec_name_lst = my_config_dict[exec_avx512_lst_tag] + our_exec_name_lst
    data_set_lst = my_config_dict[data_set_lst_tag]
    exp_res_root_name = 'exp_results'
    folder_name = 'overview-08-07'

    # parameters
    eps_lst = [0.8]
    mu_lst = [5]
    t_num = 64
    for algorithm in our_exec_name_lst:
        for data_set_name in data_set_lst:
            for eps in eps_lst:
                for mu in mu_lst:
                    statistics_dir = os.sep.join(map(str, [
                        '/home/yche/mnt/luocpu8/nfsshare/share/scan-query-root/python_experiments', exp_res_root_name,
                        folder_name, data_set_name, eps, mu, t_num]))
                    statistics_file_path = statistics_dir + os.sep + algorithm + '.txt'
                    print(statistics_file_path)
                    os.system('rm ' + statistics_file_path)
