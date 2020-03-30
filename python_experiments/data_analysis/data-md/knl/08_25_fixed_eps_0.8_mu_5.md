# Core Checking (eps = 0.8, mu = 5)


Unit: seconds


## varying num of threads


### small_snap_cit_patents

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.006 | / | / | /
naive-galloping-single | / | / | 0.005 | / | / | /
**naive-hybrid** | **/** | **/** | **0.006** | **/** | **/** | **/**
naive-merge | / | / | 0.005 | / | / | /
naive-pivot | / | / | 0.017 | / | / | /
**sse-hybrid** | **/** | **/** | **0.014** | **/** | **/** | **/**
sse-merge | / | / | 0.006 | / | / | /
sse-pivot | / | / | 0.016 | / | / | /
avx2-galloping-double | / | / | 0.013 | / | / | /
avx2-galloping-single | / | / | 0.006 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.007** | **/** | **/** | **/**
avx2-merge | / | / | 0.015 | / | / | /
avx2-merge-popcnt | / | / | 0.018 | / | / | /
avx2-pivot | / | / | 0.018 | / | / | /
avx512-galloping-double | / | / | 0.017 | / | / | /
avx512-galloping-single | / | / | 0.005 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.006** | **/** | **/** | **/**
avx512-merge | / | / | 0.006 | / | / | /
avx512-merge-popcnt | / | / | 0.006 | / | / | /
avx512-pivot | / | / | 0.005 | / | / | /


### small_snap_dblp

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.037 | / | / | /
naive-galloping-single | / | / | 0.012 | / | / | /
**naive-hybrid** | **/** | **/** | **0.019** | **/** | **/** | **/**
naive-merge | / | / | 0.027 | / | / | /
naive-pivot | / | / | 0.012 | / | / | /
**sse-hybrid** | **/** | **/** | **0.014** | **/** | **/** | **/**
sse-merge | / | / | 0.01 | / | / | /
sse-pivot | / | / | 0.024 | / | / | /
avx2-galloping-double | / | / | 0.022 | / | / | /
avx2-galloping-single | / | / | 0.016 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.01** | **/** | **/** | **/**
avx2-merge | / | / | 0.01 | / | / | /
avx2-merge-popcnt | / | / | 0.012 | / | / | /
avx2-pivot | / | / | 0.024 | / | / | /
avx512-galloping-double | / | / | 0.021 | / | / | /
avx512-galloping-single | / | / | 0.015 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.015** | **/** | **/** | **/**
avx512-merge | / | / | 0.009 | / | / | /
avx512-merge-popcnt | / | / | 0.009 | / | / | /
avx512-pivot | / | / | 0.013 | / | / | /


### small_snap_web_berkstan

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.069 | / | / | /
naive-galloping-single | / | / | 0.048 | / | / | /
**naive-hybrid** | **/** | **/** | **0.049** | **/** | **/** | **/**
naive-merge | / | / | 0.059 | / | / | /
naive-pivot | / | / | 0.062 | / | / | /
**sse-hybrid** | **/** | **/** | **0.035** | **/** | **/** | **/**
sse-merge | / | / | 0.046 | / | / | /
sse-pivot | / | / | 0.137 | / | / | /
avx2-galloping-double | / | / | 0.127 | / | / | /
avx2-galloping-single | / | / | 0.084 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.032** | **/** | **/** | **/**
avx2-merge | / | / | 0.044 | / | / | /
avx2-merge-popcnt | / | / | 0.043 | / | / | /
avx2-pivot | / | / | 0.125 | / | / | /
avx512-galloping-double | / | / | 0.111 | / | / | /
avx512-galloping-single | / | / | 0.088 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.033** | **/** | **/** | **/**
avx512-merge | / | / | 0.026 | / | / | /
avx512-merge-popcnt | / | / | 0.026 | / | / | /
avx512-pivot | / | / | 0.066 | / | / | /


