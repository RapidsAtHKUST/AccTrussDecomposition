# Core Checking (eps = 0.8, mu = 5)


Unit: seconds


## varying num of threads


### small_snap_cit_patents/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.031 | / | / | /
naive-galloping-single | / | / | 0.006 | / | / | /
**naive-hybrid** | **/** | **/** | **0.011** | **/** | **/** | **/**
naive-merge | / | / | 0.006 | / | / | /
naive-pivot | / | / | 0.006 | / | / | /
**sse-hybrid** | **/** | **/** | **0.019** | **/** | **/** | **/**
sse-merge | / | / | 0.007 | / | / | /
sse-pivot | / | / | 0.024 | / | / | /
avx2-galloping-double | / | / | 0.007 | / | / | /
avx2-galloping-single | / | / | 0.028 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.008** | **/** | **/** | **/**
avx2-merge | / | / | 0.007 | / | / | /
avx2-merge-popcnt | / | / | 0.007 | / | / | /
avx2-pivot | / | / | 0.007 | / | / | /
avx512-galloping-double | / | / | 0.025 | / | / | /
avx512-galloping-single | / | / | 0.006 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.02** | **/** | **/** | **/**
avx512-merge | / | / | 0.007 | / | / | /
avx512-merge-popcnt | / | / | 0.007 | / | / | /
avx512-pivot | / | / | 0.023 | / | / | /


### small_snap_dblp/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.019 | / | / | /
naive-galloping-single | / | / | 0.015 | / | / | /
**naive-hybrid** | **/** | **/** | **0.014** | **/** | **/** | **/**
naive-merge | / | / | 0.013 | / | / | /
naive-pivot | / | / | 0.014 | / | / | /
**sse-hybrid** | **/** | **/** | **0.011** | **/** | **/** | **/**
sse-merge | / | / | 0.024 | / | / | /
sse-pivot | / | / | 0.036 | / | / | /
avx2-galloping-double | / | / | 0.032 | / | / | /
avx2-galloping-single | / | / | 0.036 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.01** | **/** | **/** | **/**
avx2-merge | / | / | 0.01 | / | / | /
avx2-merge-popcnt | / | / | 0.014 | / | / | /
avx2-pivot | / | / | 0.046 | / | / | /
avx512-galloping-double | / | / | 0.03 | / | / | /
avx512-galloping-single | / | / | 0.033 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.009** | **/** | **/** | **/**
avx512-merge | / | / | 0.018 | / | / | /
avx512-merge-popcnt | / | / | 0.009 | / | / | /
avx512-pivot | / | / | 0.018 | / | / | /


### small_snap_web_berkstan/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.066 | / | / | /
naive-galloping-single | / | / | 0.053 | / | / | /
**naive-hybrid** | **/** | **/** | **0.053** | **/** | **/** | **/**
naive-merge | / | / | 0.04 | / | / | /
naive-pivot | / | / | 0.042 | / | / | /
**sse-hybrid** | **/** | **/** | **0.047** | **/** | **/** | **/**
sse-merge | / | / | 0.042 | / | / | /
sse-pivot | / | / | 0.144 | / | / | /
avx2-galloping-double | / | / | 0.113 | / | / | /
avx2-galloping-single | / | / | 0.077 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.032** | **/** | **/** | **/**
avx2-merge | / | / | 0.037 | / | / | /
avx2-merge-popcnt | / | / | 0.043 | / | / | /
avx2-pivot | / | / | 0.107 | / | / | /
avx512-galloping-double | / | / | 0.105 | / | / | /
avx512-galloping-single | / | / | 0.076 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.026** | **/** | **/** | **/**
avx512-merge | / | / | 0.026 | / | / | /
avx512-merge-popcnt | / | / | 0.041 | / | / | /
avx512-pivot | / | / | 0.067 | / | / | /


