# Core Checking (eps = 0.2, mu = 5)


Unit: seconds


### snap_pokec

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **0.207** | **0.032** | **0.031** | **0.144** | **0.022** | **0.122**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **0.21** | **0.031** | **0.031** | **0.148** | **0.022** | **0.126**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.026 | 0.041 | / | 0.025 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.026 | 0.038 | / | 0.024 | /
cuda-32-1-multi-gpu-multi-pass | 1.847 | 0.037 | 0.041 | 1.769 | 0.025 | 1.744
cuda-16-2-multi-gpu-multi-pass | 1.771 | 0.033 | 0.036 | 1.702 | 0.022 | 1.68
cuda-8-4-multi-gpu-multi-pass | 1.897 | 0.035 | 0.046 | 1.816 | 0.024 | 1.792
cuda-4-8-multi-gpu-multi-pass | 2.889 | 0.037 | 0.037 | 2.815 | 0.024 | 2.791
cuda-2-16-multi-gpu-multi-pass | 5.175 | 0.038 | 0.038 | 5.099 | 0.024 | 5.075
cuda-1-32-multi-gpu-multi-pass | 9.581 | 0.034 | 0.045 | 9.502 | 0.023 | 9.479
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.309** | **0.035** | **0.032** | **0.242** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.311** | **0.033** | **0.032** | **0.246** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.026 | 0.033 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.027 | 0.033 | / | / | /
cuda-32-1-single-gpu-multi-pass | 1.125 | 0.032 | 0.036 | 1.057 | / | /
cuda-16-2-single-gpu-multi-pass | 1.312 | 0.034 | 0.031 | 1.247 | / | /
cuda-8-4-single-gpu-multi-pass | 1.993 | 0.033 | 0.033 | 1.927 | / | /
cuda-4-8-single-gpu-multi-pass | 3.008 | 0.032 | 0.039 | 2.937 | / | /


### snap_pokec/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **0.233** | **0.037** | **0.031** | **0.165** | **0.021** | **0.144**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **0.261** | **0.035** | **0.037** | **0.189** | **0.024** | **0.165**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.027 | 0.036 | / | 0.03 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.029 | 0.039 | / | 0.029 | /
cuda-32-1-multi-gpu-multi-pass | 1.889 | 0.043 | 0.039 | 1.807 | 0.024 | 1.783
cuda-16-2-multi-gpu-multi-pass | 1.772 | 0.039 | 0.033 | 1.700 | 0.028 | 1.672
cuda-8-4-multi-gpu-multi-pass | 1.8 | 0.036 | 0.034 | 1.730 | 0.029 | 1.701
cuda-4-8-multi-gpu-multi-pass | 2.936 | 0.036 | 0.038 | 2.862 | 0.029 | 2.833
cuda-2-16-multi-gpu-multi-pass | 5.218 | 0.036 | 0.035 | 5.147 | 0.024 | 5.123
cuda-1-32-multi-gpu-multi-pass | 9.663 | 0.036 | 0.039 | 9.588 | 0.029 | 9.559
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.314** | **0.035** | **0.029** | **0.250** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.337** | **0.036** | **0.038** | **0.263** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.027 | 0.029 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.026 | 0.034 | / | / | /
cuda-32-1-single-gpu-multi-pass | 1.111 | 0.035 | 0.034 | 1.042 | / | /
cuda-16-2-single-gpu-multi-pass | 1.337 | 0.034 | 0.045 | 1.258 | / | /
cuda-8-4-single-gpu-multi-pass | 1.892 | 0.036 | 0.041 | 1.815 | / | /
cuda-4-8-single-gpu-multi-pass | 3.056 | 0.038 | 0.037 | 2.981 | / | /


### snap_livejournal

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **0.387** | **0.056** | **0.056** | **0.275** | **0.055** | **0.22**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **0.379** | **0.053** | **0.052** | **0.274** | **0.048** | **0.226**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.051 | 0.066 | / | 0.051 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.046 | 0.062 | / | 0.052 | /
cuda-32-1-multi-gpu-multi-pass | 2.695 | 0.068 | 0.057 | 2.570 | 0.051 | 2.519
cuda-16-2-multi-gpu-multi-pass | 3.243 | 0.062 | 0.063 | 3.118 | 0.053 | 3.065
cuda-8-4-multi-gpu-multi-pass | 4.792 | 0.062 | 0.064 | 4.666 | 0.055 | 4.611
cuda-4-8-multi-gpu-multi-pass | 8.019 | 0.061 | 0.057 | 7.901 | 0.05 | 7.851
cuda-2-16-multi-gpu-multi-pass | 14.481 | 0.061 | 0.058 | 14.362 | 0.05 | 14.312
cuda-1-32-multi-gpu-multi-pass | 27.029 | 0.062 | 0.065 | 26.902 | 0.049 | 26.853
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.63** | **0.069** | **0.066** | **0.495** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.656** | **0.063** | **0.053** | **0.540** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.053 | 0.053 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.056 | 0.056 | / | / | /
cuda-32-1-single-gpu-multi-pass | 2.995 | 0.067 | 0.054 | 2.874 | / | /
cuda-16-2-single-gpu-multi-pass | 3.448 | 0.067 | 0.068 | 3.313 | / | /
cuda-8-4-single-gpu-multi-pass | 5.018 | 0.068 | 0.055 | 4.895 | / | /
cuda-4-8-single-gpu-multi-pass | 8.325 | 0.066 | 0.066 | 8.193 | / | /


### snap_livejournal/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **0.483** | **0.065** | **0.055** | **0.363** | **0.056** | **0.307**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **0.547** | **0.068** | **0.063** | **0.416** | **0.062** | **0.354**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.048 | 0.064 | / | 0.055 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.044 | 0.064 | / | 0.064 | /
cuda-32-1-multi-gpu-multi-pass | 2.455 | 0.07 | 0.073 | 2.312 | 0.058 | 2.254
cuda-16-2-multi-gpu-multi-pass | 3.246 | 0.068 | 0.069 | 3.109 | 0.063 | 3.046
cuda-8-4-multi-gpu-multi-pass | 4.858 | 0.07 | 0.064 | 4.724 | 0.059 | 4.665
cuda-4-8-multi-gpu-multi-pass | 8.099 | 0.067 | 0.057 | 7.975 | 0.058 | 7.917
cuda-2-16-multi-gpu-multi-pass | 14.608 | 0.068 | 0.067 | 14.473 | 0.056 | 14.417
cuda-1-32-multi-gpu-multi-pass | 27.176 | 0.075 | 0.06 | 27.041 | 0.051 | 26.99
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.684** | **0.073** | **0.058** | **0.553** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.718** | **0.073** | **0.058** | **0.587** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.054 | 0.057 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.053 | 0.061 | / | / | /
cuda-32-1-single-gpu-multi-pass | 2.905 | 0.072 | 0.062 | 2.771 | / | /
cuda-16-2-single-gpu-multi-pass | 3.474 | 0.072 | 0.059 | 3.343 | / | /
cuda-8-4-single-gpu-multi-pass | 5.107 | 0.071 | 0.064 | 4.972 | / | /
cuda-4-8-single-gpu-multi-pass | 8.405 | 0.074 | 0.058 | 8.273 | / | /