### small_snap_web_notredame

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.042 | / | / | /
naive-galloping-single | / | / | 0.032 | / | / | /
**naive-hybrid** | **/** | **/** | **0.042** | **/** | **/** | **/**
naive-merge | / | / | 0.077 | / | / | /
naive-pivot | / | / | 0.063 | / | / | /
**sse-hybrid** | **/** | **/** | **0.02** | **/** | **/** | **/**
sse-merge | / | / | 0.029 | / | / | /
sse-pivot | / | / | 0.108 | / | / | /
avx2-galloping-double | / | / | 0.089 | / | / | /
avx2-galloping-single | / | / | 0.058 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.018** | **/** | **/** | **/**
avx2-merge | / | / | 0.018 | / | / | /
avx2-merge-popcnt | / | / | 0.03 | / | / | /
avx2-pivot | / | / | 0.096 | / | / | /
avx512-galloping-double | / | / | 0.086 | / | / | /
avx512-galloping-single | / | / | 0.065 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.014** | **/** | **/** | **/**
avx512-merge | / | / | 0.013 | / | / | /
avx512-merge-popcnt | / | / | 0.013 | / | / | /
avx512-pivot | / | / | 0.052 | / | / | /


### small_snap_web_stanford

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.014 | / | / | /
naive-galloping-single | / | / | 0.011 | / | / | /
**naive-hybrid** | **/** | **/** | **0.011** | **/** | **/** | **/**
naive-merge | / | / | 0.015 | / | / | /
naive-pivot | / | / | 0.01 | / | / | /
**sse-hybrid** | **/** | **/** | **0.009** | **/** | **/** | **/**
sse-merge | / | / | 0.019 | / | / | /
sse-pivot | / | / | 0.022 | / | / | /
avx2-galloping-double | / | / | 0.02 | / | / | /
avx2-galloping-single | / | / | 0.027 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.008** | **/** | **/** | **/**
avx2-merge | / | / | 0.008 | / | / | /
avx2-merge-popcnt | / | / | 0.024 | / | / | /
avx2-pivot | / | / | 0.019 | / | / | /
avx512-galloping-double | / | / | 0.018 | / | / | /
avx512-galloping-single | / | / | 0.016 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.007** | **/** | **/** | **/**
avx512-merge | / | / | 0.007 | / | / | /
avx512-merge-popcnt | / | / | 0.015 | / | / | /
avx512-pivot | / | / | 0.012 | / | / | /


### snap_pokec

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.218 | / | / | /
naive-galloping-single | / | / | 0.208 | / | / | /
**naive-hybrid** | **/** | **/** | **0.264** | **/** | **/** | **/**
naive-merge | / | / | 0.463 | / | / | /
naive-pivot | / | / | 0.581 | / | / | /
**sse-hybrid** | **/** | **/** | **0.172** | **/** | **/** | **/**
sse-merge | / | / | 0.28 | / | / | /
sse-pivot | / | / | 0.436 | / | / | /
avx2-galloping-double | / | / | 0.286 | / | / | /
avx2-galloping-single | / | / | 0.255 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.155** | **/** | **/** | **/**
avx2-merge | / | / | 0.149 | / | / | /
avx2-merge-popcnt | / | / | 0.353 | / | / | /
avx2-pivot | / | / | 0.325 | / | / | /
avx512-galloping-double | / | / | 0.215 | / | / | /
avx512-galloping-single | / | / | 0.193 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.17** | **/** | **/** | **/**
avx512-merge | / | / | 0.168 | / | / | /
avx512-merge-popcnt | / | / | 0.133 | / | / | /
avx512-pivot | / | / | 0.211 | / | / | /


