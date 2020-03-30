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

algorithm_tag_knl_lst = [knl_hybrid_tag, knl_bitmap_tag]
algorithm_tag_cpu_lst = [cpu_hybrid_tag, cpu_bitmap_tag]

tw_tag = 'webgraph_twitter'
fr_tag = 'snap_friendster'


def get_time_lst(tag, dataset):
    # varying number of threads
    if dataset is tw_tag:
        if tag is knl_hybrid_tag:
            return [5562.579, 2893.882, 1465.865, 729.686, 365.381, 184.500, 101.873, 83.067, 86.168]
        elif tag is knl_bitmap_tag:
            return [3704.287, 2031.953, 1006.197, 509.400, 258.193, 133.516, 78.077, 104.150, 161.283]
        elif tag is cpu_hybrid_tag:
            # should remove sim-cal time
            return [2891.561, 1462.247, 760.213, 388.082, 192.227, 124.453, 71.587 - 1.309]
        elif tag is cpu_bitmap_tag:
            return [996.245, 533.060, 272.331, 141.121, 76.221, 57.310, 42.803 - 1.309]
    elif dataset is fr_tag:
        if tag is knl_hybrid_tag:
            return [4382.258, 2272.660, 1136.719, 567.042, 283.142, 142.794, 74.571, 60.149, 62.806]
        elif tag is knl_bitmap_tag:
            return [8765.759, 4810.823, 2397.829, 1204.425, 623.120, 338.749, 248.722, 324.263, 421.926]
        elif tag is cpu_hybrid_tag:
            return [2470.703, 1345.677, 671.214, 338.050, 181.233, 104.453, 76.487 - 8.141]
        elif tag is cpu_bitmap_tag:
            return [1837.179, 920.572, 472.023, 252.854, 162.079, 139.908, 130.635 - 8.141]
        return


def draw_overview_elapsed_time():
    with open('../config.json') as ifs:
        my_config_dict = json.load(ifs)[knl_tag]
    data_set_lst = my_config_dict[data_set_lst_tag]

    color_lst = [
        # '#fe01b1',
        # 'orange',
        'red',
        'green',
        'black',
        '#ceb301', 'm', 'brown', 'k',
        'purple', 'blue', 'gray'
    ]
    shape_lst = [
        'D-.',
        's--',
        # 'o:',
        # 'x-',
        # 'P-', '*-',
        # 'v-',
        '^-.', '<--', '>:']

    def draw_time_knl(dataset):
        thread_lst = [1, 2, 4, 8, 16, 32, 64, 128, 256]
        x_lst = range(len(thread_lst))
        size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
        fig, ax = plt.subplots()

        # 1st: bars
        for idx, tag in enumerate(algorithm_tag_knl_lst):
            ax.plot(x_lst, get_time_lst(tag, dataset), shape_lst[idx], color=color_lst[idx], markersize=16,
                    markerfacecolor='none')

        # 2nd: x and y's ticks and labels
        ax.set_xlabel('\\textbf{Number of Threads}', fontsize=LABEL_SIZE)
        ax.set_ylabel("\\textbf{Elapsed Time (seconds)}", fontsize=LABEL_SIZE - 2)
        ax.set_yscale('log')
        ax.set_ylim(10, 40000)

        ax.set_xticks(x_lst)
        ax.set_xticklabels(thread_lst)

        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        for tick in ax.xaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        label_lst = [algorithm_name_dict[name] for name in algorithm_tag_knl_lst]
        ax.legend(['\\textbf{' + name + '}' for name in label_lst],
                  prop={'size': LEGEND_SIZE - 4, "weight": "bold"}, loc="upper right", ncol=1)
        fig.set_size_inches(*size_of_fig)  # set ratio
        fig.savefig("./figures/" + 'exp-knl-' + data_names[dataset] +
                    '-scalability' + '.png', bbox_inches='tight', dpi=300)

    def draw_time_cpu(dataset):
        thread_lst = [1, 2, 4, 8, 16, 32, 64]
        x_lst = range(len(thread_lst))
        size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
        fig, ax = plt.subplots()

        for idx, tag in enumerate(algorithm_tag_cpu_lst):
            ax.plot(x_lst, get_time_lst(tag, dataset), shape_lst[idx], color=color_lst[idx], markersize=16,
                    markerfacecolor='none')

        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        for tick in ax.xaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        ax.set_xlabel('\\textbf{Number of Threads}', fontsize=LABEL_SIZE)

        ax.set_yscale('log')

        ax.set_ylabel("\\textbf{Elapsed Time (seconds)}", fontsize=LABEL_SIZE)
        ax.set_ylim(10, 20000)
        ax.set_xticks(x_lst)
        ax.set_xticklabels(thread_lst)
        fig.set_size_inches(*size_of_fig)  # set ratio

        label_lst = [algorithm_name_dict[name] for name in algorithm_tag_cpu_lst]
        ax.legend(['\\textbf{' + name + '}' for name in label_lst],
                  prop={'size': LEGEND_SIZE, "weight": "bold"}, loc="upper right", ncol=1)
        fig.savefig("./figures/" + 'exp-cpu-' + data_names[dataset] +
                    '-scalability' + '.png', bbox_inches='tight', dpi=300)

    data_set_lst = [tw_tag, fr_tag]
    for data_set in data_set_lst:
        draw_time_knl(data_set)
        draw_time_cpu(data_set)


if __name__ == '__main__':
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif', serif='cm10')

    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