### snap_orkut

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.487** | **0.162** | **0.135** | **1.190** | **0.087** | **1.103**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.6** | **0.162** | **0.142** | **1.296** | **0.093** | **1.203**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.118 | 0.134 | / | 0.084 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.12 | 0.154 | / | 0.08 | /
cuda-32-1-multi-gpu-multi-pass | 12.461 | 0.172 | 0.144 | 12.145 | 0.086 | 12.059
cuda-16-2-multi-gpu-multi-pass | 16.045 | 0.166 | 0.142 | 15.737 | 0.084 | 15.653
cuda-8-4-multi-gpu-multi-pass | 24.007 | 0.168 | 0.138 | 23.701 | 0.093 | 23.608
cuda-4-8-multi-gpu-multi-pass | 40.072 | 0.172 | 0.139 | 39.761 | 0.08 | 39.681
cuda-2-16-multi-gpu-multi-pass | 73.44 | 0.298 | 0.151 | 72.991 | 0.08 | 72.911
cuda-1-32-multi-gpu-multi-pass | 137.08 | 0.296 | 0.148 | 136.636 | 0.088 | 136.548
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **2.966** | **0.193** | **0.141** | **2.632** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.05** | **0.194** | **0.141** | **2.715** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.168 | 0.137 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.168 | 0.136 | / | / | /
cuda-32-1-single-gpu-multi-pass | 16.124 | 0.199 | 0.144 | 15.781 | / | /
cuda-16-2-single-gpu-multi-pass | 18.113 | 0.2 | 0.143 | 17.770 | / | /
cuda-8-4-single-gpu-multi-pass | 27.266 | 0.201 | 0.144 | 26.921 | / | /
cuda-4-8-single-gpu-multi-pass | 42.379 | 0.197 | 0.146 | 42.036 | / | /


### snap_orkut/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.846** | **0.185** | **0.147** | **1.514** | **0.096** | **1.418**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.876** | **0.178** | **0.151** | **1.547** | **0.095** | **1.452**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.124 | 0.146 | / | 0.099 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.126 | 0.146 | / | 0.099 | /
cuda-32-1-multi-gpu-multi-pass | 12.383 | 0.186 | 0.152 | 12.045 | 0.102 | 11.943
cuda-16-2-multi-gpu-multi-pass | 16.087 | 0.191 | 0.156 | 15.740 | 0.089 | 15.651
cuda-8-4-multi-gpu-multi-pass | 24.215 | 0.185 | 0.154 | 23.876 | 0.1 | 23.776
cuda-4-8-multi-gpu-multi-pass | 41.041 | 0.185 | 0.159 | 40.697 | 0.098 | 40.599
cuda-2-16-multi-gpu-multi-pass | 74.578 | 0.308 | 0.153 | 74.117 | 0.097 | 74.02
cuda-1-32-multi-gpu-multi-pass | 138.919 | 0.308 | 0.175 | 138.436 | 0.094 | 138.342
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **2.972** | **0.213** | **0.195** | **2.564** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.179** | **0.221** | **0.154** | **2.804** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.166 | 0.147 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.167 | 0.179 | / | / | /
cuda-32-1-single-gpu-multi-pass | 14.996 | 0.209 | 0.153 | 14.634 | / | /
cuda-16-2-single-gpu-multi-pass | 17.753 | 0.215 | 0.152 | 17.386 | / | /
cuda-8-4-single-gpu-multi-pass | 25.796 | 0.211 | 0.155 | 25.430 | / | /
cuda-4-8-single-gpu-multi-pass | 42.983 | 0.215 | 0.155 | 42.613 | / | /


### snap_friendster

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **42.031** | **2.769** | **6.427** | **32.835** | **4.79** | **28.045**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | 58.762 | 2.992 | 6.534 | 49.236 | 5.104 | 44.132
cuda-16-2-multi-gpu-multi-pass | 49.183 | 2.973 | 6.478 | 39.732 | 5.02 | 34.712
cuda-8-4-multi-gpu-multi-pass | 46.206 | 3.077 | 6.431 | 36.698 | 4.881 | 31.817
cuda-4-8-multi-gpu-multi-pass | 46.307 | 3.004 | 6.466 | 36.837 | 4.909 | 31.928
cuda-2-16-multi-gpu-multi-pass | 51.424 | 2.976 | 6.519 | 41.929 | 5.103 | 36.826
cuda-1-32-multi-gpu-multi-pass | 61.201 | 3.011 | 6.371 | 51.819 | 4.918 | 46.901
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **135.634** | **2.796** | **6.516** | **126.322** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 231.046 | 3.006 | 6.5 | 221.540 | / | /
cuda-16-2-single-gpu-multi-pass | 149.235 | 2.977 | 6.489 | 139.769 | / | /
cuda-8-4-single-gpu-multi-pass | 123.704 | 2.97 | 6.564 | 114.170 | / | /
cuda-4-8-single-gpu-multi-pass | 130.186 | 2.959 | 6.034 | 121.193 | / | /


### snap_friendster/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **54.117** | **3.544** | **4.917** | **45.656** | **4.367** | **41.289**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | 44.524 | 3.209 | 5.271 | 36.044 | 3.873 | 32.171
cuda-16-2-multi-gpu-multi-pass | 40.376 | 3.117 | 5.365 | 31.894 | 4.408 | 27.486
cuda-8-4-multi-gpu-multi-pass | 39.326 | 3.165 | 5.094 | 31.067 | 4.672 | 26.395
cuda-4-8-multi-gpu-multi-pass | 40.615 | 3.135 | 5.425 | 32.055 | 4.355 | 27.7
cuda-2-16-multi-gpu-multi-pass | 47.589 | 3.132 | 5.224 | 39.233 | 3.904 | 35.329
cuda-1-32-multi-gpu-multi-pass | 72.439 | 3.785 | 4.793 | 63.861 | 4.271 | 59.59
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **125.868** | **2.98** | **4.892** | **117.996** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 149.176 | 3.072 | 5.15 | 140.954 | / | /
cuda-16-2-single-gpu-multi-pass | 108.941 | 3.134 | 4.926 | 100.881 | / | /
cuda-8-4-single-gpu-multi-pass | 105.547 | 3.152 | 4.877 | 97.518 | / | /
cuda-4-8-single-gpu-multi-pass | 127.947 | 3.17 | 4.76 | 120.017 | / | /


