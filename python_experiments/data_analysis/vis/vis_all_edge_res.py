import matplotlib.pyplot as plt
import numpy as np

from config import *
from data_analysis.util.read_file_utils import *
from data_analysis.vis.vis_util import *

import json

# figure parameters
FIG_SIZE_MULTIPLE = (32, 4.5)
LABEL_SIZE = 18
TICK_SIZE = 18
LEGEND_SIZE = 18

all_edge_cnt_exec_lst = [
    "scan-xp-naive-merge",
    "scan-xp-avx2-merge",
    "scan-xp-tetzank-avx2-asm",
    "scan-xp-avx2-lemire",
    "scan-xp-naive-hybrid",
    "scan-xp-avx2-hybrid",
    "scan-xp-sse-han-bmiss-sttni",
    "scan-xp-sse-han-qfilter",
    "scan-xp-sse-emptyheaded-layout-uint",
    "scan-xp-sse-emptyheaded-layout-hybrid",
    "scan-xp-sse-han-bsr-qfilter",
    "scan-xp-sse-han-bsr-scalar-merge",
    "scan-xp-sse-han-bsr-scalar-galloping",
    "scan-xp-avx2-roaring",
    "scan-xp-naive-bitvec",
    "scan-xp-naive-bitvec-2d",
    "scan-xp-naive-bitvec-adv",
    "scan-xp-naive-bitvec-op",
    "scan-xp-compact-forward-avx2-lemire",
    "scan-xp-compact-forward-qfilter",
    "scan-xp-compact-forward-bmp",
    # "scan-xp-compact-forward-avx2-asm-tetzank",
    "scan-xp-cf-hybrid"
    # "scan-xp-compact-forward-bmiss-sttni"
]
reorder_method_lst = ['org', 'gro', 'deg', 'kcore']


def get_all_edge_cnt_dict():
    with open('../data-json/gpu23/03-21-gro-exp.json') as ifs:
        return json.load(ifs)