### snap_livejournal

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.716 | / | / | /
naive-galloping-single | / | / | 0.731 | / | / | /
**naive-hybrid** | **/** | **/** | **0.7** | **/** | **/** | **/**
naive-merge | / | / | 0.991 | / | / | /
naive-pivot | / | / | 0.942 | / | / | /
**sse-hybrid** | **/** | **/** | **0.515** | **/** | **/** | **/**
sse-merge | / | / | 0.598 | / | / | /
sse-pivot | / | / | 1.197 | / | / | /
avx2-galloping-double | / | / | 1.016 | / | / | /
avx2-galloping-single | / | / | 0.749 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.465** | **/** | **/** | **/**
avx2-merge | / | / | 0.412 | / | / | /
avx2-merge-popcnt | / | / | 0.69 | / | / | /
avx2-pivot | / | / | 0.999 | / | / | /
avx512-galloping-double | / | / | 0.904 | / | / | /
avx512-galloping-single | / | / | 0.659 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.417** | **/** | **/** | **/**
avx512-merge | / | / | 0.335 | / | / | /
avx512-merge-popcnt | / | / | 0.416 | / | / | /
avx512-pivot | / | / | 0.577 | / | / | /


### snap_orkut

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 5.383 | / | / | /
naive-galloping-single | / | / | 5.011 | / | / | /
**naive-hybrid** | **/** | **/** | **5.43** | **/** | **/** | **/**
naive-merge | / | / | 6.16 | / | / | /
naive-pivot | / | / | 5.948 | / | / | /
**sse-hybrid** | **/** | **/** | **3.665** | **/** | **/** | **/**
sse-merge | / | / | 3.88 | / | / | /
sse-pivot | / | / | 8.099 | / | / | /
avx2-galloping-double | / | / | 5.97 | / | / | /
avx2-galloping-single | / | / | 5.04 | / | / | /
**avx2-hybrid** | **/** | **/** | **2.782** | **/** | **/** | **/**
avx2-merge | / | / | 2.765 | / | / | /
avx2-merge-popcnt | / | / | 4.855 | / | / | /
avx2-pivot | / | / | 6.325 | / | / | /
avx512-galloping-double | / | / | 5.109 | / | / | /
avx512-galloping-single | / | / | 4.46 | / | / | /
**avx512-hybrid** | **/** | **/** | **2.11** | **/** | **/** | **/**
avx512-merge | / | / | 2.113 | / | / | /
avx512-merge-popcnt | / | / | 2.317 | / | / | /
avx512-pivot | / | / | 3.415 | / | / | /


### snap_friendster

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 115.236 | / | / | /
naive-galloping-single | / | / | 108.622 | / | / | /
**naive-hybrid** | **/** | **/** | **107.832** | **/** | **/** | **/**
naive-merge | / | / | 107.755 | / | / | /
naive-pivot | / | / | 103.101 | / | / | /
**sse-hybrid** | **/** | **/** | **71.986** | **/** | **/** | **/**
sse-merge | / | / | 71.553 | / | / | /
sse-pivot | / | / | 161.498 | / | / | /
avx2-galloping-double | / | / | 127.044 | / | / | /
avx2-galloping-single | / | / | 106.056 | / | / | /
**avx2-hybrid** | **/** | **/** | **53.738** | **/** | **/** | **/**
avx2-merge | / | / | 52.877 | / | / | /
avx2-merge-popcnt | / | / | 93.489 | / | / | /
avx2-pivot | / | / | 124.312 | / | / | /
avx512-galloping-double | / | / | 108.902 | / | / | /
avx512-galloping-single | / | / | 92.236 | / | / | /
**avx512-hybrid** | **/** | **/** | **39.386** | **/** | **/** | **/**
avx512-merge | / | / | 38.399 | / | / | /
avx512-merge-popcnt | / | / | 42.521 | / | / | /
avx512-pivot | / | / | 66.37 | / | / | /