### webgraph_it

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **51.711** | **0.623** | **0.38** | **50.708** | **0.372** | **50.336**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **117.285** | **0.537** | **0.398** | **116.350** | **0.368** | **115.982**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.555 | 0.382 | / | 0.424 | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-multi-gpu-multi-pass | 243.909 | 0.765 | 0.368 | 242.776 | 0.401 | 242.375
cuda-4-8-multi-gpu-multi-pass | 130.562 | 0.615 | 0.379 | 129.568 | 0.38 | 129.188
cuda-2-16-multi-gpu-multi-pass | 82.781 | 0.618 | 0.381 | 81.782 | 0.408 | 81.374
cuda-1-32-multi-gpu-multi-pass | 71.691 | 0.627 | 0.373 | 70.691 | 0.375 | 70.316
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.818 | 0.368 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | /


### webgraph_it/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **6.071** | **0.624** | **0.892** | **4.555** | **0.746** | **3.809**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **9.984** | **0.613** | **0.816** | **8.555** | **0.723** | **7.832**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.613 | 0.823 | / | 0.731 | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-2-16-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **9.401** | **0.848** | **0.773** | **7.780** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **23.155** | **0.592** | **0.966** | **21.597** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.811 | 0.817 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | /


### webgraph_uk

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.088** | **0.171** | **0.126** | **0.791** | **0.158** | **0.633**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.229** | **0.172** | **0.121** | **0.936** | **0.154** | **0.782**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.169 | 0.139 | / | 0.151 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.359 | 0.122 | / | 0.167 | /
cuda-32-1-multi-gpu-multi-pass | 6.699 | 0.186 | 0.123 | 6.390 | 0.155 | 6.235
cuda-16-2-multi-gpu-multi-pass | 4.577 | 0.175 | 0.124 | 4.278 | 0.152 | 4.126
cuda-8-4-multi-gpu-multi-pass | 3.677 | 0.18 | 0.123 | 3.374 | 0.163 | 3.211
cuda-4-8-multi-gpu-multi-pass | 3.179 | 0.183 | 0.147 | 2.849 | 0.152 | 2.697
cuda-2-16-multi-gpu-multi-pass | 3.002 | 0.17 | 0.135 | 2.697 | 0.155 | 2.542
cuda-1-32-multi-gpu-multi-pass | 3.128 | 0.17 | 0.127 | 2.831 | 0.155 | 2.676
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **2.671** | **0.217** | **0.134** | **2.320** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.589** | **0.219** | **0.121** | **3.249** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.22 | 0.146 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.219 | 0.122 | / | / | /
cuda-32-1-single-gpu-multi-pass | 38.197 | 0.219 | 0.139 | 37.839 | / | /
cuda-16-2-single-gpu-multi-pass | 20.068 | 0.217 | 0.121 | 19.730 | / | /
cuda-8-4-single-gpu-multi-pass | 11.438 | 0.218 | 0.121 | 11.099 | / | /
cuda-4-8-single-gpu-multi-pass | 7.16 | 0.219 | 0.123 | 6.818 | / | /


### webgraph_uk/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.585** | **0.187** | **0.239** | **1.159** | **0.226** | **0.933**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.688** | **0.189** | **0.226** | **1.273** | **0.23** | **1.043**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.163 | 0.214 | / | 0.24 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.357 | 0.227 | / | 0.235 | /
cuda-32-1-multi-gpu-multi-pass | 255.979 | 0.362 | 0.249 | 255.368 | 0.258 | 255.11
cuda-16-2-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-2-16-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **1.808** | **0.23** | **0.224** | **1.354** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **2.381** | **0.233** | **0.243** | **1.905** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.219 | 0.226 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.219 | 0.237 | / | / | /
cuda-32-1-single-gpu-multi-pass | 260.796 | 0.232 | 0.263 | 260.301 | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | /


### webgraph_eu

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **3.139** | **0.264** | **0.262** | **2.613** | **0.152** | **2.461**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **6.605** | **0.289** | **0.236** | **6.080** | **0.143** | **5.937**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.412 | 0.238 | / | 0.14 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.383 | 0.302 | / | 0.152 | /
cuda-32-1-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-2-16-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **16.652** | **0.328** | **0.257** | **16.067** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **24.261** | **0.336** | **0.263** | **23.662** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | /


### webgraph_eu/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **4.709** | **0.274** | **0.276** | **4.159** | **0.171** | **3.988**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **4.851** | **0.276** | **0.3** | **4.275** | **0.174** | **4.101**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.282 | 0.266 | / | 0.171 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.274 | 0.315 | / | 0.178 | /
cuda-32-1-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-2-16-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **16.134** | **0.328** | **0.301** | **15.505** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **22.528** | **0.327** | **0.301** | **21.900** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | /


### webgraph_twitter

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **19.761** | **0.868** | **1.285** | **17.608** | **1.206** | **16.402**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **33.46** | **0.788** | **1.26** | **31.412** | **1.183** | **30.229**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-2-16-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **102.139** | **1.044** | **1.312** | **99.783** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **171.291** | **0.783** | **1.289** | **169.219** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | /


### webgraph_twitter/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **11.86** | **0.85** | **1.118** | **9.892** | **1.273** | **8.619**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **22.415** | **0.794** | **1.238** | **20.383** | **1.072** | **19.311**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-2-16-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **31.309** | **1.036** | **1.246** | **29.027** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **56.648** | **0.807** | **1.228** | **54.613** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | /


### webgraph_webbase

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **14.921** | **0.559** | **0.428** | **13.934** | **0.884** | **13.05**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **/** | **/** | **/** | **/** | **0.893** | **/**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.545 | 0.439 | / | 0.905 | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | 57.547 | 0.556 | 0.423 | 56.568 | 0.902 | 55.666
cuda-16-2-multi-gpu-multi-pass | 31.953 | 0.544 | 0.426 | 30.983 | 0.881 | 30.102
cuda-8-4-multi-gpu-multi-pass | 19.37 | 0.555 | 0.417 | 18.398 | 0.975 | 17.423
cuda-4-8-multi-gpu-multi-pass | 13.023 | 0.55 | 0.434 | 12.039 | 0.882 | 11.157
cuda-2-16-multi-gpu-multi-pass | 10.571 | 0.553 | 0.455 | 9.563 | 0.864 | 8.699
cuda-1-32-multi-gpu-multi-pass | 10.429 | 0.556 | 0.426 | 9.447 | 0.89 | 8.557
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **90.06** | **0.615** | **0.427** | **89.018** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.764 | 0.421 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | 226.307 | 0.769 | 0.413 | 225.125 | / | /
cuda-8-4-single-gpu-multi-pass | 120.214 | 0.768 | 0.483 | 118.963 | / | /
cuda-4-8-single-gpu-multi-pass | 68.574 | 0.769 | 0.412 | 67.393 | / | /


### webgraph_webbase/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **10.794** | **0.64** | **0.901** | **9.253** | **1.379** | **7.874**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **/** | **/** | **/** | **/** | **1.361** | **/**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.513 | 0.875 | / | 1.434 | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-2-16-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **13.495** | **0.673** | **0.87** | **11.952** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.759 | 0.913 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | /


### lfr_dataset

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.086** | **0.192** | **0.147** | **1.747** | **0.085** | **1.662**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.322** | **0.186** | **0.146** | **1.990** | **0.089** | **1.901**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.12 | 0.153 | / | 0.083 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.121 | 0.149 | / | 0.081 | /
cuda-32-1-multi-gpu-multi-pass | 3.409 | 0.19 | 0.145 | 3.074 | 0.091 | 2.983
cuda-16-2-multi-gpu-multi-pass | 3.049 | 0.193 | 0.149 | 2.707 | 0.077 | 2.63
cuda-8-4-multi-gpu-multi-pass | 2.742 | 0.189 | 0.149 | 2.404 | 0.082 | 2.322
cuda-4-8-multi-gpu-multi-pass | 2.993 | 0.196 | 0.185 | 2.612 | 0.085 | 2.527
cuda-2-16-multi-gpu-multi-pass | 2.874 | 0.199 | 0.148 | 2.527 | 0.075 | 2.452
cuda-1-32-multi-gpu-multi-pass | 2.915 | 0.191 | 0.149 | 2.575 | 0.084 | 2.491
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.642** | **0.214** | **0.152** | **3.276** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.577** | **0.22** | **0.15** | **4.207** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.169 | 0.149 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.172 | 0.159 | / | / | /
cuda-32-1-single-gpu-multi-pass | 9.477 | 0.217 | 0.149 | 9.111 | / | /
cuda-16-2-single-gpu-multi-pass | 5.999 | 0.219 | 0.151 | 5.629 | / | /
cuda-8-4-single-gpu-multi-pass | 4.361 | 0.221 | 0.15 | 3.990 | / | /
cuda-4-8-single-gpu-multi-pass | 3.783 | 0.22 | 0.149 | 3.414 | / | /


### lfr_dataset/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.848** | **0.184** | **0.148** | **1.516** | **0.103** | **1.413**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.077** | **0.175** | **0.144** | **1.758** | **0.098** | **1.66**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.12 | 0.152 | / | 0.098 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.118 | 0.15 | / | 0.097 | /
cuda-32-1-multi-gpu-multi-pass | 2.746 | 0.185 | 0.145 | 2.416 | 0.107 | 2.309
cuda-16-2-multi-gpu-multi-pass | 2.681 | 0.185 | 0.149 | 2.347 | 0.096 | 2.251
cuda-8-4-multi-gpu-multi-pass | 2.656 | 0.184 | 0.147 | 2.325 | 0.098 | 2.227
cuda-4-8-multi-gpu-multi-pass | 2.751 | 0.189 | 0.151 | 2.411 | 0.112 | 2.299
cuda-2-16-multi-gpu-multi-pass | 2.938 | 0.185 | 0.144 | 2.609 | 0.098 | 2.511
cuda-1-32-multi-gpu-multi-pass | 3.367 | 0.178 | 0.146 | 3.043 | 0.106 | 2.937
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.36** | **0.208** | **0.148** | **3.004** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.133** | **0.21** | **0.156** | **3.767** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.17 | 0.152 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.171 | 0.159 | / | / | /
cuda-32-1-single-gpu-multi-pass | 4.47 | 0.209 | 0.15 | 4.111 | / | /
cuda-16-2-single-gpu-multi-pass | 3.563 | 0.214 | 0.153 | 3.196 | / | /
cuda-8-4-single-gpu-multi-pass | 3.316 | 0.211 | 0.15 | 2.955 | / | /
cuda-4-8-single-gpu-multi-pass | 3.862 | 0.209 | 0.157 | 3.496 | / | /


### lfr_graphs/n2400000_k100_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.175** | **0.187** | **0.145** | **1.843** | **0.083** | **1.76**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.613** | **0.187** | **0.156** | **2.270** | **0.073** | **2.197**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.12 | 0.157 | / | 0.08 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.124 | 0.149 | / | 0.079 | /
cuda-32-1-multi-gpu-multi-pass | 3.43 | 0.187 | 0.144 | 3.099 | 0.077 | 3.022
cuda-16-2-multi-gpu-multi-pass | 2.964 | 0.189 | 0.145 | 2.630 | 0.078 | 2.552
cuda-8-4-multi-gpu-multi-pass | 2.874 | 0.19 | 0.2 | 2.484 | 0.075 | 2.409
cuda-4-8-multi-gpu-multi-pass | 2.764 | 0.187 | 0.183 | 2.394 | 0.072 | 2.322
cuda-2-16-multi-gpu-multi-pass | 3.028 | 0.193 | 0.145 | 2.690 | 0.073 | 2.617
cuda-1-32-multi-gpu-multi-pass | 3.124 | 0.195 | 0.143 | 2.786 | 0.08 | 2.706
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **4.025** | **0.213** | **0.144** | **3.668** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.783** | **0.21** | **0.146** | **4.427** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.168 | 0.148 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.169 | 0.15 | / | / | /
cuda-32-1-single-gpu-multi-pass | 9.653 | 0.216 | 0.146 | 9.291 | / | /
cuda-16-2-single-gpu-multi-pass | 6.117 | 0.218 | 0.147 | 5.752 | / | /
cuda-8-4-single-gpu-multi-pass | 4.446 | 0.214 | 0.145 | 4.087 | / | /
cuda-4-8-single-gpu-multi-pass | 3.957 | 0.214 | 0.147 | 3.596 | / | /


