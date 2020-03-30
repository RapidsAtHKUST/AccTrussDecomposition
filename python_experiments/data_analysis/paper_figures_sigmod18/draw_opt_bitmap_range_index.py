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

knl_bitmap_speedup_tag = 'scan-xp-naive-bitvec-hbw-2d'
cpu_bitmap_tag = 'scan-xp-naive-bitvec-2d'
m_gpu_bitmap_tag = 'scan-xp-cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass-dynamic-lb'
algorithm_name_dict = get_algorithm_name_dict()

algorithm_tag_lst = [
    knl_bitmap_speedup_tag, cpu_bitmap_tag,
    m_gpu_bitmap_tag
]


def get_range_index_speedup_lst(tag):
    # webbase, it, twitter, friendster
    if tag is knl_bitmap_speedup_tag:
        return [4.054 / 5.687, 12.260 / 17.133, 68.768 / 81.611, 400.210 / 118.551]
    elif tag is cpu_bitmap_tag:
        return [3.400 / 4.043, 6.873 / 9.178, 41.706 / 40.630, 126.163 / 67.385]
    elif tag is m_gpu_bitmap_tag:
        return [(2.797) / 4.1, (4.03) / 4.021, (11.031) / 7.988, (59.541) / 44.096]
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
    width = 0.3
    ind = 1.2 * np.arange(N)  # the x locations for the groups
    indent_lst = map(lambda idx: ind + idx * width, range(4))

    # other lst
    hatch_lst = [
        # '',
        # '|||', '.', "**",
        '',
        # 'O', '\\', 'x',
        '--',
        # '++', '//',
        'o']
    label_lst = [algorithm_name_dict[exec_name] for exec_name in algorithm_tag_lst]
    color_lst = [
        # '#fe01b1',
        # 'orange', 'green', 'red',
        'black',
        # '#ceb301', 'm', 'brown',
        'k',
        # 'purple', 'blue',
        'gray']

    # 1st: bars
    for idx, tag in enumerate(algorithm_tag_lst):
        ax.bar(indent_lst[idx], get_range_index_speedup_lst(tag), width, hatch=hatch_lst[idx], label=label_lst[idx],
               edgecolor=color_lst[idx],
               fill=False)

    # 2nd: x and y's ticks and labels
    ax.set_xticks(ind + 2 * width)
    ax.set_xticklabels(map(lambda name: name, g_names), fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    # plt.yscale('log')
    ax.set_ylabel("Range-Index Speedup", fontsize=LABEL_SIZE - 2)
    plt.yticks(fontsize=TICK_SIZE)

    plt.ylim(0.5, 3.6)
    plt.yticks(fontsize=TICK_SIZE)
    # 3rd: figure properties
    fig.set_size_inches(*size_of_fig)  # set ratio
    plt.legend(prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper left", ncol=2)
    # fig.savefig("./figures/" + 'cut_opt_bitmap_range_index.pdf', bbox_inches='tight', dpi=300)
    fig.savefig("./figures/" + 'opt_bitmap_range_index.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
