import matplotlib.pyplot as plt
import numpy as np

from data_analysis.figures_icde19.general_config import *
from data_analysis.util.read_file_utils import *
from data_analysis.vis.vis_util import *
import json

FIG_SIZE_MULTIPLE = (16, 4.5)


def get_input_lst_lst():
    bar_exec_name_lst = ['pkt-inter-legacy', 'pkt-inter-handle-skew',
                         'pkt-vm', 'pkt-gc', 'pkt-es',
                         'pkt-dstcp',
                         'pkt-bmpf', 'pkt-inter-shrink']

    lst_lst = []
    for exec_name in bar_exec_name_lst:
        with open('parse_overall/varying_cpu/{}/{}.json'.format('exp-2019-10-04-eid', exec_name)) as ifs:
            data_dict = json.load(ifs)
            lst_lst.append([sum([data_dict[data][tag] for tag in [
                "Sync Time", "Shrink Time", "Scan Time", "Proc Time"
            ]]) for data in ['webgraph_eu', 'webgraph_it', 'webgraph_twitter']])
    return lst_lst


bar_lst_lst = get_input_lst_lst()

bar_legend_lst = ['PKT-IEP', '+PSM', '+VM', '+GC', '+ES', '+DSTCP', '+BMPF', '+IDX']
dataset_abbr_lst = ['WE', 'WI', 'TW']


def draw_bars(bar_lst_lst, legend_label_lst, x_tick_label_lst, x_label_name,
              fig_folder, file_name, is_update_indent=False):
    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax = plt.subplots()

    assert len(legend_label_lst) == len(bar_lst_lst)
    assert len(bar_lst_lst) > 0
    N = len(bar_lst_lst[0])
    assert N == len(x_tick_label_lst)

    # indent lst
    width = 1.1 / len(legend_label_lst)
    ind = 1.3 * np.arange(N)  # the x locations for the groups
    indent_lst = [ind + idx * width for idx in range(len(bar_lst_lst))]

    # 1st: bars
    for idx, bar_lst in enumerate(bar_lst_lst):
        my_bar = ax.bar(indent_lst[idx], bar_lst, width, hatch=hatch_lst[idx], label=legend_label_lst[idx],
                        edgecolor=color_lst[idx], fill=False)
        autolabel(ax, my_bar, roration=45, fontsize=20)

    # 2nd: x and y's ticks and labels
    ax.set_xticks(ind + 3.5 * width)
    ax.set_xticklabels(x_tick_label_lst, fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    plt.yscale('log')
    ax.set_ylabel("Time (seconds)", fontsize=LABEL_SIZE)
    plt.yticks(fontsize=TICK_SIZE)

    max_val = max([max(lst) for lst in bar_lst_lst])
    min_val = min([min(list(filter(lambda v: v != 0, lst)) + [max_val]) for lst in bar_lst_lst])
    plt.ylim(min_val / 10, max_val * (10 ** 3) * 5)
    plt.yticks(list(filter(lambda v: v > min_val / 10, [10 ** i for i in range(-1, 5, 1)])))

    ax.set_xlabel(x_label_name, fontsize=LABEL_SIZE)

    # 3rd: figure properties
    fig.set_size_inches(*size_of_fig)  # set ratio
    plt.legend(legend_label_lst,
               prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper left", ncol=4)

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
                      '../data-pdf/icde20', 'IEP-opts' + suffix, is_update_indent=False)


        draw_varying_algorithm()