### webgraph_it

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 19.434 | / | / | /
naive-galloping-single | / | / | 17.863 | / | / | /
**naive-hybrid** | **/** | **/** | **30.398** | **/** | **/** | **/**
naive-merge | / | / | / | / | / | /
naive-pivot | / | / | / | / | / | /
**sse-hybrid** | **/** | **/** | **18.275** | **/** | **/** | **/**
sse-merge | / | / | 546.25 | / | / | /
sse-pivot | / | / | 886.769 | / | / | /
avx2-galloping-double | / | / | 41.383 | / | / | /
avx2-galloping-single | / | / | 28.849 | / | / | /
**avx2-hybrid** | **/** | **/** | **14.447** | **/** | **/** | **/**
avx2-merge | / | / | 445.392 | / | / | /
avx2-merge-popcnt | / | / | 566.096 | / | / | /
avx2-pivot | / | / | 542.288 | / | / | /
avx512-galloping-double | / | / | 38.614 | / | / | /
avx512-galloping-single | / | / | 26.103 | / | / | /
**avx512-hybrid** | **/** | **/** | **11.923** | **/** | **/** | **/**
avx512-merge | / | / | 437.608 | / | / | /
avx512-merge-popcnt | / | / | 446.922 | / | / | /
avx512-pivot | / | / | 502.248 | / | / | /


### webgraph_uk

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 2.22 | / | / | /
naive-galloping-single | / | / | 2.122 | / | / | /
**naive-hybrid** | **/** | **/** | **4.396** | **/** | **/** | **/**
naive-merge | / | / | 9.985 | / | / | /
naive-pivot | / | / | 8.166 | / | / | /
**sse-hybrid** | **/** | **/** | **2.443** | **/** | **/** | **/**
sse-merge | / | / | 4.334 | / | / | /
sse-pivot | / | / | 9.28 | / | / | /
avx2-galloping-double | / | / | 4.366 | / | / | /
avx2-galloping-single | / | / | 3.081 | / | / | /
**avx2-hybrid** | **/** | **/** | **1.764** | **/** | **/** | **/**
avx2-merge | / | / | 2.714 | / | / | /
avx2-merge-popcnt | / | / | 4.895 | / | / | /
avx2-pivot | / | / | 7.6 | / | / | /
avx512-galloping-double | / | / | 4.071 | / | / | /
avx512-galloping-single | / | / | 2.891 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.454** | **/** | **/** | **/**
avx512-merge | / | / | 2.032 | / | / | /
avx512-merge-popcnt | / | / | 2.186 | / | / | /
avx512-pivot | / | / | 5.121 | / | / | /


### webgraph_eu

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 189.632 | / | / | /
naive-galloping-single | / | / | 162.348 | / | / | /
**naive-hybrid** | **/** | **/** | **119.874** | **/** | **/** | **/**
naive-merge | / | / | 139.764 | / | / | /
naive-pivot | / | / | 146.281 | / | / | /
**sse-hybrid** | **/** | **/** | **86.361** | **/** | **/** | **/**
sse-merge | / | / | 92.96 | / | / | /
sse-pivot | / | / | 616.087 | / | / | /
avx2-galloping-double | / | / | 490.798 | / | / | /
avx2-galloping-single | / | / | 314.168 | / | / | /
**avx2-hybrid** | **/** | **/** | **75.061** | **/** | **/** | **/**
avx2-merge | / | / | 78.885 | / | / | /
avx2-merge-popcnt | / | / | 153.386 | / | / | /
avx2-pivot | / | / | 494.154 | / | / | /
avx512-galloping-double | / | / | 467.815 | / | / | /
avx512-galloping-single | / | / | 290.63 | / | / | /
**avx512-hybrid** | **/** | **/** | **43.79** | **/** | **/** | **/**
avx512-merge | / | / | 47.058 | / | / | /
avx512-merge-popcnt | / | / | 52.797 | / | / | /
avx512-pivot | / | / | 278.341 | / | / | /


