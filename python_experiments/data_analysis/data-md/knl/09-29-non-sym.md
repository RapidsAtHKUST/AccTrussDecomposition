# O(E) intersection count time


Unit: seconds


### webgraph_webbase

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
avx512-galloping-single | 7.586 | 8.548 | 0.962
**avx512-hybrid** | **3.155** | **4.111** | **0.956**
avx512-galloping-single-non-sym-assign | 14.064 | 15.086 | 1.022
avx512-hybrid-non-sym-assign | 5.408 | 6.37 | 0.962


### webgraph_webbase/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**naive-bitvec-hbw** | **4.013** | **5.154** | **1.141**
naive-bitvec-hbw-2d | 5.841 | 6.983 | 1.142
naive-bitvec-hbw-non-sym-assign | 183.319 | 184.457 | 1.138
naive-bitvec-hbw-2d-non-sym-assign | 166.513 | 167.776 | 1.263


### webgraph_it

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
avx512-galloping-single | 24.937 | 26.001 | 1.064
**avx512-hybrid** | **10.703** | **11.758** | **1.055**
avx512-galloping-single-non-sym-assign | 47.745 | 49.003 | 1.258
avx512-hybrid-non-sym-assign | 17.719 | 18.8 | 1.081


### webgraph_it/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**naive-bitvec-hbw** | **12.262** | **13.498** | **1.236**
naive-bitvec-hbw-2d | 18.250 | 19.479 | 1.229
naive-bitvec-hbw-non-sym-assign | 2485.193 | 2486.477 | 1.284
naive-bitvec-hbw-2d-non-sym-assign | 2352.592 | 2353.864 | 1.272


### webgraph_twitter

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
avx512-galloping-single | 106.729 | 108.367 | 1.638
**avx512-hybrid** | **52.631** | **54.266** | **1.635**
avx512-galloping-single-non-sym-assign | 213.958 | 215.6 | 1.642
avx512-hybrid-non-sym-assign | 105.202 | 106.838 | 1.636


### webgraph_twitter/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**naive-bitvec-hbw** | **68.673** | **70.474** | **1.801**
naive-bitvec-hbw-2d | 81.196 | 82.89 | 1.694
naive-bitvec-hbw-non-sym-assign | 4150.409 | 4152.172 | 1.763
naive-bitvec-hbw-2d-non-sym-assign | 3892.140 | 3893.992 | 1.852


### snap_friendster

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
avx512-galloping-single | 85.046 | 90.316 | 5.27
**avx512-hybrid** | **33.807** | **39.102** | **5.295**
avx512-galloping-single-non-sym-assign | 166.707 | 172.011 | 5.304
avx512-hybrid-non-sym-assign | 64.574 | 69.823 | 5.249


### snap_friendster/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**naive-bitvec-hbw** | **187.697** | **192.92** | **5.223**
naive-bitvec-hbw-2d | 92.625 | 97.863 | 5.238
naive-bitvec-hbw-non-sym-assign | 672.066 | 677.302 | 5.236
naive-bitvec-hbw-2d-non-sym-assign | 235.450 | 240.873 | 5.423