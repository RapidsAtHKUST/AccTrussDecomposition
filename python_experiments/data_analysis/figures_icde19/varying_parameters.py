import os

import matplotlib
import matplotlib.pyplot as plt
from data_analysis.figures_icde19.general_config import *
import json

# figure parameters
FIG_SIZE_MULTIPLE = (8, 4.5)


def varying_wpt(fig_folder='../data-pdf/icde20'):
    with open('./play/varying_parameters/wpt.json') as ifs:
        data_dict = json.load(ifs)
        packed_lst = [eval(x.replace(',', '')) for x in data_dict['Packed#']]
        tc_time_lst = [eval(x.replace('s', '')) for x in data_dict['TC Time']]
    wpt_lst = [0, 8, 16, 24, 32, 40, 48, 56, 64]
    packed_lst = [None if packed_lst[i] == 0 else packed_lst[i] for i in wpt_lst]
    tc_time_lst = [tc_time_lst[i] for i in wpt_lst]
    x_lst = range(len(wpt_lst))

    fig, ax_time = plt.subplots()

    idx = 0
    ax_time.plot(x_lst, tc_time_lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')
    idx = 1
    ax_packed_v = ax_time.twinx()
    ax_packed_v.plot(x_lst, packed_lst, shape_lst[idx], color=color_lst[idx], markersize=16,
                     markerfacecolor='none')

    # Size
    ax_time.tick_params(labelsize=TICK_SIZE)
    ax_packed_v.tick_params(labelsize=TICK_SIZE)
    ax_time.set_xlabel('wpt', fontsize=LABEL_SIZE)
    # Log Scale
    ax_time.set_yscale('log')
    ax_packed_v.set_yscale('log')
    # Y-Labels
    ax_time.set_ylabel("Time (seconds)", fontsize=LABEL_SIZE)
    ax_packed_v.set_ylabel("Number", fontsize=LABEL_SIZE)
    # Y-Lim
    ax_time.set_ylim((1, 10 ** 2 * 8))
    ax_packed_v.set_ylim((10 ** 2, 10 ** 9))
    # X-Ticks
    ax_time.set_xticks(x_lst)
    ax_time.set_xticklabels(wpt_lst)
    # Legends
    ax_time.legend(['$\mathbf{T_{SI}}$'], prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper left", ncol=3)
    ax_packed_v.legend(['$\mathbf{|V_{WP}|}$'], prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper right", ncol=3)

    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig.set_size_inches(*size_of_fig)  # set ratio
    os.system('mkdir -p ' + fig_folder)
    fig.savefig(fig_folder + os.sep + 'varying-wpt' + '.pdf', bbox_inches='tight', dpi=300)


def varying_ct(fig_folder='../data-pdf/icde20'):
    with open('./play/varying_parameters/gc.json') as ifs:
        data_dict = json.load(ifs)
    ct_lst = [2, 4, 8, 16, 32, 64, 128, 256]
    x_lst = range(len(ct_lst))

    fig, ax_time = plt.subplots()

    iep_time_lst = [
        data_dict[str(ct)]['Shrink Time'] + data_dict[str(ct)]['Proc Time'] + data_dict[str(ct)]['Scan Time'] for ct in
        ct_lst]
    gc_time_lst = [data_dict[str(ct)]['Shrink Time'] for ct in ct_lst]
    su_time_lst = [data_dict[str(ct)]['Proc Time'] for ct in ct_lst]
    packed_lst = [data_dict[str(ct)]['# Shrinks'] for ct in ct_lst]
    print(iep_time_lst)
    print(su_time_lst)
    idx = 0
    ax_time.plot(x_lst, iep_time_lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')
    idx = 1
    ax_time.plot(x_lst, su_time_lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')
    idx = 2
    ax_time.plot(x_lst, gc_time_lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')

    idx = 3
    ax_packed_v = ax_time.twinx()
    ax_packed_v.plot(x_lst, packed_lst, shape_lst[idx], color=color_lst[idx], markersize=16,
                     markerfacecolor='none')

    # Size
    ax_time.tick_params(labelsize=TICK_SIZE)
    ax_packed_v.tick_params(labelsize=TICK_SIZE)
    ax_time.set_xlabel('ct', fontsize=LABEL_SIZE)
    # Log Scale
    ax_time.set_yscale('log')
    ax_packed_v.set_yscale('log')
    # Y-Labels
    ax_time.set_ylabel("Time (seconds)", fontsize=LABEL_SIZE)
    ax_packed_v.set_ylabel("Number", fontsize=LABEL_SIZE)
    # Y-Lim
    ax_time.set_ylim((0.1, 10 ** 4 * 8))
    ax_packed_v.set_ylim((1, 800))
    # X-Ticks
    ax_time.set_xticks(x_lst)
    ax_time.set_xticklabels(ct_lst)
    # Legends
    ax_time.legend(['$\mathbf{T_{IEP}}$', '$\mathbf{T_{SU}}$', '$\mathbf{T_{GC}}$'],
                   prop={'size': LEGEND_SIZE, "weight": "bold"},
                   loc="upper left", ncol=2,
                   columnspacing=0.5, handletextpad=0.2)
    ax_packed_v.legend(['$\mathbf{Num_{GC}}$'], prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper right", ncol=1)

    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig.set_size_inches(*size_of_fig)  # set ratio
    os.system('mkdir -p ' + fig_folder)
    fig.savefig(fig_folder + os.sep + 'varying-ct' + '.pdf', bbox_inches='tight', dpi=300)


def varying_ept(fig_folder='../data-pdf/icde20'):
    with open('./play/varying_parameters/ept.json') as ifs:
        data_dict = json.load(ifs)
    ept_lst = [1.25 * (10 ** 8) * (2 ** i) for i in range(9)]
    x_lst = range(len(ept_lst))

    fig, ax_time = plt.subplots()

    su_time_lst = [data_dict[str(x)]['Proc Time'] for x in ept_lst]
    tc_time_lst = [sum(data_dict[str(x)]['Time']) for x in ept_lst]
    tp_time_lst = [su_time_lst[i] - tc_time_lst[i] for i in range(len(ept_lst))]
    tc_num_lst = [len(data_dict[str(x)]['Time']) for x in ept_lst]
    print(su_time_lst)
    idx = 0
    ax_time.plot(x_lst, su_time_lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')
    idx = 1
    ax_time.plot(x_lst, tc_time_lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')
    idx = 2
    ax_time.plot(x_lst, tp_time_lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')

    idx = 3
    ax_packed_v = ax_time.twinx()
    ax_packed_v.plot(x_lst, tc_num_lst, shape_lst[idx], color=color_lst[idx], markersize=16,
                     markerfacecolor='none')

    # Size
    ax_time.tick_params(labelsize=TICK_SIZE)
    ax_packed_v.tick_params(labelsize=TICK_SIZE)
    ax_time.set_xlabel('ept (base: $1.25 \cdot 10^8$)', fontsize=LABEL_SIZE)
    # Log Scale
    # Y-Labels
    ax_time.set_ylabel("Time (seconds)", fontsize=LABEL_SIZE)
    ax_packed_v.set_ylabel("Number", fontsize=LABEL_SIZE)
    # Y-Lim
    ax_time.set_ylim((0, 250))

    ax_packed_v.set_ylim((0, 40))

    # X-Ticks
    ax_time.set_xticks(x_lst)
    ax_time.set_xticklabels([(2 ** i) for i in range(9)])
    # Legends
    ax_time.legend(['$\mathbf{T_{SU}}$', '$\mathbf{T_{TC}}$', '$\mathbf{T_{TP}}$'],
                   prop={'size': LEGEND_SIZE, "weight": "bold"},
                   loc="upper left", ncol=2,
                   columnspacing=0.5, handletextpad=0.2)
    ax_packed_v.legend(['$\mathbf{Num_{TC}}$'], prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper right", ncol=1)

    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig.set_size_inches(*size_of_fig)  # set ratio
    os.system('mkdir -p ' + fig_folder)
    fig.savefig(fig_folder + os.sep + 'varying-ept' + '.pdf', bbox_inches='tight', dpi=300)


def varying_rs(fig_folder='../data-pdf/icde20'):
    with open('./play/varying_parameters/rs.json') as ifs:
        data_dict = json.load(ifs)
    ct_lst = [1, 2, 4, 8, 16, 32, 64, 128, 256]
    x_lst = range(len(ct_lst))

    fig, ax_time = plt.subplots()

    iep_time_lst = [
        data_dict[str(ct)]['Shrink Time'] + data_dict[str(ct)]['Proc Time'] + data_dict[str(ct)]['Scan Time'] for ct in
        ct_lst]
    ef_time_lst = [data_dict[str(ct)]['Scan Time'] for ct in ct_lst]
    su_time_lst = [data_dict[str(ct)]['Proc Time'] for ct in ct_lst]
    print(iep_time_lst)
    print(su_time_lst)
    idx = 0
    ax_time.plot(x_lst, iep_time_lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')
    idx = 1
    ax_time.plot(x_lst, su_time_lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')
    idx = 2
    ax_time.plot(x_lst, ef_time_lst, shape_lst[idx], color=color_lst[idx], markersize=16, markerfacecolor='none')

    # Size
    ax_time.tick_params(labelsize=TICK_SIZE)
    ax_time.set_xlabel('rs', fontsize=LABEL_SIZE)
    # Log Scale
    # Y-Labels
    ax_time.set_ylabel("Time (seconds)", fontsize=LABEL_SIZE)
    # Y-Lim
    ax_time.set_ylim((0.1, 220))
    # X-Ticks
    ax_time.set_xticks(x_lst)
    ax_time.set_xticklabels(ct_lst)
    # Legends
    ax_time.legend(['$\mathbf{T_{IEP}}$', '$\mathbf{T_{SU}}$', '$\mathbf{T_{EF}}$'],
                   prop={'size': LEGEND_SIZE, "weight": "bold"},
                   loc="upper right")

    size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
    fig.set_size_inches(*size_of_fig)  # set ratio
    os.system('mkdir -p ' + fig_folder)
    fig.savefig(fig_folder + os.sep + 'varying-rs' + '.pdf', bbox_inches='tight', dpi=300)


if __name__ == '__main__':
    matplotlib.rc('pdf', fonttype=42)

    varying_wpt()
    varying_ct()
    varying_rs()
    varying_ept()
