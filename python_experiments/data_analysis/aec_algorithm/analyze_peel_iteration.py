from data_analysis.util.read_file_utils_updated import *
from config import *
from exec_utilities import exec_utils

iter_tag = 'iter'
time_tag = 'time'
left_tag = 'left'
total_tag = 'total'

if __name__ == '__main__':
    logger = exec_utils.get_logger('/home/yche/analyzing_peel.log', __name__)

    config_dict = get_config_dict(gpu23_tag, '../..')

    root_dir = os.sep.join(
        [config_dict[exp_res_root_mount_path_tag], 'exp-2019-06-24-k-truss-refactor', gpu23_tag, ])

    dataset_lst = config_dict[data_set_lst_tag]


    def parse_line(line):
        lst = line.split()[get_log_header_col():]
        triple = [literal.replace('s', '').replace(',', '') for literal in [lst[-6], lst[-3], lst[-1]]]
        left = triple[2].split('/')[0]
        right = triple[2].split('/')[1]
        return dict(
            zip([iter_tag, time_tag, left_tag, total_tag],
                [int(triple[0]), float(triple[1]), int(left), int(right)], ))


    for dataset in dataset_lst:
        t_num = '40'
        algorithm = 'pkt-inter-shrink'
        file_path = os.sep.join([root_dir, dataset, t_num, algorithm + '.log'])
        logger.info(file_path)

        # use the last one record
        lines = get_file_lines(file_path)
        spliter = get_splitter_line(lines)
        lines = lines[spliter[-2]:spliter[-1] + 1]

        lines = filter(lambda x: contains(['Elapsed Time', 'Left/Total'], x), lines)

        lines = [parse_line(l) for l in lines]
        logger.info('iterations# (+1): {}'.format(len(lines)))
        filtered = filter(lambda x: x[time_tag] > 5, lines)
        for line in filtered:
            last_or_cur = lines[max(0, line[iter_tag] - 1)]
            logger.info(last_or_cur)
            logger.info(line)
            logger.info('Del#/Total# {}/{}, ratio: {}'.format(last_or_cur[left_tag] - line[left_tag], line[total_tag],
                                                              float(last_or_cur[left_tag] - line[left_tag])
                                                              / line[total_tag]))
        logger.info(''.join(['---' for _ in range(20)]))
