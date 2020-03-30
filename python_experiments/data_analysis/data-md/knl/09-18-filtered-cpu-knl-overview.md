# O(E) intersection count time


Unit: seconds


### webgraph_webbase

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**baseline-avx512-merge** | **36.704** | **37.668** | **0.964**
avx512-merge | 23.023 | 24.014 | 0.991
avx512-galloping-double | 11.430 | 12.391 | 0.961
avx512-galloping-single | 7.607 | 8.565 | 0.958
**avx512-hybrid** | **3.161** | **4.12** | **0.959**
naive-galloping-single | 5.202 | 6.166 | 0.964
**naive-hybrid** | **9.553** | **10.529** | **0.976**
naive-merge | 108.588 | 109.579 | 0.991


### webgraph_webbase/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**naive-bitvec-hbw** | **4.054** | **5.2** | **1.146**
naive-bitvec-hbw-2d | 5.927 | 7.067 | 1.14
**naive-bitvec** | **4.371** | **5.572** | **1.201**
naive-bitvec-2d | 5.687 | 6.861 | 1.174


### webgraph_it

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**baseline-avx512-merge** | **606.223** | **607.267** | **1.044**
avx512-merge | 447.884 | 448.927 | 1.043
avx512-galloping-double | 37.323 | 38.401 | 1.078
avx512-galloping-single | 24.964 | 26.009 | 1.045
**avx512-hybrid** | **10.715** | **11.852** | **1.137**
naive-galloping-single | 16.624 | 17.811 | 1.187
**naive-hybrid** | **29.302** | **30.362** | **1.06**
naive-merge | 1552.777 | 1553.956 | 1.179


### webgraph_it/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**naive-bitvec-hbw** | **12.260** | **13.563** | **1.303**
naive-bitvec-hbw-2d | 18.294 | 19.53 | 1.236
**naive-bitvec** | **12.398** | **13.64** | **1.242**
naive-bitvec-2d | 17.133 | 18.43 | 1.297


### webgraph_twitter

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**baseline-avx512-merge** | **1012.900** | **1014.537** | **1.637**
avx512-merge | 596.186 | 597.845 | 1.659
avx512-galloping-double | 129.844 | 131.488 | 1.644
avx512-galloping-single | 107.086 | 108.729 | 1.643
**avx512-hybrid** | **52.818** | **54.461** | **1.643**
naive-galloping-single | 126.365 | 128.08 | 1.715
**naive-hybrid** | **163.715** | **165.361** | **1.646**
naive-merge | 1657.740 | 1659.387 | 1.647


### webgraph_twitter/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**naive-bitvec-hbw** | **68.768** | **70.513** | **1.745**
naive-bitvec-hbw-2d | 81.611 | 83.289 | 1.678
**naive-bitvec** | **138.004** | **139.683** | **1.679**
naive-bitvec-2d | 88.807 | 90.484 | 1.677


### snap_friendster

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**baseline-avx512-merge** | **64.413** | **69.631** | **5.218**
avx512-merge | 36.497 | 41.861 | 5.364
avx512-galloping-double | 103.537 | 108.864 | 5.327
avx512-galloping-single | 85.496 | 90.761 | 5.265
**avx512-hybrid** | **36.781** | **42.085** | **5.304**
naive-galloping-single | 101.877 | 107.13 | 5.253
**naive-hybrid** | **102.348** | **107.563** | **5.215**
naive-merge | 102.128 | 107.498 | 5.37


### snap_friendster/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**naive-bitvec-hbw** | **418.108** | **423.329** | **5.221**
naive-bitvec-hbw-2d | 123.666 | 128.904 | 5.238
**naive-bitvec** | **400.210** | **405.446** | **5.236**
naive-bitvec-2d | 118.551 | 123.796 | 5.245