import os

import matplotlib
import matplotlib.pyplot as plt
from data_analysis.figures_icde19.general_config import *
import json

FIG_SIZE_MULTIPLE = (8, 4.5)
data_set_lst = [
    "s22-16",
    "s23-16",
    "s24-16",
    "s25-16",
    "s26-16",
    "s27-16",
    "s28-16",
    "s29-16"
]

t_num = '60'


def get_cpu_dict():
    with open('{}/{}/{}'.format('parse_overall', 'varying_cpu',
                                'exp-2020-04-09-cpu-s22-s29-pkt-inter-shrink.json')) as ifs:
        my_dict = json.load(ifs)
    return my_dict


def get_gpu_dict():
    with open('{}/{}/{}'.format('parse_overall', 'varying_gpu',
                                'exp-2020-04-09-offload-s22-s28-cuda-pkt-offload.json')) as ifs:
        my_dict = json.load(ifs)
    return my_dict


def get_cpu_tc_time_lst():
    my_dict = get_cpu_dict()
    return [my_dict[data][t_num]['Tri time'] for data in data_set_lst]


def get_cpu_iep_time_lst():
    my_dict = get_cpu_dict()
    return [my_dict[data][t_num]['Total computation cost'] - my_dict[data][t_num]['Tri time']
            for data in data_set_lst]


def get_gpu_tc_time_lst():
    my_dict = get_gpu_dict()
    res = [my_dict[data][t_num]['Tri time'] for data in data_set_lst]
    res[-1] = 0
    res[-2] = 0
    return res


def get_gpu_iep_time_lst():
    my_dict = get_gpu_dict()
    res = [
        map_non_to_zero(my_dict[data][t_num]['Offloading Comp Time']) +
        map_non_to_zero(my_dict[data][t_num]['Total computation cost']) -
        map_non_to_zero(my_dict[data][t_num]['Tri time'])
        for data in data_set_lst]
    res[-1] = 0
    return res


def get_gpu_iep_cpu_part_time_lst():
    my_dict = get_gpu_dict()
    res = [
        map_non_to_zero(my_dict[data][t_num]['Total computation cost']) -
        map_non_to_zero(my_dict[data][t_num]['Tri time'])
        for data in data_set_lst]
    res[-1] = 0
    return res


def get_gpu_iep_gpu_part_time_lst():
    my_dict = get_gpu_dict()
    res = [map_non_to_zero(my_dict[data][t_num]['Offloading Comp Time'])
           for data in data_set_lst]
    res[-1] = 0
    return res


def map_non_to_zero(e):
    return 0 if e is None else e


def map_zero_to_none(lst):
    return [e if e != 0 else None for e in lst]


