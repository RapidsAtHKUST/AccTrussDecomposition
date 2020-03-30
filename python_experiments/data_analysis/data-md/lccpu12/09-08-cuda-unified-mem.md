# Core Checking (eps = 0.2, mu = 5)


Unit: seconds


### small_snap_cit_patents

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.064** | **0.007** | **0.012** | **0.045** | **0.060**
**cuda-bitmap-kernel** | **0.064** | **0.007** | **0.012** | **0.045** | **0.058**
**cuda-baseline-hybrid** | **0.039** | **0.007** | **0.007** | **0.025** | **0.039**
cuda-baseline | 0.039 | 0.006 | 0.012 | 0.021 | 0.039
cuda-32-1 | 0.041 | 0.006 | 0.011 | 0.024 | 0.041
cuda-16-2 | 0.041 | 0.006 | 0.012 | 0.023 | 0.041
cuda-8-4 | 0.039 | 0.007 | 0.011 | 0.021 | 0.039
cuda-4-8 | 0.04 | 0.007 | 0.011 | 0.022 | 0.041
cuda-2-16 | 0.046 | 0.008 | 0.015 | 0.023 | 0.047
cuda-1-32 | 0.048 | 0.009 | 0.015 | 0.024 | 0.048


### small_snap_cit_patents/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.069** | **0.008** | **0.016** | **0.045** | **0.066**
**cuda-bitmap-kernel** | **0.072** | **0.009** | **0.013** | **0.050** | **0.066**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### small_snap_dblp

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.033** | **0.007** | **0.01** | **0.016** | **0.030**
**cuda-bitmap-kernel** | **0.038** | **0.007** | **0.014** | **0.017** | **0.034**
**cuda-baseline-hybrid** | **0.025** | **0.008** | **0.002** | **0.015** | **0.025**
cuda-baseline | 0.029 | 0.008 | 0.007 | 0.014 | 0.029
cuda-32-1 | 0.036 | 0.007 | 0.012 | 0.017 | 0.037
cuda-16-2 | 0.033 | 0.008 | 0.012 | 0.013 | 0.033
cuda-8-4 | 0.033 | 0.007 | 0.012 | 0.014 | 0.033
cuda-4-8 | 0.038 | 0.008 | 0.013 | 0.017 | 0.038
cuda-2-16 | 0.036 | 0.008 | 0.004 | 0.024 | 0.036
cuda-1-32 | 0.054 | 0.008 | 0.015 | 0.031 | 0.054


### small_snap_dblp/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.035** | **0.007** | **0.011** | **0.017** | **0.033**
**cuda-bitmap-kernel** | **0.039** | **0.007** | **0.014** | **0.018** | **0.036**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### small_snap_web_berkstan

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.043** | **0.007** | **0.013** | **0.023** | **0.040**
**cuda-bitmap-kernel** | **0.044** | **0.007** | **0.016** | **0.021** | **0.040**
**cuda-baseline-hybrid** | **0.033** | **0.007** | **0.004** | **0.022** | **0.033**
cuda-baseline | 0.051 | 0.006 | 0.013 | 0.032 | 0.051
cuda-32-1 | 0.053 | 0.007 | 0.012 | 0.034 | 0.053
cuda-16-2 | 0.046 | 0.007 | 0.011 | 0.028 | 0.046
cuda-8-4 | 0.044 | 0.007 | 0.012 | 0.025 | 0.044
cuda-4-8 | 0.033 | 0.005 | 0.003 | 0.025 | 0.034
cuda-2-16 | 0.046 | 0.007 | 0.012 | 0.027 | 0.047
cuda-1-32 | 0.056 | 0.009 | 0.006 | 0.041 | 0.056