### small_snap_web_notredame/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.061 | / | / | /
naive-galloping-single | / | / | 0.049 | / | / | /
**naive-hybrid** | **/** | **/** | **0.045** | **/** | **/** | **/**
naive-merge | / | / | 0.133 | / | / | /
naive-pivot | / | / | 0.101 | / | / | /
**sse-hybrid** | **/** | **/** | **0.022** | **/** | **/** | **/**
sse-merge | / | / | 0.041 | / | / | /
sse-pivot | / | / | 0.125 | / | / | /
avx2-galloping-double | / | / | 0.099 | / | / | /
avx2-galloping-single | / | / | 0.075 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.02** | **/** | **/** | **/**
avx2-merge | / | / | 0.021 | / | / | /
avx2-merge-popcnt | / | / | 0.042 | / | / | /
avx2-pivot | / | / | 0.092 | / | / | /
avx512-galloping-double | / | / | 0.094 | / | / | /
avx512-galloping-single | / | / | 0.059 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.014** | **/** | **/** | **/**
avx512-merge | / | / | 0.014 | / | / | /
avx512-merge-popcnt | / | / | 0.015 | / | / | /
avx512-pivot | / | / | 0.076 | / | / | /


### small_snap_web_stanford/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.008 | / | / | /
naive-galloping-single | / | / | 0.007 | / | / | /
**naive-hybrid** | **/** | **/** | **0.008** | **/** | **/** | **/**
naive-merge | / | / | 0.008 | / | / | /
naive-pivot | / | / | 0.007 | / | / | /
**sse-hybrid** | **/** | **/** | **0.006** | **/** | **/** | **/**
sse-merge | / | / | 0.006 | / | / | /
sse-pivot | / | / | 0.014 | / | / | /
avx2-galloping-double | / | / | 0.013 | / | / | /
avx2-galloping-single | / | / | 0.01 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.006** | **/** | **/** | **/**
avx2-merge | / | / | 0.006 | / | / | /
avx2-merge-popcnt | / | / | 0.007 | / | / | /
avx2-pivot | / | / | 0.012 | / | / | /
avx512-galloping-double | / | / | 0.019 | / | / | /
avx512-galloping-single | / | / | 0.009 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.005** | **/** | **/** | **/**
avx512-merge | / | / | 0.005 | / | / | /
avx512-merge-popcnt | / | / | 0.005 | / | / | /
avx512-pivot | / | / | 0.008 | / | / | /


### snap_pokec/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.253 | / | / | /
naive-galloping-single | / | / | 0.204 | / | / | /
**naive-hybrid** | **/** | **/** | **0.23** | **/** | **/** | **/**
naive-merge | / | / | 0.413 | / | / | /
naive-pivot | / | / | 0.399 | / | / | /
**sse-hybrid** | **/** | **/** | **0.205** | **/** | **/** | **/**
sse-merge | / | / | 0.226 | / | / | /
sse-pivot | / | / | 0.363 | / | / | /
avx2-galloping-double | / | / | 0.241 | / | / | /
avx2-galloping-single | / | / | 0.208 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.177** | **/** | **/** | **/**
avx2-merge | / | / | 0.161 | / | / | /
avx2-merge-popcnt | / | / | 0.268 | / | / | /
avx2-pivot | / | / | 0.297 | / | / | /
avx512-galloping-double | / | / | 0.246 | / | / | /
avx512-galloping-single | / | / | 0.189 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.148** | **/** | **/** | **/**
avx512-merge | / | / | 0.132 | / | / | /
avx512-merge-popcnt | / | / | 0.166 | / | / | /
avx512-pivot | / | / | 0.201 | / | / | /


