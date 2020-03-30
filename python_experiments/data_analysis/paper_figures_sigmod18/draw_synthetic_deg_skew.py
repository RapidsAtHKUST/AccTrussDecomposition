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
knl_bitmap_tag = 'scan-xp-naive-bitvec-hbw-2d'

cpu_merge_vec_speedup_tag = 'scan-xp-avx2-merge'
cpu_pivot_vec_speedup_tag = 'scan-xp-avx2-galloping-single'
cpu_hybrid_vec_speedup_tag = 'scan-xp-avx2-hybrid'
cpu_bitmap_tag = 'scan-xp-naive-bitvec-2d'

algorithm_name_dict = get_algorithm_name_dict()

algorithm_tag_lst = [knl_merge_vec_speedup_tag, knl_pivot_vec_speedup_tag, knl_hybrid_vec_speedup_tag, knl_bitmap_tag,
                     cpu_merge_vec_speedup_tag, cpu_pivot_vec_speedup_tag, cpu_hybrid_vec_speedup_tag, cpu_bitmap_tag]


def get_speedup_lst_over_merge(tag):
    # 8*(10**5), 2*(10**5), 5*(10**4), 1.25*(10**4)
    if tag is knl_merge_vec_speedup_tag:
        return [1, 1, 1, 1]
    elif tag is knl_pivot_vec_speedup_tag:
        return [0.402 / 0.371, 4.815 / 1.393, 3.682 / 0.513, 308.728 / 10.239]
    elif tag is knl_hybrid_vec_speedup_tag:
        return [0.402 / 0.306, 4.815 / 1.333, 3.682 / 0.503, 308.728 / 10.822]
    elif tag is knl_bitmap_tag:
        return [0.402 / 0.150, 4.815 / 0.321, 3.682 / 0.094, 308.728 / 0.868]
    elif tag is cpu_merge_vec_speedup_tag:
        return [1, 1, 1, 1]
    elif tag is cpu_pivot_vec_speedup_tag:
        return [0.403 / 0.159, 4.234 / 0.491, 3.510 / 0.204, 117.771 / 3.300]
    elif tag is cpu_hybrid_vec_speedup_tag:
        return [0.403 / 0.184, 4.234 / 0.590, 3.510 / 0.217, 117.771 / 3.479]
    elif tag is cpu_bitmap_tag:
        return [0.403 / 0.067, 4.234 / 0.143, 3.510 / 0.043, 117.771 / 0.332]
    return [1, 1, 1, 1]


def draw_overview_elapsed_time():
    g_names = list(
        reversed(['$d_u = 8\\cdot 10^5$', '$d_u =  2\\cdot 10^5$', '$d_u = 5\\cdot 10^4$', '$d_u = 1.25\\cdot 10^4$']))

    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax = plt.subplots()
    N = len(g_names)

    # indent lst
    width = 0.08
    ind = 1.1 * np.arange(N)  # the x locations for the groups
    indent_lst = map(lambda idx: ind + idx * width, range(8))
    for idx in xrange(4, 8):
        indent_lst[idx] += 0.75 * width

    # other lst
    hatch_lst = [
        '',
        '|||', '.', "**",
        '',
        'O', '\\', 'x', '--', '++', '//', 'o']
    label_lst = [algorithm_name_dict[exec_name] for exec_name in algorithm_tag_lst]
    color_lst = [
        '#fe01b1',
        'orange', 'green', 'red',
        'black',
        '#ceb301', 'm', 'brown', 'k',
        'purple', 'blue', 'gray']

    # 1st: bars
    for idx, tag in enumerate(algorithm_tag_lst):
        ax.bar(indent_lst[idx], get_speedup_lst_over_merge(tag), width, hatch=hatch_lst[1:][idx], label=label_lst[idx],
               edgecolor=color_lst[1:][idx], fill=False)

    # 2nd: x and y's ticks and labels
    ax.set_xticks(ind + 3 * width)
    ax.set_xticklabels(map(lambda name: name, g_names), fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    ax.set_ylabel("Speedup over Merge", fontsize=LABEL_SIZE-2)
    plt.yticks(fontsize=TICK_SIZE)
    ax.set_yscale('log')
    plt.ylim(0.1, 40000)
    plt.yticks([1, 10, 100, 1000], fontsize=TICK_SIZE)
    # 3rd: figure properties)
    fig.set_size_inches(*size_of_fig)  # set ratio
    plt.legend(prop={'size': LEGEND_SIZE - 2, "weight": "bold"}, loc="upper left", ncol=4)
    fig.savefig("./figures/" + 'synthetic_deg.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
