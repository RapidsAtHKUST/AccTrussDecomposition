# O(E) intersection count time


Unit: seconds


### webgraph_webbase

file-name | 1 | 2 | 4 | 8
--- | --- | --- | --- | ---
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass-dynamic-lb | 88.507 | 45.900 | 24.503 | 13.417
cuda-hybrid-kernels-multi-gpu-multi-pass-dynamic-lb | 10.151 | 6.757 | 5.080 | 5.027
cuda-4-8-multi-gpu-multi-pass-dynamic-lb | 10.613 | 8.088 | 5.200 | 5.161
cuda-2-16-multi-gpu-multi-pass-dynamic-lb | 10.610 | 7.821 | 5.016 | 5.074
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass | 88.426 | 46.565 | 25.854 | 13.463
cuda-hybrid-kernels-multi-gpu-multi-pass | 10.483 | 6.726 | 4.689 | 5.148
cuda-4-8-multi-gpu-multi-pass | 10.674 | 6.407 | 4.792 | 5.117
cuda-2-16-multi-gpu-multi-pass | 10.490 | 7.199 | 4.721 | 4.755


### webgraph_webbase/rev_deg

file-name | 1 | 2 | 4 | 8
--- | --- | --- | --- | ---
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass-dynamic-lb | 11.124 | 9.142 | 8.222 | 7.421
cuda-hybrid-kernels-multi-gpu-multi-pass-dynamic-lb | 14.455 | 9.111 | 6.684 | 6.935
cuda-4-8-multi-gpu-multi-pass-dynamic-lb | 50.333 | 43.707 | 41.727 | 42.601
cuda-2-16-multi-gpu-multi-pass-dynamic-lb | 51.191 | 42.266 | 42.005 | 42.895
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass | 11.611 | 11.678 | 8.827 | 8.751
cuda-hybrid-kernels-multi-gpu-multi-pass | 14.126 | 11.674 | 7.757 | 7.092
cuda-4-8-multi-gpu-multi-pass | 46.329 | 43.598 | 42.844 | 42.748
cuda-2-16-multi-gpu-multi-pass | 45.114 | 43.215 | 42.659 | 43.003


### webgraph_it

file-name | 1 | 2 | 4 | 8
--- | --- | --- | --- | ---
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass-dynamic-lb | 395.383 | 197.743 | 99.472 | 49.710
cuda-hybrid-kernels-multi-gpu-multi-pass-dynamic-lb | 24.159 | 14.378 | 14.217 | 8.852
cuda-4-8-multi-gpu-multi-pass-dynamic-lb | 26.921 | 16.339 | 15.159 | 10.558
cuda-2-16-multi-gpu-multi-pass-dynamic-lb | 28.416 | 17.514 | 16.803 | 10.087
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass | 396.683 | 199.199 | 100.811 | 50.947
cuda-hybrid-kernels-multi-gpu-multi-pass | 23.866 | 17.579 | 15.046 | 14.714
cuda-4-8-multi-gpu-multi-pass | 27.532 | 17.654 | 16.288 | 15.904
cuda-2-16-multi-gpu-multi-pass | 27.592 | 18.863 | 17.595 | 17.327


### webgraph_it/rev_deg

file-name | 1 | 2 | 4 | 8
--- | --- | --- | --- | ---
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass-dynamic-lb | 8.977 | 5.470 | 4.473 | 4.021
cuda-hybrid-kernels-multi-gpu-multi-pass-dynamic-lb | 52.014 | 31.424 | 30.617 | 29.009
cuda-4-8-multi-gpu-multi-pass-dynamic-lb | 227.729 | 203.331 | 203.420 | 202.633
cuda-2-16-multi-gpu-multi-pass-dynamic-lb | 227.137 | 203.678 | 203.371 | 202.811
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass | 6.882 | 5.789 | 4.367 | 4.321
cuda-hybrid-kernels-multi-gpu-multi-pass | 46.598 | 37.477 | 34.084 | 32.867
cuda-4-8-multi-gpu-multi-pass | 213.761 | 209.377 | 207.930 | 208.442
cuda-2-16-multi-gpu-multi-pass | 213.817 | 209.251 | 207.875 | 208.677