### webgraph_twitter

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 135.563 | / | / | /
naive-galloping-single | / | / | 129.724 | / | / | /
**naive-hybrid** | **/** | **/** | **166.046** | **/** | **/** | **/**
naive-merge | / | / | / | / | / | /
naive-pivot | / | / | / | / | / | /
**sse-hybrid** | **/** | **/** | **101.776** | **/** | **/** | **/**
sse-merge | / | / | 734.685 | / | / | /
sse-pivot | / | / | / | / | / | /
avx2-galloping-double | / | / | 157.312 | / | / | /
avx2-galloping-single | / | / | 133.59 | / | / | /
**avx2-hybrid** | **/** | **/** | **74.607** | **/** | **/** | **/**
avx2-merge | / | / | 626.889 | / | / | /
avx2-merge-popcnt | / | / | 774.998 | / | / | /
avx2-pivot | / | / | / | / | / | /
avx512-galloping-double | / | / | 131.584 | / | / | /
avx512-galloping-single | / | / | 110.673 | / | / | /
**avx512-hybrid** | **/** | **/** | **54.932** | **/** | **/** | **/**
avx512-merge | / | / | 600.309 | / | / | /
avx512-merge-popcnt | / | / | 606.346 | / | / | /
avx512-pivot | / | / | 956.376 | / | / | /


### webgraph_webbase

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 6.781 | / | / | /
naive-galloping-single | / | / | 6.254 | / | / | /
**naive-hybrid** | **/** | **/** | **10.563** | **/** | **/** | **/**
naive-merge | / | / | 110.809 | / | / | /
naive-pivot | / | / | 88.243 | / | / | /
**sse-hybrid** | **/** | **/** | **6.545** | **/** | **/** | **/**
sse-merge | / | / | 40.342 | / | / | /
sse-pivot | / | / | 80.827 | / | / | /
avx2-galloping-double | / | / | 13.43 | / | / | /
avx2-galloping-single | / | / | 9.625 | / | / | /
**avx2-hybrid** | **/** | **/** | **5.285** | **/** | **/** | **/**
avx2-merge | / | / | 27.097 | / | / | /
avx2-merge-popcnt | / | / | 43.271 | / | / | /
avx2-pivot | / | / | 72.947 | / | / | /
avx512-galloping-double | / | / | 12.455 | / | / | /
avx512-galloping-single | / | / | 8.625 | / | / | /
**avx512-hybrid** | **/** | **/** | **4.261** | **/** | **/** | **/**
avx512-merge | / | / | 24.087 | / | / | /
avx512-merge-popcnt | / | / | 24.32 | / | / | /
avx512-pivot | / | / | 54.758 | / | / | /


### lfr_dataset

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 3.297 | / | / | /
naive-galloping-single | / | / | 2.993 | / | / | /
**naive-hybrid** | **/** | **/** | **3.208** | **/** | **/** | **/**
naive-merge | / | / | 3.138 | / | / | /
naive-pivot | / | / | 2.989 | / | / | /
**sse-hybrid** | **/** | **/** | **2.286** | **/** | **/** | **/**
sse-merge | / | / | 2.277 | / | / | /
sse-pivot | / | / | 6.278 | / | / | /
avx2-galloping-double | / | / | 5.342 | / | / | /
avx2-galloping-single | / | / | 4.03 | / | / | /
**avx2-hybrid** | **/** | **/** | **2.031** | **/** | **/** | **/**
avx2-merge | / | / | 1.923 | / | / | /
avx2-merge-popcnt | / | / | 2.827 | / | / | /
avx2-pivot | / | / | 4.904 | / | / | /
avx512-galloping-double | / | / | 4.905 | / | / | /
avx512-galloping-single | / | / | 3.466 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.696** | **/** | **/** | **/**
avx512-merge | / | / | 1.664 | / | / | /
avx512-merge-popcnt | / | / | 1.773 | / | / | /
avx512-pivot | / | / | 2.943 | / | / | /


