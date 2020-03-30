# Core Checking (eps = 0.2, mu = 5)


Unit: seconds


### snap_pokec

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **0.254** | **0.031** | **0.035** | **0.188** | **0.222**
cuda-hybrid-kernels-multi-gpu-multi-pass | 0.365 | 0.031 | 0.036 | 0.298 | 0.331
cuda-baseline-hybrid-multi-gpu-multi-pass | 0.443 | 0.031 | 0.036 | 0.376 | 0.414
cuda-4-8-multi-gpu-multi-pass | 0.709 | 0.032 | 0.039 | 0.638 | 0.672
cuda-2-16-multi-gpu-multi-pass | 0.694 | 0.035 | 0.04 | 0.619 | 0.663
cuda-1-32-multi-gpu-multi-pass | 0.737 | 0.032 | 0.042 | 0.663 | 0.702


### snap_pokec/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **0.282** | **0.036** | **0.039** | **0.207** | **0.248**
cuda-hybrid-kernels-multi-gpu-multi-pass | 0.408 | 0.037 | 0.036 | 0.335 | 0.365
cuda-baseline-hybrid-multi-gpu-multi-pass | 0.373 | 0.034 | 0.033 | 0.306 | 0.341
cuda-4-8-multi-gpu-multi-pass | 1.306 | 0.031 | 0.041 | 1.234 | 1.275
cuda-2-16-multi-gpu-multi-pass | 1.302 | 0.034 | 0.032 | 1.236 | 1.270
cuda-1-32-multi-gpu-multi-pass | 1.35 | 0.036 | 0.034 | 1.280 | 1.314


### snap_livejournal

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **0.551** | **0.059** | **0.061** | **0.431** | **0.478**
cuda-hybrid-kernels-multi-gpu-multi-pass | 1.202 | 0.061 | 0.064 | 1.077 | 1.121
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.067 | 0.063 | 0.054 | 0.950 | 0.994
cuda-4-8-multi-gpu-multi-pass | 2.433 | 0.063 | 0.068 | 2.302 | 2.363
cuda-2-16-multi-gpu-multi-pass | 2.401 | 0.059 | 0.058 | 2.284 | 2.329
cuda-1-32-multi-gpu-multi-pass | 2.473 | 0.062 | 0.073 | 2.338 | 2.404


### snap_livejournal/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **0.597** | **0.067** | **0.063** | **0.467** | **0.522**
cuda-hybrid-kernels-multi-gpu-multi-pass | 1.092 | 0.068 | 0.066 | 0.958 | 1.003
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.087 | 0.068 | 0.065 | 0.954 | 1.011
cuda-4-8-multi-gpu-multi-pass | 2.996 | 0.068 | 0.067 | 2.861 | 2.895
cuda-2-16-multi-gpu-multi-pass | 3.012 | 0.066 | 0.06 | 2.886 | 2.938
cuda-1-32-multi-gpu-multi-pass | 2.999 | 0.071 | 0.061 | 2.867 | 2.914


### snap_orkut

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.498** | **0.172** | **0.141** | **2.185** | **2.404**
cuda-hybrid-kernels-multi-gpu-multi-pass | 8.099 | 0.174 | 0.139 | 7.786 | 8.000
cuda-baseline-hybrid-multi-gpu-multi-pass | 8.556 | 0.167 | 0.137 | 8.252 | 8.469
cuda-4-8-multi-gpu-multi-pass | 14.274 | 0.177 | 0.17 | 13.927 | 14.182
cuda-2-16-multi-gpu-multi-pass | 13.983 | 0.176 | 0.156 | 13.651 | 13.880
cuda-1-32-multi-gpu-multi-pass | 14.626 | 0.169 | 0.139 | 14.318 | 14.519


