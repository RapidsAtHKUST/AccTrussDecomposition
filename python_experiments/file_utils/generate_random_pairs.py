import os

if __name__ == '__main__':
    small_data_set_lst = ['ca-GrQc', 'ca-HepTh', 'p2p-Gnutella06', 'wiki-Vote']
    data_set_lst = [
        # 'email-Enron', 'email-EuAll',
        # 'web-NotreDame', 'web-Stanford', 'web-BerkStan', 'web-Google', 'cit-Patents',
        # 'soc-LiveJournal1'
        'wiki-Link'
    ]
    generate_exec_path = '/homes/ywangby/workspace/yche/git-repos/SimRank/LPMC-Profile/build/playground/random_pair_gen'


    def generate_small():
        for data_set in small_data_set_lst:
            round_num = 10
            for sample_num in [10 ** 3, 10 ** 4, 10 ** 5, 10 ** 6]:
                cmd = ' '.join(map(str, [generate_exec_path, data_set, sample_num, round_num]))
                print(cmd)
                os.system(cmd)


    for data_set in data_set_lst:
        round_num = 2
        for sample_num in [10 ** 2, 10 ** 3, 10 ** 4, 10 ** 5, 10 ** 6]:
            cmd = ' '.join(map(str, [generate_exec_path, data_set, sample_num, round_num]))
            print(cmd)
            os.system(cmd)
