from exec_utilities import exec_utils, time_out_util
import os

if __name__ == '__main__':
    data_set_lst = [
        # "snap_livejournal",
        # "snap_orkut",
        # "webgraph_eu",
        # "webgraph_uk",
        # "webgraph_webbase",
        # "webgraph_it",
        # "webgraph_twitter",
        # "snap_friendster",
        # "rmat_v50m_e0.5g",
        # "rmat_v5m_e0.5g",
        # "rmat_v0.5m_e0.5g",
        "s22-16",
        "s23-16",
        "s24-16",
        "s25-16",
        "s26-16",
        "s27-16",
        "s28-16",
    ]
    # folder_root = '/home/yche/mnt/luocpu9/mnt/storage1/yche/datasets'
    folder_root = '/home/yche/mnt/gpu24/mnt/nvme-ssd/yche/datasets'
    logger = exec_utils.get_logger("/home/yche/log.log", name=__name__)
    for data_set in data_set_lst:
        cmd = 'md5sum ' + os.sep.join([folder_root, data_set, 'ktruss-pkt-inter-shrink.histogram'])
        logger.info(time_out_util.run_with_timeout(cmd, timeout_sec=10))
