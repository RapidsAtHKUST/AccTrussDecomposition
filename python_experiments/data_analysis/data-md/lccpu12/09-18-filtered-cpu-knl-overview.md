# O(E) intersection count time


Unit: seconds


### webgraph_webbase

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
avx2-merge | 10.353 | 10.798 | 0.445
avx2-galloping-double | 6.592 | 7.011 | 0.419
avx2-galloping-single | 5.143 | 5.714 | 0.571
**avx2-hybrid** | **3.002** | **3.459** | **0.457**
naive-galloping-single | 3.907 | 4.441 | 0.534
naive-merge | 44.098 | 44.527 | 0.429
**naive-hybrid** | **5.278** | **5.722** | **0.444**


### webgraph_webbase/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
naive-bitvec-2d | 4.043 | 5.144 | 1.101
**naive-bitvec** | **3.400** | **4.504** | **1.104**


### webgraph_it

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
avx2-merge | 271.643 | 272.025 | 0.382
avx2-galloping-double | 20.727 | 21.07 | 0.343
avx2-galloping-single | 13.304 | 13.66 | 0.356
**avx2-hybrid** | **7.936** | **8.282** | **0.346**
naive-galloping-single | 8.844 | 9.196 | 0.352
naive-merge | 654.587 | 654.918 | 0.331
**naive-hybrid** | **14.704** | **15.079** | **0.375**


### webgraph_it/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
naive-bitvec-2d | 9.178 | 9.986 | 0.808
**naive-bitvec** | **6.873** | **7.771** | **0.898**


### webgraph_twitter

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
avx2-merge | 231.872 | 232.949 | 1.077
avx2-galloping-double | 115.137 | 116.264 | 1.127
avx2-galloping-single | 115.762 | 116.83 | 1.068
**avx2-hybrid** | **77.098** | **78.198** | **1.1**
naive-galloping-single | 139.445 | 140.594 | 1.149
naive-merge | 729.220 | 730.317 | 1.097
**naive-hybrid** | **143.317** | **144.454** | **1.137**


### webgraph_twitter/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
naive-bitvec-2d | 40.630 | 41.713 | 1.083
**naive-bitvec** | **41.706** | **42.803** | **1.097**


### snap_friendster

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
avx2-merge | 70.959 | 76.535 | 5.576
avx2-galloping-double | 102.791 | 108.321 | 5.53
avx2-galloping-single | 105.790 | 111.297 | 5.507
**avx2-hybrid** | **70.929** | **76.487** | **5.558**
naive-galloping-single | 132.740 | 138.228 | 5.488
naive-merge | 123.374 | 128.965 | 5.591
**naive-hybrid** | **124.063** | **129.612** | **5.549**


### snap_friendster/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
naive-bitvec-2d | 67.385 | 71.923 | 4.538
**naive-bitvec** | **126.163** | **130.635** | **4.472**