### lfr_graphs/n2400000_k100_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.96** | **0.175** | **0.144** | **1.641** | **0.092** | **1.549**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.3** | **0.179** | **0.147** | **1.974** | **0.093** | **1.881**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.12 | 0.15 | / | 0.097 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.124 | 0.194 | / | 0.096 | /
cuda-32-1-multi-gpu-multi-pass | 2.775 | 0.182 | 0.145 | 2.448 | 0.096 | 2.352
cuda-16-2-multi-gpu-multi-pass | 2.733 | 0.192 | 0.187 | 2.354 | 0.104 | 2.25
cuda-8-4-multi-gpu-multi-pass | 2.721 | 0.186 | 0.146 | 2.389 | 0.098 | 2.291
cuda-4-8-multi-gpu-multi-pass | 2.635 | 0.184 | 0.146 | 2.305 | 0.098 | 2.207
cuda-2-16-multi-gpu-multi-pass | 2.954 | 0.178 | 0.144 | 2.632 | 0.092 | 2.54
cuda-1-32-multi-gpu-multi-pass | 3.324 | 0.181 | 0.142 | 3.001 | 0.086 | 2.915
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.761** | **0.207** | **0.146** | **3.408** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.361** | **0.215** | **0.152** | **3.994** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.17 | 0.15 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.167 | 0.146 | / | / | /
cuda-32-1-single-gpu-multi-pass | 5.03 | 0.209 | 0.148 | 4.673 | / | /
cuda-16-2-single-gpu-multi-pass | 5.158 | 0.209 | 0.142 | 4.807 | / | /
cuda-8-4-single-gpu-multi-pass | 3.618 | 0.207 | 0.148 | 3.263 | / | /
cuda-4-8-single-gpu-multi-pass | 4.005 | 0.216 | 0.147 | 3.642 | / | /


### lfr_graphs/n3000000_k80_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.052** | **0.186** | **0.145** | **1.721** | **0.078** | **1.643**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.328** | **0.188** | **0.146** | **1.994** | **0.092** | **1.902**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.121 | 0.149 | / | 0.084 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.121 | 0.15 | / | 0.095 | /
cuda-32-1-multi-gpu-multi-pass | 3.487 | 0.191 | 0.165 | 3.131 | 0.08 | 3.051
cuda-16-2-multi-gpu-multi-pass | 3.152 | 0.193 | 0.149 | 2.810 | 0.086 | 2.724
cuda-8-4-multi-gpu-multi-pass | 2.769 | 0.192 | 0.151 | 2.426 | 0.085 | 2.341
cuda-4-8-multi-gpu-multi-pass | 2.688 | 0.183 | 0.146 | 2.359 | 0.083 | 2.276
cuda-2-16-multi-gpu-multi-pass | 2.771 | 0.198 | 0.193 | 2.380 | 0.08 | 2.3
cuda-1-32-multi-gpu-multi-pass | 3.01 | 0.193 | 0.15 | 2.667 | 0.082 | 2.585
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.843** | **0.215** | **0.149** | **3.479** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.614** | **0.22** | **0.149** | **4.245** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.169 | 0.153 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.17 | 0.152 | / | / | /
cuda-32-1-single-gpu-multi-pass | 9.376 | 0.218 | 0.15 | 9.008 | / | /
cuda-16-2-single-gpu-multi-pass | 5.988 | 0.221 | 0.149 | 5.618 | / | /
cuda-8-4-single-gpu-multi-pass | 4.53 | 0.224 | 0.149 | 4.157 | / | /
cuda-4-8-single-gpu-multi-pass | 3.689 | 0.213 | 0.149 | 3.327 | / | /


### lfr_graphs/n3000000_k80_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.945** | **0.176** | **0.147** | **1.622** | **0.102** | **1.52**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.052** | **0.177** | **0.145** | **1.730** | **0.101** | **1.629**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.127 | 0.192 | / | 0.095 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.123 | 0.15 | / | 0.103 | /
cuda-32-1-multi-gpu-multi-pass | 2.764 | 0.181 | 0.167 | 2.416 | 0.092 | 2.324
cuda-16-2-multi-gpu-multi-pass | 2.603 | 0.185 | 0.164 | 2.254 | 0.096 | 2.158
cuda-8-4-multi-gpu-multi-pass | 2.673 | 0.183 | 0.146 | 2.344 | 0.098 | 2.246
cuda-4-8-multi-gpu-multi-pass | 2.636 | 0.18 | 0.147 | 2.309 | 0.105 | 2.204
cuda-2-16-multi-gpu-multi-pass | 2.913 | 0.191 | 0.149 | 2.573 | 0.098 | 2.475
cuda-1-32-multi-gpu-multi-pass | 3.409 | 0.185 | 0.151 | 3.073 | 0.096 | 2.977
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.518** | **0.209** | **0.149** | **3.160** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.209** | **0.209** | **0.149** | **3.851** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.17 | 0.148 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.169 | 0.151 | / | / | /
cuda-32-1-single-gpu-multi-pass | 4.504 | 0.216 | 0.151 | 4.137 | / | /
cuda-16-2-single-gpu-multi-pass | 3.611 | 0.209 | 0.165 | 3.237 | / | /
cuda-8-4-single-gpu-multi-pass | 3.348 | 0.208 | 0.15 | 2.990 | / | /
cuda-4-8-single-gpu-multi-pass | 3.833 | 0.214 | 0.15 | 3.469 | / | /


### lfr_graphs/n4000000_k60_C0dot1_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.065** | **0.208** | **0.154** | **1.703** | **0.095** | **1.608**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.291** | **0.199** | **0.151** | **1.941** | **0.097** | **1.844**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.125 | 0.165 | / | 0.087 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.121 | 0.158 | / | 0.098 | /
cuda-32-1-multi-gpu-multi-pass | 3.388 | 0.204 | 0.195 | 2.989 | 0.091 | 2.898
cuda-16-2-multi-gpu-multi-pass | 3.01 | 0.195 | 0.151 | 2.664 | 0.097 | 2.567
cuda-8-4-multi-gpu-multi-pass | 2.963 | 0.202 | 0.153 | 2.608 | 0.098 | 2.51
cuda-4-8-multi-gpu-multi-pass | 2.824 | 0.197 | 0.154 | 2.473 | 0.094 | 2.379
cuda-2-16-multi-gpu-multi-pass | 2.687 | 0.2 | 0.153 | 2.334 | 0.093 | 2.241
cuda-1-32-multi-gpu-multi-pass | 3.241 | 0.197 | 0.158 | 2.886 | 0.091 | 2.795
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.595** | **0.224** | **0.157** | **3.214** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.108** | **0.224** | **0.155** | **3.729** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.174 | 0.197 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.173 | 0.159 | / | / | /
cuda-32-1-single-gpu-multi-pass | 9.076 | 0.225 | 0.158 | 8.693 | / | /
cuda-16-2-single-gpu-multi-pass | 6.844 | 0.229 | 0.158 | 6.457 | / | /
cuda-8-4-single-gpu-multi-pass | 4.377 | 0.228 | 0.156 | 3.993 | / | /
cuda-4-8-single-gpu-multi-pass | 3.781 | 0.226 | 0.171 | 3.384 | / | /