### snap_livejournal/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 0.797 | / | / | /
naive-galloping-single | / | / | 0.674 | / | / | /
**naive-hybrid** | **/** | **/** | **0.78** | **/** | **/** | **/**
naive-merge | / | / | 0.971 | / | / | /
naive-pivot | / | / | 0.883 | / | / | /
**sse-hybrid** | **/** | **/** | **0.513** | **/** | **/** | **/**
sse-merge | / | / | 0.57 | / | / | /
sse-pivot | / | / | 1.21 | / | / | /
avx2-galloping-double | / | / | 1.006 | / | / | /
avx2-galloping-single | / | / | 0.847 | / | / | /
**avx2-hybrid** | **/** | **/** | **0.422** | **/** | **/** | **/**
avx2-merge | / | / | 0.451 | / | / | /
avx2-merge-popcnt | / | / | 0.638 | / | / | /
avx2-pivot | / | / | 0.955 | / | / | /
avx512-galloping-double | / | / | 0.985 | / | / | /
avx512-galloping-single | / | / | 0.683 | / | / | /
**avx512-hybrid** | **/** | **/** | **0.412** | **/** | **/** | **/**
avx512-merge | / | / | 0.338 | / | / | /
avx512-merge-popcnt | / | / | 0.415 | / | / | /
avx512-pivot | / | / | 0.588 | / | / | /


### snap_orkut/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 5.2 | / | / | /
naive-galloping-single | / | / | 4.913 | / | / | /
**naive-hybrid** | **/** | **/** | **5.424** | **/** | **/** | **/**
naive-merge | / | / | 6.512 | / | / | /
naive-pivot | / | / | 6.095 | / | / | /
**sse-hybrid** | **/** | **/** | **3.582** | **/** | **/** | **/**
sse-merge | / | / | 4.016 | / | / | /
sse-pivot | / | / | 8.179 | / | / | /
avx2-galloping-double | / | / | 5.854 | / | / | /
avx2-galloping-single | / | / | 5.0 | / | / | /
**avx2-hybrid** | **/** | **/** | **2.753** | **/** | **/** | **/**
avx2-merge | / | / | 2.742 | / | / | /
avx2-merge-popcnt | / | / | 4.969 | / | / | /
avx2-pivot | / | / | 6.272 | / | / | /
avx512-galloping-double | / | / | 5.13 | / | / | /
avx512-galloping-single | / | / | 4.319 | / | / | /
**avx512-hybrid** | **/** | **/** | **2.078** | **/** | **/** | **/**
avx512-merge | / | / | 2.145 | / | / | /
avx512-merge-popcnt | / | / | 2.205 | / | / | /
avx512-pivot | / | / | 3.62 | / | / | /


### snap_friendster/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 105.375 | / | / | /
naive-galloping-single | / | / | 99.634 | / | / | /
**naive-hybrid** | **/** | **/** | **104.583** | **/** | **/** | **/**
naive-merge | / | / | 104.392 | / | / | /
naive-pivot | / | / | 99.127 | / | / | /
**sse-hybrid** | **/** | **/** | **71.078** | **/** | **/** | **/**
sse-merge | / | / | 70.803 | / | / | /
sse-pivot | / | / | 147.072 | / | / | /
avx2-galloping-double | / | / | 113.776 | / | / | /
avx2-galloping-single | / | / | 97.847 | / | / | /
**avx2-hybrid** | **/** | **/** | **52.631** | **/** | **/** | **/**
avx2-merge | / | / | 52.01 | / | / | /
avx2-merge-popcnt | / | / | 92.887 | / | / | /
avx2-pivot | / | / | 112.214 | / | / | /
avx512-galloping-double | / | / | 96.552 | / | / | /
avx512-galloping-single | / | / | 84.795 | / | / | /
**avx512-hybrid** | **/** | **/** | **38.266** | **/** | **/** | **/**
avx512-merge | / | / | 37.353 | / | / | /
avx512-merge-popcnt | / | / | 41.701 | / | / | /
avx512-pivot | / | / | 60.142 | / | / | /


