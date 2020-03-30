if __name__ == '__main__':
    # lst = [0.21, 1.44, 1.54, 0.41, 1.21, 2.71, 17.75, 40.58]
    # lst2 = [0.33, 1.97, 2.47, 0.44, 1.47, 2.85, 21.43, 43.00]
    # lst3 = [0.41, 2.39, 4.5, 0.54, 1.85, 2.99, 23.64, 43.92]
    # speedup = [(w / u, w / v) for u, v, w in zip(lst, lst2, lst3)]
    # print speedup
    tri_cnt_lst = [0.17, 1.22, 0.14, 0.75,
                   0.7, 0.77, 16.22, 36.30,
                   6.58, 19.5, 27.86]
    all_edge_cnt_lst = [0.4, 2.6, 0.45, 3.6,
                        2.1, 2.5, 55.9, 73.0,
                        14.5, 45.0, 135.5]
    speedup = [w / v for v, w in zip(tri_cnt_lst, all_edge_cnt_lst)]
    print(speedup)
