import socket

from exec_utilities.exec_utils import *
from exec_utilities import time_out_util
from config import *


def get_config_dict(hostname):
    if hostname.startswith('lccpu12'):
        env_tag = lccpu12_tag
    elif hostname.startswith('ustgpu2'):
        env_tag = ustgpu2_tag
    elif hostname.startswith('ustgpu1'):
        env_tag = ustgpu1_tag
    elif hostname.startswith('gpu23'):
        env_tag = gpu23_tag
    elif hostname.startswith('gpu'):
        env_tag = gpu_other_tag
    else:
        env_tag = None
    with open('config.json') as ifs:
        return json.load(ifs)[env_tag]


if __name__ == '__main__':
    hostname = socket.gethostname().strip().split('.')[0]
    logger = get_logger("./exp_results/log/tmp-{}.log".format(hostname), name=__name__)

    my_config_dict = get_config_dict(hostname)

    logger.info('Hostname: {}'.format(hostname))


    def exec_compile_lst(build_dir, src_dir, extra_cmake_options):
        compile_cmd_lst = [
            # ' '.join(['rm -r', build_dir]),
            ' '.join(['mkdir -p', build_dir]),
            ' '.join(['cmake', '-B' + build_dir, '-H' + src_dir] + extra_cmake_options),
            ' '.join(['make', '-C', build_dir, '-j'])]
        for compile_cmd in compile_cmd_lst:
            logger.info(compile_cmd)
            is_time_out, stderr, stdout = time_out_util.run_with_timeout(
                compile_cmd, timeout_sec=100)
            logger.info('is_time_out:{}'.format(is_time_out))
            logger.info('stderr: {}'.format(stderr))
            logger.info('stdout: {}'.format(stdout))


    compiler_flags = \
        ['-DCMAKE_CXX_COMPILER=/opt/rh/devtoolset-7/root/usr/bin/g++',
         '-DCMAKE_C_COMPILER=/opt/rh/devtoolset-7/root/usr/bin/gcc'] if hostname.startswith('gpu') else \
            [
                '-DCMAKE_CXX_COMPILER=/opt/rh/devtoolset-{}/root/usr/bin/g++'.format(
                    '6' if hostname == 'ustgpu2' else '7'),
                '-DCMAKE_C_COMPILER=/opt/rh/devtoolset-{}/root/usr/bin/gcc'.format(
                    '6' if hostname == 'ustgpu2' else '7')
            ]
    working_dir = '/mnt/storage1/yche/git-repos/OutOfCoreSCAN/' if hostname.startswith('gpu') else \
        '/home/zlai/workspace/yche/git-repos/OutOfCoreSCAN/'

    if hostname in ['gpu11', 'gpu12', 'gpu15', 'gpu14', 'gpu16', 'gpu18', 'gpu19', 'gpu21']:
        logger.info('Compile PKT...')
        build_path_tag = k_truss_exec_path_tag
        os.system('mkdir -p ' + my_config_dict[build_path_tag])
        pkt_extra_cmake_options = ['-DTBB_ROOT_DIR=/mnt/nfsshare/intel/tbb'] + compiler_flags

        exec_compile_lst(build_dir=my_config_dict[build_path_tag],
                         src_dir='{}/truss-decomp'.format(working_dir),
                         extra_cmake_options=pkt_extra_cmake_options)
    elif hostname in ['ustgpu1', 'ustgpu2']:
        logger.info('Compile PKT...')
        build_path_tag = k_truss_exec_path_tag
        os.system('mkdir -p ' + my_config_dict[build_path_tag])
        exec_compile_lst(build_dir=my_config_dict[build_path_tag],
                         src_dir='{}/truss-decomp'.format(working_dir),
                         extra_cmake_options=compiler_flags)

    if hostname in ['gpu11', 'gpu12', 'gpu13'] + ['gpu' + str(x) for x in range(14, 22)]:
        logger.info('Compile Karypis...')
        build_path_tag = karypis_k_truss_exec_path_tag

        exec_compile_lst(build_dir=my_config_dict[build_path_tag],
                         src_dir='{}/related_projects/2017-hepc-K-Truss'.format(working_dir),
                         extra_cmake_options=[
                                                 # '-DENABLE_GPERFTOOLS=ON',
                                             ] + compiler_flags)
    elif hostname in ['ustgpu1', 'ustgpu2']:
        logger.info('Compile Karypis...')
        build_path_tag = karypis_k_truss_exec_path_tag

        exec_compile_lst(build_dir=my_config_dict[build_path_tag],
                         src_dir='{}/related_projects/2017-hepc-K-Truss'.format(working_dir),
                         extra_cmake_options=compiler_flags)

    if hostname in ['gpu11', 'gpu12', 'gpu13', 'gpu14', 'gpu15', 'gpu16'] + ['gpu' + str(x) for x in range(17, 22)]:
        logger.info('Compile Necleus Decomp...')
        build_path_tag = necleus_decomp_exec_path_tag
        exec_compile_lst(build_dir=my_config_dict[build_path_tag],
                         src_dir='{}/necleus-decomp'.format(working_dir),
                         extra_cmake_options=[
                                                 # '-DENABLE_GPERFTOOLS=ON',
                                             ] + compiler_flags)

    elif hostname in ['ustgpu1', 'ustgpu2']:
        build_path_tag = necleus_decomp_exec_path_tag
        exec_compile_lst(build_dir=my_config_dict[build_path_tag],
                         src_dir='{}/necleus-decomp'.format(working_dir),
                         extra_cmake_options=[] + compiler_flags)