### webgraph_it/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 36.428 | / | / | /
naive-galloping-single | / | / | 34.425 | / | / | /
**naive-hybrid** | **/** | **/** | **39.423** | **/** | **/** | **/**
naive-merge | / | / | / | / | / | /
naive-pivot | / | / | / | / | / | /
**sse-hybrid** | **/** | **/** | **29.248** | **/** | **/** | **/**
sse-merge | / | / | 538.606 | / | / | /
sse-pivot | / | / | / | / | / | /
avx2-galloping-double | / | / | 56.698 | / | / | /
avx2-galloping-single | / | / | 43.309 | / | / | /
**avx2-hybrid** | **/** | **/** | **25.192** | **/** | **/** | **/**
avx2-merge | / | / | 396.14 | / | / | /
avx2-merge-popcnt | / | / | 555.853 | / | / | /
avx2-pivot | / | / | / | / | / | /
avx512-galloping-double | / | / | 50.817 | / | / | /
avx512-galloping-single | / | / | 37.493 | / | / | /
**avx512-hybrid** | **/** | **/** | **19.83** | **/** | **/** | **/**
avx512-merge | / | / | 385.606 | / | / | /
avx512-merge-popcnt | / | / | 386.328 | / | / | /
avx512-pivot | / | / | 609.303 | / | / | /


### webgraph_uk/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 3.289 | / | / | /
naive-galloping-single | / | / | 3.216 | / | / | /
**naive-hybrid** | **/** | **/** | **4.387** | **/** | **/** | **/**
naive-merge | / | / | 11.007 | / | / | /
naive-pivot | / | / | 9.317 | / | / | /
**sse-hybrid** | **/** | **/** | **2.685** | **/** | **/** | **/**
sse-merge | / | / | 4.896 | / | / | /
sse-pivot | / | / | 10.808 | / | / | /
avx2-galloping-double | / | / | 5.179 | / | / | /
avx2-galloping-single | / | / | 3.96 | / | / | /
**avx2-hybrid** | **/** | **/** | **2.067** | **/** | **/** | **/**
avx2-merge | / | / | 2.886 | / | / | /
avx2-merge-popcnt | / | / | 5.718 | / | / | /
avx2-pivot | / | / | 10.037 | / | / | /
avx512-galloping-double | / | / | 4.529 | / | / | /
avx512-galloping-single | / | / | 3.354 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.626** | **/** | **/** | **/**
avx512-merge | / | / | 2.047 | / | / | /
avx512-merge-popcnt | / | / | 2.151 | / | / | /
avx512-pivot | / | / | 6.88 | / | / | /


### webgraph_eu/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 192.053 | / | / | /
naive-galloping-single | / | / | 163.908 | / | / | /
**naive-hybrid** | **/** | **/** | **121.497** | **/** | **/** | **/**
naive-merge | / | / | 138.95 | / | / | /
naive-pivot | / | / | 145.984 | / | / | /
**sse-hybrid** | **/** | **/** | **89.609** | **/** | **/** | **/**
sse-merge | / | / | 96.155 | / | / | /
sse-pivot | / | / | 617.984 | / | / | /
avx2-galloping-double | / | / | 492.868 | / | / | /
avx2-galloping-single | / | / | 313.309 | / | / | /
**avx2-hybrid** | **/** | **/** | **76.219** | **/** | **/** | **/**
avx2-merge | / | / | 79.714 | / | / | /
avx2-merge-popcnt | / | / | 156.011 | / | / | /
avx2-pivot | / | / | 496.577 | / | / | /
avx512-galloping-double | / | / | 469.232 | / | / | /
avx512-galloping-single | / | / | 291.639 | / | / | /
**avx512-hybrid** | **/** | **/** | **44.63** | **/** | **/** | **/**
avx512-merge | / | / | 47.523 | / | / | /
avx512-merge-popcnt | / | / | 53.504 | / | / | /
avx512-pivot | / | / | 277.057 | / | / | /