### small_snap_web_berkstan/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.044** | **0.009** | **0.012** | **0.023** | **0.041**
**cuda-bitmap-kernel** | **0.047** | **0.009** | **0.01** | **0.028** | **0.043**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### small_snap_web_notredame

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.031** | **0.004** | **0.013** | **0.014** | **0.027**
**cuda-bitmap-kernel** | **0.031** | **0.004** | **0.01** | **0.017** | **0.027**
**cuda-baseline-hybrid** | **0.05** | **0.004** | **0.001** | **0.045** | **0.050**
cuda-baseline | 0.075 | 0.006 | 0.01 | 0.059 | 0.075
cuda-32-1 | 0.098 | 0.004 | 0.012 | 0.082 | 0.099
cuda-16-2 | 0.124 | 0.004 | 0.013 | 0.107 | 0.124
cuda-8-4 | 0.176 | 0.004 | 0.004 | 0.168 | 0.177
cuda-4-8 | 0.292 | 0.004 | 0.005 | 0.283 | 0.293
cuda-2-16 | 0.493 | 0.007 | 0.001 | 0.485 | 0.493
cuda-1-32 | 0.842 | 0.006 | 0.008 | 0.828 | 0.842


### small_snap_web_notredame/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.029** | **0.004** | **0.011** | **0.014** | **0.026**
**cuda-bitmap-kernel** | **0.027** | **0.004** | **0.01** | **0.013** | **0.024**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### small_snap_web_stanford

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.019** | **0.004** | **0.004** | **0.011** | **0.017**
**cuda-bitmap-kernel** | **0.02** | **0.004** | **0.003** | **0.013** | **0.017**
**cuda-baseline-hybrid** | **0.017** | **0.004** | **0.002** | **0.011** | **0.017**
cuda-baseline | 0.025 | 0.005 | 0.008 | 0.012 | 0.026
cuda-32-1 | 0.025 | 0.004 | 0.009 | 0.012 | 0.026
cuda-16-2 | 0.018 | 0.004 | 0.003 | 0.011 | 0.018
cuda-8-4 | 0.023 | 0.004 | 0.007 | 0.012 | 0.023
cuda-4-8 | 0.026 | 0.005 | 0.01 | 0.011 | 0.026
cuda-2-16 | 0.032 | 0.004 | 0.013 | 0.015 | 0.032
cuda-1-32 | 0.039 | 0.004 | 0.013 | 0.022 | 0.040


### small_snap_web_stanford/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.033** | **0.004** | **0.016** | **0.013** | **0.030**
**cuda-bitmap-kernel** | **0.028** | **0.004** | **0.011** | **0.013** | **0.025**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### snap_pokec

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.26** | **0.075** | **0.033** | **0.152** | **0.257**
**cuda-bitmap-kernel** | **0.248** | **0.07** | **0.028** | **0.150** | **0.244**
**cuda-baseline-hybrid** | **0.696** | **0.074** | **0.027** | **0.595** | **0.696**
cuda-baseline | 0.803 | 0.071 | 0.031 | 0.701 | 0.803
cuda-32-1 | 0.85 | 0.069 | 0.026 | 0.755 | 0.850
cuda-16-2 | 1.044 | 0.069 | 0.026 | 0.949 | 1.044
cuda-8-4 | 1.537 | 0.075 | 0.027 | 1.435 | 1.537
cuda-4-8 | 2.589 | 0.071 | 0.033 | 2.485 | 2.589
cuda-2-16 | 4.628 | 0.073 | 0.037 | 4.518 | 4.628
cuda-1-32 | 8.599 | 0.073 | 0.031 | 8.495 | 8.599


### snap_pokec/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.246** | **0.082** | **0.029** | **0.135** | **0.243**
**cuda-bitmap-kernel** | **0.257** | **0.075** | **0.024** | **0.158** | **0.252**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### snap_livejournal

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.501** | **0.148** | **0.044** | **0.309** | **0.495**
**cuda-bitmap-kernel** | **0.569** | **0.145** | **0.044** | **0.380** | **0.562**
**cuda-baseline-hybrid** | **1.769** | **0.145** | **0.048** | **1.576** | **1.769**
cuda-baseline | 2.099 | 0.146 | 0.047 | 1.906 | 2.099
cuda-32-1 | 2.227 | 0.145 | 0.052 | 2.030 | 2.228
cuda-16-2 | 2.745 | 0.144 | 0.045 | 2.556 | 2.745
cuda-8-4 | 4.158 | 0.145 | 0.046 | 3.967 | 4.158
cuda-4-8 | 7.048 | 0.144 | 0.046 | 6.858 | 7.048
cuda-2-16 | 12.962 | 0.142 | 0.046 | 12.774 | 12.962
cuda-1-32 | 24.304 | 0.145 | 0.049 | 24.110 | 24.303


