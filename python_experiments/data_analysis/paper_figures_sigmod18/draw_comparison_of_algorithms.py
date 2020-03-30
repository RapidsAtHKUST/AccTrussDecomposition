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

scan_xp_tag = 'scan-xp-baseline-avx512-merge'
knl_merge_tag = 'scan-xp-avx512-merge'
knl_pivot_tag = 'scan-xp-avx512-galloping-single'
knl_hybrid_tag = 'scan-xp-avx512-hybrid'
knl_bitmap_tag = 'scan-xp-naive-bitvec-hbw-2d'
cpu_merge_tag = 'scan-xp-avx2-merge'
cpu_pivot_tag = 'scan-xp-avx2-galloping-single'
cpu_hybrid_tag = 'scan-xp-avx2-hybrid'
cpu_bitmap_tag = 'scan-xp-naive-bitvec-2d'
m_gpu_warp_tag = 'scan-xp-cuda-4-8-multi-gpu-multi-pass-dynamic-lb'
m_gpu_kernel_tag = 'scan-xp-cuda-hybrid-kernels-multi-gpu-multi-pass-dynamic-lb'
m_gpu_bitmap_tag = 'scan-xp-cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass-dynamic-lb'

algorithm_name_dict = get_algorithm_name_dict()

algorithm_tag_lst = [scan_xp_tag, knl_merge_tag, knl_pivot_tag, knl_hybrid_tag, knl_bitmap_tag,
                     cpu_merge_tag, cpu_pivot_tag, cpu_hybrid_tag, cpu_bitmap_tag,
                     m_gpu_warp_tag, m_gpu_kernel_tag, m_gpu_bitmap_tag
                     ]


def get_algorithm_elapsed_time_lst(tag):
    # webbase, it, twitter, friendster
    if tag is scan_xp_tag:
        return [36.704, 606.223, 1012.900, 64.413]
    elif tag is knl_merge_tag:
        return [23.023, 447.884, 596.186, 36.497]
    elif tag is knl_pivot_tag:
        return [7.607, 24.964, 107.086, 85.496]
    elif tag is knl_hybrid_tag:
        return [3.161, 10.715, 52.818, 36.781]
    elif tag is knl_bitmap_tag:
        return [4.054, 12.260, 68.768, 118.551]
    elif tag is cpu_merge_tag:
        return [10.353, 271.643, 231.872, 70.959]
    elif tag is cpu_pivot_tag:
        return [5.143, 13.304, 115.762, 105.790]
    elif tag is cpu_hybrid_tag:
        return [3.002, 7.936, 77.098, 70.929]
    elif tag is cpu_bitmap_tag:
        return [3.400, 6.873, 40.630, 67.385]
    elif tag is m_gpu_warp_tag:
        return [5.074, 10.087, min(534.534, 517.84), 25.925]  # second is the static scheduling
    elif tag is m_gpu_kernel_tag:
        return [5.027, 8.852, min(158.843, 97.94), 29.066]  # second is the reversed degree graph
    elif tag is m_gpu_bitmap_tag:
        return [min(7.421, 2.797), min(4.021, 5.03), min(7.988, 11.031), min(44.096, 59.541)]
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
    width = 0.08
    ind = 1.3 * np.arange(N)  # the x locations for the groups
    indent_lst = map(lambda idx: ind + idx * width, range(12))
    for idx in xrange(5, 12):
        indent_lst[idx] += 0.75 * width
    for idx in xrange(9, 12):
        indent_lst[idx] += 0.75 * width

    # other lst
    hatch_lst = ['', '|||', '.', "**", '', 'O', '\\', 'x', '--', '++', '//', 'o']
    label_lst = [algorithm_name_dict[exec_name] for exec_name in algorithm_tag_lst]
    color_lst = ['#fe01b1', 'orange', 'green', 'red', 'black',
                 '#ceb301', 'm', 'brown', 'k',
                 'purple', 'blue', 'gray']

    # 1st: bars
    for idx, tag in enumerate(algorithm_tag_lst):
        ax.bar(indent_lst[idx], get_algorithm_elapsed_time_lst(tag), width, hatch=hatch_lst[idx], label=label_lst[idx],
               edgecolor=color_lst[idx],
               color=color_lst[idx] if tag in [scan_xp_tag] else None,
               fill=True if tag in [scan_xp_tag] else False)

    # 2nd: x and y's ticks and labels
    # ax.set_xticks(ind + 5 * width)
    ax.set_xticks(ind + 6.25 * width)
    ax.set_xticklabels(map(lambda name: name + ' (KNL, CPU, mGPU)', g_names), fontsize=LABEL_SIZE)
    # ax.set_xticklabels(map(lambda name: name + ' (KNL, CPU)', g_names), fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    plt.yscale('log')
    ax.set_ylabel("Elapsed Time (seconds)", fontsize=LABEL_SIZE-2)
    plt.yticks(fontsize=TICK_SIZE)

    plt.ylim(10 ** 0, 10 ** 4 * 8)

    # 3rd: figure properties
    fig.set_size_inches(*size_of_fig)  # set ratio
    # plt.legend(prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper left", ncol=5)
    plt.legend(prop={'size': LEGEND_SIZE - 2, "weight": "bold"}, loc="upper left", ncol=6)
    # fig.savefig("./figures/" + 'cut_overall_cmp_elapsed_time_real_world.pdf', bbox_inches='tight', dpi=300)
    fig.savefig("./figures/" + 'overall_cmp_elapsed_time_real_world.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