### webgraph_twitter

file-name | 1 | 2 | 4 | 8
--- | --- | --- | --- | ---
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass-dynamic-lb | 96.429 | 51.371 | 28.061 | 15.981
cuda-hybrid-kernels-multi-gpu-multi-pass-dynamic-lb | 350.845 | 228.067 | 184.092 | 158.843
cuda-4-8-multi-gpu-multi-pass-dynamic-lb | 957.093 | 646.776 | 589.829 | 544.279
cuda-2-16-multi-gpu-multi-pass-dynamic-lb | 962.457 | 639.057 | 599.061 | 534.534
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass | 97.246 | 49.929 | 28.750 | 17.388
cuda-hybrid-kernels-multi-gpu-multi-pass | 250.050 | 235.295 | 199.819 | 179.215
cuda-4-8-multi-gpu-multi-pass | 576.154 | 570.566 | 548.902 | 517.840
cuda-2-16-multi-gpu-multi-pass | 583.012 | 561.822 | 539.396 | 516.776


### webgraph_twitter/rev_deg

file-name | 1 | 2 | 4 | 8
--- | --- | --- | --- | ---
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass-dynamic-lb | 27.529 | 20.510 | 11.179 | 7.988
cuda-hybrid-kernels-multi-gpu-multi-pass-dynamic-lb | 249.507 | 163.678 | 118.962 | 97.949
cuda-4-8-multi-gpu-multi-pass-dynamic-lb | 900.823 | 781.857 | 779.340 | 777.522
cuda-2-16-multi-gpu-multi-pass-dynamic-lb | 896.805 | 779.133 | 774.997 | 774.688
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass | 27.935 | 15.297 | 11.649 | 9.795
cuda-hybrid-kernels-multi-gpu-multi-pass | 205.084 | 175.718 | 156.477 | 140.538
cuda-4-8-multi-gpu-multi-pass | 815.805 | 803.392 | 793.609 | 791.503
cuda-2-16-multi-gpu-multi-pass | 810.551 | 795.780 | 788.186 | 788.279


### snap_friendster

file-name | 1 | 2 | 4 | 8
--- | --- | --- | --- | ---
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass-dynamic-lb | 99.988 | 64.812 | 42.451 | 41.019
cuda-hybrid-kernels-multi-gpu-multi-pass-dynamic-lb | 93.083 | 65.520 | 36.420 | 29.066
cuda-4-8-multi-gpu-multi-pass-dynamic-lb | 94.733 | 55.195 | 33.017 | 25.925
cuda-2-16-multi-gpu-multi-pass-dynamic-lb | 106.600 | 57.000 | 38.853 | 30.023
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass | 110.484 | 72.059 | 35.560 | 30.981
cuda-hybrid-kernels-multi-gpu-multi-pass | 106.646 | 77.407 | 38.317 | 32.553
cuda-4-8-multi-gpu-multi-pass | 94.014 | 53.497 | 35.041 | 32.901
cuda-2-16-multi-gpu-multi-pass | 103.431 | 59.125 | 37.679 | 33.545


### snap_friendster/rev_deg

file-name | 1 | 2 | 4 | 8
--- | --- | --- | --- | ---
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass-dynamic-lb | 100.534 | 61.857 | 59.766 | 55.334
cuda-hybrid-kernels-multi-gpu-multi-pass-dynamic-lb | 90.786 | 54.484 | 41.381 | 34.220
cuda-4-8-multi-gpu-multi-pass-dynamic-lb | 89.683 | 53.701 | 40.460 | 34.223
cuda-2-16-multi-gpu-multi-pass-dynamic-lb | 101.169 | 56.800 | 42.823 | 36.461
cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass | 114.077 | 79.280 | 57.292 | 44.096
cuda-hybrid-kernels-multi-gpu-multi-pass | 95.543 | 54.516 | 40.697 | 30.663
cuda-4-8-multi-gpu-multi-pass | 84.399 | 45.061 | 31.943 | 28.806
cuda-2-16-multi-gpu-multi-pass | 90.893 | 49.740 | 34.518 | 29.528