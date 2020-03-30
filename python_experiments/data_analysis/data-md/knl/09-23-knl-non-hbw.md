# O(E) intersection count time


Unit: seconds


### webgraph_webbase

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**baseline-avx512-merge** | **36.834** | **37.834** | **1.0**
avx512-merge | 22.803 | 23.774 | 0.971
avx512-galloping-double | 11.391 | 12.356 | 0.965
avx512-galloping-single | 7.617 | 8.581 | 0.964
**avx512-hybrid** | **3.163** | **4.125** | **0.962**
naive-galloping-single | / | / | /
**naive-hybrid** | **/** | **/** | **/**
naive-merge | / | / | /


### webgraph_webbase/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**naive-bitvec-hbw** | **/** | **/** | **/**
naive-bitvec-hbw-2d | / | / | /
**naive-bitvec** | **6.417** | **7.609** | **1.192**
naive-bitvec-2d | 7.149 | 8.294 | 1.145


### webgraph_it

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**baseline-avx512-merge** | **792.013** | **793.074** | **1.061**
avx512-merge | 599.707 | 600.749 | 1.042
avx512-galloping-double | 37.294 | 38.378 | 1.084
avx512-galloping-single | 24.925 | 25.97 | 1.045
**avx512-hybrid** | **10.741** | **11.824** | **1.083**
naive-galloping-single | / | / | /
**naive-hybrid** | **/** | **/** | **/**
naive-merge | / | / | /


### webgraph_it/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**naive-bitvec-hbw** | **/** | **/** | **/**
naive-bitvec-hbw-2d | / | / | /
**naive-bitvec** | **14.317** | **15.555** | **1.238**
naive-bitvec-2d | 17.930 | 19.165 | 1.235


### webgraph_twitter

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**baseline-avx512-merge** | **/** | **/** | **/**
avx512-merge | 645.667 | 647.314 | 1.647
avx512-galloping-double | 137.704 | 139.349 | 1.645
avx512-galloping-single | 118.273 | 119.92 | 1.647
**avx512-hybrid** | **86.460** | **88.11** | **1.65**
naive-galloping-single | / | / | /
**naive-hybrid** | **/** | **/** | **/**
naive-merge | / | / | /


### webgraph_twitter/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**naive-bitvec-hbw** | **/** | **/** | **/**
naive-bitvec-hbw-2d | / | / | /
**naive-bitvec** | **163.073** | **164.933** | **1.86**
naive-bitvec-2d | 109.959 | 111.694 | 1.735


### snap_friendster

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**baseline-avx512-merge** | **126.810** | **132.13** | **5.32**
avx512-merge | 62.634 | 68.04 | 5.406
avx512-galloping-double | 103.501 | 108.851 | 5.35
avx512-galloping-single | 85.715 | 91.173 | 5.458
**avx512-hybrid** | **63.137** | **68.431** | **5.294**
naive-galloping-single | / | / | /
**naive-hybrid** | **/** | **/** | **/**
naive-merge | / | / | /


### snap_friendster/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
**naive-bitvec-hbw** | **/** | **/** | **/**
naive-bitvec-hbw-2d | / | / | /
**naive-bitvec** | **423.059** | **428.293** | **5.234**
naive-bitvec-2d | 144.108 | 149.346 | 5.238