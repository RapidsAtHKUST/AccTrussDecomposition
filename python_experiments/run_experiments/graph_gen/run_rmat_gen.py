import socket
from exec_utilities import time_out_util
from config import *
from exec_utilities.exec_utils import *


def run_exp(env_tag=knl_tag, data_path_tag=exec_path_tag):
    with open('config.json') as ifs:
        my_config_dict = json.load(ifs)[env_tag]
    ######################
    our_exec_path = '/mnt/nfs/var/nfsshare/yche/git-repos/PaRMAT/src-with-cmake/build'
    rmat_exec_name = 'PaRMAT'
    data_set_path = my_config_dict[data_set_path_tag]
    reorder_path = os.sep.join([my_config_dict[han_order_exec_path_tag], '../converter', ])
    reorder_exec_name = 'edge_list_to_csr_performance_measure_double_dir'
    ######################

    exp_res_root_name = 'exp_results'
    folder_name = 'log-rmat-gen'

    work_dir = os.sep.join(['.', exp_res_root_name, folder_name])
    os.system('mkdir -p ' + work_dir)
    logger = get_logger(os.sep.join([work_dir, hostname + '.log']), name=__name__)
    logger.info('our exec folder', our_exec_path)

    n_m_lst = [
        # (pow(10, 5), pow(10, 7), 'rmat_test'),
        (pow(10, 6) / 2, pow(10, 9) / 2, 'rmat_v0.5m_e0.5g'),
        (pow(10, 7) / 2, pow(10, 9) / 2, 'rmat_v5m_e0.5g'),
        (pow(10, 8) / 2, pow(10, 9) / 2, 'rmat_v50m_e0.5g'),
        # (pow(10, 6), pow(10, 9), 'rmat_v1m_e1g'),
        # (pow(10, 7), pow(10, 9), 'rmat_v10m_e1g'),
        # (pow(10, 8), pow(10, 9), 'rmat_v100m_e1g'),
        # (2 * pow(10, 6), 2 * pow(10, 9), 'rmat_v2m_e2g'),
        # (2 * pow(10, 7), 2 * pow(10, 9), 'rmat_v20m_e2g'),
        # (2 * pow(10, 8), 2 * pow(10, 9), 'rmat_v200m_e2g')
    ]

    def one_round():
        statistics_dir = os.sep.join(
            map(str,
                ['.',
                 exp_res_root_name, folder_name]))
        os.system('mkdir -p ' + statistics_dir)
        statistics_file_path = statistics_dir + os.sep + folder_name + '.txt'
        logger.info(statistics_file_path)
        thread_num = my_config_dict[thread_num_tag]

        for n, m, dataset_name in n_m_lst:
            # 1st: write header
            os.system(
                ' '.join(['echo', my_splitter + time.ctime() + my_splitter, '>>', statistics_file_path]))
            # 2nd: run rmat cmd
            rmat_path = our_exec_path + os.sep + rmat_exec_name
            params_lst = map(str,
                             [rmat_path, '-nVertices', n, '-nEdges', m,
                              '-noEdgeToSelf', '-noDuplicateEdges', '-undirected', '-memUsage',
                              0.8, '-threads', thread_num, '-outbin',
                              data_set_path + os.sep + dataset_name] +
                             ['>>&', statistics_file_path])
            os.system('mkdir -p ' + data_set_path + os.sep + dataset_name)

            cmd = ' '.join(params_lst)
            logger.info('cmd: ', cmd)
            time_out = 7200
            my_env = os.environ.copy()
            my_env['OMP_NUM_THREADS'] = str(thread_num)
            tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out, env=my_env)
            # 3rd: append outputs
            write_split(statistics_file_path)
            with open(statistics_file_path, 'a+') as ifs:
                ifs.write(correct_info)
                ifs.write('\nis_time_out:' + str(tle_flag))
                ifs.write(my_splitter + time.ctime() + my_splitter)
                ifs.write('\n\n\n\n')
            logger.info('finish:', cmd)

            # 4th: run reordering cmd
            converter_path = reorder_path + os.sep + reorder_exec_name
            params_lst = map(str,
                             [converter_path, data_set_path + os.sep + dataset_name,
                              statistics_file_path])
            cmd = ' '.join(params_lst)
            logger.info('cmd: ', cmd)
            tle_flag, info, correct_info = time_out_util.run_with_timeout(cmd, timeout_sec=time_out, env=my_env)
            write_split(statistics_file_path)
            with open(statistics_file_path, 'a+') as ifs:
                ifs.write(correct_info)
                ifs.write('\nis_time_out:' + str(tle_flag))
                ifs.write(my_splitter + time.ctime() + my_splitter)
                ifs.write('\n\n\n\n')
            logger.info('finish:', cmd)

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
