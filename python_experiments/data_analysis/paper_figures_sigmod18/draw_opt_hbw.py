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

knl_merge_vec_speedup_tag = 'scan-xp-avx512-merge'
knl_pivot_vec_speedup_tag = 'scan-xp-avx512-galloping-single'
knl_hybrid_vec_speedup_tag = 'scan-xp-avx512-hybrid'
knl_bitmap_speedup_tag = 'scan-xp-naive-bitvec-hbw-2d'

algorithm_name_dict = get_algorithm_name_dict()

algorithm_tag_lst = [knl_merge_vec_speedup_tag, knl_pivot_vec_speedup_tag, knl_hybrid_vec_speedup_tag,
                     knl_bitmap_speedup_tag]


def get_hbw_speedup_lst(tag):
    # webbase, it, twitter, friendster
    if tag is knl_merge_vec_speedup_tag:
        return [23.803 / 23.023, 599.707 / 447.884, 645.667 / 596.186, 62.634 / 36.497]
    elif tag is knl_pivot_vec_speedup_tag:
        return [7.617 / 7.607, 25.925 / 24.964, 118.273 / 107.086, 85.715 / 85.496]
    elif tag is knl_hybrid_vec_speedup_tag:
        return [3.163 / 3.161, 10.741 / 10.715, 86.460 / 52.818, 63.137 / 36.781]
    elif tag is knl_bitmap_speedup_tag:
        return [6.417 / 4.054, 14.317 / 12.260, 109.959 / 68.768, 144.108 / 118.551]
    return


def draw_overview_elapsed_time():
    with open('../config.json') as ifs:
        my_config_dict = json.load(ifs)[knl_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]
    g_names = map(lambda data: data_names[data], data_set_lst)

    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax = plt.subplots()
    N = len(g_names)

    # indent lst
    width = 0.2
    ind = 1.2 * np.arange(N)  # the x locations for the groups
    indent_lst = map(lambda idx: ind + idx * width, range(4))

    # other lst
    hatch_lst = [
        # '',
        '|||', '.', "**",
        '',
        'O', '\\', 'x', '--', '++', '//', 'o']
    label_lst = [algorithm_name_dict[exec_name] for exec_name in algorithm_tag_lst]
    color_lst = [
        # '#fe01b1',
        'orange', 'green', 'red',
        'black',
        '#ceb301', 'm', 'brown', 'k',
        'purple', 'blue', 'gray']

    # 1st: bars
    for idx, tag in enumerate(algorithm_tag_lst):
        ax.bar(indent_lst[idx], get_hbw_speedup_lst(tag), width, hatch=hatch_lst[idx], label=label_lst[idx],
               edgecolor=color_lst[idx],
               fill=False)

    # 2nd: x and y's ticks and labels
    ax.set_xticks(ind + 2 * width)
    ax.set_xticklabels(map(lambda name: name, g_names), fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    # plt.yscale('log')
    ax.set_ylabel("MCDRAM Speedup", fontsize=LABEL_SIZE - 2)
    plt.yticks(fontsize=TICK_SIZE)

    plt.ylim(0.75, 2.2)
    plt.yticks([1, 1.2, 1.4, 1.6, 1.8], fontsize=TICK_SIZE)
    # 3rd: figure properties
    fig.set_size_inches(*size_of_fig)  # set ratio
    plt.legend(prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper left", ncol=2)
    fig.savefig("./figures/" + 'opt_hbw.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
