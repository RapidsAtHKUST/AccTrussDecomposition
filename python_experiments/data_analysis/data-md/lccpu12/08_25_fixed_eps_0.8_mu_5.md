# Core Checking (eps = 0.8, mu = 5)


Unit: seconds


## varying num of threads


### small_snap_dblp

file-name | 16 | 64 | 56 | 16-up | 64-up | 56-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.028 | / | / | /
naive-galloping-single | / | / | 0.029 | / | / | /
**naive-hybrid** | **/** | **/** | **0.028** | **/** | **/** | **/**
naive-merge | / | / | 0.024 | / | / | /
naive-pivot | / | / | 0.029 | / | / | /
**sse-hybrid** | **/** | **/** | **0.025** | **/** | **/** | **/**
sse-merge | / | / | 0.028 | / | / | /
sse-pivot | / | / | 0.03 | / | / | /
avx2-galloping-double | / | / | 0.016 | / | / | /
avx2-galloping-single | / | / | 0.028 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.027** | **/** | **/** | **/**
avx2-merge | / | / | 0.024 | / | / | /
avx2-merge-popcnt | / | / | 0.01 | / | / | /
avx2-pivot | / | / | 0.029 | / | / | /


### snap_pokec

file-name | 16 | 64 | 56 | 16-up | 64-up | 56-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.255 | / | / | /
naive-galloping-single | / | / | 0.254 | / | / | /
**naive-hybrid** | **/** | **/** | **0.238** | **/** | **/** | **/**
naive-merge | / | / | 0.237 | / | / | /
naive-pivot | / | / | 0.251 | / | / | /
**sse-hybrid** | **/** | **/** | **0.199** | **/** | **/** | **/**
sse-merge | / | / | 0.199 | / | / | /
sse-pivot | / | / | 0.321 | / | / | /
avx2-galloping-double | / | / | 0.222 | / | / | /
avx2-galloping-single | / | / | 0.227 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.184** | **/** | **/** | **/**
avx2-merge | / | / | 0.189 | / | / | /
avx2-merge-popcnt | / | / | 0.193 | / | / | /
avx2-pivot | / | / | 0.228 | / | / | /


### snap_livejournal

file-name | 16 | 64 | 56 | 16-up | 64-up | 56-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.771 | / | / | /
naive-galloping-single | / | / | 0.748 | / | / | /
**naive-hybrid** | **/** | **/** | **0.722** | **/** | **/** | **/**
naive-merge | / | / | 0.706 | / | / | /
naive-pivot | / | / | 0.714 | / | / | /
**sse-hybrid** | **/** | **/** | **0.563** | **/** | **/** | **/**
sse-merge | / | / | 0.578 | / | / | /
sse-pivot | / | / | 1.063 | / | / | /
avx2-galloping-double | / | / | 0.685 | / | / | /
avx2-galloping-single | / | / | 0.656 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.475** | **/** | **/** | **/**
avx2-merge | / | / | 0.478 | / | / | /
avx2-merge-popcnt | / | / | 0.482 | / | / | /
avx2-pivot | / | / | 0.682 | / | / | /


### snap_orkut

file-name | 16 | 64 | 56 | 16-up | 64-up | 56-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 5.81 | / | / | /
naive-galloping-single | / | / | 5.608 | / | / | /
**naive-hybrid** | **/** | **/** | **5.134** | **/** | **/** | **/**
naive-merge | / | / | 5.446 | / | / | /
naive-pivot | / | / | 5.616 | / | / | /
**sse-hybrid** | **/** | **/** | **4.011** | **/** | **/** | **/**
sse-merge | / | / | 4.175 | / | / | /
sse-pivot | / | / | 7.6 | / | / | /
avx2-galloping-double | / | / | 4.602 | / | / | /
avx2-galloping-single | / | / | 4.607 | / | / | /
**avx2-hybrid** | **/** | **/** | **3.167** | **/** | **/** | **/**
avx2-merge | / | / | 3.238 | / | / | /
avx2-merge-popcnt | / | / | 3.368 | / | / | /
avx2-pivot | / | / | 4.466 | / | / | /


### snap_friendster

