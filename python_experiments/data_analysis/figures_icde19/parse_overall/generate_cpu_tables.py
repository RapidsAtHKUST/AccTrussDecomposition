import json


def get_global_dict():
    bar_exec_name_lst = ['pkt-vm', 'pkt-gc',
                         'pkt-dstcp', 'pkt-bmpf', 'pkt-inter-shrink']

    global_dict = dict()

    for exec_name in bar_exec_name_lst:
        with open('./varying_cpu/{}/{}.json'.format('exp-2019-10-04-eid', exec_name)) as ifs:
            data_dict = json.load(ifs)
            global_dict[exec_name] = data_dict
    return global_dict


if __name__ == '__main__':
    data_set_lst = ['webgraph_eu', 'webgraph_it', 'webgraph_twitter']
    name_dict = {
        'webgraph_twitter': 'TW',
        'webgraph_it': 'WI',
        'webgraph_eu': 'WE'
    }

    shrink_tag = 'Shrink Time'
    scan_tag = 'Scan Time'
    sup_update_tag = 'Proc Time'

    print('GC:\n')
    data_dict = get_global_dict()
    for data_set in data_set_lst:
        lst = [name_dict[data_set], 0.0, data_dict['pkt-vm'][data_set][sup_update_tag],
               data_dict['pkt-gc'][data_set][shrink_tag],
               data_dict['pkt-gc'][data_set][sup_update_tag]]
        lst.append(sum(lst[1:3]) - sum(lst[3:5]))
        print(' & '.join(['%.1f' % x if isinstance(x, float) else x for x in lst]) + r'\\' + '\n' + r'\hline')

    print('\nBMPF + IDX:\n')
    for data_set in data_set_lst:
        lst = [name_dict[data_set],
               data_dict['pkt-dstcp'][data_set][scan_tag],
               data_dict['pkt-dstcp'][data_set][sup_update_tag],
               data_dict['pkt-bmpf'][data_set][scan_tag],
               data_dict['pkt-bmpf'][data_set][sup_update_tag]]
        lst.append(sum(lst[1:3]) - sum(lst[3:5]))  # idx: 5
        lst.extend([data_dict['pkt-inter-shrink'][data_set][scan_tag],
                    data_dict['pkt-inter-shrink'][data_set][sup_update_tag]])
        lst.append(sum(lst[1:3]) - sum(lst[6:8]))
        print(' & '.join(['%.1f' % x if isinstance(x, float) else x for x in lst]) + r'\\' + '\n' + r'\hline')