### webgraph_twitter/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 180.482 | / | / | /
naive-galloping-single | / | / | 174.128 | / | / | /
**naive-hybrid** | **/** | **/** | **199.485** | **/** | **/** | **/**
naive-merge | / | / | / | / | / | /
naive-pivot | / | / | / | / | / | /
**sse-hybrid** | **/** | **/** | **132.947** | **/** | **/** | **/**
sse-merge | / | / | / | / | / | /
sse-pivot | / | / | / | / | / | /
avx2-galloping-double | / | / | 203.336 | / | / | /
avx2-galloping-single | / | / | 175.339 | / | / | /
**avx2-hybrid** | **/** | **/** | **105.963** | **/** | **/** | **/**
avx2-merge | / | / | 622.822 | / | / | /
avx2-merge-popcnt | / | / | / | / | / | /
avx2-pivot | / | / | / | / | / | /
avx512-galloping-double | / | / | 171.934 | / | / | /
avx512-galloping-single | / | / | 145.934 | / | / | /
**avx512-hybrid** | **/** | **/** | **82.946** | **/** | **/** | **/**
avx512-merge | / | / | 600.16 | / | / | /
avx512-merge-popcnt | / | / | 606.178 | / | / | /
avx512-pivot | / | / | / | / | / | /


### webgraph_webbase/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 9.525 | / | / | /
naive-galloping-single | / | / | 8.945 | / | / | /
**naive-hybrid** | **/** | **/** | **11.119** | **/** | **/** | **/**
naive-merge | / | / | 108.874 | / | / | /
naive-pivot | / | / | 95.669 | / | / | /
**sse-hybrid** | **/** | **/** | **7.607** | **/** | **/** | **/**
sse-merge | / | / | 44.263 | / | / | /
sse-pivot | / | / | 89.561 | / | / | /
avx2-galloping-double | / | / | 15.82 | / | / | /
avx2-galloping-single | / | / | 11.794 | / | / | /
**avx2-hybrid** | **/** | **/** | **6.235** | **/** | **/** | **/**
avx2-merge | / | / | 24.513 | / | / | /
avx2-merge-popcnt | / | / | 46.885 | / | / | /
avx2-pivot | / | / | 77.783 | / | / | /
avx512-galloping-double | / | / | 13.946 | / | / | /
avx512-galloping-single | / | / | 9.953 | / | / | /
**avx512-hybrid** | **/** | **/** | **4.924** | **/** | **/** | **/**
avx512-merge | / | / | 18.723 | / | / | /
avx512-merge-popcnt | / | / | 19.05 | / | / | /
avx512-pivot | / | / | 57.191 | / | / | /


### lfr_dataset/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 3.12 | / | / | /
naive-galloping-single | / | / | 2.819 | / | / | /
**naive-hybrid** | **/** | **/** | **2.937** | **/** | **/** | **/**
naive-merge | / | / | 2.834 | / | / | /
naive-pivot | / | / | 2.835 | / | / | /
**sse-hybrid** | **/** | **/** | **2.083** | **/** | **/** | **/**
sse-merge | / | / | 2.001 | / | / | /
sse-pivot | / | / | 5.884 | / | / | /
avx2-galloping-double | / | / | 4.869 | / | / | /
avx2-galloping-single | / | / | 3.497 | / | / | /
**avx2-hybrid** | **/** | **/** | **1.593** | **/** | **/** | **/**
avx2-merge | / | / | 1.716 | / | / | /
avx2-merge-popcnt | / | / | 2.613 | / | / | /
avx2-pivot | / | / | 4.675 | / | / | /
avx512-galloping-double | / | / | 4.42 | / | / | /
avx512-galloping-single | / | / | 3.14 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.413** | **/** | **/** | **/**
avx512-merge | / | / | 1.287 | / | / | /
avx512-merge-popcnt | / | / | 1.466 | / | / | /
avx512-pivot | / | / | 2.772 | / | / | /


