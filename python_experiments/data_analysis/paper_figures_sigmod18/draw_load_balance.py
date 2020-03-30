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


def get_speedup_lst(tag):
    # webbase, web-it, twitter, friendster
    if tag is m_gpu_bitmap_tag:
        return [8.751 / 7.421, 4.321 / 4.0, 9.795 / 7.988, 44 / 55.]
    elif tag is m_gpu_warp_tag:
        return [5.117 / 5.161, 15.904 / 10.558, 517.840 / 544.279, 32.901 / 25.925]
    elif tag is m_gpu_kernel_tag:
        return [5.148 / 5.027, 14.714 / 8.852, 179.215 / 158.843, 32.553 / 29.066]


def get_multi_pass_time_lst():
    return [None, None, 134.360, 44.323, 45.662, 52.735
        , 53.866, 64.090, 73.034, 70.928, 80.839, 83.462
        , 88.561, 93.068, 98.792]


def draw_overview_elapsed_time():
    with open('../config.json') as ifs:
        my_config_dict = json.load(ifs)[knl_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]
    g_names = map(lambda data: data_names[data], data_set_lst)
    algorithm_name_dict = get_algorithm_name_dict()

    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax = plt.subplots()
    N = len(g_names)

    color_lst = [
        '#fe01b1',
        'orange',
        'green', 'red',
        'black',
        '#ceb301', 'm', 'brown', 'k',
        'purple', 'blue', 'gray'
    ]

    hatch_lst = ['', '|||', '.', "**", '', 'O',
                 '\\', 'x', '--', '++', '//', 'o']

    def draw_load_balance():
        width = 0.2
        ind = 1.2 * np.arange(N)  # the x locations for the groups
        indent_lst = map(lambda idx: ind + idx * width, range(3))

        # 1st: bars
        algo_lst = [m_gpu_warp_tag, m_gpu_kernel_tag, m_gpu_bitmap_tag]
        for idx, tag in enumerate(algo_lst):
            ax.bar(indent_lst[idx], get_speedup_lst(tag), width, hatch=hatch_lst[9 + idx], edgecolor=color_lst[9 + idx],
                   fill=False)

            # 2nd: x and y's ticks and labels
            ax.set_ylabel("Speedup", fontsize=LABEL_SIZE)
            ax.set_ylim(0.75, 1.8)

            ax.set_xticks(ind)
            ax.set_xticklabels(map(lambda name: name, g_names), fontsize=LABEL_SIZE)

            for tick in ax.yaxis.get_major_ticks():
                tick.label.set_fontsize(TICK_SIZE)
            for tick in ax.xaxis.get_major_ticks():
                tick.label.set_fontsize(TICK_SIZE)
        ax.legend([algorithm_name_dict[ele] for ele in algo_lst],
                  prop={'size': LEGEND_SIZE - 4, "weight": "bold"}, loc="upper right", ncol=1)

    draw_load_balance()
    fig.set_size_inches(*size_of_fig)
    fig.savefig("./figures/" + 'load_balance.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