### lfr_graphs/n4000000_k60_C0dot1_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.785** | **0.184** | **0.156** | **1.445** | **0.12** | **1.325**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.963** | **0.18** | **0.154** | **1.629** | **0.113** | **1.516**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.121 | 0.157 | / | 0.12 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.121 | 0.156 | / | 0.123 | /
cuda-32-1-multi-gpu-multi-pass | 2.711 | 0.183 | 0.156 | 2.372 | 0.101 | 2.271
cuda-16-2-multi-gpu-multi-pass | 2.623 | 0.187 | 0.156 | 2.280 | 0.12 | 2.16
cuda-8-4-multi-gpu-multi-pass | 2.578 | 0.186 | 0.156 | 2.236 | 0.118 | 2.118
cuda-4-8-multi-gpu-multi-pass | 2.628 | 0.178 | 0.153 | 2.297 | 0.115 | 2.182
cuda-2-16-multi-gpu-multi-pass | 3.032 | 0.195 | 0.192 | 2.645 | 0.109 | 2.536
cuda-1-32-multi-gpu-multi-pass | 3.546 | 0.186 | 0.173 | 3.187 | 0.116 | 3.071
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.245** | **0.221** | **0.167** | **2.857** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.0** | **0.224** | **0.194** | **3.582** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.171 | 0.158 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.173 | 0.16 | / | / | /
cuda-32-1-single-gpu-multi-pass | 4.026 | 0.22 | 0.155 | 3.651 | / | /
cuda-16-2-single-gpu-multi-pass | 3.363 | 0.211 | 0.158 | 2.994 | / | /
cuda-8-4-single-gpu-multi-pass | 3.221 | 0.214 | 0.158 | 2.849 | / | /
cuda-4-8-single-gpu-multi-pass | 3.729 | 0.211 | 0.154 | 3.364 | / | /


### lfr_graphs/n4000000_k60_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.131** | **0.211** | **0.156** | **1.764** | **0.1** | **1.664**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.279** | **0.199** | **0.153** | **1.927** | **0.099** | **1.828**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.124 | 0.158 | / | 0.093 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.12 | 0.182 | / | 0.101 | /
cuda-32-1-multi-gpu-multi-pass | 3.341 | 0.193 | 0.156 | 2.992 | 0.098 | 2.894
cuda-16-2-multi-gpu-multi-pass | 2.951 | 0.197 | 0.152 | 2.602 | 0.096 | 2.506
cuda-8-4-multi-gpu-multi-pass | 2.831 | 0.202 | 0.159 | 2.470 | 0.084 | 2.386
cuda-4-8-multi-gpu-multi-pass | 3.012 | 0.206 | 0.17 | 2.636 | 0.097 | 2.539
cuda-2-16-multi-gpu-multi-pass | 2.941 | 0.203 | 0.156 | 2.582 | 0.098 | 2.484
cuda-1-32-multi-gpu-multi-pass | 3.038 | 0.193 | 0.154 | 2.691 | 0.092 | 2.599
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.627** | **0.227** | **0.159** | **3.241** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.357** | **0.223** | **0.155** | **3.979** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.172 | 0.16 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.174 | 0.164 | / | / | /
cuda-32-1-single-gpu-multi-pass | 9.136 | 0.223 | 0.157 | 8.756 | / | /
cuda-16-2-single-gpu-multi-pass | 5.631 | 0.224 | 0.155 | 5.252 | / | /
cuda-8-4-single-gpu-multi-pass | 4.261 | 0.228 | 0.155 | 3.878 | / | /
cuda-4-8-single-gpu-multi-pass | 3.651 | 0.225 | 0.161 | 3.265 | / | /


### lfr_graphs/n4000000_k60_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.775** | **0.187** | **0.156** | **1.432** | **0.116** | **1.316**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.112** | **0.186** | **0.149** | **1.777** | **0.11** | **1.667**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.118 | 0.156 | / | 0.109 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.124 | 0.161 | / | 0.115 | /
cuda-32-1-multi-gpu-multi-pass | 2.67 | 0.182 | 0.155 | 2.333 | 0.111 | 2.222
cuda-16-2-multi-gpu-multi-pass | 2.669 | 0.189 | 0.155 | 2.325 | 0.118 | 2.207
cuda-8-4-multi-gpu-multi-pass | 2.624 | 0.193 | 0.154 | 2.277 | 0.111 | 2.166
cuda-4-8-multi-gpu-multi-pass | 2.66 | 0.183 | 0.153 | 2.324 | 0.116 | 2.208
cuda-2-16-multi-gpu-multi-pass | 3.127 | 0.196 | 0.153 | 2.778 | 0.114 | 2.664
cuda-1-32-multi-gpu-multi-pass | 3.517 | 0.19 | 0.155 | 3.172 | 0.117 | 3.055
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.204** | **0.215** | **0.156** | **2.833** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.933** | **0.214** | **0.157** | **3.562** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.174 | 0.18 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.175 | 0.196 | / | / | /
cuda-32-1-single-gpu-multi-pass | 4.102 | 0.217 | 0.157 | 3.728 | / | /
cuda-16-2-single-gpu-multi-pass | 4.17 | 0.212 | 0.16 | 3.798 | / | /
cuda-8-4-single-gpu-multi-pass | 3.185 | 0.21 | 0.156 | 2.819 | / | /
cuda-4-8-single-gpu-multi-pass | 3.881 | 0.213 | 0.154 | 3.514 | / | /


### lfr_graphs/n6000000_k40_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.943** | **0.202** | **0.175** | **1.566** | **0.108** | **1.458**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.096** | **0.209** | **0.178** | **1.709** | **0.115** | **1.594**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.125 | 0.194 | / | 0.123 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.127 | 0.168 | / | 0.123 | /
cuda-32-1-multi-gpu-multi-pass | 3.489 | 0.213 | 0.211 | 3.065 | 0.115 | 2.95
cuda-16-2-multi-gpu-multi-pass | 3.217 | 0.204 | 0.192 | 2.821 | 0.109 | 2.712
cuda-8-4-multi-gpu-multi-pass | 2.852 | 0.208 | 0.177 | 2.467 | 0.116 | 2.351
cuda-4-8-multi-gpu-multi-pass | 2.883 | 0.217 | 0.188 | 2.478 | 0.126 | 2.352
cuda-2-16-multi-gpu-multi-pass | 2.939 | 0.211 | 0.212 | 2.516 | 0.113 | 2.403
cuda-1-32-multi-gpu-multi-pass | 3.124 | 0.207 | 0.186 | 2.731 | 0.121 | 2.61
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.279** | **0.236** | **0.182** | **2.861** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.025** | **0.24** | **0.186** | **3.599** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.178 | 0.223 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.176 | 0.177 | / | / | /
cuda-32-1-single-gpu-multi-pass | 8.802 | 0.234 | 0.192 | 8.376 | / | /
cuda-16-2-single-gpu-multi-pass | 5.387 | 0.235 | 0.178 | 4.974 | / | /
cuda-8-4-single-gpu-multi-pass | 4.144 | 0.234 | 0.182 | 3.728 | / | /
cuda-4-8-single-gpu-multi-pass | 3.528 | 0.23 | 0.193 | 3.105 | / | /


