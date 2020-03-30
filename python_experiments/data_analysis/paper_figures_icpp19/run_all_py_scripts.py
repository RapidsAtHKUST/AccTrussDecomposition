import os

if __name__ == '__main__':
    for file in ['draw_bitmap_range_filtering_optimization.py',
                 'draw_comparison_of_algorithms.py',
                 'draw_degree_skew_handling.py',
                 'draw_mcdram_opt.py',
                 'draw_multi_pass.py',
                 'draw_scalability_to_num_of_threads.py',
                 'draw_simd_optimization.py',
                 'draw_varying_block_size.py'
                 ]:
        os.system('~/anaconda3/bin/python ' + file)