### lfr_graphs/n2400000_k100_C0dot3_Bin

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 3.846 | / | / | /
naive-galloping-single | / | / | 3.548 | / | / | /
**naive-hybrid** | **/** | **/** | **3.613** | **/** | **/** | **/**
naive-merge | / | / | 3.548 | / | / | /
naive-pivot | / | / | 3.364 | / | / | /
**sse-hybrid** | **/** | **/** | **2.455** | **/** | **/** | **/**
sse-merge | / | / | 2.417 | / | / | /
sse-pivot | / | / | 7.138 | / | / | /
avx2-galloping-double | / | / | 6.276 | / | / | /
avx2-galloping-single | / | / | 4.666 | / | / | /
**avx2-hybrid** | **/** | **/** | **2.038** | **/** | **/** | **/**
avx2-merge | / | / | 2.067 | / | / | /
avx2-merge-popcnt | / | / | 3.239 | / | / | /
avx2-pivot | / | / | 5.846 | / | / | /
avx512-galloping-double | / | / | 5.617 | / | / | /
avx512-galloping-single | / | / | 4.103 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.844** | **/** | **/** | **/**
avx512-merge | / | / | 1.69 | / | / | /
avx512-merge-popcnt | / | / | 1.869 | / | / | /
avx512-pivot | / | / | 3.395 | / | / | /


### lfr_graphs/n3000000_k80_C0dot3_Bin

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 3.38 | / | / | /
naive-galloping-single | / | / | 3.12 | / | / | /
**naive-hybrid** | **/** | **/** | **3.232** | **/** | **/** | **/**
naive-merge | / | / | 3.127 | / | / | /
naive-pivot | / | / | 2.987 | / | / | /
**sse-hybrid** | **/** | **/** | **2.27** | **/** | **/** | **/**
sse-merge | / | / | 2.302 | / | / | /
sse-pivot | / | / | 6.318 | / | / | /
avx2-galloping-double | / | / | 5.377 | / | / | /
avx2-galloping-single | / | / | 4.063 | / | / | /
**avx2-hybrid** | **/** | **/** | **1.991** | **/** | **/** | **/**
avx2-merge | / | / | 1.95 | / | / | /
avx2-merge-popcnt | / | / | 2.955 | / | / | /
avx2-pivot | / | / | 5.018 | / | / | /
avx512-galloping-double | / | / | 4.815 | / | / | /
avx512-galloping-single | / | / | 3.536 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.744** | **/** | **/** | **/**
avx512-merge | / | / | 1.476 | / | / | /
avx512-merge-popcnt | / | / | 1.723 | / | / | /
avx512-pivot | / | / | 2.991 | / | / | /


### lfr_graphs/n4000000_k60_C0dot1_Bin

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 2.952 | / | / | /
naive-galloping-single | / | / | 2.621 | / | / | /
**naive-hybrid** | **/** | **/** | **2.975** | **/** | **/** | **/**
naive-merge | / | / | 2.897 | / | / | /
naive-pivot | / | / | 2.716 | / | / | /
**sse-hybrid** | **/** | **/** | **2.172** | **/** | **/** | **/**
sse-merge | / | / | 2.134 | / | / | /
sse-pivot | / | / | 5.129 | / | / | /
avx2-galloping-double | / | / | 4.533 | / | / | /
avx2-galloping-single | / | / | 3.417 | / | / | /
**avx2-hybrid** | **/** | **/** | **1.877** | **/** | **/** | **/**
avx2-merge | / | / | 1.816 | / | / | /
avx2-merge-popcnt | / | / | 2.654 | / | / | /
avx2-pivot | / | / | 4.155 | / | / | /
avx512-galloping-double | / | / | 4.22 | / | / | /
avx512-galloping-single | / | / | 3.098 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.705** | **/** | **/** | **/**
avx512-merge | / | / | 1.422 | / | / | /
avx512-merge-popcnt | / | / | 1.627 | / | / | /
avx512-pivot | / | / | 2.49 | / | / | /


