from data_analysis.util.read_file_utils_updated import get_log_header_col, format_str, get_splitter_line, contains
from exec_utilities import exec_utils


def parse_line(line, tag_lst):
    data_len = len(tag_lst)
    if line is None:
        time_lst = [None for _ in range(data_len)]
    else:
        lst = line.split()[get_log_header_col():]
        # eval all between the ':' and 's'
        my_str = ' '.join(lst) + 's'
        print(my_str)
        colon_idx_lst = []
        unit_idx_lst2 = []
        for idx, ch in enumerate(my_str):
            if ch == ':':
                colon_idx_lst.append(idx)
            if ch == 's' or ch == ' ':
                # last ch is numeric
                if idx - 1 > 0 and my_str[idx - 1] in [str(i) for i in range(10)]:
                    unit_idx_lst2.append(idx)
        print(colon_idx_lst)
        print(unit_idx_lst2)
        # assert len(colon_idx_lst) == len(unit_idx_lst2) == data_len
        if len(colon_idx_lst) == len(unit_idx_lst2) == data_len:
            time_lst = [eval(my_str[beg + 1:end]) for beg, end in zip(colon_idx_lst, unit_idx_lst2)]
        else:
            logger = exec_utils.get_logger('/home/yche/logs/' + 'error.log', __name__)
            logger.info('err:' + my_str)
            time_lst = [None for _ in range(data_len)]
    return dict(zip(tag_lst,
                    map(lambda ele: None if ele is None else float(ele), time_lst)))


def union(first_dict, second_dict):
    for k, v in second_dict.items():
        first_dict[k] = v
    return first_dict


# Algorithm's Detailed Time Info
def parse_lines(lines, local_tag_lst, total_time_tag, total_time_tag_lst):
    if lines is not None and has_is_time_out(lines):
        # use the last one record
        spliter = get_splitter_line(lines)
        org_lines = lines[spliter[-2]:spliter[-1] + 1]

        lines = list(filter(lambda x: contains(['Tri time', 'Shrink Time'], x), org_lines))
        local_dict = parse_line(None if len(lines) == 0 else lines[0], tag_lst=local_tag_lst)

        lines = list(filter(lambda x: contains([total_time_tag], x), org_lines))
        another_dict = parse_line(None if len(lines) == 0 else lines[0], tag_lst=total_time_tag_lst)

        total_time_str = format_str(another_dict[total_time_tag])
        local_dict[total_time_tag] = float(total_time_str) if total_time_str is not None else None
    else:
        local_dict = parse_line(None, tag_lst=local_tag_lst)
        local_dict[total_time_tag] = None
    return local_dict


def parse_lines_cuda(lines, tag_lst):
    local_dict = dict(zip(tag_lst, [None for _ in range(len(tag_lst))]))
    if lines is not None and has_is_time_out(lines):
        # use the last one record
        spliter = get_splitter_line(lines)
        org_lines = lines[spliter[-2]:spliter[-1] + 1]

        for tag in tag_lst:
            lines = list(filter(lambda x: contains([tag], x), org_lines))
            local_dict[tag] = parse_line(None if len(lines) == 0 else lines[0], [tag])[tag]
        return local_dict
    return local_dict


def get_speedup(t_small, t_large, my_info, tag_lst, speedup_tag):
    for tag in tag_lst:
        if speedup_tag not in my_info[t_large]:
            my_info[t_large][speedup_tag] = dict()
        my_info[t_large][speedup_tag][tag] = format_str(user_div(my_info[t_small][tag],
                                                                 my_info[t_large][tag]))


def has_is_time_out(lines):
    for line in lines:
        if 'is_time_out' in line:
            return True
    return False


def transform(x):
    return str(x) if x is not None else '/'


def user_div(v1, v2):
    if v1 is None or v2 is None or v2 == 0:
        return None
    else:
        return v1 / v2


def generate_md_table_from_lines(bold_line, lines, logger, output_md_file):
    md_table = '\n### ' + bold_line + '\n\n' + \
               '\n'.join([' | '.join([transform(x) for x in l]) for l in lines]) + '\n'
    logger.info(md_table)
    output_md_file.write(md_table)


if __name__ == '__main__':
    print(parse_line(
        '2020-01-10 03:32:29 INFO  (ts: 1578598349.354976 s,  et: 47.490135 s) cuda_tc.cu:310: End-To-End Time: 38.164506156s',
        ['End-To-End Time']))