### snap_orkut/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.384** | **0.18** | **0.149** | **2.055** | **2.277**
cuda-hybrid-kernels-multi-gpu-multi-pass | 6.898 | 0.178 | 0.15 | 6.570 | 6.797
cuda-baseline-hybrid-multi-gpu-multi-pass | 12.076 | 0.19 | 0.155 | 11.731 | 11.970
cuda-4-8-multi-gpu-multi-pass | 16.694 | 0.18 | 0.154 | 16.360 | 16.587
cuda-2-16-multi-gpu-multi-pass | 16.206 | 0.183 | 0.156 | 15.867 | 16.099
cuda-1-32-multi-gpu-multi-pass | 17.88 | 0.193 | 0.153 | 17.534 | 17.774


### snap_friendster

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **124.129** | **2.804** | **6.504** | **114.821** | **112.903**
cuda-hybrid-kernels-multi-gpu-multi-pass | 116.092 | 2.9 | 6.552 | 106.640 | 109.377
cuda-baseline-hybrid-multi-gpu-multi-pass | 1243.007 | 2.898 | 6.546 | 1233.563 | 1235.830
cuda-4-8-multi-gpu-multi-pass | 105.246 | 2.858 | 6.533 | 95.855 | 98.009
cuda-2-16-multi-gpu-multi-pass | 113.757 | 2.905 | 6.527 | 104.325 | 106.543
cuda-1-32-multi-gpu-multi-pass | 162.28 | 2.861 | 6.582 | 152.837 | 155.951


### snap_friendster/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **107.435** | **2.905** | **5.674** | **98.856** | **101.112**
cuda-hybrid-kernels-multi-gpu-multi-pass | 100.877 | 2.89 | 5.74 | 92.247 | 95.218
cuda-baseline-hybrid-multi-gpu-multi-pass | 1392.556 | 3.05 | 5.364 | 1384.142 | 1385.726
cuda-4-8-multi-gpu-multi-pass | 92.758 | 3.026 | 5.43 | 84.302 | 87.877
cuda-2-16-multi-gpu-multi-pass | 98.913 | 3.065 | 5.128 | 90.720 | 93.038
cuda-1-32-multi-gpu-multi-pass | 145.512 | 3.132 | 5.564 | 136.816 | 139.087


### webgraph_it

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **397.959** | **0.62** | **0.376** | **396.963** | **397.413**
cuda-hybrid-kernels-multi-gpu-multi-pass | 24.764 | 0.615 | 0.369 | 23.780 | 24.232
cuda-baseline-hybrid-multi-gpu-multi-pass | 19.886 | 0.624 | 0.382 | 18.880 | 19.288
cuda-4-8-multi-gpu-multi-pass | 27.217 | 0.62 | 0.376 | 26.221 | 26.654
cuda-2-16-multi-gpu-multi-pass | 28.564 | 0.624 | 0.368 | 27.572 | 28.031
cuda-1-32-multi-gpu-multi-pass | 38.777 | 0.614 | 0.366 | 37.797 | 38.219


### webgraph_it/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **8.006** | **0.641** | **0.869** | **6.496** | **7.091**
cuda-hybrid-kernels-multi-gpu-multi-pass | 48.542 | 0.671 | 0.854 | 47.017 | 47.671
cuda-baseline-hybrid-multi-gpu-multi-pass | 45.826 | 0.639 | 0.791 | 44.396 | 44.919
cuda-4-8-multi-gpu-multi-pass | 215.432 | 0.663 | 0.868 | 213.901 | 214.560
cuda-2-16-multi-gpu-multi-pass | 216.352 | 0.656 | 0.963 | 214.733 | 215.428
cuda-1-32-multi-gpu-multi-pass | 219.945 | 0.657 | 0.836 | 218.452 | 219.096


