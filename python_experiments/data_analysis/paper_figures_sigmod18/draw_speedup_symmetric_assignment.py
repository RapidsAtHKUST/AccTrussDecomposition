import matplotlib.pyplot as plt
import numpy as np

from config import *

from my_utils import *

# data set abbreviation dictionary
data_names = get_name_dict()

# figure parameters
FIG_SIZE_MULTIPLE = (32, 4)
LABEL_SIZE = 22
TICK_SIZE = 22
LEGEND_SIZE = 22

knl_pivot_tag = 'scan-xp-avx512-galloping-single'
knl_hybrid_tag = 'scan-xp-avx512-hybrid'
knl_bitmap_tag = 'scan-xp-naive-bitvec-hbw-2d'
cpu_pivot_tag = 'scan-xp-avx2-galloping-single'
cpu_hybrid_tag = 'scan-xp-avx2-hybrid'
cpu_bitmap_tag = 'scan-xp-naive-bitvec-2d'

algorithm_name_dict = get_algorithm_name_dict()

algorithm_tag_lst = [knl_pivot_tag, knl_hybrid_tag, knl_bitmap_tag,
                     cpu_pivot_tag, cpu_hybrid_tag, cpu_bitmap_tag]


def get_algorithm_elapsed_time_lst(tag):
    # webbase, it, twitter, friendster
    if tag is knl_pivot_tag:
        return [14.064 / 7.586, 47.745 / 24.937, 213.958 / 106.729, 166.707 / 85.046]
    elif tag is knl_hybrid_tag:
        return [5.408 / 3.155, 17.719 / 10.703, 105.202 / 52.631, 64.574 / 33.807]
    elif tag is knl_bitmap_tag:
        return [183.319 / 4.013, 2485.193 / 12.262, 4150.409 / 68.673, 235.450 / 92.625]
    elif tag is cpu_pivot_tag:
        return [13.081 / 7.754, 44.341 / 20.410, 425.223 / 191.299, 342.786 / 177.837]
    elif tag is cpu_hybrid_tag:
        return [10.663 / 5.729, 28.448 / 13.289, 296.707 / 142.323, 252.604 / 120.813]
    elif tag is cpu_bitmap_tag:
        return [120.813 / 5.440, 2307.952 / 13.934, 5512.336 / 81.623, 346.212 / 138.408]


def draw_overview_elapsed_time():
    with open('../config.json') as ifs:
        my_config_dict = json.load(ifs)[knl_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]
    g_names = map(lambda data: data_names[data], data_set_lst)

    size_of_fig = (FIG_SIZE_MULTIPLE[0] / 2, FIG_SIZE_MULTIPLE[1])
    fig, ax = plt.subplots()
    N = len(g_names)

    # indent lst
    width = 0.12
    ind = 1.3 * np.arange(N)  # the x locations for the groups
    indent_lst = map(lambda idx: ind + idx * width, range(6))
    for idx in xrange(3, 6):
        indent_lst[idx] += 0.75 * width

    # other lst
    hatch_lst = [
        # '', '|||',
        '.', "**", '',
        # 'O',
        '\\', 'x', '--', '++', '//', 'o']
    label_lst = [algorithm_name_dict[exec_name] for exec_name in algorithm_tag_lst]
    color_lst = [
        # '#fe01b1', 'orange',
        'green', 'red', 'black',
        # '#ceb301',
        'm', 'brown', 'k',
        'purple', 'blue', 'gray']

    # 1st: bars
    for idx, tag in enumerate(algorithm_tag_lst):
        ax.bar(indent_lst[idx], get_algorithm_elapsed_time_lst(tag), width,
               hatch=hatch_lst[idx], label=label_lst[idx],
               edgecolor=color_lst[idx], fill=None)

    # 2nd: x and y's ticks and labels
    ax.set_xticks(ind + 3 * width)
    ax.set_xticklabels(map(lambda name: name + ' (KNL, CPU)', g_names), fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    plt.yscale('log')
    ax.set_ylabel("Speedup", fontsize=LABEL_SIZE)
    plt.yticks(fontsize=TICK_SIZE)

    plt.ylim(10 ** 0, 4 * 10 ** 3)

    # 3rd: figure properties
    fig.set_size_inches(*size_of_fig)  # set ratio
    plt.legend(prop={'size': LEGEND_SIZE - 2, "weight": "bold"}, loc="upper left", ncol=3)
    fig.savefig("./figures/" + 'opt_symmetric_assignment.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
