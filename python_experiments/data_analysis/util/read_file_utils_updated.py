import re

from data_analysis.util.read_file_utils import *

all_edge_cnt_time_tag_lst = [reorder_tag, preprocess_tag2, all_edge_cnc_comp_tag, all_edge_cnc_total_tag,
                             output_cores_non_cores_tag]
max_d_tag = 'max d'
triangle_cnt_tag = 'Triangle Cnt'


def ret_all(pat, line):
    return [x for x in re.findall('{}'.format(pat), line)]


def split_val(split_ch, x):
    ret = x.split(split_ch)[-1].strip()
    return ret


def contains(key_word_lst, line):
    return reduce(lambda l, r: l and r, [k in line for k in key_word_lst], True)


def get_log_header_col():
    sample = '2020-01-10 03:31:40 INFO  (ts: 1578598300.514116 s,  et: 114.041621 s) histogram.h:90: '
    return len(sample.split())


def get_splitter_line(lines):
    lines = list(lines)
    splitter_line_num = [0]
    for i in range(len(lines)):
        if 'is_time_out' in lines[i]:
            splitter_line_num.append(i + 1)
    return splitter_line_num


def get_file_lines(file_path):
    if not os.path.exists(file_path):
        return None
    with open(file_path) as ifs:
        return list(map(lambda s: s.strip(), ifs.readlines()))


def get_simple_tag_info_updated(lines, tag, functor):
    if lines is None:
        return None
    else:
        # assume unit seconds
        my_lines = filter(lambda line: tag in line, lines)
        my_lines = map(lambda line: line if '*-' not in line else line.split('*-')[0], my_lines)
        filtered_tuples = list(map(lambda line:
                                   eval(line.strip().split(':')[-1].replace(',', '')), my_lines))
        return None if len(filtered_tuples) == 0 else functor(filtered_tuples)


def get_time_mem_info_updated(lines, tag, functor):
    if lines is None:
        return None
    else:
        header_len = get_log_header_col()

        # assume unit seconds
        tuples = filter(lambda t: len(t) >= header_len,
                        map(lambda l: l.strip().split(),
                            filter(lambda l: not l.startswith('*-*-'), lines)))
        filtered_tuples = [' '.join(t[header_len:]) for t in tuples]
        # print 'filtered_tuples:', filtered_tuples

        filtered_tuples = filter(lambda t: t.startswith(tag), filtered_tuples)

        # print tag, 'filtered:', filtered_tuples

        def get_time_mem(l):
            # print l
            t = l.split('s,')
            time = eval(t[0].split(':')[-1].split()[0])
            if time is not None:
                time = float(format_str(time))
            mem = t[1].split(':')[-1].split()[0]
            return {time_tag: time, mem_tag: mem}

        filtered_tuples = list(map(get_time_mem, filtered_tuples))
        return None if len(filtered_tuples) == 0 else functor(filtered_tuples)


def get_all_edge_cnt_time_mem_info(file_path):
    my_time_tag_lst = all_edge_cnt_time_tag_lst
    lines = get_file_lines(file_path)
    # print lines
    my_dict = dict(zip(my_time_tag_lst, [get_time_mem_info_updated(lines, tag, func) for tag in my_time_tag_lst]))
    my_dict[is_correct_tag] = \
        my_dict[output_cores_non_cores_tag] is not None and \
        get_simple_tag_info_updated(lines, is_correct_tag,
                                    lambda input_lst: reduce(lambda l, r: l and r, input_lst, True)) is True
    my_dict[is_time_out_tag] = get_simple_tag_info_updated(lines, is_time_out_tag,
                                                           lambda input_lst: reduce(lambda l, r: l or r, input_lst,
                                                                                    False))
    return my_dict


def get_triangle_cnt_time_mem_info_updated(file_path):
    my_time_tag_lst = tri_cnt_time_lst

    lines = get_file_lines(file_path)
    # print lines
    my_dict = dict(zip(my_time_tag_lst, [get_time_mem_info_updated(lines, tag, func) for tag in my_time_tag_lst]))
    my_dict[is_time_out_tag] = get_simple_tag_info_updated(lines, is_time_out_tag,
                                                           lambda input_lst: reduce(lambda l, r: l or r, input_lst,
                                                                                    False))
    my_dict[max_d_tag] = get_simple_tag_info_updated(lines, max_d_tag, lambda x: x[-1])
    my_dict[triangle_cnt_tag] = get_simple_tag_info_updated(lines, triangle_cnt_tag, lambda x: x[-1])
    return my_dict


if __name__ == '__main__':
    print(get_all_edge_cnt_time_mem_info(
        '/home/yche/mnt/luocpu9/var/nfsshare/yche/git-repos/OutOfCoreSCAN/python_experiments/exp_results/'
        'exp-03-21-study-all-edge-counting/snap_friendster/gro/0.2/5/40/scan-xp-avx2-roaring.txt'))

    print(get_all_edge_cnt_time_mem_info(
        '/home/yche/mnt/luocpu9/var/nfsshare/yche/git-repos/OutOfCoreSCAN/python_experiments/exp_results/'
        'exp-03-21-study-all-edge-counting/snap_livejournal/gro/0.2/5/40/scan-xp-naive-bitvec-adv.txt'))

    print(get_triangle_cnt_time_mem_info_updated(
        '/home/yche/mnt/luocpu9/var/nfsshare/yche/git-repos/OutOfCoreSCAN/python_experiments/exp_results/'
        'exp-03-25-study-tri-cnt/snap_livejournal/gro/40/tri-cnt-naive-bitvec-adv.txt'
    ))
