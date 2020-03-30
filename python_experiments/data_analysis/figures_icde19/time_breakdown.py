import matplotlib.pyplot as plt
import numpy as np

from data_analysis.util.read_file_utils import *
from data_analysis.vis.vis_util import *

FIG_SIZE_MULTIPLE = (16, 4.5)
# FIG_SIZE_MULTIPLE = (32, 4.5)
LABEL_SIZE = 24
TICK_SIZE = 24
LEGEND_SIZE = 24

# 'WE' and 'TW'
bar_lst_lst = [
    [746.306, 256.111, ],
    [598.467, 2233.894, ],
    [84.191, 43.873]
]

bar_legend_lst = ['Support Initialization',
                  'Triangle Peeling',
                  'Edge Filtering']
dataset_abbr_lst = ['European Web Graph', 'Twitter Graph']


def draw_bars(bar_lst_lst, legend_label_lst, x_tick_label_lst, x_label_name,
              fig_folder, file_name, is_update_indent=False):
    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax = plt.subplots()

    assert len(legend_label_lst) == len(bar_lst_lst)
    assert len(bar_lst_lst) > 0
    N = len(bar_lst_lst[0])
    assert N == len(x_tick_label_lst)

    # indent lst
    width = 1.0 / len(legend_label_lst)
    ind = 1.3 * np.arange(N)  # the x locations for the groups
    indent_lst = [ind + idx * width for idx in range(len(bar_lst_lst))]

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
        autolabel(ax, my_bar, roration=0)

    # 2nd: x and y's ticks and labels
    ax.set_xticks(ind + len(legend_label_lst) / 2 * width)
    ax.set_xticklabels(x_tick_label_lst, fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    plt.yscale('log')
    ax.set_ylabel("Time (seconds)", fontsize=LABEL_SIZE)
    plt.yticks(fontsize=TICK_SIZE)

    max_val = max([max(lst) for lst in bar_lst_lst])
    min_val = min([min(list(filter(lambda v: v != 0, lst)) + [max_val]) for lst in bar_lst_lst])

    plt.ylim(min_val / 10, max_val * (10 ** 2))
    plt.yticks(list(filter(lambda v: v > min_val / 10, [10 ** (-1), 10 ** (0), 10 ** (1), 10 ** (2), 10 ** (3)])))

    ax.set_xlabel(x_label_name, fontsize=LABEL_SIZE)

    # 3rd: figure properties
    fig.set_size_inches(*size_of_fig)  # set ratio
    ncols = 2
    plt.legend(legend_label_lst,
               prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper left", ncol=ncols)

    plt.tight_layout()

    os.system('mkdir -p ' + fig_folder)
    fig.savefig(os.sep.join([fig_folder, file_name]), bbox_inches='tight', dpi=300)
    plt.close()


def option_time_tag_wrapper(obj):
    return obj[time_tag] if obj is not None else 0


if __name__ == '__main__':
    for suffix in ['.pdf']:
        def draw_varying_algorithm():
            draw_bars(bar_lst_lst, bar_legend_lst, dataset_abbr_lst, 'Dataset',
                      '../data-pdf/icde20', 'time-breakdown' + suffix, is_update_indent=False)


        draw_varying_algorithm()