file-name | 16 | 64 | 56 | 16-up | 64-up | 56-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 129.73 | / | / | /
naive-galloping-single | / | / | 124.93 | / | / | /
**naive-hybrid** | **/** | **/** | **112.683** | **/** | **/** | **/**
naive-merge | / | / | 112.504 | / | / | /
naive-pivot | / | / | 115.218 | / | / | /
**sse-hybrid** | **/** | **/** | **87.274** | **/** | **/** | **/**
sse-merge | / | / | 89.981 | / | / | /
sse-pivot | / | / | 166.095 | / | / | /
avx2-galloping-double | / | / | 103.401 | / | / | /
avx2-galloping-single | / | / | 101.041 | / | / | /
**avx2-hybrid** | **/** | **/** | **78.809** | **/** | **/** | **/**
avx2-merge | / | / | 78.755 | / | / | /
avx2-merge-popcnt | / | / | 80.267 | / | / | /
avx2-pivot | / | / | 100.341 | / | / | /


### webgraph_twitter

file-name | 16 | 64 | 56 | 16-up | 64-up | 56-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 149.853 | / | / | /
naive-galloping-single | / | / | 145.971 | / | / | /
**naive-hybrid** | **/** | **/** | **143.009** | **/** | **/** | **/**
naive-merge | / | / | 697.953 | / | / | /
naive-pivot | / | / | 687.286 | / | / | /
**sse-hybrid** | **/** | **/** | **116.733** | **/** | **/** | **/**
sse-merge | / | / | 483.39 | / | / | /
sse-pivot | / | / | 575.651 | / | / | /
avx2-galloping-double | / | / | 128.782 | / | / | /
avx2-galloping-single | / | / | 125.838 | / | / | /
**avx2-hybrid** | **/** | **/** | **97.379** | **/** | **/** | **/**
avx2-merge | / | / | 285.75 | / | / | /
avx2-merge-popcnt | / | / | 325.343 | / | / | /
avx2-pivot | / | / | 509.135 | / | / | /


### webgraph_eu

file-name | 16 | 64 | 56 | 16-up | 64-up | 56-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 82.346 | / | / | /
naive-galloping-single | / | / | 69.871 | / | / | /
**naive-hybrid** | **/** | **/** | **68.142** | **/** | **/** | **/**
naive-merge | / | / | 74.503 | / | / | /
naive-pivot | / | / | 62.002 | / | / | /
**sse-hybrid** | **/** | **/** | **61.159** | **/** | **/** | **/**
sse-merge | / | / | 64.164 | / | / | /
sse-pivot | / | / | 515.319 | / | / | /
avx2-galloping-double | / | / | 255.088 | / | / | /
avx2-galloping-single | / | / | 140.638 | / | / | /
**avx2-hybrid** | **/** | **/** | **46.035** | **/** | **/** | **/**
avx2-merge | / | / | 47.782 | / | / | /
avx2-merge-popcnt | / | / | 53.05 | / | / | /
avx2-pivot | / | / | 249.368 | / | / | /


### webgraph_uk

file-name | 16 | 64 | 56 | 16-up | 64-up | 56-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 1.182 | / | / | /
naive-galloping-single | / | / | 1.121 | / | / | /
**naive-hybrid** | **/** | **/** | **2.156** | **/** | **/** | **/**
naive-merge | / | / | 4.386 | / | / | /
naive-pivot | / | / | 3.411 | / | / | /
**sse-hybrid** | **/** | **/** | **1.584** | **/** | **/** | **/**
sse-merge | / | / | 2.682 | / | / | /
sse-pivot | / | / | 5.326 | / | / | /
avx2-galloping-double | / | / | 2.236 | / | / | /
avx2-galloping-single | / | / | 1.537 | / | / | /
**avx2-hybrid** | **/** | **/** | **1.197** | **/** | **/** | **/**
avx2-merge | / | / | 1.703 | / | / | /
avx2-merge-popcnt | / | / | 1.911 | / | / | /
avx2-pivot | / | / | 3.185 | / | / | /


### webgraph_webbase

file-name | 16 | 64 | 56 | 16-up | 64-up | 56-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 3.551 | / | / | /
naive-galloping-single | / | / | 3.355 | / | / | /
**naive-hybrid** | **/** | **/** | **5.392** | **/** | **/** | **/**
naive-merge | / | / | 44.277 | / | / | /
naive-pivot | / | / | 33.313 | / | / | /
**sse-hybrid** | **/** | **/** | **4.251** | **/** | **/** | **/**
sse-merge | / | / | 23.67 | / | / | /
sse-pivot | / | / | 33.879 | / | / | /
avx2-galloping-double | / | / | 6.827 | / | / | /
avx2-galloping-single | / | / | 4.666 | / | / | /
**avx2-hybrid** | **/** | **/** | **3.316** | **/** | **/** | **/**
avx2-merge | / | / | 13.023 | / | / | /
avx2-merge-popcnt | / | / | 15.515 | / | / | /
avx2-pivot | / | / | 26.326 | / | / | /