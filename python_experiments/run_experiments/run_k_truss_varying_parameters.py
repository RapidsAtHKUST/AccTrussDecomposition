import socket

from exec_utilities import time_out_util
from config import *
from exec_utilities.exec_utils import *
from multiprocessing import Process

gt_tag = 'graph-compaction'
ept_tag = 'dstc-tp'
rs_tag = 'range-size'

option_dict = {
    gt_tag: '--gt',
    ept_tag: '--ept',
    rs_tag: '--rs'
}


def run_exp(option_tag, val_lst, env_tag=ustgpu2_tag, with_c_group=True, data_path_tag=k_truss_exec_path_tag):
    assert option_tag in [gt_tag, ept_tag, rs_tag]
    hostname = socket.gethostname()

    with open('config.json') as ifs:
        my_config_dict = json.load(ifs)[env_tag]
    our_exec_path = my_config_dict[data_path_tag]
    data_set_path = my_config_dict[data_set_path_tag]
    data_set_lst = [
        "webgraph_eu" if option_tag in [ept_tag, rs_tag] else "webgraph_twitter"
    ]
    thread_num_lst = [40]

    exp_res_root_name = 'exp_results'
    folder_name = 'exp-2019-10-06-parameters' + os.sep + hostname
    org_order_lst = ['org']
    our_reorder_dict = {
        'ustgpu2': org_order_lst,
        'ustgpu1': org_order_lst,
        'gpu23': org_order_lst
    }
    our_algorithm = 'pkt-varying'

    filtered_reorder_lst = our_reorder_dict[hostname]

    work_dir = os.sep.join(['.', exp_res_root_name, folder_name])
    os.system('mkdir -p ' + work_dir)

    logger = get_logger(os.sep.join([work_dir, hostname + '.log']), name=__name__)
    logger.info(my_splitter + time.ctime() + my_splitter)
    logger.info('res folder: {}'.format(folder_name))
    logger.info('our exec folder: {}'.format(our_exec_path))
    logger.info('our exec name list: {}'.format(our_algorithm))
    logger.info('thread# lst: {}'.format(thread_num_lst))
    logger.info('data set lst: {}'.format(data_set_lst))
    logger.info('filtered_reorder_lst: {}'.format(filtered_reorder_lst))

    def one_round():

        for data_set_name in data_set_lst:
            for reorder_method in filtered_reorder_lst:
                for t_num in thread_num_lst:
                    for option_val in val_lst:
                        statistics_dir = os.sep.join(
                            map(str, ['.', exp_res_root_name, folder_name, data_set_name, reorder_method, t_num,
                                      option_tag]))
                        os.system('mkdir -p ' + os.sep.join([statistics_dir, 'log']))
                        os.system('mkdir -p ' + os.sep.join([statistics_dir, 'dstat']))
                        os.system('mkdir -p ' + os.sep.join([statistics_dir, 'dstat_clean']))
                        file_name = '{}-{}'.format(our_algorithm, option_val)
                        statistics_file_path = statistics_dir + os.sep + file_name + '.log'
                        dstat_file_path = os.sep.join([statistics_dir, 'dstat', file_name + '-dstat.log'])
                        log_file_path = os.sep.join([statistics_dir, 'log', file_name + '-raw.log'])
                        logger.info('stat file path: {}'.format(statistics_file_path))

                        # 1st: write header
                        append_header(statistics_file_path)
                        append_header(dstat_file_path)
                        append_header(log_file_path)

                        # 2nd: run exec cmd
                        algorithm_path = our_exec_path + os.sep + our_algorithm
                        params_lst = map(str, ['cgexec -g memory:yche-exp' if with_c_group else '',
                                               algorithm_path, data_set_path + os.sep + data_set_name,
                                               reorder_method,
                                               statistics_file_path,
                                               option_dict[option_tag], option_val])
                        cmd = ' '.join(params_lst)
                        logger.info('exec-cmd: {}'.format(cmd))
                        time_out = 3600 * 5
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
                        write_split(statistics_file_path)
                        with open(statistics_file_path, 'a+') as ifs:
                            ifs.write(correct_info)
                            ifs.write('\nis_time_out:' + str(tle_flag))
                            ifs.write(my_splitter + time.ctime() + my_splitter)
                            ifs.write('\n\n\n\n')
                        if len(info) > 0:
                            with open(log_file_path, 'a+') as ofs:
                                ofs.write(info)

                        logger.info('finish: {}'.format(cmd))

    for _ in range(1):
        one_round()


if __name__ == '__main__':
    hostname = socket.gethostname()
    if hostname.startswith('ustgpu2'):
        # run_exp(gt_tag, [2 ** i for i in range(9)], env_tag=ustgpu2_tag, with_c_group=False)
        # run_exp(ept_tag, [1.25 * (10 ** 8) * (2 ** i) for i in range(9)], env_tag=ustgpu2_tag, with_c_group=False)
        run_exp(rs_tag, [2 ** i for i in range(9)], env_tag=ustgpu2_tag, with_c_group=False)
