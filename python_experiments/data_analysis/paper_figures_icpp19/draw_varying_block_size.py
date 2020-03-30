import matplotlib.pyplot as plt

from data_analysis.util.read_file_utils import core_checking_sim_cal_cost_tag, cpu_side_task_range_init_tag, \
    is_correct_tag, time_tag, time_tag_lst
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
    with open('../data_analysis/data-json/lccpu12/10-17-varying-block-size.json') as ifs:
        my_dict = json.load(ifs)
    mps_tag = 'scan-xp-cuda-experimental-hybrid-kernels-varying-block-size'
    bmp_tag = 'scan-xp-cuda-experimental-bitmap-varying-block-size'

    def get_time_lst(data_set, algorithm, thread_num_str='56'):
        block_size_lst = map(str, range(1, 33))
        tmp_lst = []

        for block_size in block_size_lst:
            algorithm_dict = my_dict['1'][algorithm][data_set + '/rev_deg'][thread_num_str][block_size]

            def get_time_if_not_none(usr_tag):
                return algorithm_dict[usr_tag][time_tag] if usr_tag in algorithm_dict and algorithm_dict[
                    usr_tag] is not None else None

            time_lst = list(map(
                lambda tag: get_time_if_not_none(tag) if algorithm_dict[is_correct_tag] == True else None,
                time_tag_lst))

            core_checking_time = time_lst[0]
            sim_cal_time = get_time_if_not_none(core_checking_sim_cal_cost_tag)
            task_init_time = get_time_if_not_none(cpu_side_task_range_init_tag)
            tmp_lst.append(float(core_checking_time) - float(sim_cal_time) - float(task_init_time))
        return tmp_lst

    if dataset is tw_tag:
        if tag is cpu_hybrid_tag:
            # should remove sim-cal time
            return get_time_lst(tw_tag, mps_tag)
        elif tag is cpu_bitmap_tag:
            return get_time_lst(tw_tag, bmp_tag)
    elif dataset is fr_tag:
        if tag is cpu_hybrid_tag:
            return get_time_lst(fr_tag, mps_tag)
        elif tag is cpu_bitmap_tag:
            return get_time_lst(fr_tag, bmp_tag)
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
        '*--',
        #  '>:'
    ]

    def draw_time_multi_pass(dataset, y_lim):
        pass_lst = range(1, 33, 1)
        x_lst = range(len(pass_lst))
        size_of_fig = (FIG_SIZE_MULTIPLE[0], FIG_SIZE_MULTIPLE[1])
        fig, ax = plt.subplots()

        # 1st: bars
        for idx, tag in enumerate(algorithm_tag_cpu_lst):
            ax.plot(x_lst, get_time_lst(tag, dataset), shape_lst[idx], color=color_lst[idx], markersize=14,
                    markerfacecolor='none')

        # 2nd: x and y's ticks and labels
        ax.set_xlabel('\\textbf{Number of Waprs per Block}', fontsize=LABEL_SIZE)
        ax.set_ylabel("\\textbf{Elapsed Time (seconds)}", fontsize=LABEL_SIZE - 2)
        ax.set_yscale('log')
        ax.set_ylim(y_lim[0], y_lim[1])

        # ax.set_xticks(x_lst)
        # ax.set_xticklabels(pass_lst)
        ax.set_xticks([0, 3, 7, 11, 15, 19, 23, 27, 31])
        ax.set_xticklabels([1, 4, 8, 12, 16, 20, 24, 28, 32])
        for tick in ax.yaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        for tick in ax.xaxis.get_major_ticks():
            tick.label.set_fontsize(TICK_SIZE)
        label_lst = [algorithm_name_dict[name] for name in algorithm_tag_cpu_lst]
        ax.legend(['\\textbf{' + name + '}' for name in label_lst],
                  prop={'size': LEGEND_SIZE - 4, "weight": "bold"}, loc="upper right", ncol=1)
        fig.set_size_inches(*size_of_fig)  # set ratio
        fig.savefig("./figures/" + 'exp-gpu-' + data_names[dataset] +
                    '-varying-block-size' + '.png', bbox_inches='tight', dpi=300)

    draw_time_multi_pass(tw_tag, y_lim=(10, 1000))
    draw_time_multi_pass(fr_tag, y_lim=(10, 1500))


if __name__ == '__main__':
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif', serif='cm10')

    os.system('mkdir -p figures')
    draw_overview_elapsed_time()