### lfr_graphs/n2400000_k100_C0dot3_Bin/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 3.595 | / | / | /
naive-galloping-single | / | / | 3.181 | / | / | /
**naive-hybrid** | **/** | **/** | **3.248** | **/** | **/** | **/**
naive-merge | / | / | 3.105 | / | / | /
naive-pivot | / | / | 3.102 | / | / | /
**sse-hybrid** | **/** | **/** | **2.277** | **/** | **/** | **/**
sse-merge | / | / | 2.24 | / | / | /
sse-pivot | / | / | 6.748 | / | / | /
avx2-galloping-double | / | / | 5.711 | / | / | /
avx2-galloping-single | / | / | 4.081 | / | / | /
**avx2-hybrid** | **/** | **/** | **1.832** | **/** | **/** | **/**
avx2-merge | / | / | 1.869 | / | / | /
avx2-merge-popcnt | / | / | 2.915 | / | / | /
avx2-pivot | / | / | 5.532 | / | / | /
avx512-galloping-double | / | / | 5.351 | / | / | /
avx512-galloping-single | / | / | 3.641 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.433** | **/** | **/** | **/**
avx512-merge | / | / | 1.455 | / | / | /
avx512-merge-popcnt | / | / | 1.524 | / | / | /
avx512-pivot | / | / | 3.187 | / | / | /


### lfr_graphs/n3000000_k80_C0dot3_Bin/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 3.06 | / | / | /
naive-galloping-single | / | / | 2.758 | / | / | /
**naive-hybrid** | **/** | **/** | **2.903** | **/** | **/** | **/**
naive-merge | / | / | 2.803 | / | / | /
naive-pivot | / | / | 2.748 | / | / | /
**sse-hybrid** | **/** | **/** | **2.077** | **/** | **/** | **/**
sse-merge | / | / | 2.04 | / | / | /
sse-pivot | / | / | 5.848 | / | / | /
avx2-galloping-double | / | / | 4.871 | / | / | /
avx2-galloping-single | / | / | 3.494 | / | / | /
**avx2-hybrid** | **/** | **/** | **1.697** | **/** | **/** | **/**
avx2-merge | / | / | 1.728 | / | / | /
avx2-merge-popcnt | / | / | 2.608 | / | / | /
avx2-pivot | / | / | 4.768 | / | / | /
avx512-galloping-double | / | / | 4.432 | / | / | /
avx512-galloping-single | / | / | 3.199 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.369** | **/** | **/** | **/**
avx512-merge | / | / | 1.298 | / | / | /
avx512-merge-popcnt | / | / | 1.428 | / | / | /
avx512-pivot | / | / | 2.795 | / | / | /


### lfr_graphs/n4000000_k60_C0dot1_Bin/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 2.668 | / | / | /
naive-galloping-single | / | / | 2.49 | / | / | /
**naive-hybrid** | **/** | **/** | **2.606** | **/** | **/** | **/**
naive-merge | / | / | 2.614 | / | / | /
naive-pivot | / | / | 2.482 | / | / | /
**sse-hybrid** | **/** | **/** | **1.838** | **/** | **/** | **/**
sse-merge | / | / | 1.876 | / | / | /
sse-pivot | / | / | 4.79 | / | / | /
avx2-galloping-double | / | / | 4.043 | / | / | /
avx2-galloping-single | / | / | 2.992 | / | / | /
**avx2-hybrid** | **/** | **/** | **1.615** | **/** | **/** | **/**
avx2-merge | / | / | 1.478 | / | / | /
avx2-merge-popcnt | / | / | 2.292 | / | / | /
avx2-pivot | / | / | 3.905 | / | / | /
avx512-galloping-double | / | / | 3.67 | / | / | /
avx512-galloping-single | / | / | 2.554 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.281** | **/** | **/** | **/**
avx512-merge | / | / | 1.297 | / | / | /
avx512-merge-popcnt | / | / | 1.258 | / | / | /
avx512-pivot | / | / | 2.385 | / | / | /


