import json

import matplotlib
import matplotlib.pyplot as plt
import numpy as np

from data_analysis.figures_icde19.general_config import *
from data_analysis.figures_icde19.parse_overall.parse_gpu_results import varying_gpu_tag, summary_tag, \
    off_tc_tag, off_cpu_iep_tag, off_gpu_iep_tag, off_iep_total_tag, config_lst
from data_analysis.figures_icde19.parse_overall.parse_support_initialization import si_dir
from data_analysis.util.read_file_utils import *
from data_analysis.vis.vis_util import *

FIG_SIZE_MULTIPLE = (16, 4.5)

data_set_lst = ['webgraph_eu', 'webgraph_it', 'webgraph_twitter']
cuda_off_load_opt = 'cuda-pkt-offload-opt'
cuda_off_load = 'cuda-pkt-offload'
cuda_off_load_shrink = 'cuda-pkt-shrink-all-opt'


def get_opt_cpu_tc_lst():
    with open('{}/{}/{}'.format('parse_overall', si_dir, 'pkt-eval-tc-wp.json')) as ifs:
        tc_wp_si = json.load(ifs)
    return [tc_wp_si[data]['40'] for data in data_set_lst]


def get_opt_cpu_iep_lst(cpu_exp_dir='exp-2019-10-04-eid'):
    with open('parse_overall/varying_cpu/{}/{}.json'.format(cpu_exp_dir, 'pkt-bmpf')) as ifs:
        bmpf_dict = json.load(ifs)
    with open('parse_overall/varying_cpu/{}/{}.json'.format(cpu_exp_dir, 'pkt-inter-shrink')) as ifs:
        bmpf_idx_dict = json.load(ifs)

    def get_single_iep_time(data_dict, data):
        return sum([data_dict[data][tag] for tag in ["Sync Time", "Shrink Time", "Scan Time", "Proc Time"]])

    return [min(get_single_iep_time(bmpf_dict, data), get_single_iep_time(bmpf_idx_dict, data)) for data in
            data_set_lst]


def get_off_iep_with_tag(tag, exec_name, lst):
    with open('parse_overall/{}/{}/{}.json'.format(varying_gpu_tag, config_lst[0], exec_name)) as ifs:
        cuda_offload_opt_dict = json.load(ifs)
    return [cuda_offload_opt_dict[data][summary_tag][tag] for data in lst]


def get_off_tc():
    return get_off_iep_with_tag(off_tc_tag, cuda_off_load_opt, data_set_lst)


bar_lst_lst = [
    get_opt_cpu_tc_lst(),  # OPT-CPU-TC
    get_off_tc(),  # OFF-TC
    get_opt_cpu_iep_lst(),  # OPT-CPU-IEP
    get_off_iep_with_tag(off_iep_total_tag, cuda_off_load_shrink, data_set_lst),
    get_off_iep_with_tag(off_iep_total_tag, cuda_off_load_opt, data_set_lst),
    get_off_iep_with_tag(off_cpu_iep_tag, cuda_off_load_opt, data_set_lst),
    get_off_iep_with_tag(off_gpu_iep_tag, cuda_off_load_opt, data_set_lst),
]

bar_legend_lst = ['\\textbf{' + name + '}' for name in
                  ['OPT-TC', 'OFF-TC', 'OPT-IEP', 'OFF-EIEP',
                   'OFF-RIEP-Total',
                   'OFF-RIEP-CPU',
                   'OFF-RIEP-GPU']]

dataset_abbr_lst = ['WE', 'WI', 'TW']

for idx, bar_lst in enumerate(bar_lst_lst):
    print(bar_legend_lst[idx], bar_lst)


def draw_bars(bar_lst_lst, legend_label_lst, x_tick_label_lst, x_label_name, fig_folder, file_name):
    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax = plt.subplots()

    assert len(bar_lst_lst) > 0
    N = len(bar_lst_lst[0])
    assert N == len(x_tick_label_lst)

    # indent lst
    width = 1.1 / len(legend_label_lst)
    ind = 1.3 * np.arange(N)  # the x locations for the groups
    indent_lst = [ind + idx * width for idx in range(len(bar_lst_lst))]

    for i in range(2, 5):
        indent_lst[i] += 0.3 * width
    for i in range(5, 7):
        indent_lst[i] += 0.6 * width

    # 1st: bars
    for idx, bar_lst in enumerate(bar_lst_lst):
        my_bar = ax.bar(indent_lst[idx], bar_lst, width, hatch=hatch_lst[idx], label=legend_label_lst[idx],
                        edgecolor=color_lst[idx], fill=False)
        autolabel(ax, my_bar, roration=45, fontsize=20)

    # 2nd: x and y's ticks and labels
    ax.set_xticks(ind + 3.3 * width)
    ax.set_xticklabels(x_tick_label_lst, fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    plt.yscale('log')
    ax.set_ylabel("Time (seconds)", fontsize=LABEL_SIZE)
    plt.yticks(fontsize=TICK_SIZE)

    max_val = max([max(lst) for lst in bar_lst_lst])
    min_val = min([min(list(filter(lambda v: v != 0, lst)) + [max_val]) for lst in bar_lst_lst])

    plt.ylim(min_val / 3, max_val * (10 ** 3) * 40)
    plt.yticks(list(filter(lambda v: v > min_val / 10, [10 ** i for i in range(-1, 5, 1)])))

    ax.set_xlabel(x_label_name, fontsize=LABEL_SIZE)

    # 3rd: figure properties
    fig.set_size_inches(*size_of_fig)  # set ratio
    plt.legend(legend_label_lst,
               prop={'size': LEGEND_SIZE - 3, "weight": "bold"}, loc="upper left", ncol=4)

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
                      '../data-pdf/icde20', 'OFF-opts' + suffix)


        draw_varying_algorithm()
