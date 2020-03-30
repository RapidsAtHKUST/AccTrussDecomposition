if __name__ == '__main__':
    for data_set in ["snap_orkut",
                     "webgraph_uk",
                     "webgraph_eu",
                     "webgraph_webbase",
                     "webgraph_it",
                     "webgraph_twitter"]:
        root_path = '/home/yche/mnt/luocpu9/mnt/storage1/yche/datasets'
        file_name = 'ktruss-pkt-inter.histogram'
        with open('{}/{}/{}'.format(root_path, data_set, file_name)) as ifs:
            arr = eval(ifs.readline())
            if 'eu' in data_set:
                print(arr[9584],arr[9585])
            match_lst = []
            mv = max(arr)
            for i in range(len(arr)):
                if arr[i] == mv:
                    match_lst.append(i)
            print(data_set, match_lst, mv)