### webgraph_uk

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.712** | **0.167** | **0.118** | **2.427** | **2.462**
cuda-hybrid-kernels-multi-gpu-multi-pass | 3.653 | 0.175 | 0.148 | 3.330 | 3.428
cuda-baseline-hybrid-multi-gpu-multi-pass | 3.472 | 0.176 | 0.149 | 3.147 | 3.244
cuda-4-8-multi-gpu-multi-pass | 3.795 | 0.172 | 0.125 | 3.498 | 3.574
cuda-2-16-multi-gpu-multi-pass | 3.634 | 0.167 | 0.126 | 3.341 | 3.391
cuda-1-32-multi-gpu-multi-pass | 4.457 | 0.17 | 0.118 | 4.169 | 4.205


### webgraph_uk/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.768** | **0.193** | **0.229** | **1.346** | **1.424**
cuda-hybrid-kernels-multi-gpu-multi-pass | 4.693 | 0.194 | 0.262 | 4.237 | 4.370
cuda-baseline-hybrid-multi-gpu-multi-pass | 2.741 | 0.197 | 0.239 | 2.305 | 2.403
cuda-4-8-multi-gpu-multi-pass | 12.612 | 0.203 | 0.225 | 12.184 | 12.247
cuda-2-16-multi-gpu-multi-pass | 12.553 | 0.195 | 0.241 | 12.117 | 12.226
cuda-1-32-multi-gpu-multi-pass | 12.626 | 0.193 | 0.262 | 12.171 | 12.299


### webgraph_eu

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **15.491** | **0.276** | **0.262** | **14.953** | **15.288**
cuda-hybrid-kernels-multi-gpu-multi-pass | 112.834 | 0.273 | 0.239 | 112.322 | 112.615
cuda-baseline-hybrid-multi-gpu-multi-pass | 194.431 | 0.276 | 0.221 | 193.934 | 194.240
cuda-4-8-multi-gpu-multi-pass | 118.29 | 0.282 | 0.249 | 117.759 | 118.066
cuda-2-16-multi-gpu-multi-pass | 168.53 | 0.275 | 0.241 | 168.014 | 168.340
cuda-1-32-multi-gpu-multi-pass | 306.206 | 0.275 | 0.239 | 305.692 | 305.998


### webgraph_eu/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **15.519** | **0.276** | **0.267** | **14.976** | **15.286**
cuda-hybrid-kernels-multi-gpu-multi-pass | 113.017 | 0.284 | 0.277 | 112.456 | 112.773
cuda-baseline-hybrid-multi-gpu-multi-pass | 197.563 | 0.284 | 0.294 | 196.985 | 197.346
cuda-4-8-multi-gpu-multi-pass | 111.965 | 0.28 | 0.292 | 111.393 | 111.763
cuda-2-16-multi-gpu-multi-pass | 161.494 | 0.276 | 0.297 | 160.921 | 161.269
cuda-1-32-multi-gpu-multi-pass | 296.879 | 0.286 | 0.279 | 296.314 | 296.644


### webgraph_twitter

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **98.612** | **0.869** | **1.304** | **96.439** | **97.319**
cuda-hybrid-kernels-multi-gpu-multi-pass | 241.616 | 0.876 | 1.312 | 239.428 | 240.208
cuda-baseline-hybrid-multi-gpu-multi-pass | 537.379 | 0.861 | 1.316 | 535.202 | 536.050
cuda-4-8-multi-gpu-multi-pass | 579.969 | 0.86 | 1.306 | 577.803 | 578.448
cuda-2-16-multi-gpu-multi-pass | 582.81 | 0.865 | 1.362 | 580.583 | 581.499
cuda-1-32-multi-gpu-multi-pass | 616.628 | 0.863 | 1.295 | 614.470 | 615.371


### webgraph_twitter/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **27.326** | **0.875** | **1.345** | **25.106** | **25.945**
cuda-hybrid-kernels-multi-gpu-multi-pass | 201.861 | 0.908 | 1.23 | 199.723 | 200.403
cuda-baseline-hybrid-multi-gpu-multi-pass | 669.174 | 0.902 | 1.308 | 666.964 | 667.721
cuda-4-8-multi-gpu-multi-pass | 824.232 | 0.898 | 1.137 | 822.197 | 822.635
cuda-2-16-multi-gpu-multi-pass | 815.998 | 0.888 | 1.241 | 813.869 | 814.386
cuda-1-32-multi-gpu-multi-pass | 829.114 | 0.875 | 1.188 | 827.051 | 827.605


