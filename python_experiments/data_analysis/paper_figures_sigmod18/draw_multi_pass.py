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


def get_speedup_lst():
    # webbase, web-it, twitter, friendster
    return [8.751 / 7.421, 4.321 / 4.0, 9.795 / 7.988, 44 / 55.]


def get_multi_pass_time_lst(is_twitter=True):
    if is_twitter:
        return [ele - (9.626 - 8) for ele in [9.626, 11.332, 13.548, 13.174, 14.575, 15.864
            , 15.579, 17.460, 18.983, 16.829, 19.521, 20.335, 19.158, 22.007, 23.142]]
    return [None, None, 134.360, 44.323, 45.662, 52.735
        , 53.866, 64.090, 73.034, 70.928, 80.839, 83.462
        , 88.561, 93.068, 98.792]


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

    def draw_multi_pass_time_tw():
        thread_lst = range(15)
        x_lst = range(len(thread_lst))

        ax = ax_lst[1]

        ax.plot(x_lst, get_multi_pass_time_lst(is_twitter=True), '*-', color='gray', markersize=16,
                markerfacecolor='none')

        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        for tick in ax.xaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        ax.set_xlabel('(b) on TW', fontsize=LABEL_SIZE)

        # ax.set_yscale('log')
        # ax.set_xscale('log')
        ax.set_ylim(5, 30)

        ax.set_ylabel("Elapsed Time (seconds)", fontsize=LABEL_SIZE - 2)
        ax.set_xticks([0, 1, 2, 3, 5, 7, 9, 11, 13])
        ax.set_xticklabels([1, 2, 3, 4, 6, 8, 10, 12, 14])

        ax.legend(['mGPU-Bitmap'],
                  prop={'size': LEGEND_SIZE - 4, "weight": "bold"}, loc="upper right", ncol=1)

    def draw_multi_pass_time_fr():
        thread_lst = range(15)
        x_lst = range(len(thread_lst))

        ax = ax_lst[0]

        ax.plot(x_lst, get_multi_pass_time_lst(is_twitter=False), '*-', color='gray', markersize=16,
                markerfacecolor='none')

        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        for tick in ax.xaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        ax.set_xlabel('(a) on FR (super large $|E|$)', fontsize=LABEL_SIZE)

        # ax.set_yscale('log')
        # ax.set_xscale('log')
        ax.set_ylim(30, 150)

        ax.set_ylabel("Elapsed Time (seconds)", fontsize=LABEL_SIZE - 2)
        ax.set_xticks([0, 1, 2, 3, 5, 7, 9, 11, 13])
        ax.set_xticklabels([1, 2, 3, 4, 6, 8, 10, 12, 14])

        ax.legend(['mGPU-Bitmap'],
                  prop={'size': LEGEND_SIZE - 4, "weight": "bold"}, loc="upper right", ncol=1)

    draw_multi_pass_time_fr()
    draw_multi_pass_time_tw()
    fig.subplots_adjust(wspace=0.22)
    fig.savefig("./figures/" + 'multi_pass_varying_datasets.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
