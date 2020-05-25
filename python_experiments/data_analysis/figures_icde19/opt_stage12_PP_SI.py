import matplotlib
import matplotlib.pyplot as plt
import numpy as np

from data_analysis.figures_icde19.general_config import *
from data_analysis.util.read_file_utils import *
from data_analysis.vis.vis_util import *
from data_analysis.figures_icde19.parse_overall.parse_gpu23_pre_processing import gpu23_pp_dir
from data_analysis.figures_icde19.parse_overall.parse_support_initialization import si_dir
import json

FIG_SIZE_MULTIPLE = (16, 4.5)


def get_lst_lst_preprocessing():
    lst_lst = []
    with open('{}/{}/{}'.format('parse_overall', gpu23_pp_dir, 'pkt-eid.json')) as ifs:
        pkt_pp_dict = json.load(ifs)
        print(pkt_pp_dict)
    with open('{}/{}/{}'.format('parse_overall', gpu23_pp_dir, 'pkt-eid-parallel.json')) as ifs:
        pp_p_dict = json.load(ifs)
        print(pp_p_dict)
    data_set_lst = ['webgraph_eu', 'webgraph_it', 'webgraph_twitter']

    lst_lst.append([pkt_pp_dict[data]['40'] for data in data_set_lst])
    lst_lst.append([pp_p_dict[data]['1'] for data in data_set_lst])
    lst_lst.append([pp_p_dict[data]['40'] for data in data_set_lst])
    return lst_lst


def get_lst_lst_support_init():
    lst_lst = []
    with open('{}/{}/{}'.format('parse_overall', si_dir, 'pkt-eval-tc-baseline.json')) as ifs:
        baseline_si = json.load(ifs)
        print(baseline_si)
    with open('{}/{}/{}'.format('parse_overall', si_dir, 'pkt-eval-tc-dtc.json')) as ifs:
        tc_dtc_si = json.load(ifs)
        print(tc_dtc_si)
    with open('{}/{}/{}'.format('parse_overall', si_dir, 'pkt-eval-tc-wp.json')) as ifs:
        tc_wp_si = json.load(ifs)
        print(tc_wp_si)
    data_set_lst = ['webgraph_eu', 'webgraph_it', 'webgraph_twitter']
    lst_lst.append([baseline_si[data]['40'] for data in data_set_lst])
    lst_lst.append([tc_dtc_si[data]['40'] for data in data_set_lst])
    lst_lst.append([tc_wp_si[data]['40'] for data in data_set_lst])
    return lst_lst


bar_lst_lst = get_lst_lst_preprocessing() + get_lst_lst_support_init()

bar_legend_lst = ['\\textbf{' + name + '}' for name in
                  ['PKT-PP', 'PP-SEQ', 'PP+P', 'PKT-SI', 'SI+DTC', 'SI+DTC+WP']
                  ]
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

    for i in range(3, 6):
        indent_lst[i] += 0.4 * width

    # 1st: bars
    for idx, bar_lst in enumerate(bar_lst_lst):
        my_bar = ax.bar(indent_lst[idx], bar_lst, width, hatch=hatch_lst[idx], label=legend_label_lst[idx],
                        edgecolor=color_lst[idx], fill=False)
        autolabel(ax, my_bar, roration=45, fontsize=20)

    # 2nd: x and y's ticks and labels
    ax.set_xticks(ind + 2.7 * width)
    ax.set_xticklabels(x_tick_label_lst, fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    plt.yscale('log')
    ax.set_ylabel("Time (seconds)", fontsize=LABEL_SIZE)
    plt.yticks(fontsize=TICK_SIZE)

    max_val = max([max(lst) for lst in bar_lst_lst])
    min_val = min([min(list(filter(lambda v: v != 0, lst)) + [max_val]) for lst in bar_lst_lst])
    plt.ylim(min_val / 10, max_val * (10 ** 4) * 2)
    plt.yticks(list(filter(lambda v: v > min_val / 10, [10 ** i for i in range(-1, 5, 1)])))

    ax.set_xlabel(x_label_name, fontsize=LABEL_SIZE)

    # 3rd: figure properties
    fig.set_size_inches(*size_of_fig)  # set ratio
    plt.legend(legend_label_lst,
               prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper left", ncol=3)

    plt.tight_layout()

    os.system('mkdir -p ' + fig_folder)
    fig.savefig(os.sep.join([fig_folder, file_name]), bbox_inches='tight', dpi=300)
    plt.close()


def option_time_tag_wrapper(obj):
    return obj[time_tag] if obj is not None else 0


if __name__ == '__main__':
    # matplotlib.rc('pdf', fonttype=42)
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')

    for suffix in ['.pdf']:
        def draw_varying_algorithm():
            draw_bars(bar_lst_lst, bar_legend_lst, dataset_abbr_lst, 'Dataset',
                      '../data-pdf/icde20', 'PP-SI-opts' + suffix, is_update_indent=False)


        draw_varying_algorithm()
