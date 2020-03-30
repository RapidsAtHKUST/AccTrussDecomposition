msp = [56.956644000000004, 56.545167, 251.260545, 2155.704126, 999999999, 1446.816547]
pkt = [35.144, 36.781000000000006, 226.92, 2460.729, 1418.587, 2537.142]
opt_cpu = [14.939000000000002, 14.372, 38.891, 83.812196339, 80.41175144, 256.8017791]
opt_gpu = [3.9100104090000007, 4.973361710000001, 31.208920864, 60.151409141, 20.652948106, 88.207327759]


def get_speedup(lst1, lst2):
    return [lst1[i] / lst2[i] for i in range(len(lst1))]


def get_min_lst(lst1, lst2):
    return [min(lst1[i], lst2[i]) for i in range(len(lst1))]


if __name__ == '__main__':
    art_lst = get_min_lst(msp, pkt)
    print('art:', art_lst)
    print(get_speedup(art_lst, opt_cpu))
    print(get_speedup(art_lst, opt_gpu))