### webgraph_webbase

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **90.755** | **0.523** | **0.489** | **89.743** | **89.062**
cuda-hybrid-kernels-multi-gpu-multi-pass | 11.357 | 0.536 | 0.431 | 10.390 | 9.770
cuda-baseline-hybrid-multi-gpu-multi-pass | 10.307 | 0.528 | 0.409 | 9.370 | 8.765
cuda-4-8-multi-gpu-multi-pass | 13.25 | 0.551 | 0.415 | 12.284 | 11.691
cuda-2-16-multi-gpu-multi-pass | 11.666 | 0.561 | 0.425 | 10.680 | 10.161
cuda-1-32-multi-gpu-multi-pass | 14.481 | 0.541 | 0.424 | 13.516 | 12.791


### webgraph_webbase/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **12.799** | **0.587** | **0.92** | **11.292** | **10.967**
cuda-hybrid-kernels-multi-gpu-multi-pass | 15.547 | 0.638 | 0.9 | 14.009 | 13.388
cuda-baseline-hybrid-multi-gpu-multi-pass | 13.195 | 0.646 | 0.909 | 11.640 | 11.149
cuda-4-8-multi-gpu-multi-pass | 47.953 | 0.649 | 0.902 | 46.402 | 45.720
cuda-2-16-multi-gpu-multi-pass | 48.131 | 0.645 | 0.895 | 46.591 | 45.870
cuda-1-32-multi-gpu-multi-pass | 48.953 | 0.636 | 0.924 | 47.393 | 46.748


### n12dot5_m80_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **20.422** | **1.596** | **2.029** | **16.797** | **18.738**
cuda-hybrid-kernels-multi-gpu-multi-pass | 48.681 | 1.539 | 2.027 | 45.115 | 46.885
cuda-baseline-hybrid-multi-gpu-multi-pass | 656.577 | 1.643 | 2.014 | 652.920 | 654.847
cuda-4-8-multi-gpu-multi-pass | 61.112 | 1.589 | 2.016 | 57.507 | 59.335
cuda-2-16-multi-gpu-multi-pass | 59.882 | 1.579 | 2.023 | 56.280 | 58.160
cuda-1-32-multi-gpu-multi-pass | 70.204 | 1.596 | 1.989 | 66.619 | 68.526


### n12dot5_m80_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **20.255** | **1.545** | **1.959** | **16.751** | **18.867**
cuda-hybrid-kernels-multi-gpu-multi-pass | 47.995 | 1.517 | 1.989 | 44.489 | 46.343
cuda-baseline-hybrid-multi-gpu-multi-pass | 626.606 | 1.636 | 1.987 | 622.983 | 624.867
cuda-4-8-multi-gpu-multi-pass | 61.489 | 1.608 | 1.996 | 57.885 | 59.775
cuda-2-16-multi-gpu-multi-pass | 61.343 | 1.602 | 1.987 | 57.754 | 59.739
cuda-1-32-multi-gpu-multi-pass | 70.19 | 1.589 | 1.971 | 66.630 | 68.509


### n16dot7_m60_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **18.913** | **1.581** | **2.378** | **14.954** | **16.871**
cuda-hybrid-kernels-multi-gpu-multi-pass | 39.297 | 1.503 | 2.324 | 35.470 | 37.374
cuda-baseline-hybrid-multi-gpu-multi-pass | 550.79 | 1.659 | 2.314 | 546.817 | 548.819
cuda-4-8-multi-gpu-multi-pass | 56.026 | 1.626 | 2.296 | 52.104 | 54.084
cuda-2-16-multi-gpu-multi-pass | 58.239 | 1.65 | 2.335 | 54.254 | 56.172
cuda-1-32-multi-gpu-multi-pass | 61.799 | 1.645 | 2.336 | 57.818 | 59.777


