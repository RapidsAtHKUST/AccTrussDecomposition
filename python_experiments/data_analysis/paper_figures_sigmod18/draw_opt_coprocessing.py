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

elapsed_time_tag = 'Total (With Co-Processing)'
elapsed_time_wo_tag = 'Total (W/O Co-Processing)'
coprocessing_time_tag = 'Co-Processing (CPU)'

algorithm_name_dict = get_algorithm_name_dict()

algorithm_tag_lst = [elapsed_time_wo_tag, elapsed_time_tag, coprocessing_time_tag]


def get_time_lst(tag):
    # webbase, it, twitter, friendster
    if tag is elapsed_time_tag:
        return [7.421, 4.021, 7.988, 44.096]
    if tag is elapsed_time_wo_tag:
        return [7.421 + 2.242, 4.021 + 2.353, 7.988 + 7.613, 44.096 + 23.632]
    elif tag is coprocessing_time_tag:
        return [2.242, 2.353, 7.613, 23.632]
    return


def get_speedup_list():
    prev = [7.421 + 2.242, 4.021 + 2.353, 7.988 + 7.613, 44.096 + 23.632]
    cur = [7.421, 4.021, 7.988, 44.096]
    return list(map(lambda tuple: tuple[0] / tuple[1], zip(prev, cur)))


def draw_overview_elapsed_time():
    with open('../config.json') as ifs:
        my_config_dict = json.load(ifs)[knl_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]
    g_names = map(lambda data: data_names[data], data_set_lst)

    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax_lst = plt.subplots(1, 2, figsize=size_of_fig)
    N = len(g_names)

    def draw_time():
        ax = ax_lst[0]
        # indent lst
        width = 0.2
        ind = 1.1 * np.arange(N)  # the x locations for the groups
        indent_lst = map(lambda idx: ind + (idx) * width, range(3))
        for idx in xrange(1, 3):
            indent_lst[idx] += width

        # other lst
        hatch_lst = [
            # '',
            # '|||', '.', "**",
            # '',
            # 'O', '\\', 'x', '--',
            '+', '/', 'o']
        label_lst = [exec_name for exec_name in algorithm_tag_lst]
        color_lst = [
            # '#fe01b1',
            # 'orange', 'green', 'red',
            # 'black',
            # '#ceb301', 'm', 'brown', 'k',
            'purple', 'blue', 'gray']

        # 1st: bars
        for idx, tag in enumerate(algorithm_tag_lst):
            ax.bar(indent_lst[idx], get_time_lst(tag), width, hatch=hatch_lst[idx], label=label_lst[idx],
                   edgecolor=color_lst[idx],
                   fill=False)

        # 2nd: x and y's ticks and labels
        ax.set_xticks(ind + 1.5 * width)
        ax.set_xticklabels(map(lambda name: name, g_names), fontsize=LABEL_SIZE)

        ax.set_xlabel('(a) Comparison of elapsed time', fontsize=LABEL_SIZE)
        ax.set_yscale('log')
        ax.set_ylabel("Elapsed Time (seconds)", fontsize=LABEL_SIZE - 2)
        ax.set_ylim(1, 1888)
        ax.set_yticks([1, 10, 100])
        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        ax.legend(prop={'size': LEGEND_SIZE - 4, "weight": "bold"}, loc="upper left", ncol=1)

    def draw_speedup():
        ax = ax_lst[1]
        # indent lst
        width = 0.4
        ind = 1.2 * np.arange(N)  # the x locations for the groups
        # 1st: bars
        ax.bar(ind, get_speedup_list(), width, hatch='o', label='Speedup Over W/O Co-Processing',
               edgecolor='black', fill=False)

        # 2nd: x and y's ticks and labels
        ax.set_xticks(ind)
        ax.set_xticklabels(map(lambda name: name, g_names), fontsize=LABEL_SIZE)
        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        ax.set_ylabel("Co-Processing Speedup", fontsize=LABEL_SIZE - 2)
        ax.set_xlabel('(b) Speedup', fontsize=LABEL_SIZE)
        ax.set_ylim(1, 2.2)
        ax.legend(prop={'size': LEGEND_SIZE - 4, "weight": "bold"}, loc="upper left", ncol=1)

    draw_time()
    draw_speedup()

    fig.subplots_adjust(wspace=0.22)
    fig.savefig("./figures/" + 'opt_coprocessing.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
