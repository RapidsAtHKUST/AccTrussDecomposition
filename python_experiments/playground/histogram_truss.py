import matplotlib.pyplot as plt
import numpy as np
import os


def get_prefix_sum_lst(exec_name='ktruss-pkt-inter-shrink'):
    data_set_root_path = '/home/yche/mnt/luocpu9/mnt/storage1/yche/datasets/'
    with open('{}/{}/{}.histogram'.format(data_set_root_path, data_set, exec_name)) as ifs:
        lst = eval(ifs.readline())
        lst = np.cumsum(lst)
        return lst


if __name__ == '__main__':
    pdf_dir = 'pdf'
    os.system('mkdir -p {}'.format(pdf_dir))
    for data_set in ["snap_livejournal",
                     "snap_orkut",
                     "webgraph_eu",
                     "webgraph_uk",
                     "webgraph_webbase",
                     "webgraph_it",
                     "webgraph_twitter", ]:
        k_truss_lst = get_prefix_sum_lst()
        kcore_lst = get_prefix_sum_lst('kcore-test_pkc_imporved')
        fig, ax = plt.subplots()

        plt.plot(range(len(kcore_lst)), kcore_lst, 'x', c='green')
        plt.plot(range(len(k_truss_lst)), k_truss_lst, 'x', c='blue')
        fig.savefig(os.sep.join([pdf_dir, data_set + '.pdf']), bbox_inches='tight', dpi=300)