### snap_livejournal/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **0.594** | **0.178** | **0.054** | **0.362** | **0.591**
**cuda-bitmap-kernel** | **0.639** | **0.177** | **0.051** | **0.411** | **0.632**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### snap_orkut

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **2.402** | **0.605** | **0.129** | **1.668** | **2.395**
**cuda-bitmap-kernel** | **2.706** | **0.626** | **0.124** | **1.956** | **2.699**
**cuda-baseline-hybrid** | **13.782** | **0.62** | **0.123** | **13.039** | **13.782**
cuda-baseline | 14.012 | 0.612 | 0.127 | 13.273 | 14.012
cuda-32-1 | 12.959 | 0.626 | 0.125 | 12.208 | 12.959
cuda-16-2 | 14.539 | 0.62 | 0.126 | 13.793 | 14.538
cuda-8-4 | 21.617 | 0.622 | 0.127 | 20.868 | 21.617
cuda-4-8 | 36.412 | 0.61 | 0.129 | 35.673 | 36.411
cuda-2-16 | 65.465 | 0.615 | 0.129 | 64.721 | 65.463
cuda-1-32 | 125.509 | 0.619 | 0.125 | 124.765 | 125.505


### snap_orkut/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **2.498** | **0.722** | **0.128** | **1.648** | **2.494**
**cuda-bitmap-kernel** | **2.688** | **0.741** | **0.14** | **1.807** | **2.682**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### snap_friendster

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **/** | **/** | **/** | **/** | **/**
**cuda-bitmap-kernel** | **/** | **/** | **/** | **/** | **/**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### snap_friendster/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **/** | **/** | **/** | **/** | **/**
**cuda-bitmap-kernel** | **/** | **/** | **/** | **/** | **/**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### webgraph_it

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **/** | **/** | **/** | **/** | **/**
**cuda-bitmap-kernel** | **/** | **/** | **/** | **/** | **/**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### webgraph_it/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **16.731** | **2.153** | **0.82** | **13.758** | **16.716**
**cuda-bitmap-kernel** | **781.115** | **1.788** | **0.833** | **778.494** | **781.040**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### webgraph_uk

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **6.383** | **0.332** | **0.125** | **5.926** | **6.377**
**cuda-bitmap-kernel** | **11.296** | **0.331** | **0.122** | **10.843** | **11.279**
**cuda-baseline-hybrid** | **5.621** | **0.331** | **0.121** | **5.169** | **5.621**
cuda-baseline | 186.157 | 0.333 | 0.12 | 185.704 | 186.151
cuda-32-1 | 32.044 | 0.336 | 0.13 | 31.578 | 32.043
cuda-16-2 | 16.984 | 0.329 | 0.123 | 16.532 | 16.984
cuda-8-4 | 9.614 | 0.337 | 0.12 | 9.157 | 9.614
cuda-4-8 | 6.055 | 0.33 | 0.117 | 5.608 | 6.055
cuda-2-16 | 4.788 | 0.33 | 0.115 | 4.343 | 4.788
cuda-1-32 | 5.226 | 0.333 | 0.127 | 4.766 | 5.227


### webgraph_uk/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **2.299** | **0.551** | **0.222** | **1.526** | **2.291**
**cuda-bitmap-kernel** | **3.644** | **0.555** | **0.211** | **2.878** | **3.624**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### webgraph_eu

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **25.563** | **0.666** | **0.2** | **24.697** | **25.556**
**cuda-bitmap-kernel** | **80.498** | **0.662** | **0.194** | **79.642** | **80.485**
**cuda-baseline-hybrid** | **390.206** | **0.667** | **0.196** | **389.343** | **390.192**
cuda-baseline | 529.135 | 0.665 | 0.193 | 528.277 | 529.116
cuda-32-1 | 512.221 | 0.669 | 0.243 | 511.309 | 512.203
cuda-16-2 | 494.739 | 0.666 | 0.211 | 493.862 | 494.722
cuda-8-4 | 669.013 | 0.666 | 0.196 | 668.151 | 668.990
cuda-4-8 | 1108.36 | 0.668 | 0.205 | 1107.487 | 1108.322
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### webgraph_eu/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **21.816** | **0.779** | **0.267** | **20.770** | **21.810**
**cuda-bitmap-kernel** | **68.816** | **0.783** | **0.228** | **67.805** | **68.804**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### webgraph_twitter

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **444.125** | **5.49** | **1.301** | **437.334** | **444.096**
**cuda-bitmap-kernel** | **/** | **/** | **/** | **/** | **/**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### webgraph_twitter/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **43.581** | **6.08** | **1.146** | **36.355** | **43.566**
**cuda-bitmap-kernel** | **/** | **/** | **/** | **/** | **/**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### webgraph_webbase

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **/** | **/** | **/** | **/** | **/**
**cuda-bitmap-kernel** | **/** | **/** | **/** | **/** | **/**
**cuda-baseline-hybrid** | **19.397** | **1.138** | **0.403** | **17.856** | **19.396**
cuda-baseline | / | / | / | / | /
cuda-32-1 | 367.854 | 1.146 | 0.409 | 366.299 | 367.841
cuda-16-2 | 189.533 | 1.154 | 0.397 | 187.982 | 189.526
cuda-8-4 | 101.105 | 1.152 | 0.404 | 99.549 | 101.102
cuda-4-8 | 58.144 | 1.147 | 0.412 | 56.585 | 58.142
cuda-2-16 | 39.012 | 1.147 | 0.411 | 37.454 | 39.011
cuda-1-32 | 33.612 | 1.142 | 0.406 | 32.064 | 33.611


### webgraph_webbase/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **/** | **/** | **/** | **/** | **/**
**cuda-bitmap-kernel** | **/** | **/** | **/** | **/** | **/**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### lfr_dataset

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **3.273** | **0.829** | **0.124** | **2.320** | **3.270**
**cuda-bitmap-kernel** | **4.04** | **0.82** | **0.123** | **3.097** | **4.033**
**cuda-baseline-hybrid** | **8.098** | **0.835** | **0.16** | **7.103** | **8.098**
cuda-baseline | 7.009 | 0.823 | 0.126 | 6.060 | 7.009
cuda-32-1 | 7.733 | 0.83 | 0.122 | 6.781 | 7.733
cuda-16-2 | 4.849 | 0.821 | 0.136 | 3.892 | 4.849
cuda-8-4 | 3.501 | 0.851 | 0.124 | 2.526 | 3.501
cuda-4-8 | 3.063 | 0.814 | 0.125 | 2.124 | 3.064
cuda-2-16 | 3.189 | 0.809 | 0.124 | 2.256 | 3.189
cuda-1-32 | 4.092 | 0.822 | 0.139 | 3.131 | 4.092


### lfr_dataset/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **3.181** | **0.789** | **0.131** | **2.261** | **3.176**
**cuda-bitmap-kernel** | **3.753** | **0.761** | **0.123** | **2.869** | **3.748**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### lfr_graphs/n2400000_k100_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **3.466** | **0.825** | **0.124** | **2.517** | **3.463**
**cuda-bitmap-kernel** | **4.311** | **0.818** | **0.122** | **3.371** | **4.305**
**cuda-baseline-hybrid** | **7.605** | **0.844** | **0.126** | **6.635** | **7.605**
cuda-baseline | 7.489 | 0.814 | 0.121 | 6.554 | 7.489
cuda-32-1 | 8.022 | 0.815 | 0.123 | 7.084 | 8.021
cuda-16-2 | 4.95 | 0.816 | 0.122 | 4.012 | 4.950
cuda-8-4 | 3.599 | 0.844 | 0.128 | 2.627 | 3.599
cuda-4-8 | 3.065 | 0.825 | 0.127 | 2.113 | 3.065
cuda-2-16 | 3.415 | 0.809 | 0.13 | 2.476 | 3.416
cuda-1-32 | 4.538 | 0.846 | 0.121 | 3.571 | 4.538


### lfr_graphs/n2400000_k100_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **3.414** | **0.74** | **0.125** | **2.549** | **3.407**
**cuda-bitmap-kernel** | **4.093** | **0.744** | **0.123** | **3.226** | **4.087**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### lfr_graphs/n3000000_k80_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **3.281** | **0.817** | **0.136** | **2.328** | **3.279**
**cuda-bitmap-kernel** | **4.032** | **0.842** | **0.127** | **3.063** | **4.027**
**cuda-baseline-hybrid** | **7.085** | **0.823** | **0.125** | **6.137** | **7.085**
cuda-baseline | 7.18 | 0.853 | 0.122 | 6.205 | 7.180
cuda-32-1 | 7.609 | 0.832 | 0.125 | 6.652 | 7.609
cuda-16-2 | 4.855 | 0.821 | 0.124 | 3.910 | 4.855
cuda-8-4 | 3.569 | 0.813 | 0.129 | 2.627 | 3.569
cuda-4-8 | 3.02 | 0.868 | 0.125 | 2.027 | 3.020
cuda-2-16 | 3.156 | 0.82 | 0.124 | 2.212 | 3.156
cuda-1-32 | 4.053 | 0.822 | 0.123 | 3.108 | 4.053


### lfr_graphs/n3000000_k80_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **3.011** | **0.73** | **0.125** | **2.156** | **3.006**
**cuda-bitmap-kernel** | **3.84** | **0.776** | **0.129** | **2.935** | **3.835**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### lfr_graphs/n4000000_k60_C0dot1_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **3.042** | **0.87** | **0.141** | **2.031** | **3.037**
**cuda-bitmap-kernel** | **3.689** | **0.831** | **0.141** | **2.717** | **3.682**
**cuda-baseline-hybrid** | **6.629** | **0.829** | **0.132** | **5.668** | **6.629**
cuda-baseline | 6.66 | 0.84 | 0.132 | 5.688 | 6.660
cuda-32-1 | 7.517 | 0.854 | 0.13 | 6.533 | 7.517
cuda-16-2 | 4.691 | 0.863 | 0.131 | 3.697 | 4.691
cuda-8-4 | 3.4 | 0.851 | 0.134 | 2.415 | 3.401
cuda-4-8 | 2.894 | 0.838 | 0.131 | 1.925 | 2.894
cuda-2-16 | 3.001 | 0.87 | 0.131 | 2.000 | 3.002
cuda-1-32 | 3.683 | 0.831 | 0.129 | 2.723 | 3.683


### lfr_graphs/n4000000_k60_C0dot1_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **2.668** | **0.75** | **0.145** | **1.773** | **2.663**
**cuda-bitmap-kernel** | **3.329** | **0.773** | **0.134** | **2.422** | **3.321**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### lfr_graphs/n4000000_k60_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **3.437** | **0.897** | **0.131** | **2.409** | **3.432**
**cuda-bitmap-kernel** | **3.72** | **0.851** | **0.151** | **2.718** | **3.712**
**cuda-baseline-hybrid** | **6.579** | **0.852** | **0.144** | **5.583** | **6.579**
cuda-baseline | 6.681 | 0.877 | 0.13 | 5.674 | 6.681
cuda-32-1 | 7.454 | 0.833 | 0.133 | 6.488 | 7.454
cuda-16-2 | 4.668 | 0.828 | 0.13 | 3.710 | 4.668
cuda-8-4 | 3.507 | 0.871 | 0.154 | 2.482 | 3.508
cuda-4-8 | 2.923 | 0.837 | 0.13 | 1.956 | 2.924
cuda-2-16 | 2.971 | 0.853 | 0.131 | 1.987 | 2.971
cuda-1-32 | 3.641 | 0.877 | 0.132 | 2.632 | 3.641


### lfr_graphs/n4000000_k60_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **2.752** | **0.759** | **0.133** | **1.860** | **2.747**
**cuda-bitmap-kernel** | **3.284** | **0.787** | **0.132** | **2.365** | **3.276**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### lfr_graphs/n6000000_k40_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **2.773** | **0.848** | **0.153** | **1.772** | **2.768**
**cuda-bitmap-kernel** | **3.459** | **0.845** | **0.149** | **2.465** | **3.450**
**cuda-baseline-hybrid** | **6.135** | **0.85** | **0.161** | **5.124** | **6.135**
cuda-baseline | 6.14 | 0.901 | 0.153 | 5.086 | 6.140
cuda-32-1 | 7.082 | 0.884 | 0.156 | 6.042 | 7.082
cuda-16-2 | 4.554 | 0.879 | 0.157 | 3.518 | 4.554
cuda-8-4 | 3.328 | 0.848 | 0.154 | 2.326 | 3.329
cuda-4-8 | 2.759 | 0.85 | 0.152 | 1.757 | 2.759
cuda-2-16 | 2.727 | 0.853 | 0.155 | 1.719 | 2.727
cuda-1-32 | 3.221 | 0.857 | 0.154 | 2.210 | 3.221


### lfr_graphs/n6000000_k40_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **2.509** | **0.802** | **0.152** | **1.555** | **2.503**
**cuda-bitmap-kernel** | **2.776** | **0.816** | **0.153** | **1.807** | **2.767**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### n12dot5_m80_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **22.947** | **8.436** | **1.983** | **12.528** | **22.941**
**cuda-bitmap-kernel** | **31.97** | **8.588** | **1.983** | **21.399** | **31.952**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### n12dot5_m80_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **24.95** | **8.775** | **1.969** | **14.206** | **24.944**
**cuda-bitmap-kernel** | **33.425** | **8.348** | **1.97** | **23.107** | **33.408**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### n16dot7_m60_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **23.003** | **8.273** | **2.314** | **12.416** | **22.995**
**cuda-bitmap-kernel** | **33.752** | **7.912** | **2.295** | **23.545** | **33.730**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### n16dot7_m60_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **23.113** | **8.517** | **2.303** | **12.293** | **23.104**
**cuda-bitmap-kernel** | **33.324** | **8.298** | **2.308** | **22.718** | **33.302**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### n25_m40_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **21.843** | **8.066** | **2.717** | **11.060** | **21.832**
**cuda-bitmap-kernel** | **/** | **/** | **/** | **/** | **/**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### n25_m40_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **22.799** | **8.08** | **2.782** | **11.937** | **22.788**
**cuda-bitmap-kernel** | **/** | **/** | **/** | **/** | **/**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### n50_m20_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **/** | **/** | **/** | **/** | **/**
**cuda-bitmap-kernel** | **/** | **/** | **/** | **/** | **/**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /


### n50_m20_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both)
--- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex** | **/** | **/** | **/** | **/** | **/**
**cuda-bitmap-kernel** | **/** | **/** | **/** | **/** | **/**
**cuda-baseline-hybrid** | **/** | **/** | **/** | **/** | **/**
cuda-baseline | / | / | / | / | /
cuda-32-1 | / | / | / | / | /
cuda-16-2 | / | / | / | / | /
cuda-8-4 | / | / | / | / | /
cuda-4-8 | / | / | / | / | /
cuda-2-16 | / | / | / | / | /
cuda-1-32 | / | / | / | / | /