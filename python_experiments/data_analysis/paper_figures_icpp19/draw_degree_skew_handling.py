import matplotlib.pyplot as plt
import numpy as np

from config import *
from data_analysis.paper_figures_icpp19.my_utils import *

# data set abbreviation dictionary
data_names = get_name_dict()
algorithm_name_dict = get_algorithm_name_dict()

# figure parameters
FIG_SIZE_MULTIPLE = (8, 4)
LABEL_SIZE = 22
TICK_SIZE = 22
LEGEND_SIZE = 22

cpu_draw_algorithm_tag_lst = [cpu_merge_tag, cpu_hybrid_tag, cpu_bitmap_tag]
knl_draw_algorithm_tag_lst = [knl_merge_tag, knl_hybrid_tag, knl_bitmap_tag]


def get_algorithm_elapsed_time_lst(tag):
    # twitter, friendster
    if tag is knl_merge_tag:
        return [3388.080 * 32, 349.998 * 32]
    elif tag is knl_hybrid_tag:
        return [476.388 * 32, 350.752 * 32]
    elif tag is knl_bitmap_tag:
        return [3704.287, 2397.829 * 4]
    elif tag is cpu_merge_tag:
        return [10032.646 * 2, 4528.821]
    elif tag is cpu_hybrid_tag:
        return [5527.204, 4919.126]
    elif tag is cpu_bitmap_tag:
        return [996.245, 1837.179]


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
        width = 0.3
        ind = 1.3 * np.arange(N)  # the x locations for the groups
        indent_lst = list(map(lambda idx: ind + idx * width, range(12)))

        # other lst
        hatch_lst = ['', '||', '.', "**", '', 'O', '\\', 'x', '--', '++', '//', 'o']
        label_lst = [algorithm_name_dict[exec_name] for exec_name in draw_algorithm_tag_lst]
        color_lst = ['#fe01b1', 'orange', 'green', 'red', 'black',
                     '#ceb301', 'm', 'brown', 'k',
                     'purple', 'blue', 'gray']

        # 1st: bars
        for idx, tag in enumerate(draw_algorithm_tag_lst):
            ax.bar(indent_lst[idx], get_algorithm_elapsed_time_lst(tag), width, hatch=hatch_lst[idx],
                   label=label_lst[idx], edgecolor=color_lst[idx], fill=False)

        # 2nd: x and y's ticks and labels
        ax.set_xticks(ind + width)
        ax.set_xticklabels(map(lambda name: name, g_names), fontsize=LABEL_SIZE)
        plt.xticks(fontsize=TICK_SIZE)

        plt.yscale('log')
        ax.set_ylabel("\\textbf{Elapsed Time (seconds)}", fontsize=LABEL_SIZE)
        ax.set_xlabel("\\textbf{Dataset}", fontsize=LABEL_SIZE)
        plt.yticks(fontsize=TICK_SIZE)
        plt.ylim(ylim_lst[0], ylim_lst[1])

        # 3rd: figure properties
        fig.set_size_inches(*size_of_fig)  # set ratio
        plt.legend(['\\textbf{' + name + '}' for name in label_lst], prop={'size': LEGEND_SIZE, "weight": "bold"},
                   loc="upper right", ncol=2)
        fig.savefig("./figures/" + fig_name + '.png', bbox_inches='tight', dpi=300)

    draw_time_bars(fig_name='exp-cpu-deg-skew', draw_algorithm_tag_lst=cpu_draw_algorithm_tag_lst,
                   ylim_lst=[10 ** 2 * 5, 10 ** 5])
    draw_time_bars(fig_name='exp-knl-deg-skew', draw_algorithm_tag_lst=knl_draw_algorithm_tag_lst,
                   ylim_lst=[10 ** 3, 10 ** 6])


if __name__ == '__main__':
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif', serif='cm10')

    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
