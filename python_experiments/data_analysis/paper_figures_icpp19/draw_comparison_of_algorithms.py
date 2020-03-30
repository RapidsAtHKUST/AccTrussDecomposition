import matplotlib.pyplot as plt
import numpy as np

from config import *

from data_analysis.paper_figures_icpp19.my_utils import *

# data set abbreviation dictionary
data_names = get_name_dict()

# figure parameters
FIG_SIZE_MULTIPLE = (32, 4)
LABEL_SIZE = 22
TICK_SIZE = 22
LEGEND_SIZE = 22

knl_hybrid_tag = 'scan-xp-avx512-hybrid'
knl_bitmap_tag = 'scan-xp-naive-bitvec-hbw-2d'
cpu_hybrid_tag = 'scan-xp-avx2-hybrid'
cpu_bitmap_tag = 'scan-xp-naive-bitvec-2d'
m_gpu_kernel_tag = 'scan-xp-cuda-hybrid-kernels-multi-gpu-multi-pass-dynamic-lb'
m_gpu_bitmap_tag = 'scan-xp-cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass-dynamic-lb'

algorithm_name_dict = get_algorithm_name_dict()

algorithm_tag_lst = [
    cpu_hybrid_tag, cpu_bitmap_tag,
    knl_hybrid_tag, knl_bitmap_tag,
    m_gpu_kernel_tag, m_gpu_bitmap_tag
]


def get_algorithm_elapsed_time_lst(tag):
    # lj, orkut, webbase, it, twitter, friendster
    if tag is knl_hybrid_tag:
        return [0.261, 1.756,
                # 3.161,
                10.715, 52.7, 33.9]  # done    # best
    elif tag is knl_bitmap_tag:
        return [0.503, 3.676,
                # 4.378,
                12.260, 68.5, 92.6]  # done
    elif tag is cpu_hybrid_tag:
        return [0.391, 3.014,
                # 3.122,
                8.668, 70.3, 68.3]  # done
    elif tag is cpu_bitmap_tag:
        return [0.367, 2.258,
                # 3.4,
                7.585, 40.4, 63.8]  # done # best
    elif tag is m_gpu_kernel_tag:
        return [0.765, 4.764,
                # 13.046,
                48.047, 193.285, 106.983]  # done
    elif tag is m_gpu_bitmap_tag:
        return [0.446, 1.494,
                # 7.462,
                6.111, 21.505, 48.675]  # done # best


def draw_overview_elapsed_time():
    with open('../config.json') as ifs:
        my_config_dict = json.load(ifs)[knl_tag]
    # data_set_lst = filter(lambda name: 'webbase' not in name, my_config_dict[data_set_lst_tag])
    data_set_lst = ['snap_livejournal', 'snap_orkut', 'webgraph_it', 'webgraph_twitter', 'snap_friendster']
    g_names = list(map(lambda data: data_names[data], data_set_lst))

    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax = plt.subplots()
    N = len(g_names)

    # indent lst
    width = 0.18
    ind = 1.5 * np.arange(N)  # the x locations for the groups
    indent_lst = list(map(lambda idx: ind + idx * width, range(6)))
    for i in range(2, 4):
        indent_lst[i] += 0.3 * width
    for i in range(4, 6):
        indent_lst[i] += 0.6 * width
    # other lst
    hatch_lst = ['', '||', '.', "//", 'O', '\\', 'x', '--', '++', '//', 'o']

    color_lst = ['#fe01b1', 'orange', 'green', 'red', 'black',
                 '#ceb301', 'm', 'brown', 'k',
                 'purple', 'blue', 'gray']
    label_lst = ['CPU-MPS', 'CPU-BMP', 'KNL-MPS', 'KNL-BMP', 'GPU-MPS', 'GPU-BMP']

    # 1st: bars
    def autolabel(rects):
        """
        Attach a text label above each bar displaying its height
        """
        for rect in rects:
            height = rect.get_height()
            ax.text(rect.get_x() + rect.get_width() / 2., 1.05 * height,
                    '%.1f' % float(height) if height > 5 else '%.2f' % float(height),
                    ha='center', va='bottom', fontsize=20)

    for idx, tag in enumerate(algorithm_tag_lst):
        my_bar = ax.bar(indent_lst[idx], get_algorithm_elapsed_time_lst(tag), width, hatch=hatch_lst[idx],
                        label=label_lst[idx],
                        edgecolor=color_lst[idx], fill=False)
        value_format = "{:.1%}"  # displaying values as percentage with one fractional digit
        autolabel(my_bar)
    # 2nd: x and y's ticks and labels
    # ax.set_xticks(ind + 5 * width)
    ax.set_xticks(ind + 2.8 * width)
    ax.set_xticklabels(map(lambda name: name, g_names), fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    plt.yscale('log')
    ax.set_ylabel("\\textbf{Elapsed Time (seconds)}", fontsize=LABEL_SIZE)
    plt.yticks(fontsize=TICK_SIZE)

    plt.ylim(10 ** (-1), 10 ** 3 * 8)
    plt.yticks([10 ** (-1), 10 ** (0), 10 ** (1), 10 ** (2)])
    ax.set_xlabel("\\textbf{Dataset}", fontsize=LABEL_SIZE)

    # 3rd: figure properties
    fig.set_size_inches(*size_of_fig)  # set ratio
    plt.legend(['\\textbf{' + name + '}' for name in label_lst],
               prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper left", ncol=6)
    fig.savefig("./figures/" + 'overall_cmp_of_bests.png', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif', serif='cm10')

    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
