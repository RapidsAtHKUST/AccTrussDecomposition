import socket

from exec_utilities import time_out_util
from config import *
from exec_utilities.exec_utils import *
from multiprocessing import Process


def run_exp(env_tag=knl_tag, with_c_group=True, data_path_tag=k_truss_exec_path_tag):
    hostname = socket.gethostname()

    with open('config.json') as ifs:
        my_config_dict = json.load(ifs)[env_tag]
    our_exec_path = my_config_dict[data_path_tag]
    data_set_path = my_config_dict[data_set_path_tag]
    data_set_lst = [
        "webgraph_eu",
        "webgraph_it",
        "webgraph_twitter"
        # "s24-16",
        # "s24-32",
        # "ssca2-config-s17-c1000",
        # "ssca2-config-s17-c10000"
        # "snap_friendster"

        # "ssca-s17-c1k",
        # "ssca-s17-c2k",
        # "ssca-s17-c4k",
        # "ssca-s17-c6k",
        # "ssca-s17-c8k",
        #
        # "s22-16",
        # "s23-16",
        # "s24-16",
        # "s25-16",
        #
        # "ssca-s17-c10k",
        # "s26-16",
        # "s27-16"
    ]
    # thread_num_lst = [1, 2, 4, 8, 16, 32, 40, 56]
    thread_num_lst = [64] if env_tag is gpu24_tag else [40]

    exp_res_root_name = 'exp_results'
    folder_name = 'exp-2020-04-01-psm-effect' + os.sep + hostname
    org_order_lst = ['org']
    our_reorder_dict = {
        'ustgpu2': org_order_lst,
        'ustgpu1': org_order_lst,
        'gpu23': org_order_lst,
        'gpu24': org_order_lst,
        'gpu16': org_order_lst
    }
    our_exec_name_lst = [
        # 'pkt-eid',
        # 'pkt-eid-parallel',
        # 'pkt-eval-tc-baseline',
        # 'pkt-eval-tc-dtc',
        # 'pkt-eval-tc-wp',
        #
        # 'pkt-inter-legacy',
        # 'pkt-inter-handle-skew',  # +PSM
        'pkt-disable-psm',
        'pkt-vm',  # +VM
        # 'pkt-gc',  # +GC
        # 'pkt-es',  # +ES
        # 'pkt-dstcp',  # +DSTCP
        # 'pkt-bmpf',  # +BMPF
        # 'pkt-inter-shrink',  # +IDX
        #
        # 'cuda-pkt-shrink-all',  # OFF-EIEP
        # 'cuda-pkt-shrink-all-opt',  # OFF-EIEP + IDX
        # 'cuda-pkt-offload-opt',  # OFF-RIEP + IDX
        # 'cuda-pkt-offload',  # OFF-RIEP
    ]
    filtered_reorder_lst = our_reorder_dict[hostname]

    work_dir = os.sep.join(['.', exp_res_root_name, folder_name])
    os.system('mkdir -p ' + work_dir)
    logger = get_logger(os.sep.join([work_dir, hostname + '.log']), name=__name__)
    logger.info(my_splitter + time.ctime() + my_splitter)
    logger.info('res folder: {}'.format(folder_name))
    logger.info('our exec folder: {}'.format(our_exec_path))
    logger.info('our exec name list: {}'.format(our_exec_name_lst))
    logger.info('thread# lst: {}'.format(thread_num_lst))
    logger.info('data set lst: {}'.format(data_set_lst))
    logger.info('filtered_reorder_lst: {}'.format(filtered_reorder_lst))

    def one_round():
        for data_set_name in data_set_lst:
            for reorder_method in filtered_reorder_lst:
                for our_algorithm in our_exec_name_lst:
                    for t_num in thread_num_lst:
                        statistics_dir = os.sep.join(
                            map(str, ['.', exp_res_root_name, folder_name, data_set_name, reorder_method, t_num]))
                        os.system('mkdir -p ' + os.sep.join([statistics_dir, 'log']))
                        os.system('mkdir -p ' + os.sep.join([statistics_dir, 'dstat']))
                        os.system('mkdir -p ' + os.sep.join([statistics_dir, 'dstat_clean']))
                        statistics_file_path = statistics_dir + os.sep + our_algorithm + '.log'
                        dstat_file_path = os.sep.join([statistics_dir, 'dstat', our_algorithm + '-dstat.log'])
                        log_file_path = os.sep.join([statistics_dir, 'log', our_algorithm + '-raw.log'])
                        logger.info('stat file path: {}'.format(statistics_file_path))

                        # 1st: write header
                        append_header(statistics_file_path)
                        append_header(dstat_file_path)
                        append_header(log_file_path)

                        # 2nd: run exec cmd
                        algorithm_path = our_exec_path + os.sep + our_algorithm
                        params_lst = map(str, ['cgexec -g memory:yche-exp' if with_c_group else '',
                                               algorithm_path, data_set_path + os.sep + data_set_name, reorder_method,
                                               statistics_file_path])
                        cmd = ' '.join(params_lst)
                        logger.info('exec-cmd: {}'.format(cmd))
                        time_out = 3600 * 5 if 'cuda' not in our_algorithm else 600
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
        run_exp(env_tag=ustgpu2_tag, with_c_group=False)
    elif hostname.startswith('ustgpu1'):
        run_exp(env_tag=ustgpu1_tag, with_c_group=False)
    elif hostname.startswith('lccpu12'):
        run_exp(env_tag=lccpu12_tag, with_c_group=False)
    elif hostname.startswith('knl'):
        run_exp(env_tag=knl_tag, with_c_group=False)
    elif hostname.startswith('gpu24'):
        run_exp(env_tag=gpu24_tag, with_c_group=False)
    elif hostname.startswith('gpu23'):
        run_exp(env_tag=gpu23_tag)
    elif hostname.startswith('gpu'):
        run_exp(env_tag=gpu_other_tag)
    elif hostname.startswith('hnode'):
        run_exp(env_tag=hnode_79_tag, with_c_group=False)
    else:
        # run_exp(env_tag=knl_tag, data_path_tag=exec_path_tag)
        run_exp(env_tag=knl_tag, data_path_tag=exec_path_non_hbw_tag)
