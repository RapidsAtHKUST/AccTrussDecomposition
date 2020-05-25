import matplotlib
import matplotlib.pyplot as plt
import numpy as np

from data_analysis.figures_icde19.parse_overall.parse_support_initialization import si_dir
from data_analysis.util.read_file_utils import *
from data_analysis.vis.vis_util import *
from data_analysis.figures_icde19.general_config import *
from data_analysis.figures_icde19.parse_overall.parse_gpu_results import off_total_tag
from data_analysis.figures_icde19.opt_gpu import get_off_iep_with_tag, cuda_off_load_opt, cuda_off_load
import json

FIG_SIZE_MULTIPLE = (16, 4.5)

data_set_lst = [
    'snap_orkut', 'webgraph_uk', 'webgraph_webbase',
    'webgraph_it', 'webgraph_eu', 'webgraph_twitter'
]


def get_legacy_cpu_lst(cpu_exp_dir='exp-2019-10-05-best'):
    with open('parse_overall/varying_cpu/{}/{}.json'.format(cpu_exp_dir, 'pkt-legacy')) as ifs:
        legacy_pkt_dict = json.load(ifs)

    def get_total_time(data_dict, data):
        return sum([data_dict[data][tag] for tag in ["Sync Time", "Shrink Time", "Scan Time", "Proc Time",
                                                     "Tri time"]])

    return [get_total_time(legacy_pkt_dict, data) for data in data_set_lst]


def get_opt_cpu_lst(cpu_exp_dir='exp-2019-10-05-best'):
    with open('parse_overall/varying_cpu/{}/{}.json'.format(cpu_exp_dir, 'pkt-bmpf')) as ifs:
        bmpf_dict = json.load(ifs)
    with open('parse_overall/varying_cpu/{}/{}.json'.format(cpu_exp_dir, 'pkt-inter-shrink')) as ifs:
        bmpf_idx_dict = json.load(ifs)

    cpu_exp_dir2 = 'exp-2019-10-04-eid'
    with open('parse_overall/varying_cpu/{}/{}.json'.format(cpu_exp_dir2, 'pkt-bmpf')) as ifs:
        bmpf_dict2 = json.load(ifs)
    with open('parse_overall/varying_cpu/{}/{}.json'.format(cpu_exp_dir2, 'pkt-inter-shrink')) as ifs:
        bmpf_idx_dict2 = json.load(ifs)
    with open('{}/{}/{}'.format('parse_overall', si_dir, 'pkt-eval-tc-wp.json')) as ifs:
        tc_wp_si = json.load(ifs)

    def get_single_iep_time(data_dict, data):
        return sum([data_dict[data][tag] for tag in ["Sync Time", "Shrink Time", "Scan Time", "Proc Time"]])

    def get_total_time(data_dict, data):
        if data in ['webgraph_eu', 'webgraph_it', 'webgraph_twitter']:
            tmp_time = tc_wp_si[data]['40'] + min(get_single_iep_time(bmpf_dict2, data),
                                                  get_single_iep_time(bmpf_idx_dict2, data))
        else:
            tmp_time = 999999999999
        total_time = sum([data_dict[data][tag] for tag in ["Sync Time", "Shrink Time", "Scan Time", "Proc Time",
                                                           "Tri time"]])
        return min(total_time, tmp_time)

    return [min(get_total_time(bmpf_dict, data),
                get_total_time(bmpf_idx_dict, data)) for data in data_set_lst]


def min_lst(iter1: list, iter2: list):
    assert len(iter1) == len(iter2)
    return [min(iter1[i], iter2[i]) for i in range(len(iter1))]


def get_hidx(name):
    with open('parse_others/h-idx/{}-2300.json'.format(name)) as ifs:
        hidx_dict = json.load(ifs)
    return [hidx_dict[data] for data in data_set_lst]


def get_msp(name='ktruss-msp'):
    with open('parse_others/msp/{}.json'.format(name)) as ifs:
        hidx_dict = json.load(ifs)
    return [hidx_dict[data] for data in data_set_lst]


bar_lst_lst = [
    get_hidx('hidx-org'),
    get_hidx('pnd'),
    get_msp(),
    get_legacy_cpu_lst(),
    get_opt_cpu_lst(),
    min_lst(get_off_iep_with_tag(off_total_tag, cuda_off_load, data_set_lst),
            get_off_iep_with_tag(off_total_tag, cuda_off_load_opt, data_set_lst))
]

bar_legend_lst = ['\\textbf{' + name + '}' for name in
                  ['H-IDX', 'H-IDX+', 'MSP', 'PKT', 'OPT-CPU', 'OPT-HPU']]
dataset_abbr_lst = ['OR', 'WU', 'WB', 'WI', 'WE', 'TW']

print('\n\n')
for idx, bar_lst in enumerate(bar_lst_lst):
    print(bar_legend_lst[idx], bar_lst)


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
    for i in range(2, 6):
        indent_lst[i] += 0.5 * width

    # 1st: bars
    for idx, bar_lst in enumerate(bar_lst_lst):
        my_bar = ax.bar(indent_lst[idx], bar_lst, width,
                        hatch=hatch_lst[idx], label=legend_label_lst[idx],
                        edgecolor=color_lst[idx], fill=False
                        )
        # value_format = "{:.1%}"  # displaying values as percentage with one fractional digit
        autolabel(ax, my_bar, roration=45, fontsize=18)

    # 2nd: x and y's ticks and labels
    ax.set_xticks(ind + 2.7 * width)
    ax.set_xticklabels(x_tick_label_lst, fontsize=LABEL_SIZE)
    plt.xticks(fontsize=TICK_SIZE)

    plt.yscale('log')
    ax.set_ylabel("Time (seconds)", fontsize=LABEL_SIZE)
    plt.yticks(fontsize=TICK_SIZE)

    max_val = max([max(lst) for lst in bar_lst_lst])
    min_val = min([min(list(filter(lambda v: v != 0, lst)) + [max_val]) for lst in bar_lst_lst])

    plt.ylim(min_val / 20, max_val * (10 ** 3) * 14)
    plt.yticks(list(filter(lambda v: v > min_val / 10, [10 ** (-1), 10 ** (0), 10 ** (1), 10 ** (2), 10 ** (3),
                                                        10 ** (4)])))

    ax.set_xlabel(x_label_name, fontsize=LABEL_SIZE)

    # 3rd: figure properties
    fig.set_size_inches(*size_of_fig)  # set ratio
    ncols = len(legend_label_lst) if len(legend_label_lst) < 7 else int((len(legend_label_lst) + 1) / 2)
    plt.legend(legend_label_lst,
               prop={'size': LEGEND_SIZE - 2, "weight": "bold"}, loc="upper left", ncol=3)

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
                      '../data-pdf/icde20', 'overview_end_to_end_time' + suffix, is_update_indent=False)


        draw_varying_algorithm()