### lfr_graphs/n4000000_k60_C0dot3_Bin

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 3.027 | / | / | /
naive-galloping-single | / | / | 2.63 | / | / | /
**naive-hybrid** | **/** | **/** | **2.983** | **/** | **/** | **/**
naive-merge | / | / | 2.891 | / | / | /
naive-pivot | / | / | 2.718 | / | / | /
**sse-hybrid** | **/** | **/** | **2.085** | **/** | **/** | **/**
sse-merge | / | / | 2.099 | / | / | /
sse-pivot | / | / | 5.131 | / | / | /
avx2-galloping-double | / | / | 4.501 | / | / | /
avx2-galloping-single | / | / | 3.442 | / | / | /
**avx2-hybrid** | **/** | **/** | **1.894** | **/** | **/** | **/**
avx2-merge | / | / | 1.89 | / | / | /
avx2-merge-popcnt | / | / | 2.527 | / | / | /
avx2-pivot | / | / | 4.24 | / | / | /
avx512-galloping-double | / | / | 4.214 | / | / | /
avx512-galloping-single | / | / | 2.994 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.614** | **/** | **/** | **/**
avx512-merge | / | / | 1.421 | / | / | /
avx512-merge-popcnt | / | / | 1.638 | / | / | /
avx512-pivot | / | / | 2.577 | / | / | /


### lfr_graphs/n6000000_k40_C0dot3_Bin

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 2.586 | / | / | /
naive-galloping-single | / | / | 2.292 | / | / | /
**naive-hybrid** | **/** | **/** | **2.721** | **/** | **/** | **/**
naive-merge | / | / | 2.641 | / | / | /
naive-pivot | / | / | 2.453 | / | / | /
**sse-hybrid** | **/** | **/** | **1.926** | **/** | **/** | **/**
sse-merge | / | / | 1.955 | / | / | /
sse-pivot | / | / | 4.272 | / | / | /
avx2-galloping-double | / | / | 3.572 | / | / | /
avx2-galloping-single | / | / | 2.916 | / | / | /
**avx2-hybrid** | **/** | **/** | **1.779** | **/** | **/** | **/**
avx2-merge | / | / | 1.675 | / | / | /
avx2-merge-popcnt | / | / | 2.299 | / | / | /
avx2-pivot | / | / | 3.249 | / | / | /
avx512-galloping-double | / | / | 3.224 | / | / | /
avx512-galloping-single | / | / | 2.482 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.626** | **/** | **/** | **/**
avx512-merge | / | / | 1.576 | / | / | /
avx512-merge-popcnt | / | / | 1.542 | / | / | /
avx512-pivot | / | / | 2.237 | / | / | /


### n12dot5_m80_1billion_edge

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 61.781 | / | / | /
naive-galloping-single | / | / | 58.85 | / | / | /
**naive-hybrid** | **/** | **/** | **59.542** | **/** | **/** | **/**
naive-merge | / | / | 72.033 | / | / | /
naive-pivot | / | / | 70.123 | / | / | /
**sse-hybrid** | **/** | **/** | **39.91** | **/** | **/** | **/**
sse-merge | / | / | 43.17 | / | / | /
sse-pivot | / | / | 92.664 | / | / | /
avx2-galloping-double | / | / | 67.984 | / | / | /
avx2-galloping-single | / | / | 56.107 | / | / | /
**avx2-hybrid** | **/** | **/** | **30.278** | **/** | **/** | **/**
avx2-merge | / | / | 29.915 | / | / | /
avx2-merge-popcnt | / | / | 53.57 | / | / | /
avx2-pivot | / | / | 69.453 | / | / | /
avx512-galloping-double | / | / | 57.109 | / | / | /
avx512-galloping-single | / | / | 47.401 | / | / | /
**avx512-hybrid** | **/** | **/** | **22.149** | **/** | **/** | **/**
avx512-merge | / | / | 21.516 | / | / | /
avx512-merge-popcnt | / | / | 23.583 | / | / | /
avx512-pivot | / | / | 36.067 | / | / | /


