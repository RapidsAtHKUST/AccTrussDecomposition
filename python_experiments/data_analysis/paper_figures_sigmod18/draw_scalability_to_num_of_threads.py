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

knl_pivot_tag = 'scan-xp-avx512-galloping-single'
knl_hybrid_tag = 'scan-xp-avx512-hybrid'
knl_bitmap_tag = 'scan-xp-naive-bitvec-hbw-2d'
cpu_merge_tag = 'scan-xp-avx2-merge'
cpu_pivot_tag = 'scan-xp-avx2-galloping-single'
cpu_hybrid_tag = 'scan-xp-avx2-hybrid'
cpu_bitmap_tag = 'scan-xp-naive-bitvec-2d'

algorithm_name_dict = get_algorithm_name_dict()

algorithm_tag_knl_lst = [knl_pivot_tag, knl_hybrid_tag, knl_bitmap_tag]
algorithm_tag_cpu_lst = [cpu_pivot_tag, cpu_hybrid_tag, cpu_bitmap_tag]


def get_time_lst(tag):
    # varying number of threads
    if tag is knl_pivot_tag:
        return [11265.877, 5927.422, 2971.073, 1479.465, 736.907, 367.984, 184.870, 127.824, 107.062]
    if tag is knl_hybrid_tag:
        return [5635.032, 2967.865, 1498.283, 744.207, 369.727, 184.685, 93.222, 62.162, 52.806]
    elif tag is knl_bitmap_tag:
        return [3783.250, 2149.613, 1070.497, 536.894, 269.955, 136.350, 71.149, 65.523, 68.518]
    elif tag is cpu_pivot_tag:
        return [5025.186, 2459.766, 1214.021, 652.225, 327.335, 192.484, min(119.728, 116.085)]
    elif tag is cpu_hybrid_tag:
        return [2629.050, 1474.934, 778.041, 408.533, 222.888, 128.809, min(94.356, 80.548)]
    elif tag is cpu_bitmap_tag:
        return [948.769, 535.145, 277.381, 151.769, 74.219, 57.705, min(47.074, 47.281)]
    return


def draw_overview_elapsed_time():
    with open('../config.json') as ifs:
        my_config_dict = json.load(ifs)[knl_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]
    g_names = map(lambda data: data_names[data], data_set_lst)

    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax_lst = plt.subplots(1, 2, figsize=size_of_fig)
    N = len(g_names)

    color_lst = [
        '#fe01b1',
        'orange',
        'green', 'red',
        'black',
        '#ceb301', 'm', 'brown', 'k',
        'purple', 'blue', 'gray'
    ]
    shape_lst = ['D-.', 's--', 'o:',
                 # 'x-',
                 # 'P-', '*-',
                 # 'v-',
                 '^-.', '<--', '>:']

    def draw_time_knl():
        thread_lst = [1, 2, 4, 8, 16, 32, 64, 128, 256]
        x_lst = range(len(thread_lst))

        ax = ax_lst[0]

        # 1st: bars
        for idx, tag in enumerate(algorithm_tag_knl_lst):
            ax.plot(x_lst, get_time_lst(tag), shape_lst[idx], color=color_lst[2:5][idx], markersize=16,
                    markerfacecolor='none')

        # 2nd: x and y's ticks and labels
        ax.set_xlabel('(a) On KNL', fontsize=LABEL_SIZE)
        ax.set_yscale('log')
        ax.set_ylabel("Elapsed Time (seconds)", fontsize=LABEL_SIZE - 2)
        ax.set_yscale('log')
        ax.set_ylim(10, 40000)

        ax.set_xticks(x_lst)
        ax.set_xticklabels(thread_lst)

        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        for tick in ax.xaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        ax.legend([algorithm_name_dict[name] for name in algorithm_tag_knl_lst],
                  prop={'size': LEGEND_SIZE - 4, "weight": "bold"}, loc="upper right", ncol=1)

    def draw_time_cpu():
        thread_lst = [1, 2, 4, 8, 16, 32, 64]
        x_lst = range(len(thread_lst))

        ax = ax_lst[1]
        for idx, tag in enumerate(algorithm_tag_cpu_lst):
            ax.plot(x_lst, get_time_lst(tag), shape_lst[3:][idx], color=color_lst[6:9][idx], markersize=16,
                    markerfacecolor='none')

        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        for tick in ax.xaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        ax.set_xlabel('(b) On CPU', fontsize=LABEL_SIZE)

        ax.set_yscale('log')
        # ax.set_xscale('log')

        ax.set_ylabel("Elapsed Time (seconds)", fontsize=LABEL_SIZE - 2)
        ax.set_ylim(10, 20000)
        ax.set_xticks(x_lst)
        ax.set_xticklabels(thread_lst)

        ax.legend([algorithm_name_dict[name] for name in algorithm_tag_cpu_lst],
                  prop={'size': LEGEND_SIZE - 4, "weight": "bold"}, loc="upper right", ncol=1)

    draw_time_knl()
    draw_time_cpu()

    fig.subplots_adjust(wspace=0.22)
    fig.savefig("./figures/" + 'scalability_knl_cpu.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