### lfr_graphs/n4000000_k60_C0dot3_Bin/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 2.655 | / | / | /
naive-galloping-single | / | / | 2.477 | / | / | /
**naive-hybrid** | **/** | **/** | **2.599** | **/** | **/** | **/**
naive-merge | / | / | 2.604 | / | / | /
naive-pivot | / | / | 2.452 | / | / | /
**sse-hybrid** | **/** | **/** | **1.829** | **/** | **/** | **/**
sse-merge | / | / | 1.856 | / | / | /
sse-pivot | / | / | 4.779 | / | / | /
avx2-galloping-double | / | / | 4.056 | / | / | /
avx2-galloping-single | / | / | 2.947 | / | / | /
**avx2-hybrid** | **/** | **/** | **1.595** | **/** | **/** | **/**
avx2-merge | / | / | 1.487 | / | / | /
avx2-merge-popcnt | / | / | 2.292 | / | / | /
avx2-pivot | / | / | 3.923 | / | / | /
avx512-galloping-double | / | / | 3.744 | / | / | /
avx512-galloping-single | / | / | 2.589 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.195** | **/** | **/** | **/**
avx512-merge | / | / | 1.269 | / | / | /
avx512-merge-popcnt | / | / | 1.301 | / | / | /
avx512-pivot | / | / | 2.383 | / | / | /


### lfr_graphs/n6000000_k40_C0dot3_Bin/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 2.184 | / | / | /
naive-galloping-single | / | / | 2.129 | / | / | /
**naive-hybrid** | **/** | **/** | **2.283** | **/** | **/** | **/**
naive-merge | / | / | 2.297 | / | / | /
naive-pivot | / | / | 2.095 | / | / | /
**sse-hybrid** | **/** | **/** | **1.675** | **/** | **/** | **/**
sse-merge | / | / | 1.579 | / | / | /
sse-pivot | / | / | 3.814 | / | / | /
avx2-galloping-double | / | / | 3.243 | / | / | /
avx2-galloping-single | / | / | 2.375 | / | / | /
**avx2-hybrid** | **/** | **/** | **1.29** | **/** | **/** | **/**
avx2-merge | / | / | 1.353 | / | / | /
avx2-merge-popcnt | / | / | 1.918 | / | / | /
avx2-pivot | / | / | 3.115 | / | / | /
avx512-galloping-double | / | / | 2.853 | / | / | /
avx512-galloping-single | / | / | 2.06 | / | / | /
**avx512-hybrid** | **/** | **/** | **1.195** | **/** | **/** | **/**
avx512-merge | / | / | 1.1 | / | / | /
avx512-merge-popcnt | / | / | 1.133 | / | / | /
avx512-pivot | / | / | 1.965 | / | / | /


### n12dot5_m80_1billion_edge/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 62.985 | / | / | /
naive-galloping-single | / | / | 60.376 | / | / | /
**naive-hybrid** | **/** | **/** | **63.066** | **/** | **/** | **/**
naive-merge | / | / | 77.376 | / | / | /
naive-pivot | / | / | 71.614 | / | / | /
**sse-hybrid** | **/** | **/** | **40.474** | **/** | **/** | **/**
sse-merge | / | / | 43.74 | / | / | /
sse-pivot | / | / | 94.675 | / | / | /
avx2-galloping-double | / | / | 69.422 | / | / | /
avx2-galloping-single | / | / | 57.4 | / | / | /
**avx2-hybrid** | **/** | **/** | **30.861** | **/** | **/** | **/**
avx2-merge | / | / | 30.019 | / | / | /
avx2-merge-popcnt | / | / | 54.598 | / | / | /
avx2-pivot | / | / | 71.455 | / | / | /
avx512-galloping-double | / | / | 58.337 | / | / | /
avx512-galloping-single | / | / | 48.571 | / | / | /
**avx512-hybrid** | **/** | **/** | **23.066** | **/** | **/** | **/**
avx512-merge | / | / | 21.615 | / | / | /
avx512-merge-popcnt | / | / | 23.813 | / | / | /
avx512-pivot | / | / | 36.632 | / | / | /


