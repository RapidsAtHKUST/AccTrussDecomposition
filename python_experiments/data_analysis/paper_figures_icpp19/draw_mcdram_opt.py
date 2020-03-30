import matplotlib.pyplot as plt
import numpy as np

from config import *

from data_analysis.paper_figures_icpp19.my_utils import *

# data set abbreviation dictionary
data_names = get_name_dict()
algorithm_name_dict = get_algorithm_name_dict()

# figure parameters
FIG_SIZE_MULTIPLE = (16, 4)
LABEL_SIZE = 22
TICK_SIZE = 22
LEGEND_SIZE = 22

knl_hybrid_avx512_tag = 'KNL-MPS'

knl_mps_hbw_flat = 'MPS-Flat'
knl_mps_hbw_cache = 'MPS-Cache'
knl_bmp_hbw_flat = 'BMP-Flat'
knl_bmp_hbw_cache = 'BMP-Cache'

knl_draw_algorithm_tag_lst = [
    knl_hybrid_tag, knl_mps_hbw_cache, knl_mps_hbw_flat,
    knl_bitmap_tag, knl_bmp_hbw_cache, knl_bmp_hbw_flat]


def get_algorithm_elapsed_time_lst(tag):
    # twitter, friendster
    if tag is knl_hybrid_tag:
        return [83.067, 60.149]
    elif tag is knl_bitmap_tag:
        return [82.134, 115.740]
    elif tag is knl_mps_hbw_flat:
        return [52.652, 33.852]
    elif tag is knl_mps_hbw_cache:
        return [53.333, 34.731]
    elif tag is knl_bmp_hbw_flat:
        return [68.519, 92.655]
    elif tag is knl_bmp_hbw_cache:
        return [69.526, 93.201]


def draw_overview_elapsed_time():
    with open('../config.json') as ifs:
        my_config_dict = json.load(ifs)[knl_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]
    g_names = list(filter(lambda name: name in ['TW', 'FR'], map(lambda data: data_names[data], data_set_lst)))

    def draw_time_bars(fig_name, draw_algorithm_tag_lst, ylim_lst):
        size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
        fig, ax = plt.subplots()
        N = len(g_names)
        # indent lst
        width = 0.16
        ind = 1.3 * np.arange(N)  # the x locations for the groups
        indent_lst = list(map(lambda idx: ind + idx * width, range(12)))
        for i in range(3, 7):
            indent_lst[i] += 0.2 * width
        # other lst
        hatch_lst = [
            '-',
            '+',
            'x',
            "*", '\\', '//', 'o']
        label_lst = [algorithm_name_dict[exec_name] for exec_name in draw_algorithm_tag_lst]
        color_lst = [
            # '#fe01b1',
            'red',
            'k',
            'blue',
            'purple',
            'gray',
            'brown'
            # 'green',
            # 'black',
            # '#ceb301', 'm', 'brown',
        ]

        # 1st: bars
        for idx, tag in enumerate(draw_algorithm_tag_lst):
            ax.bar(indent_lst[idx], get_algorithm_elapsed_time_lst(tag), width, hatch=hatch_lst[idx],
                   label=label_lst[idx], edgecolor=color_lst[idx], fill=False)

        # 2nd: x and y's ticks and labels
        ax.set_xticks(ind + 2.6 * width)
        ax.set_xticklabels(map(lambda name: name, g_names), fontsize=LABEL_SIZE)
        plt.xticks(fontsize=TICK_SIZE)

        # plt.yscale('log')
        ax.set_ylabel("\\textbf{Elapsed Time (seconds)}", fontsize=LABEL_SIZE)
        ax.set_xlabel("\\textbf{Dataset}", fontsize=LABEL_SIZE)
        plt.yticks([0, 25, 50, 75, 100, 125, 150], fontsize=TICK_SIZE)

        plt.ylim(ylim_lst[0], ylim_lst[1])

        # 3rd: figure properties
        fig.set_size_inches(*size_of_fig)  # set ratio
        plt.legend(['\\textbf{' + name + '}' for name in label_lst],
                   prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper left", ncol=2,
                   )
        fig.savefig("./figures/" + fig_name + '.png', bbox_inches='tight', dpi=300)

    draw_time_bars(fig_name='exp-knl-mcdram', draw_algorithm_tag_lst=knl_draw_algorithm_tag_lst,
                   ylim_lst=[0, 10 ** 2 * 2])


if __name__ == '__main__':
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif', serif='cm10')
    plt.rcParams['font.weight'] = 'bold'

    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
