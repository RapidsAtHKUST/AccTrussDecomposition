import os

from exec_utilities.exec_utils import get_logger

if __name__ == '__main__':
    files = [
        # 'run_k_truss_reorderd_graph_PP_SI.py',
        # 'run_k_truss_reorderd_graph_nvprof.py',
        # 'run_k_truss_reorderd_graph_cuda.py',
        # 'run_k_truss_reorderd_graph.py',
        'run_k_truss_performance.py',
        'run_necleus_decomposition.py',
    ]

    work_dir = '/home/zlai/workspace/yche/git-repos/' \
               'OutOfCoreSCAN/python_experiments/exp_results'
    os.system('mkdir -p {}'.format(work_dir))
    hostname = 'ustgpu2'
    logger = get_logger(os.sep.join([work_dir, hostname + '.log']), name=__name__)

    for i in range(3):
        for f in files:
            cmd = 'python /home/zlai/workspace/yche/git-repos/' \
                  'OutOfCoreSCAN/python_experiments/run_experiments/{}'.format(f)
            logger.info(cmd)
            os.system(cmd)