### n16dot7_m60_1billion_edge/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 49.067 | / | / | /
naive-galloping-single | / | / | 46.827 | / | / | /
**naive-hybrid** | **/** | **/** | **49.568** | **/** | **/** | **/**
naive-merge | / | / | 61.826 | / | / | /
naive-pivot | / | / | 57.021 | / | / | /
**sse-hybrid** | **/** | **/** | **32.298** | **/** | **/** | **/**
sse-merge | / | / | 35.111 | / | / | /
sse-pivot | / | / | 74.205 | / | / | /
avx2-galloping-double | / | / | 54.102 | / | / | /
avx2-galloping-single | / | / | 45.035 | / | / | /
**avx2-hybrid** | **/** | **/** | **25.097** | **/** | **/** | **/**
avx2-merge | / | / | 24.609 | / | / | /
avx2-merge-popcnt | / | / | 43.561 | / | / | /
avx2-pivot | / | / | 56.304 | / | / | /
avx512-galloping-double | / | / | 45.675 | / | / | /
avx512-galloping-single | / | / | 38.201 | / | / | /
**avx512-hybrid** | **/** | **/** | **19.33** | **/** | **/** | **/**
avx512-merge | / | / | 18.148 | / | / | /
avx512-merge-popcnt | / | / | 19.78 | / | / | /
avx512-pivot | / | / | 30.229 | / | / | /


### n25_m40_1billion_edge/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 34.769 | / | / | /
naive-galloping-single | / | / | 33.169 | / | / | /
**naive-hybrid** | **/** | **/** | **35.148** | **/** | **/** | **/**
naive-merge | / | / | 44.869 | / | / | /
naive-pivot | / | / | 41.339 | / | / | /
**sse-hybrid** | **/** | **/** | **23.657** | **/** | **/** | **/**
sse-merge | / | / | 26.047 | / | / | /
sse-pivot | / | / | 52.471 | / | / | /
avx2-galloping-double | / | / | 38.584 | / | / | /
avx2-galloping-single | / | / | 32.169 | / | / | /
**avx2-hybrid** | **/** | **/** | **19.227** | **/** | **/** | **/**
avx2-merge | / | / | 18.868 | / | / | /
avx2-merge-popcnt | / | / | 31.736 | / | / | /
avx2-pivot | / | / | 40.342 | / | / | /
avx512-galloping-double | / | / | 32.608 | / | / | /
avx512-galloping-single | / | / | 27.512 | / | / | /
**avx512-hybrid** | **/** | **/** | **15.552** | **/** | **/** | **/**
avx512-merge | / | / | 14.635 | / | / | /
avx512-merge-popcnt | / | / | 15.559 | / | / | /
avx512-pivot | / | / | 23.52 | / | / | /


### n50_m20_1billion_edge/rabbit_order

file-name | 16 | 64 | 256 | 16-up | 64-up | 256-up
--- | --- | --- | --- | --- | --- | ---
naive-galloping-double | / | / | 20.215 | / | / | /
naive-galloping-single | / | / | 19.571 | / | / | /
**naive-hybrid** | **/** | **/** | **20.713** | **/** | **/** | **/**
naive-merge | / | / | 27.419 | / | / | /
naive-pivot | / | / | 25.5 | / | / | /
**sse-hybrid** | **/** | **/** | **15.168** | **/** | **/** | **/**
sse-merge | / | / | 16.707 | / | / | /
sse-pivot | / | / | 30.661 | / | / | /
avx2-galloping-double | / | / | 22.596 | / | / | /
avx2-galloping-single | / | / | 19.403 | / | / | /
**avx2-hybrid** | **/** | **/** | **13.322** | **/** | **/** | **/**
avx2-merge | / | / | 13.13 | / | / | /
avx2-merge-popcnt | / | / | 19.874 | / | / | /
avx2-pivot | / | / | 24.173 | / | / | /
avx512-galloping-double | / | / | 19.383 | / | / | /
avx512-galloping-single | / | / | 16.836 | / | / | /
**avx512-hybrid** | **/** | **/** | **11.778** | **/** | **/** | **/**
avx512-merge | / | / | 10.946 | / | / | /
avx512-merge-popcnt | / | / | 11.287 | / | / | /
avx512-pivot | / | / | 17.13 | / | / | /