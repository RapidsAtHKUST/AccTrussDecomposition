import json

t_lst = [str(i) for i in [1, 2, 4, 8, 16, 32, 40]]
data_set = 'webgraph_eu'

SI_tag = 'Tri time'
GC_tag = 'Shrink Time'
SU_tag = 'Proc Time'
EF_tag = 'Scan Time'


def get_info(data_set):
    with open('../raw/2019-10-04-scalability.json') as ifs:
        data = json.load(ifs)
        for tag in [SI_tag, GC_tag, SU_tag, EF_tag]:
            print(tag, [data[data_set][t][tag] for t in t_lst])


def get_speedup_lst(lst):
    return ['%.3lf' % (lst[0] / lst[i]) for i in range(len(lst))]


if __name__ == '__main__':
    # get_info('webgraph_eu')
    # get_info('webgraph_twitter')

    tw = [
        [163.460475845, 77.162269694, 39.399081851, 20.127860415, 11.020530589, 7.994592890, 7.653588639],
        [1262.702, 693.938, 361.507, 191.406, 102.025, 68.401, 61.703],
        [91.301, 62.759, 31.691, 16.61, 10.175, 10.337, 11.117],
        [3004.889, 1902.128, 973.938, 510.41, 276.963, 195.452, 185.827],
        [40.937, 26.97, 16.574, 11.007, 7.512, 6.347, 6.596]
    ]
    we = [
        [16.499579638, 9.081253523, 4.879305611, 2.614189525, 1.465709209, 1.124959859, 1.259007943],
        [73.797, 40.647, 20.939, 10.679, 5.587, 3.872, 3.487],
        [5.832, 4.109, 2.054, 1.229, 0.92, 1.04, 1.127],
        [1199.141, 621.584, 296.154, 158.478, 89.935, 67.853, 65.676],
        [117.699, 59.952, 32.986, 17.374, 10.158, 8.359, 8.9]
    ]

    label_lst = ['PP', 'SI', 'GC', 'SU', 'EF']
    print('WE:\n')
    for idx, lst in enumerate(tw):
        print(label_lst[idx], get_speedup_lst(tw[idx]))

    print('\nTW:\n')
    for idx, lst in enumerate(we):
        print(label_lst[idx], get_speedup_lst(we[idx]))