### lfr_graphs/n6000000_k40_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.83** | **0.193** | **0.182** | **1.455** | **0.15** | **1.305**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.935** | **0.186** | **0.183** | **1.566** | **0.155** | **1.411**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.123 | 0.188 | / | 0.153 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.129 | 0.192 | / | 0.162 | /
cuda-32-1-multi-gpu-multi-pass | 2.683 | 0.19 | 0.185 | 2.308 | 0.152 | 2.156
cuda-16-2-multi-gpu-multi-pass | 2.614 | 0.185 | 0.188 | 2.241 | 0.172 | 2.069
cuda-8-4-multi-gpu-multi-pass | 2.643 | 0.194 | 0.18 | 2.269 | 0.15 | 2.119
cuda-4-8-multi-gpu-multi-pass | 2.725 | 0.191 | 0.187 | 2.347 | 0.156 | 2.191
cuda-2-16-multi-gpu-multi-pass | 2.884 | 0.192 | 0.178 | 2.514 | 0.149 | 2.365
cuda-1-32-multi-gpu-multi-pass | 3.646 | 0.196 | 0.184 | 3.266 | 0.145 | 3.121
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **2.959** | **0.215** | **0.182** | **2.562** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.629** | **0.221** | **0.185** | **3.223** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | 0.175 | 0.188 | / | / | /
cuda-baseline-single-gpu-multi-pass | / | 0.177 | 0.182 | / | / | /
cuda-32-1-single-gpu-multi-pass | 3.561 | 0.216 | 0.184 | 3.161 | / | /
cuda-16-2-single-gpu-multi-pass | 3.199 | 0.224 | 0.184 | 2.791 | / | /
cuda-8-4-single-gpu-multi-pass | 3.384 | 0.218 | 0.184 | 2.982 | / | /
cuda-4-8-single-gpu-multi-pass | 3.738 | 0.219 | 0.185 | 3.334 | / | /


### n12dot5_m80_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.152** | **1.556** | **1.974** | **13.622** | **1.666** | **11.956**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **17.559** | **1.606** | **2.0** | **13.953** | **1.61** | **12.343**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | 41.378 | 1.6 | 2.0 | 37.778 | 1.615 | 36.163
cuda-16-2-multi-gpu-multi-pass | 49.715 | 1.775 | 1.999 | 45.941 | 1.607 | 44.334
cuda-8-4-multi-gpu-multi-pass | 69.949 | 2.282 | 1.941 | 65.726 | 1.655 | 64.071
cuda-4-8-multi-gpu-multi-pass | 112.588 | 2.289 | 1.981 | 108.318 | 1.736 | 106.582
cuda-2-16-multi-gpu-multi-pass | 200.649 | 2.263 | 1.971 | 196.415 | 1.568 | 194.847
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **29.03** | **1.667** | **2.059** | **25.304** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **30.359** | **1.661** | **1.946** | **26.752** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 73.312 | 1.695 | 1.99 | 69.627 | / | /
cuda-16-2-single-gpu-multi-pass | 70.728 | 1.701 | 1.986 | 67.041 | / | /
cuda-8-4-single-gpu-multi-pass | 88.254 | 1.673 | 1.993 | 84.588 | / | /
cuda-4-8-single-gpu-multi-pass | 139.455 | 1.675 | 2.018 | 135.762 | / | /


### n12dot5_m80_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **16.814** | **1.553** | **2.008** | **13.253** | **1.539** | **11.714**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **17.408** | **1.547** | **2.023** | **13.838** | **1.633** | **12.205**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | 41.966 | 1.584 | 1.982 | 38.400 | 1.702 | 36.698
cuda-16-2-multi-gpu-multi-pass | 50.491 | 1.823 | 2.022 | 46.646 | 1.668 | 44.978
cuda-8-4-multi-gpu-multi-pass | 71.179 | 2.262 | 1.958 | 66.959 | 1.787 | 65.172
cuda-4-8-multi-gpu-multi-pass | 114.183 | 2.319 | 1.968 | 109.896 | 1.501 | 108.395
cuda-2-16-multi-gpu-multi-pass | 203.364 | 2.301 | 1.986 | 199.077 | 1.586 | 197.491
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **29.549** | **1.682** | **1.985** | **25.882** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **28.367** | **1.657** | **1.984** | **24.726** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 71.25 | 1.69 | 1.996 | 67.564 | / | /
cuda-16-2-single-gpu-multi-pass | 69.903 | 1.687 | 2.007 | 66.209 | / | /
cuda-8-4-single-gpu-multi-pass | 89.933 | 1.704 | 2.011 | 86.218 | / | /
cuda-4-8-single-gpu-multi-pass | 138.712 | 1.712 | 1.994 | 135.006 | / | /


### n16dot7_m60_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.478** | **1.572** | **2.349** | **13.557** | **1.86** | **11.697**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **17.651** | **1.625** | **2.33** | **13.696** | **1.789** | **11.907**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | 43.867 | 1.603 | 2.362 | 39.902 | 1.937 | 37.965
cuda-16-2-multi-gpu-multi-pass | 54.723 | 2.151 | 2.327 | 50.245 | 1.879 | 48.366
cuda-8-4-multi-gpu-multi-pass | 77.082 | 2.277 | 2.364 | 72.441 | 1.927 | 70.514
cuda-4-8-multi-gpu-multi-pass | 123.495 | 2.311 | 2.352 | 118.832 | 1.93 | 116.902
cuda-2-16-multi-gpu-multi-pass | 218.483 | 2.355 | 2.336 | 213.792 | 1.848 | 211.944
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **27.925** | **1.71** | **2.361** | **23.854** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **28.098** | **1.659** | **2.334** | **24.105** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 68.173 | 1.749 | 2.376 | 64.048 | / | /
cuda-16-2-single-gpu-multi-pass | 70.368 | 1.728 | 2.369 | 66.271 | / | /
cuda-8-4-single-gpu-multi-pass | 91.782 | 1.702 | 2.397 | 87.683 | / | /
cuda-4-8-single-gpu-multi-pass | 141.47 | 1.699 | 2.346 | 137.425 | / | /