### n16dot7_m60_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **18.89** | **1.61** | **2.286** | **14.994** | **16.991**
cuda-hybrid-kernels-multi-gpu-multi-pass | 39.96 | 1.477 | 2.268 | 36.215 | 38.050
cuda-baseline-hybrid-multi-gpu-multi-pass | 493.204 | 1.66 | 2.319 | 489.225 | 491.216
cuda-4-8-multi-gpu-multi-pass | 54.602 | 1.564 | 2.26 | 50.778 | 52.773
cuda-2-16-multi-gpu-multi-pass | 58.35 | 1.609 | 2.316 | 54.425 | 56.479
cuda-1-32-multi-gpu-multi-pass | 60.729 | 1.616 | 2.321 | 56.792 | 58.752


### n25_m40_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **19.131** | **1.706** | **2.729** | **14.696** | **16.814**
cuda-hybrid-kernels-multi-gpu-multi-pass | 31.522 | 1.536 | 2.707 | 27.279 | 29.224
cuda-baseline-hybrid-multi-gpu-multi-pass | 410.974 | 1.674 | 2.675 | 406.625 | 408.662
cuda-4-8-multi-gpu-multi-pass | 45.202 | 1.658 | 2.721 | 40.823 | 42.970
cuda-2-16-multi-gpu-multi-pass | 44.01 | 1.645 | 2.727 | 39.638 | 41.714
cuda-1-32-multi-gpu-multi-pass | 47.675 | 1.718 | 2.688 | 43.269 | 45.313


### n25_m40_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **18.17** | **1.677** | **2.688** | **13.805** | **15.872**
cuda-hybrid-kernels-multi-gpu-multi-pass | 32.605 | 1.569 | 2.698 | 28.338 | 30.283
cuda-baseline-hybrid-multi-gpu-multi-pass | 373.256 | 1.635 | 2.726 | 368.895 | 371.045
cuda-4-8-multi-gpu-multi-pass | 43.636 | 1.631 | 2.685 | 39.320 | 41.301
cuda-2-16-multi-gpu-multi-pass | 44.726 | 1.649 | 2.689 | 40.388 | 42.521
cuda-1-32-multi-gpu-multi-pass | 48.165 | 1.654 | 2.745 | 43.766 | 45.904


### n50_m20_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.538** | **1.723** | **3.203** | **12.612** | **14.573**
cuda-hybrid-kernels-multi-gpu-multi-pass | 25.393 | 1.579 | 3.155 | 20.659 | 22.668
cuda-baseline-hybrid-multi-gpu-multi-pass | 247.911 | 1.776 | 3.18 | 242.955 | 244.898
cuda-4-8-multi-gpu-multi-pass | 34.589 | 1.621 | 3.124 | 29.844 | 31.709
cuda-2-16-multi-gpu-multi-pass | 33.54 | 1.683 | 3.177 | 28.680 | 30.540
cuda-1-32-multi-gpu-multi-pass | 37.342 | 1.683 | 3.219 | 32.440 | 34.066


### n50_m20_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.934** | **1.679** | **3.195** | **13.060** | **15.088**
cuda-hybrid-kernels-multi-gpu-multi-pass | 24.682 | 1.618 | 3.175 | 19.889 | 21.643
cuda-baseline-hybrid-multi-gpu-multi-pass | 237.416 | 1.694 | 3.19 | 232.532 | 234.499
cuda-4-8-multi-gpu-multi-pass | 33.851 | 1.636 | 3.135 | 29.080 | 31.143
cuda-2-16-multi-gpu-multi-pass | 33.12 | 1.665 | 3.183 | 28.272 | 30.316
cuda-1-32-multi-gpu-multi-pass | 36.48 | 1.653 | 3.155 | 31.672 | 33.775