def draw_varying_e_tc(bar_lst_lst, label_lst, name, fig_folder='../data-pdf/icde20'):
    e_lst = ['$2^{}$'.format('{' + str(i + 4) + '}') for i in range(22, 30, 1)]
    x_lst = range(len(e_lst))
    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax = plt.subplots()

    for idx, lst in enumerate(bar_lst_lst):
        ax.plot(x_lst, lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')

    for tick in ax.yaxis.get_major_ticks():
        tick.label.set_fontsize(TICK_SIZE)
    for tick in ax.xaxis.get_major_ticks():
        tick.label.set_fontsize(TICK_SIZE)
    ax.set_xlabel('|E|', fontsize=LABEL_SIZE)
    ax.set_yscale('log')
    ax.set_ylabel("Time (seconds)", fontsize=LABEL_SIZE)
    max_val = max([max(filter(lambda v: v is not None and v != 0, lst)) for lst in bar_lst_lst])
    min_val = min([min(list(filter(lambda v: v is not None and v != 0, lst)) + [max_val]) for lst in bar_lst_lst])

    plt.ylim(4, max_val * (10 ** 2) * 4)
    plt.yticks(list(filter(lambda v: v > min_val / 10, [10 ** (0), 10 ** (1), 10 ** (2), 10 ** (3),
                                                        10 ** (4)])))

    ax.set_xticks(x_lst)
    ax.set_xticklabels(e_lst)
    fig.set_size_inches(*size_of_fig)  # set ratio

    ax.legend(label_lst, prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper right", ncol=2)

    os.system('mkdir -p ' + fig_folder)
    fig.savefig(fig_folder + os.sep +
                name + '-varying-e' + '.pdf', bbox_inches='tight', dpi=300)


def draw_varying_e_iep(bar_lst_lst, label_lst, name, fig_folder='../data-pdf/icde20'):
    e_lst = ['$2^{}$'.format('{' + str(i + 4) + '}') for i in range(22, 30, 1)]
    x_lst = range(len(e_lst))
    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig, ax = plt.subplots()

    for idx, lst in enumerate(bar_lst_lst):
        ax.plot(x_lst, lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')

    for tick in ax.yaxis.get_major_ticks():
        tick.label.set_fontsize(TICK_SIZE)
    for tick in ax.xaxis.get_major_ticks():
        tick.label.set_fontsize(TICK_SIZE)
    ax.set_xlabel('|E|', fontsize=LABEL_SIZE)
    ax.set_yscale('log')
    ax.set_ylabel("Time (seconds)", fontsize=LABEL_SIZE)
    max_val = max([max(filter(lambda v: v is not None and v != 0, lst)) for lst in bar_lst_lst])
    min_val = min([min(list(filter(lambda v: v is not None and v != 0, lst)) + [max_val]) for lst in bar_lst_lst])

    plt.ylim(4, max_val * (10 ** 2) * 4)
    plt.yticks(list(filter(lambda v: v > min_val / 10, [10 ** (-1), 10 ** (0), 10 ** (1), 10 ** (2), 10 ** (3),
                                                        10 ** (4)])))

    ax.set_xticks(x_lst)
    ax.set_xticklabels(e_lst)
    fig.set_size_inches(*size_of_fig)  # set ratio

    ax.legend(label_lst, prop={'size': LEGEND_SIZE - 6, "weight": "bold"}, loc="upper right", ncol=2)

    os.system('mkdir -p ' + fig_folder)
    fig.savefig(fig_folder + os.sep +
                name + '-varying-e' + '.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    # matplotlib.rc('pdf', fonttype=42)
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')

    bar_lst_lst = []
    # draw_varying_e_tc()
    tc_cpu_lst = get_cpu_tc_time_lst()
    tc_gpu_lst = map_zero_to_none(get_gpu_tc_time_lst())
    for x, y in zip(tc_gpu_lst, tc_cpu_lst):
        if x is not None and y is not None:
            print(y / x)
    draw_varying_e_tc(bar_lst_lst=[tc_cpu_lst, tc_gpu_lst],
                      label_lst=['\\textbf{' + name + '}' for name in ['OPT-TC', 'OFF-TC']], name='tc')

    cpu_iep_lst = get_cpu_iep_time_lst()
    gpu_iep_lst = map_zero_to_none(get_gpu_iep_time_lst())
    gpu_iep_lst_cpu_part = map_zero_to_none(get_gpu_iep_cpu_part_time_lst())
    gpu_iep_lst_gpu_part = map_zero_to_none(get_gpu_iep_gpu_part_time_lst())
    draw_varying_e_iep(bar_lst_lst=[cpu_iep_lst, gpu_iep_lst, gpu_iep_lst_cpu_part, gpu_iep_lst_gpu_part],
                       label_lst=['\\textbf{' + name + '}' for name in
                                  ['OPT-IEP', 'OFF-RIEP-Total', 'OFF-RIEP-CPU', 'OFF-RIEP-GPU']],
                       name='iep')

    print(cpu_iep_lst)
    print(gpu_iep_lst)
    print(gpu_iep_lst_cpu_part)
    print(gpu_iep_lst_gpu_part)
    for i in range(7):
        print((cpu_iep_lst[i] - gpu_iep_lst_cpu_part[i]) / gpu_iep_lst_gpu_part[i])