### n16dot7_m60_1billion_edge

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 47.904 | / | / | /
naive-galloping-single | / | / | 45.729 | / | / | /
**naive-hybrid** | **/** | **/** | **46.286** | **/** | **/** | **/**
naive-merge | / | / | 56.859 | / | / | /
naive-pivot | / | / | 55.568 | / | / | /
**sse-hybrid** | **/** | **/** | **31.535** | **/** | **/** | **/**
sse-merge | / | / | 34.556 | / | / | /
sse-pivot | / | / | 71.967 | / | / | /
avx2-galloping-double | / | / | 52.896 | / | / | /
avx2-galloping-single | / | / | 43.807 | / | / | /
**avx2-hybrid** | **/** | **/** | **24.472** | **/** | **/** | **/**
avx2-merge | / | / | 24.118 | / | / | /
avx2-merge-popcnt | / | / | 42.405 | / | / | /
avx2-pivot | / | / | 54.114 | / | / | /
avx512-galloping-double | / | / | 44.53 | / | / | /
avx512-galloping-single | / | / | 37.066 | / | / | /
**avx512-hybrid** | **/** | **/** | **18.606** | **/** | **/** | **/**
avx512-merge | / | / | 17.562 | / | / | /
avx512-merge-popcnt | / | / | 19.093 | / | / | /
avx512-pivot | / | / | 29.135 | / | / | /


### n25_m40_1billion_edge

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 33.882 | / | / | /
naive-galloping-single | / | / | 32.518 | / | / | /
**naive-hybrid** | **/** | **/** | **33.008** | **/** | **/** | **/**
naive-merge | / | / | 41.267 | / | / | /
naive-pivot | / | / | 40.221 | / | / | /
**sse-hybrid** | **/** | **/** | **23.207** | **/** | **/** | **/**
sse-merge | / | / | 25.582 | / | / | /
sse-pivot | / | / | 50.744 | / | / | /
avx2-galloping-double | / | / | 37.496 | / | / | /
avx2-galloping-single | / | / | 31.308 | / | / | /
**avx2-hybrid** | **/** | **/** | **18.59** | **/** | **/** | **/**
avx2-merge | / | / | 18.369 | / | / | /
avx2-merge-popcnt | / | / | 30.907 | / | / | /
avx2-pivot | / | / | 38.587 | / | / | /
avx512-galloping-double | / | / | 31.745 | / | / | /
avx512-galloping-single | / | / | 26.692 | / | / | /
**avx512-hybrid** | **/** | **/** | **14.906** | **/** | **/** | **/**
avx512-merge | / | / | 14.122 | / | / | /
avx512-merge-popcnt | / | / | 14.862 | / | / | /
avx512-pivot | / | / | 22.648 | / | / | /


### n50_m20_1billion_edge

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 19.773 | / | / | /
naive-galloping-single | / | / | 19.165 | / | / | /
**naive-hybrid** | **/** | **/** | **19.897** | **/** | **/** | **/**
naive-merge | / | / | 24.826 | / | / | /
naive-pivot | / | / | 24.389 | / | / | /
**sse-hybrid** | **/** | **/** | **15.039** | **/** | **/** | **/**
sse-merge | / | / | 16.514 | / | / | /
sse-pivot | / | / | 29.079 | / | / | /
avx2-galloping-double | / | / | 22.111 | / | / | /
avx2-galloping-single | / | / | 18.856 | / | / | /
**avx2-hybrid** | **/** | **/** | **13.035** | **/** | **/** | **/**
avx2-merge | / | / | 12.859 | / | / | /
avx2-merge-popcnt | / | / | 19.097 | / | / | /
avx2-pivot | / | / | 23.045 | / | / | /
avx512-galloping-double | / | / | 18.886 | / | / | /
avx512-galloping-single | / | / | 16.375 | / | / | /
**avx512-hybrid** | **/** | **/** | **11.413** | **/** | **/** | **/**
avx512-merge | / | / | 10.768 | / | / | /
avx512-merge-popcnt | / | / | 10.954 | / | / | /
avx512-pivot | / | / | 16.308 | / | / | /