### lfr_graphs/n2400000_k100_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **3.045** | **0.191** | **0.143** | **2.711** | **2.954**
cuda-hybrid-kernels-multi-gpu-multi-pass | 3.065 | 0.181 | 0.145 | 2.739 | 2.974
cuda-baseline-hybrid-multi-gpu-multi-pass | 3.665 | 0.187 | 0.146 | 3.332 | 3.573
cuda-4-8-multi-gpu-multi-pass | 3.102 | 0.185 | 0.147 | 2.770 | 3.015
cuda-2-16-multi-gpu-multi-pass | 3.514 | 0.192 | 0.145 | 3.177 | 3.427
cuda-1-32-multi-gpu-multi-pass | 4.653 | 0.183 | 0.146 | 4.324 | 4.565


### lfr_graphs/n2400000_k100_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **3.032** | **0.175** | **0.145** | **2.712** | **2.933**
cuda-hybrid-kernels-multi-gpu-multi-pass | 2.771 | 0.178 | 0.145 | 2.448 | 2.673
cuda-baseline-hybrid-multi-gpu-multi-pass | 3.704 | 0.181 | 0.146 | 3.377 | 3.598
cuda-4-8-multi-gpu-multi-pass | 2.798 | 0.182 | 0.142 | 2.474 | 2.687
cuda-2-16-multi-gpu-multi-pass | 3.289 | 0.177 | 0.144 | 2.968 | 3.188
cuda-1-32-multi-gpu-multi-pass | 4.652 | 0.182 | 0.147 | 4.323 | 4.547


### lfr_graphs/n3000000_k80_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.941** | **0.19** | **0.154** | **2.597** | **2.847**
cuda-hybrid-kernels-multi-gpu-multi-pass | 3.325 | 0.189 | 0.148 | 2.988 | 3.229
cuda-baseline-hybrid-multi-gpu-multi-pass | 3.475 | 0.195 | 0.161 | 3.119 | 3.378
cuda-4-8-multi-gpu-multi-pass | 2.992 | 0.196 | 0.148 | 2.648 | 2.893
cuda-2-16-multi-gpu-multi-pass | 3.184 | 0.187 | 0.15 | 2.847 | 3.084
cuda-1-32-multi-gpu-multi-pass | 4.199 | 0.188 | 0.149 | 3.862 | 4.103


### lfr_graphs/n3000000_k80_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.731** | **0.184** | **0.184** | **2.363** | **2.626**
cuda-hybrid-kernels-multi-gpu-multi-pass | 2.693 | 0.181 | 0.147 | 2.365 | 2.590
cuda-baseline-hybrid-multi-gpu-multi-pass | 3.317 | 0.178 | 0.149 | 2.990 | 3.205
cuda-4-8-multi-gpu-multi-pass | 2.71 | 0.174 | 0.146 | 2.390 | 2.599
cuda-2-16-multi-gpu-multi-pass | 3.025 | 0.18 | 0.147 | 2.698 | 2.906
cuda-1-32-multi-gpu-multi-pass | 4.078 | 0.182 | 0.149 | 3.747 | 3.969


### lfr_graphs/n4000000_k60_C0dot1_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.681** | **0.195** | **0.156** | **2.330** | **2.567**
cuda-hybrid-kernels-multi-gpu-multi-pass | 3.276 | 0.195 | 0.155 | 2.926 | 3.158
cuda-baseline-hybrid-multi-gpu-multi-pass | 3.307 | 0.2 | 0.156 | 2.951 | 3.198
cuda-4-8-multi-gpu-multi-pass | 2.608 | 0.194 | 0.154 | 2.260 | 2.504
cuda-2-16-multi-gpu-multi-pass | 2.721 | 0.199 | 0.154 | 2.368 | 2.615
cuda-1-32-multi-gpu-multi-pass | 3.821 | 0.194 | 0.152 | 3.475 | 3.720


