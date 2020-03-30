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
cpu_merge_vec_speedup_tag = 'scan-xp-avx2-merge'
cpu_pivot_vec_speedup_tag = 'scan-xp-avx2-galloping-single'
cpu_hybrid_vec_speedup_tag = 'scan-xp-avx2-hybrid'

algorithm_name_dict = get_algorithm_name_dict()

algorithm_tag_lst = [knl_merge_vec_speedup_tag, knl_pivot_vec_speedup_tag, knl_hybrid_vec_speedup_tag,
                     cpu_merge_vec_speedup_tag, cpu_pivot_vec_speedup_tag, cpu_hybrid_vec_speedup_tag]


def get_vec_speedup_lst(tag):
    # webbase, it, twitter, friendster
    if tag is knl_merge_vec_speedup_tag:
        return [108.588 / 23.023, 1552.777 / 447.884, 1657.740 / 596.186, 102.128 / 36.497]
    elif tag is knl_pivot_vec_speedup_tag:
        return [9.553 / 7.607, 16.624 / 24.964, 126.365 / 107.086, 101.877 / 85.496]
    elif tag is knl_hybrid_vec_speedup_tag:
        return [9.553 / 3.161, 29.302 / 10.715, 163.715 / 52.818, 102.348 / 36.781]
    elif tag is cpu_merge_vec_speedup_tag:
        return [44.098 / 10.353, 654.587 / 271.643, 729.220 / 231.872, 123.374 / 70.959]
    elif tag is cpu_pivot_vec_speedup_tag:
        return [3.907 / 5.143, 8.844 / 13.304, 139.445 / 115.762, 132.740 / 105.790]
    elif tag is cpu_hybrid_vec_speedup_tag:
        return [5.278 / 3.002, 14.704 / 7.936, 143.317 / 77.098, 124.063 / 70.929]
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
    width = 0.12
    ind = 1.1 * np.arange(N)  # the x locations for the groups
    indent_lst = map(lambda idx: ind + idx * width, range(6))
    for idx in xrange(3, 6):
        indent_lst[idx] += 0.75 * width

    # other lst
    hatch_lst = [
        # '',
        '|||', '.', "**",
        # '',
        'O', '\\', 'x', '--', '++', '//', 'o']
    label_lst = [algorithm_name_dict[exec_name] for exec_name in algorithm_tag_lst]
    color_lst = [
        # '#fe01b1',
        'orange', 'green', 'red',
        # 'black',
        '#ceb301', 'm', 'brown', 'k',
        'purple', 'blue', 'gray']

    # 1st: bars
    for idx, tag in enumerate(algorithm_tag_lst):
        ax.bar(indent_lst[idx], get_vec_speedup_lst(tag), width, hatch=hatch_lst[idx], label=label_lst[idx],
               edgecolor=color_lst[idx],
               fill=False)

    # 2nd: x and y's ticks and labels
    ax.set_xticks(ind + 3 * width)
    ax.set_xticklabels(map(lambda name: name + ' (KNL, CPU)', g_names), fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    # plt.yscale('log')
    ax.set_ylabel("Vectorization Speedup", fontsize=LABEL_SIZE-2)
    plt.yticks(fontsize=TICK_SIZE)

    plt.ylim(0, 7)
    plt.yticks([1, 2, 3, 4, 5], fontsize=TICK_SIZE)
    # 3rd: figure properties
    fig.set_size_inches(*size_of_fig)  # set ratio
    plt.legend(prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper right", ncol=2)
    fig.savefig("./figures/" + 'opt_vectorization.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
