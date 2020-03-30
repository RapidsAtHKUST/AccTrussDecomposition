from data_analysis.figures_icde19.parse_overall.parse_gpu_results import *

if __name__ == '__main__':
    with open('./{}/{}/{}.json'.format(varying_gpu_tag, config_lst[0], 'cuda-pkt-offload')) as ifs:
        without_idx_dict = json.load(ifs)
    with open('./{}/{}/{}.json'.format(varying_gpu_tag, config_lst[0], 'cuda-pkt-offload-opt')) as ifs:
        with_idx_dict = json.load(ifs)
    name_dict = {
        'webgraph_twitter': 'TW',
        'webgraph_it': 'WI',
        'webgraph_eu': 'WE'
    }
    for data_set in ['webgraph_eu', 'webgraph_it', 'webgraph_twitter']:
        lst = [name_dict[data_set], without_idx_dict[data_set][extra_tag][scan_cpu_time_tag],
               without_idx_dict[data_set][extra_tag][sub_level_process_cpu_time_tag],
               with_idx_dict[data_set][extra_tag][scan_cpu_time_tag],
               with_idx_dict[data_set][extra_tag][sub_level_process_cpu_time_tag]]
        lst.append(sum(lst[1:3]) - sum(lst[3:5]))
        print(' & '.join(['%.1f' % x if isinstance(x, float) else x for x in lst]) + r'\\' + '\n' + r'\hline')
