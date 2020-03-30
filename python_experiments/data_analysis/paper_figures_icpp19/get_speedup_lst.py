def get_speedup(lst_l, lst_s):
    return [p[0] / p[1] for p in zip(lst_l, lst_s)]


def get_scalability_speedup(lst):
    return list([lst[0] / e for e in lst])


def get_speedup_deg_skew():
    cpu_m = [20065.292, 4528.821]
    cpu_mps = [5527.204, 4919.126]
    cpu_bmp = [996.245, 1837.179]
    print(get_speedup(cpu_m, cpu_mps))
    print(get_speedup(cpu_m, cpu_bmp))

    knl_m = [108418.56, 11199.936]
    knl_mps = [15244.416, 11224.064]
    knl_bmp = [3704.287, 9591.316]
    print(get_speedup(knl_m, knl_mps))
    print(get_speedup(knl_m, knl_bmp))


def get_speedup_vec():
    cpu_mps = [5527.204, 4919.126]
    cpu_mps_vec = [2891.561, 2470.703]
    cpu_bmp = [996.245, 1837.179]
    print(get_speedup(cpu_mps, cpu_mps_vec))
    print('cmp', get_speedup(cpu_mps_vec, cpu_bmp))

    knl_mps = [15244.416, 11224.064]
    knl_mps_vec = [5904.0, 4569.408]
    knl_bmp = [3704.287, 9591.316]
    print(get_speedup(knl_mps, knl_mps_vec))
    print('cmp:', get_speedup(knl_mps_vec, knl_bmp))
    print('cmp r:', get_speedup(knl_bmp, knl_mps_vec))


def get_speedup_scalability():
    knl_avx512_tw = [5562.579, 2893.882, 1465.865, 729.686, 365.381, 184.5, 101.873, 83.067, 86.168]
    knl_bitmap_tw = [3704.287, 2031.953, 1006.197, 509.4, 258.193, 133.516, 78.077, 104.15, 161.283]
    cpu_avx2_tw = [2891.561, 1462.247, 760.213, 388.082, 192.227, 124.453, 70.278]
    cpu_bitmap_tw = [996.245, 533.06, 272.331, 141.121, 76.221, 57.31, 41.494]

    knl_avx512_fr = [4382.258, 2272.66, 1136.719, 567.042, 283.142, 142.794, 74.571, 60.149, 62.806]
    knl_bitmap_fr = [8765.759, 4810.823, 2397.829, 1204.425, 623.12, 338.749, 248.722, 324.263, 421.926]
    cpu_avx2_fr = [2470.703, 1345.677, 671.214, 338.05, 181.233, 104.453, 68.34599999999999]
    cpu_bitmap_fr = [1837.179, 920.572, 472.023, 252.854, 162.079, 139.908, 122.49399999999999]

    for idx, lst in enumerate([knl_avx512_tw, knl_bitmap_tw, cpu_avx2_tw, cpu_bitmap_tw] \
                              + [knl_avx512_fr, knl_bitmap_fr, cpu_avx2_fr, cpu_bitmap_fr]):
        if idx == 4:
            print()
        print(get_scalability_speedup(lst))


def get_speedup_range_filtering():
    knl_mps = [83.067, 60.149]
    knl_bmp = [78.077, 248.722]
    knl_bmp_rf = [82.134, 115.740]
    cpu_mps = [71.587 - 1.309, 76.487 - 8.141]
    cpu_bmp = [42.803 - 1.309, 130.635 - 8.141]
    cpu_bmp_rf = [41.713 - 1.309, 71.923 - 8.141]
    print(get_speedup(cpu_bmp, cpu_bmp_rf))
    print(get_speedup(knl_bmp, knl_bmp_rf))


def get_speedup_mcdram():
    knl_mps = [83.067, 60.149]
    knl_mps_hbw_flat = [52.652, 33.852]
    knl_mps_hbw_cache = [53.333, 34.731]

    knl_bmp = [82.134, 115.740]
    knl_bmp_hbw_flat = [68.519, 92.655]
    knl_bmp_hbw_cache = [69.526, 93.201]

    print(get_speedup(knl_mps, knl_mps_hbw_cache))
    print(get_speedup(knl_mps, knl_mps_hbw_flat))
    print(get_speedup(knl_bmp, knl_bmp_hbw_flat))
    print(get_speedup(knl_bmp, knl_bmp_hbw_cache))


def print_overall_cmp():
    # lj, orkut, webbase, it, twitter, friendster
    knl_hybrid_tag = [0.26, 1.7, 3.2, 10.7, 52.7, 33.9]  # done    # best
    cpu_bitmap_tag = [0.37, 2.2, 3.4, 7.6, 40.4, 63.8]  # done # best
    m_gpu_bitmap_tag = [0.45, 1.5, 7.5, 6.1, 21.5, 48.6]  # done # best
    print([max(tu) / min(tu) for tu in zip(knl_hybrid_tag, cpu_bitmap_tag, m_gpu_bitmap_tag)])


def print_all_cmp():
    knl_hybrid = [0.261, 1.756, 3.161, 10.715, 52.7, 33.9]  # done    # best
    knl_bitmap_tag = [0.503, 3.676, 4.378, 12.260, 68.768, 92.6]  # done
    cpu_hybrid_tag = [0.391, 3.014, 3.122, 8.668, 70.3, 68.3]  # done
    cpu_bitmap_tag = [0.367, 2.258, 3.4, 7.585, 40.4, 63.8]  # done # best
    m_gpu_kernel_tag = [0.765, 4.764, 13.046, 48.047, 193.285, 106.983]  # done
    m_gpu_bitmap_tag = [0.446, 1.494, 7.462, 6.111, 21.505, 48.675]  # done # best
    # print(get_speedup(m_gpu_kernel_tag, knl_hybrid)
    # print(get_speedup(cpu_hybrid_tag, knl_hybrid)
    # print(get_speedup(m_gpu_kernel_tag, cpu_hybrid_tag)

    print(get_speedup(cpu_bitmap_tag, m_gpu_bitmap_tag))
    print(get_speedup(cpu_bitmap_tag, knl_hybrid))
    # print(get_speedup(knl_bitmap_tag, m_gpu_bitmap_tag)


if __name__ == '__main__':
    # get_speedup_deg_skew()
    # get_speedup_vec()
    # get_speedup_scalability()
    # get_speedup_range_filtering()
    # get_speedup_mcdram()
    # print_overall_cmp()
    print_all_cmp()