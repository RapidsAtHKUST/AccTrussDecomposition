import sys

if __name__ == '__main__':
    # file_path = sys.argv[1]
    for exec in ['pkt-dstcp', 'pkt-es']:
        for dataset in ['webgraph_eu', 'webgraph_twitter', 'webgraph_it']:
            file_path = '/home/yche/mnt/gpu24/mnt/storage1/yche/git-repos/OutOfCoreSCAN/python_experiments/exp_results/' \
                        'exp-2020-04-02/{}/{}/org/40/log/{}-raw.log'.format('gpu23', dataset, exec)
            with open(file_path) as ifs:
                txt = '\n'.join(ifs.readlines()).replace('\\n', '\n')
            out_path = file_path + '.refined'
            with open(out_path, 'w') as ofs:
                ofs.write(txt)