### n16dot7_m60_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.198** | **1.596** | **2.329** | **13.273** | **1.748** | **11.525**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **17.513** | **1.602** | **2.329** | **13.582** | **1.931** | **11.651**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | 43.585 | 1.661 | 2.303 | 39.621 | 1.826 | 37.795
cuda-16-2-multi-gpu-multi-pass | 54.536 | 2.094 | 2.59 | 49.852 | 1.896 | 47.956
cuda-8-4-multi-gpu-multi-pass | 76.482 | 2.238 | 2.312 | 71.932 | 1.879 | 70.053
cuda-4-8-multi-gpu-multi-pass | 122.942 | 2.21 | 2.316 | 118.416 | 1.937 | 116.479
cuda-2-16-multi-gpu-multi-pass | 217.985 | 2.307 | 2.309 | 213.369 | 1.917 | 211.452
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **28.26** | **1.754** | **2.323** | **24.183** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **27.46** | **1.602** | **2.333** | **23.525** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 68.227 | 1.802 | 2.339 | 64.086 | / | /
cuda-16-2-single-gpu-multi-pass | 70.639 | 1.756 | 2.331 | 66.552 | / | /
cuda-8-4-single-gpu-multi-pass | 92.676 | 1.735 | 2.368 | 88.573 | / | /
cuda-4-8-single-gpu-multi-pass | 145.139 | 1.708 | 2.324 | 141.107 | / | /


### n25_m40_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.731** | **1.57** | **2.742** | **13.419** | **2.058** | **11.361**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **18.103** | **1.635** | **2.712** | **13.756** | **2.089** | **11.667**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | 41.985 | 1.665 | 2.722 | 37.598 | 2.27 | 35.328
cuda-16-2-multi-gpu-multi-pass | 52.24 | 1.976 | 2.721 | 47.543 | 2.072 | 45.471
cuda-8-4-multi-gpu-multi-pass | 73.717 | 2.269 | 2.692 | 68.756 | 2.239 | 66.517
cuda-4-8-multi-gpu-multi-pass | 118.263 | 2.277 | 2.697 | 113.289 | 2.157 | 111.132
cuda-2-16-multi-gpu-multi-pass | 207.204 | 2.279 | 2.698 | 202.227 | 2.12 | 200.107
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **25.665** | **1.739** | **2.71** | **21.216** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **37.196** | **1.632** | **2.699** | **32.865** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 61.884 | 1.807 | 2.734 | 57.343 | / | /
cuda-16-2-single-gpu-multi-pass | 66.146 | 1.754 | 2.717 | 61.675 | / | /
cuda-8-4-single-gpu-multi-pass | 88.82 | 1.781 | 2.716 | 84.323 | / | /
cuda-4-8-single-gpu-multi-pass | 136.15 | 1.723 | 2.753 | 131.674 | / | /


### n25_m40_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.38** | **1.486** | **2.706** | **13.188** | **2.085** | **11.103**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **18.591** | **1.659** | **2.708** | **14.224** | **2.028** | **12.196**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | 41.27 | 1.622 | 2.742 | 36.906 | 2.188 | 34.718
cuda-16-2-multi-gpu-multi-pass | 52.208 | 2.078 | 2.703 | 47.427 | 2.221 | 45.206
cuda-8-4-multi-gpu-multi-pass | 73.123 | 2.357 | 2.701 | 68.065 | 2.238 | 65.827
cuda-4-8-multi-gpu-multi-pass | 117.709 | 2.34 | 2.659 | 112.710 | 2.179 | 110.531
cuda-2-16-multi-gpu-multi-pass | 206.888 | 2.249 | 2.64 | 201.999 | 2.006 | 199.993
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **25.906** | **1.744** | **2.716** | **21.446** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **34.768** | **1.636** | **2.741** | **30.391** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 61.779 | 1.769 | 2.688 | 57.322 | / | /
cuda-16-2-single-gpu-multi-pass | 65.709 | 1.74 | 2.677 | 61.292 | / | /
cuda-8-4-single-gpu-multi-pass | 87.897 | 1.731 | 2.705 | 83.461 | / | /
cuda-4-8-single-gpu-multi-pass | 135.926 | 1.724 | 2.703 | 131.499 | / | /


### n50_m20_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **16.917** | **1.488** | **3.166** | **12.263** | **2.448** | **9.815**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **90.745** | **1.774** | **3.187** | **85.784** | **2.529** | **83.255**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 1.657 | 3.261 | / | 2.526 | /
cuda-baseline-multi-gpu-multi-pass | / | 1.622 | 3.252 | / | 2.514 | /
cuda-32-1-multi-gpu-multi-pass | 42.236 | 1.694 | 3.196 | 37.346 | 2.624 | 34.722
cuda-16-2-multi-gpu-multi-pass | 54.058 | 2.117 | 3.157 | 48.784 | 2.57 | 46.214
cuda-8-4-multi-gpu-multi-pass | 77.642 | 2.315 | 3.164 | 72.163 | 2.473 | 69.69
cuda-4-8-multi-gpu-multi-pass | 125.287 | 2.29 | 3.219 | 119.778 | 2.57 | 117.208
cuda-2-16-multi-gpu-multi-pass | 218.571 | 2.174 | 3.217 | 213.180 | 2.626 | 210.554
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **24.485** | **1.818** | **3.204** | **19.463** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 55.767 | 1.789 | 3.206 | 50.772 | / | /
cuda-16-2-single-gpu-multi-pass | 66.054 | 1.801 | 3.313 | 60.940 | / | /
cuda-8-4-single-gpu-multi-pass | 90.208 | 1.787 | 3.191 | 85.230 | / | /
cuda-4-8-single-gpu-multi-pass | 137.665 | 1.804 | 3.151 | 132.710 | / | /


### n50_m20_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.153** | **1.427** | **3.192** | **12.534** | **2.343** | **10.191**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **93.903** | **1.775** | **3.169** | **88.959** | **2.554** | **86.405**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 1.609 | 3.417 | / | 2.606 | /
cuda-baseline-multi-gpu-multi-pass | / | 1.61 | 3.406 | / | 2.691 | /
cuda-32-1-multi-gpu-multi-pass | 42.526 | 1.685 | 3.139 | 37.702 | 2.531 | 35.171
cuda-16-2-multi-gpu-multi-pass | 54.319 | 1.965 | 3.176 | 49.178 | 2.52 | 46.658
cuda-8-4-multi-gpu-multi-pass | 77.036 | 2.212 | 2.818 | 72.006 | 2.093 | 69.913
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | /
cuda-2-16-multi-gpu-multi-pass | 219.518 | 2.263 | 3.121 | 214.134 | 2.556 | 211.578
cuda-1-32-multi-gpu-multi-pass | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **24.568** | **1.8** | **3.141** | **19.627** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 58.033 | 1.815 | 3.2 | 53.018 | / | /
cuda-16-2-single-gpu-multi-pass | 66.77 | 1.789 | 3.204 | 61.777 | / | /
cuda-8-4-single-gpu-multi-pass | 90.85 | 1.745 | 3.193 | 85.912 | / | /
cuda-4-8-single-gpu-multi-pass | 139.258 | 1.794 | 3.222 | 134.242 | / | /