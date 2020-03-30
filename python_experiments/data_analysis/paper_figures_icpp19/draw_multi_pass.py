import matplotlib.pyplot as plt
from data_analysis.paper_figures_icpp19.my_utils import *
from config import *


def get_name_dict():
    with open('config/data_names.json') as ifs:
        return eval(''.join(ifs.readlines()))


def get_algorithm_name_dict():
    with open('config/algorithm_info.json') as ifs:
        return json.load(ifs)["algorithm_abbr"]


# data set abbreviation dictionary
data_names = get_name_dict()

# figure parameters
FIG_SIZE_MULTIPLE = (8, 4)
LABEL_SIZE = 22
TICK_SIZE = 22
LEGEND_SIZE = 22

algorithm_name_dict = get_algorithm_name_dict()

algorithm_tag_cpu_lst = [cpu_hybrid_tag, cpu_bitmap_tag]

tw_tag = 'webgraph_twitter'
fr_tag = 'snap_friendster'


def get_time_lst(tag, dataset):
    # varying number of threads
    if dataset is tw_tag:
        if tag is cpu_hybrid_tag:
            # should remove sim-cal time
            return [194.928, 192.938, 194.956, 193.114, 195.115, 194.354, 196.445, 197.624, 198.760, 198.771]
        elif tag is cpu_bitmap_tag:
            return [46.809, 48.481, 49.316, 51.228, 51.689, 52.811, 54.032, 56.404, 58.562, 58.489]
    elif dataset is fr_tag:
        if tag is cpu_hybrid_tag:
            return [937.604, 108.005, 114.918, 123.179, 131.082, 137.973, 148.378, 157.284, 164.700, 172.872]
        elif tag is cpu_bitmap_tag:
            return [None, None, 337.671, 184.162, 189.586, 197.109, 205.792, 214.603, 223.047, 232.490]
        return


def draw_overview_elapsed_time():
    with open('../config.json') as ifs:
        my_config_dict = json.load(ifs)[knl_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]

    color_lst = [
        # '#fe01b1',
        # 'orange',
        # 'red',
        # 'green',
        # 'black',
        # '#ceb301', 'm', 'brown',
        'purple',
        'k',
        'blue',
        'gray'
    ]
    shape_lst = [
        # 'D-.',
        # 's--',
        'o:',
        # 'x-',
        # 'P-',
        # '*-',
        # 'v-',
        # '^-.',
        '<--',
        #  '>:'
    ]

    def draw_time_multi_pass(dataset, y_lim):
        pass_lst = range(1, 11, 1)
        x_lst = list(range(len(pass_lst)))
        size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
        fig, ax = plt.subplots()

        # 1st: bars
        for idx, tag in enumerate(algorithm_tag_cpu_lst):
            ax.plot(x_lst, get_time_lst(tag, dataset), shape_lst[idx], color=color_lst[idx], markersize=16,
                    markerfacecolor='none')

        # 2nd: x and y's ticks and labels
        ax.set_xlabel('\\textbf{Number of Passes}', fontsize=LABEL_SIZE)
        ax.set_ylabel("\\textbf{Elapsed Time (seconds)}", fontsize=LABEL_SIZE - 2)
        ax.set_yscale('log')
        ax.set_ylim(y_lim[0], y_lim[1])

        ax.set_xticks(x_lst)
        ax.set_xticklabels(pass_lst)

        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        for tick in ax.xaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        label_lst = [algorithm_name_dict[name] for name in algorithm_tag_cpu_lst]
        ax.legend(['\\textbf{' + name + '}' for name in label_lst],
                  prop={'size': LEGEND_SIZE - 4, "weight": "bold"}, loc="upper right", ncol=1)
        fig.set_size_inches(*size_of_fig)  # set ratio
        fig.savefig("./figures/" + 'exp-gpu-' + data_names[dataset] +
                    '-multi-pass' + '.png', bbox_inches='tight', dpi=300)

    draw_time_multi_pass(tw_tag, y_lim=(10, 1000))
    draw_time_multi_pass(fr_tag, y_lim=(10, 1500))


if __name__ == '__main__':
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif', serif='cm10')

    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
