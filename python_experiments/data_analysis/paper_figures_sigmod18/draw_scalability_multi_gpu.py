import matplotlib.pyplot as plt
import numpy as np

from config import *


def get_name_dict():
    with open('config/data_names.json') as ifs:
        return eval(''.join(ifs.readlines()))


def get_algorithm_name_dict():
    with open('config/algorithm_info.json') as ifs:
        return json.load(ifs)["algorithm_abbr"]


# data set abbreviation dictionary
data_names = get_name_dict()

# figure parameters
FIG_SIZE_MULTIPLE = (16, 4)
LABEL_SIZE = 22
TICK_SIZE = 22
LEGEND_SIZE = 22

m_gpu_warp_tag = 'scan-xp-cuda-4-8-multi-gpu-multi-pass-dynamic-lb'
m_gpu_kernel_tag = 'scan-xp-cuda-hybrid-kernels-multi-gpu-multi-pass-dynamic-lb'
m_gpu_bitmap_tag = 'scan-xp-cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass-dynamic-lb'

algorithm_name_dict = get_algorithm_name_dict()

algorithm_tag_gpu_lst = [m_gpu_warp_tag, m_gpu_kernel_tag, m_gpu_bitmap_tag]
tw_tag = 'webgraph_twitter'
fr_tag = 'snap_friendster'


def get_time_lst(tag, dataset):
    if dataset == tw_tag:
        if tag is m_gpu_warp_tag:
            return [962.457, 639.057, 599.061, 534.534]
        elif tag is m_gpu_kernel_tag:
            return [249.507, 163.678, 118.962, 97.949]  # load is balanced, problem with unified-memory
        elif tag is m_gpu_bitmap_tag:
            return [27.529, 16.2, 11.179, 7.988]  # manually run experiments
    elif dataset == fr_tag:
        if tag is m_gpu_warp_tag:
            return [94.733, 55.195, 33.017, 25.925]
        elif tag is m_gpu_kernel_tag:
            return [93.083, 65.520, 36.420, 29.066]
        elif tag is m_gpu_bitmap_tag:
            return [114.077, 79.280, 57.292, 44.096]


def draw_overview_elapsed_time():
    with open('../config.json') as ifs:
        my_config_dict = json.load(ifs)[knl_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]
    g_names = map(lambda data: data_names[data], data_set_lst)

    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax_lst = plt.subplots(1, 2, figsize=size_of_fig)
    N = len(g_names)

    color_lst = [
        # '#fe01b1',
        # 'orange',
        # 'green', 'red',
        # 'black',
        # '#ceb301', 'm', 'brown', 'k',
        'purple', 'blue', 'gray'
    ]
    shape_lst = [
        # 'D-.', 's--', 'o:',
        'x-',
        'P-', '*-',
        'v-',
        '^-.', '<--', '>:']
    thread_lst = [1, 2, 4, 8]

    def draw_time_twitter():
        x_lst = range(len(thread_lst))
        print x_lst
        ax = ax_lst[0]

        # 1st: bars
        for idx, tag in enumerate(algorithm_tag_gpu_lst):
            ax.plot(x_lst, get_time_lst(tag, tw_tag), shape_lst[idx], color=color_lst[idx], markersize=16,
                    markerfacecolor='none')

        # 2nd: x and y's ticks and labels
        ax.set_xlabel('(a) On TW (degree-skew)', fontsize=LABEL_SIZE)
        ax.set_yscale('log')
        ax.set_ylabel("Elapsed Time (seconds)", fontsize=LABEL_SIZE - 2)
        ax.set_yscale('log')
        ax.set_ylim(4, 40000)
        ax.set_yticks([10, 100, 1000])

        ax.set_xticks(x_lst)
        ax.set_xticklabels(thread_lst)

        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        for tick in ax.xaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        ax.legend([algorithm_name_dict[name] for name in algorithm_tag_gpu_lst],
                  prop={'size': LEGEND_SIZE - 4, "weight": "bold"}, loc="upper right", ncol=1)

    def draw_time_friendster():

        x_lst = range(len(thread_lst))

        ax = ax_lst[1]
        for idx, tag in enumerate(algorithm_tag_gpu_lst):
            ax.plot(x_lst, get_time_lst(tag, fr_tag), shape_lst[idx], color=color_lst[idx], markersize=16,
                    markerfacecolor='none')

        ax.set_xlabel('(b) On FR (super-large)', fontsize=LABEL_SIZE)

        ax.set_yscale('log')
        ax.set_ylabel("Elapsed Time (seconds)", fontsize=LABEL_SIZE - 2)
        ax.set_ylim(10, 400)

        ax.set_xticks(x_lst)
        ax.set_xticklabels(thread_lst)

        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        for tick in ax.xaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        ax.legend([algorithm_name_dict[name] for name in algorithm_tag_gpu_lst],
                  prop={'size': LEGEND_SIZE - 4, "weight": "bold"}, loc="upper right", ncol=1)

    draw_time_twitter()
    draw_time_friendster()

    fig.subplots_adjust(wspace=0.22)
    fig.savefig("./figures/" + 'scalability_gpu.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
