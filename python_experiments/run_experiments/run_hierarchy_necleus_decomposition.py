import socket

from exec_utilities import time_out_util
from config import *
from exec_utilities.exec_utils import *
from multiprocessing import Process


def run_exp(env_tag=knl_tag, with_c_group=True, data_path_tag=necleus_decomp_exec_path_tag):
    hostname = socket.gethostname()
    with open('config.json') as ifs:
        my_config_dict = json.load(ifs)[env_tag]
    our_exec_path = my_config_dict[data_path_tag]
    data_set_path = my_config_dict[data_set_path_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]
    exp_res_root_name = '/mnt/nvme-ssd/yche/exp_results'
    folder_name = 'exp-2020-02-29-nd' + os.sep + env_tag
    our_exec_name_lst = [
        'nd'
    ]
    work_dir = os.sep.join([exp_res_root_name, folder_name])
    os.system('mkdir -p ' + work_dir)
    logger = get_logger(os.sep.join([work_dir, hostname + '.log']), name=__name__)

    logger.info(my_splitter + time.ctime() + my_splitter)
    logger.info('res folder: {}'.format(folder_name))
    logger.info('our exec folder: {}'.format(our_exec_path))
    logger.info('our exec name list: {}'.format(our_exec_name_lst))
    logger.info('data set lst: {}'.format(data_set_lst))

    def one_round():
        t_num = 64
        for data_set_name in data_set_lst:
            for our_algorithm in our_exec_name_lst:
                for kt_type_name in ['12', '23']:
                    # for hierarchy in ['NO', 'YES']:
                    # for hierarchy in ['YES']:
                    for hierarchy in ['NO']:
                        statistics_dir = os.sep.join(map(str, [work_dir, data_set_name, t_num, hierarchy]))
                        output_dir = os.sep.join([statistics_dir, 'output'])
                        os.system('mkdir -p ' + os.sep.join([statistics_dir, 'log']))
                        os.system('mkdir -p ' + output_dir)
                        dstat_file_path = statistics_dir + os.sep + our_algorithm + '-' + kt_type_name + '-dstat.log'
                        log_file_path = os.sep.join(
                            [statistics_dir, 'log', '-'.join([our_algorithm, kt_type_name, 'raw.log'])])
                        logger.info('log file path: {}'.format(log_file_path))

                        # 1st: append headers
                        append_header(dstat_file_path)
                        append_header(log_file_path)

                        # 2nd: run exec cmd
                        algorithm_path = our_exec_path + os.sep + our_algorithm
                        os.chdir(output_dir)
                        params_lst = map(str,
                                         ['cgexec -g memory:yche-exp' if with_c_group else '',
                                          algorithm_path,
                                          data_set_path + os.sep + data_set_name, kt_type_name, hierarchy])
                        cmd = ' '.join(params_lst)
                        logger.info('exec-cmd: {}'.format(cmd))
                        time_out = 3600 * 10
                        my_env = os.environ.copy()

                        def execute_cmd(my_cmd):
                            logger.info('sub-process: {}'.format(my_cmd))
                            os.system(my_cmd)

                        # 3rd: spawn a new process to run the exec
                        dstat_cmd = 'dstat -tcdrlmgyn --fs >> ' + dstat_file_path
                        p = Process(target=execute_cmd, args=(dstat_cmd,))
                        p.start()
                        my_env['OMP_NUM_THREADS'] = str(t_num)
                        tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out,
                                                                                      env=my_env)
                        time_out_util.kill_term_recursive(p.pid)
                        modify_dstat_file(dstat_file_path)

                        # 4th: append outputs
                        if len(info) > 0:
                            with open(log_file_path, 'a+') as ofs:
                                ofs.write(info)

                        logger.info('finish: {}'.format(cmd))

    one_round()


if __name__ == '__main__':
    hostname = socket.gethostname()
    if hostname.startswith('gpu24'):
        run_exp(env_tag=gpu24_tag, with_c_group=False)