### lfr_graphs/n4000000_k60_C0dot1_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.486** | **0.186** | **0.155** | **2.145** | **2.359**
cuda-hybrid-kernels-multi-gpu-multi-pass | 2.728 | 0.186 | 0.158 | 2.384 | 2.596
cuda-baseline-hybrid-multi-gpu-multi-pass | 2.862 | 0.182 | 0.156 | 2.524 | 2.730
cuda-4-8-multi-gpu-multi-pass | 2.621 | 0.179 | 0.151 | 2.291 | 2.494
cuda-2-16-multi-gpu-multi-pass | 2.646 | 0.18 | 0.153 | 2.313 | 2.517
cuda-1-32-multi-gpu-multi-pass | 3.707 | 0.189 | 0.156 | 3.362 | 3.580


### lfr_graphs/n4000000_k60_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.622** | **0.202** | **0.153** | **2.267** | **2.503**
cuda-hybrid-kernels-multi-gpu-multi-pass | 2.802 | 0.205 | 0.189 | 2.408 | 2.682
cuda-baseline-hybrid-multi-gpu-multi-pass | 3.304 | 0.199 | 0.157 | 2.948 | 3.203
cuda-4-8-multi-gpu-multi-pass | 2.656 | 0.198 | 0.154 | 2.304 | 2.545
cuda-2-16-multi-gpu-multi-pass | 2.764 | 0.197 | 0.154 | 2.413 | 2.655
cuda-1-32-multi-gpu-multi-pass | 3.769 | 0.202 | 0.156 | 3.411 | 3.656


### lfr_graphs/n4000000_k60_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.473** | **0.18** | **0.155** | **2.138** | **2.337**
cuda-hybrid-kernels-multi-gpu-multi-pass | 2.603 | 0.194 | 0.156 | 2.253 | 2.477
cuda-baseline-hybrid-multi-gpu-multi-pass | 2.978 | 0.188 | 0.157 | 2.633 | 2.858
cuda-4-8-multi-gpu-multi-pass | 2.554 | 0.181 | 0.157 | 2.216 | 2.418
cuda-2-16-multi-gpu-multi-pass | 2.609 | 0.186 | 0.157 | 2.266 | 2.484
cuda-1-32-multi-gpu-multi-pass | 3.602 | 0.184 | 0.154 | 3.264 | 3.471


### lfr_graphs/n6000000_k40_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.379** | **0.205** | **0.18** | **1.994** | **2.220**
cuda-hybrid-kernels-multi-gpu-multi-pass | 2.474 | 0.205 | 0.177 | 2.092 | 2.337
cuda-baseline-hybrid-multi-gpu-multi-pass | 3.285 | 0.21 | 0.19 | 2.885 | 3.148
cuda-4-8-multi-gpu-multi-pass | 2.503 | 0.208 | 0.174 | 2.121 | 2.358
cuda-2-16-multi-gpu-multi-pass | 2.533 | 0.211 | 0.178 | 2.144 | 2.394
cuda-1-32-multi-gpu-multi-pass | 3.258 | 0.205 | 0.194 | 2.859 | 3.110


### lfr_graphs/n6000000_k40_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.424** | **0.194** | **0.188** | **2.042** | **2.242**
cuda-hybrid-kernels-multi-gpu-multi-pass | 2.494 | 0.187 | 0.182 | 2.125 | 2.313
cuda-baseline-hybrid-multi-gpu-multi-pass | 2.745 | 0.19 | 0.181 | 2.374 | 2.570
cuda-4-8-multi-gpu-multi-pass | 2.369 | 0.192 | 0.183 | 1.994 | 2.199
cuda-2-16-multi-gpu-multi-pass | 2.613 | 0.188 | 0.178 | 2.247 | 2.435
cuda-1-32-multi-gpu-multi-pass | 3.073 | 0.186 | 0.189 | 2.698 | 2.898