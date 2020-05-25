import os

import matplotlib
import matplotlib.pyplot as plt
from data_analysis.figures_icde19.general_config import *
from data_analysis.figures_icde19.parse_overall.parse_gpu23_pre_processing import gpu23_pp_dir
from data_analysis.figures_icde19.parse_overall.parse_scalability_iep import scalability_iep_tag
from data_analysis.figures_icde19.parse_overall.parse_support_initialization import si_dir
from data_analysis.aec_algorithm.local_config.ktruss_exec_tags import *
import json

# figure parameters
FIG_SIZE_MULTIPLE = (8, 4.5)

label_lst = ['\\textbf{' + name + '}' for name in ['PP', 'SI', 'GC', 'SU', 'EF']]
data_names = {
    'webgraph_twitter': 'TW',
    'webgraph_eu': 'WE'
}


def get_speedup_lst(lst):
    return ['%.3lf' % (lst[0] / lst[i]) for i in range(len(lst))]


def get_pp_lst(data):
    with open('{}/{}/{}'.format('parse_overall', gpu23_pp_dir, 'pkt-eid-parallel.json')) as ifs:
        pp_p_dict = json.load(ifs)
    return [pp_p_dict[data][str(i)] for i in [1, 2, 4, 8, 16, 32, 40]]


def get_iep_lst_lst(data):
    with open('{}/{}/{}/{}'.format('parse_overall', scalability_iep_tag, 'exp-2019-10-04-eid',
                                   'pkt-inter-shrink.json')) as ifs:
        iep_dict = json.load(ifs)
    return [
        [iep_dict[data][str(i)][shrink_time_tag] for i in [1, 2, 4, 8, 16, 32, 40]],
        [iep_dict[data][str(i)][proc_time_tag] for i in [1, 2, 4, 8, 16, 32, 40]],
        [iep_dict[data][str(i)][scan_time_tag] for i in [1, 2, 4, 8, 16, 32, 40]]
    ]


def get_tc_lst(data):
    with open('{}/{}/{}'.format('parse_overall', si_dir, 'pkt-eval-tc-wp.json')) as ifs:
        tc_dict = json.load(ifs)
    return [tc_dict[data][str(i)] for i in [1, 2, 4, 8, 16, 32, 40]]


tw_lst_lst = [get_pp_lst('webgraph_twitter'),  # gpu23
              get_tc_lst('webgraph_twitter'),  # ustgpu2
              ] + get_iep_lst_lst('webgraph_twitter')
we_lst_lst = [get_pp_lst('webgraph_eu'),  # gpu23
              get_tc_lst('webgraph_eu'),  # ustgpu2
              ] + get_iep_lst_lst('webgraph_eu')

for lst_lst in [we_lst_lst, tw_lst_lst]:
    for idx, lst in enumerate(lst_lst):
        print(label_lst[idx], lst)
    print()


def draw_overview_elapsed_time(bar_lst_lst, name, fig_folder='../data-pdf/icde20'):
    thread_lst = [1, 2, 4, 8, 16, 32, 64]
    x_lst = range(len(thread_lst))
    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax = plt.subplots()

    for idx, lst in enumerate(bar_lst_lst):
        ax.plot(x_lst, lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')

    for tick in ax.yaxis.get_major_ticks():
        tick.label.set_fontsize(TICK_SIZE)
    for tick in ax.xaxis.get_major_ticks():
        tick.label.set_fontsize(TICK_SIZE)
    ax.set_xlabel('Number of Threads', fontsize=LABEL_SIZE)
    ax.set_yscale('log')

    ax.set_ylabel("Time (seconds)", fontsize=LABEL_SIZE)
    max_val = max([max(lst) for lst in bar_lst_lst])
    min_val = min([min(list(filter(lambda v: v != 0, lst)) + [max_val]) for lst in bar_lst_lst])
    plt.ylim(4, max_val * (10 ** 2) * 4)
    plt.yticks(list(filter(lambda v: v > min_val / 10, [10 ** (-1), 10 ** (0), 10 ** (1), 10 ** (2), 10 ** (3),
                                                        10 ** (4)])))

    ax.set_xticks(x_lst)
    ax.set_xticklabels(thread_lst)
    fig.set_size_inches(*size_of_fig)  # set ratio

    ax.legend(label_lst, prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper right", ncol=3)

    os.system('mkdir -p ' + fig_folder)
    fig.savefig(fig_folder + os.sep +
                name + '-scalability' + '.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    # matplotlib.rc('pdf', fonttype=42)
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')

    draw_overview_elapsed_time(tw_lst_lst, 'TW')
    draw_overview_elapsed_time(we_lst_lst, 'WE')

    print('WE:\n')
    for idx, lst in enumerate(we_lst_lst):
        print(label_lst[idx], get_speedup_lst(lst))

    print('\nTW:\n')
    for idx, lst in enumerate(tw_lst_lst):
        print(label_lst[idx], get_speedup_lst(lst))