def draw_bars(bar_lst_lst, legend_label_lst, x_tick_label_lst, x_label_name, fig_folder, file_name,
              is_update_indent=False):
    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax = plt.subplots()

    assert len(legend_label_lst) == len(bar_lst_lst)
    assert len(bar_lst_lst) > 0
    N = len(bar_lst_lst[0])
    assert N == len(x_tick_label_lst)

    # indent lst
    width = 1.0 / len(legend_label_lst)
    ind = 1.5 * np.arange(N)  # the x locations for the groups
    indent_lst = list(map(lambda idx: ind + idx * width, range(len(bar_lst_lst))))

    if is_update_indent:
        for i in range(8, 14):
            indent_lst[i] += 1 * width
        for i in range(14, 16):
            indent_lst[i] += 2 * width
        for i in range(16, 22):
            indent_lst[i] += 3 * width
    # other lst
    hatch_lst = ['', '||', '.', "//", 'O', '\\', 'x', '--', '++', '//', 'o', '', '||', '.', "//", "*", 'o', '\\', 'x',
                 '--', '', '||', '.', ]

    color_lst = ['#fe01b1', 'orange', 'green', 'red', 'black',
                 '#ceb301', 'm', 'brown', 'k',
                 'purple', 'blue', 'gray', 'magenta', 'pink', 'grey', 'cyan', 'green', 'yellow', 'm', 'brown', 'k',
                 '#fe01b1', 'orange', 'green', ]

    # 1st: bars

    for idx, bar_lst in enumerate(bar_lst_lst):
        my_bar = ax.bar(indent_lst[idx], bar_lst, width,
                        hatch=hatch_lst[idx], label=legend_label_lst[idx],
                        edgecolor=color_lst[idx], fill=False
                        )
        value_format = "{:.1%}"  # displaying values as percentage with one fractional digit
        autolabel(ax, my_bar)

    # 2nd: x and y's ticks and labels
    ax.set_xticks(ind + len(legend_label_lst) / 2 * width)
    ax.set_xticklabels(x_tick_label_lst, fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    plt.yscale('log')
    ax.set_ylabel("Elapsed Time (seconds)", fontsize=LABEL_SIZE)
    plt.yticks(fontsize=TICK_SIZE)

    max_val = max([max(lst) for lst in bar_lst_lst])
    min_val = min([min(list(filter(lambda v: v != 0, lst)) + [max_val]) for lst in bar_lst_lst])
    ax.text(0.9, 0.8, 'Max: %.1f, Min: %.1f, Gap: %.1f' % (float(max_val), float(min_val), float(max_val / min_val)),
            horizontalalignment='center', verticalalignment='center',
            transform=ax.transAxes, fontsize=25)
    plt.ylim(min_val / 10, max_val * (10 ** 3))
    plt.yticks(filter(lambda v: v > min_val / 10, [10 ** (-1), 10 ** (0), 10 ** (1), 10 ** (2), 10 ** (3)]))

    ax.set_xlabel(x_label_name, fontsize=LABEL_SIZE)

    # 3rd: figure properties
    fig.set_size_inches(*size_of_fig)  # set ratio
    plt.legend(legend_label_lst,
               prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper left",
               ncol=len(legend_label_lst) if len(legend_label_lst) < 7 else (len(legend_label_lst) + 1) / 2)

    plt.tight_layout()

    os.system('mkdir -p ' + fig_folder)
    fig.savefig(os.sep.join([fig_folder, file_name]), bbox_inches='tight', dpi=300)
    plt.close()


def option_time_tag_wrapper(obj):
    return obj[time_tag] if obj is not None else 0


# fixed algorithms as legends
def get_varying_ordering_time_lst(dataset, algo_name):
    return [
        option_time_tag_wrapper(
            stat_dict[os.sep.join([dataset, reorder_method])]['40'][algo_name][all_edge_cnc_comp_tag])
        for reorder_method in reorder_method_lst]


def get_varying_algorithm_time_lst(dataset, reorder_method):
    return [option_time_tag_wrapper(
        stat_dict[os.sep.join([dataset, reorder_method])]['40'][algo_name][all_edge_cnc_comp_tag])
        for algo_name in all_edge_cnt_exec_lst]


if __name__ == '__main__':
    # plt.rc('text', usetex=True)
    # plt.rc('font', family='serif', serif='cm10')
    stat_dict = get_all_edge_cnt_dict()
    my_config_dict = get_config_dict(gpu23_tag, '../..')
    datasets = my_config_dict[data_set_lst_tag]


    def draw_varying_ordering():
        for data_set in datasets:
            bar_lst_lst = [get_varying_ordering_time_lst(dataset=data_set, algo_name=algorithm_name)
                           for algorithm_name in all_edge_cnt_exec_lst]
            legend_lst = [all_edge_cnt_exec_alias_dict[algorithm_name] for algorithm_name in all_edge_cnt_exec_lst]
            ax_lst = [method.upper() for method in reorder_method_lst]
            ax_lst = [f + '\n' + s for f, s in zip(ax_lst, statistics_select_col(bar_lst_lst))]

            draw_bars(bar_lst_lst, legend_lst, ax_lst,
                      'Reordering Method', '../data-pdf/all-edge-cnt/varying-ordering',
                      data_set.replace('.', 'dot') + '.pdf', is_update_indent=True)


    def draw_varying_algorithm():
        for data_set in datasets:
            bar_lst_lst = [get_varying_algorithm_time_lst(dataset=data_set, reorder_method=reorder_method)
                           for reorder_method in reorder_method_lst]
            legend_lst = [reorder_method.upper() for reorder_method in reorder_method_lst]
            ax_lst = [all_edge_cnt_exec_alias_dict[algorithm_name] for algorithm_name in all_edge_cnt_exec_lst]
            ax_lst = [f + '\n' + s for f, s in zip(ax_lst, statistics_select_col(bar_lst_lst))]

            draw_bars(bar_lst_lst, legend_lst, ax_lst,
                      'Algorithm', '../data-pdf/all-edge-cnt/varying-algorithm',
                      data_set.replace('.', 'dot') + '.pdf', is_update_indent=False)


    draw_varying_ordering()
    draw_varying_algorithm()
