# Core Checking (eps = 0.2, mu = 5)


Unit: seconds


### small_snap_cit_patents

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **1.945** | **0.017** | **0.02** | **1.908** | **1.650** | **0.266** | **1.642**
**cuda-bitmap-kernel-multi-gpu** | **1.969** | **0.017** | **0.014** | **1.938** | **1.662** | **0.293** | **1.645**
cuda-baseline-hybrid-multi-gpu | 2.009 | 0.018 | 0.012 | 1.979 | 1.656 | 0.344 | 1.635
cuda-baseline-multi-gpu | 2.15 | 0.016 | 0.022 | 2.112 | 1.636 | 0.507 | 1.605
cuda-32-1-multi-gpu | 1.91 | 0.013 | 0.014 | 1.883 | 1.637 | 0.267 | 1.616
cuda-16-2-multi-gpu | 1.948 | 0.015 | 0.021 | 1.912 | 1.648 | 0.289 | 1.623
cuda-8-4-multi-gpu | 1.95 | 0.017 | 0.015 | 1.918 | 1.684 | 0.261 | 1.657
cuda-4-8-multi-gpu | 2.047 | 0.016 | 0.021 | 2.010 | 1.672 | 0.366 | 1.644
cuda-2-16-multi-gpu | 2.338 | 0.016 | 0.02 | 2.302 | 1.679 | 0.651 | 1.651
cuda-1-32-multi-gpu | 1.937 | 0.019 | 0.013 | 1.905 | 1.668 | 0.262 | 1.643


### small_snap_cit_patents/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **2.196** | **0.016** | **0.021** | **2.159** | **1.924** | **0.241** | **1.918**
**cuda-bitmap-kernel-multi-gpu** | **1.966** | **0.015** | **0.016** | **1.935** | **1.707** | **0.237** | **1.698**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### small_snap_dblp

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **1.711** | **0.018** | **0.017** | **1.676** | **1.623** | **0.052** | **1.624**
**cuda-bitmap-kernel-multi-gpu** | **1.739** | **0.014** | **0.018** | **1.707** | **1.653** | **0.048** | **1.659**
cuda-baseline-hybrid-multi-gpu | 1.785 | 0.016 | 0.021 | 1.748 | 1.720 | 0.06 | 1.688
cuda-baseline-multi-gpu | 1.745 | 0.015 | 0.02 | 1.710 | 1.686 | 0.052 | 1.658
cuda-32-1-multi-gpu | 1.738 | 0.017 | 0.022 | 1.699 | 1.693 | 0.041 | 1.658
cuda-16-2-multi-gpu | 1.713 | 0.014 | 0.018 | 1.681 | 1.661 | 0.047 | 1.634
cuda-8-4-multi-gpu | 1.691 | 0.013 | 0.014 | 1.664 | 1.639 | 0.044 | 1.62
cuda-4-8-multi-gpu | 1.743 | 0.02 | 0.013 | 1.710 | 1.681 | 0.055 | 1.655
cuda-2-16-multi-gpu | 1.724 | 0.015 | 0.019 | 1.690 | 1.664 | 0.054 | 1.636
cuda-1-32-multi-gpu | 1.761 | 0.015 | 0.019 | 1.727 | 1.692 | 0.053 | 1.674


### small_snap_dblp/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **1.772** | **0.015** | **0.016** | **1.741** | **1.682** | **0.057** | **1.684**
**cuda-bitmap-kernel-multi-gpu** | **1.728** | **0.015** | **0.012** | **1.701** | **1.620** | **0.091** | **1.61**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### small_snap_web_berkstan

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **1.734** | **0.014** | **0.015** | **1.705** | **1.639** | **0.081** | **1.624**
**cuda-bitmap-kernel-multi-gpu** | **1.802** | **0.013** | **0.017** | **1.772** | **1.683** | **0.133** | **1.639**
cuda-baseline-hybrid-multi-gpu | 1.808 | 0.014 | 0.018 | 1.776 | 1.668 | 0.131 | 1.645
cuda-baseline-multi-gpu | 1.734 | 0.015 | 0.022 | 1.697 | 1.668 | 0.059 | 1.638
cuda-32-1-multi-gpu | 1.718 | 0.014 | 0.015 | 1.689 | 1.627 | 0.086 | 1.603
cuda-16-2-multi-gpu | 1.783 | 0.015 | 0.018 | 1.750 | 1.688 | 0.088 | 1.662
cuda-8-4-multi-gpu | 1.715 | 0.014 | 0.019 | 1.682 | 1.623 | 0.086 | 1.596
cuda-4-8-multi-gpu | 1.696 | 0.014 | 0.016 | 1.666 | 1.603 | 0.084 | 1.582
cuda-2-16-multi-gpu | 1.738 | 0.016 | 0.02 | 1.702 | 1.639 | 0.092 | 1.61
cuda-1-32-multi-gpu | 1.778 | 0.016 | 0.014 | 1.748 | 1.674 | 0.095 | 1.653


### small_snap_web_berkstan/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **1.773** | **0.019** | **0.017** | **1.737** | **1.699** | **0.062** | **1.675**
**cuda-bitmap-kernel-multi-gpu** | **1.783** | **0.017** | **0.008** | **1.758** | **1.615** | **0.122** | **1.636**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### small_snap_web_notredame

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **1.825** | **0.011** | **0.016** | **1.798** | **1.763** | **0.033** | **1.765**
**cuda-bitmap-kernel-multi-gpu** | **1.79** | **0.013** | **0.017** | **1.760** | **1.719** | **0.035** | **1.725**
cuda-baseline-hybrid-multi-gpu | 1.76 | 0.012 | 0.02 | 1.728 | 1.693 | 0.031 | 1.697
cuda-baseline-multi-gpu | 1.695 | 0.011 | 0.018 | 1.666 | 1.609 | 0.042 | 1.624
cuda-32-1-multi-gpu | 1.722 | 0.012 | 0.015 | 1.695 | 1.618 | 0.034 | 1.661
cuda-16-2-multi-gpu | 1.78 | 0.013 | 0.015 | 1.752 | 1.644 | 0.037 | 1.715
cuda-8-4-multi-gpu | 1.722 | 0.009 | 0.012 | 1.701 | 1.530 | 0.04 | 1.661
cuda-4-8-multi-gpu | 1.711 | 0.008 | 0.018 | 1.685 | 1.432 | 0.034 | 1.651
cuda-2-16-multi-gpu | 2.161 | 0.011 | 0.015 | 2.135 | 1.665 | 0.071 | 2.064
cuda-1-32-multi-gpu | 2.436 | 0.01 | 0.018 | 2.408 | 1.603 | 0.046 | 2.362


### small_snap_web_notredame/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **1.745** | **0.016** | **0.013** | **1.716** | **1.677** | **0.033** | **1.683**
**cuda-bitmap-kernel-multi-gpu** | **1.756** | **0.012** | **0.017** | **1.727** | **1.683** | **0.031** | **1.696**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### small_snap_web_stanford

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **1.715** | **0.01** | **0.012** | **1.693** | **1.662** | **0.028** | **1.665**
**cuda-bitmap-kernel-multi-gpu** | **1.749** | **0.011** | **0.015** | **1.723** | **1.688** | **0.044** | **1.679**
cuda-baseline-hybrid-multi-gpu | 1.762 | 0.014 | 0.016 | 1.732 | 1.711 | 0.044 | 1.688
cuda-baseline-multi-gpu | 1.703 | 0.009 | 0.009 | 1.685 | 1.661 | 0.034 | 1.651
cuda-32-1-multi-gpu | 1.712 | 0.011 | 0.013 | 1.688 | 1.672 | 0.032 | 1.656
cuda-16-2-multi-gpu | 1.701 | 0.01 | 0.012 | 1.679 | 1.664 | 0.029 | 1.65
cuda-8-4-multi-gpu | 1.732 | 0.014 | 0.012 | 1.706 | 1.680 | 0.046 | 1.66
cuda-4-8-multi-gpu | 1.695 | 0.014 | 0.011 | 1.670 | 1.648 | 0.038 | 1.632
cuda-2-16-multi-gpu | 1.755 | 0.015 | 0.013 | 1.727 | 1.708 | 0.039 | 1.688
cuda-1-32-multi-gpu | 1.72 | 0.01 | 0.017 | 1.693 | 1.681 | 0.029 | 1.664


### small_snap_web_stanford/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **1.785** | **0.012** | **0.015** | **1.758** | **1.704** | **0.051** | **1.707**
**cuda-bitmap-kernel-multi-gpu** | **1.672** | **0.012** | **0.011** | **1.649** | **1.611** | **0.032** | **1.617**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### snap_pokec

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **1.979** | **0.085** | **0.031** | **1.863** | **1.741** | **0.148** | **1.715**
**cuda-bitmap-kernel-multi-gpu** | **1.971** | **0.086** | **0.033** | **1.852** | **1.720** | **0.144** | **1.708**
cuda-baseline-hybrid-multi-gpu | 2.064 | 0.091 | 0.032 | 1.941 | 1.597 | 0.149 | 1.792
cuda-baseline-multi-gpu | 2.047 | 0.085 | 0.035 | 1.927 | 1.338 | 0.164 | 1.763
cuda-32-1-multi-gpu | 1.979 | 0.085 | 0.032 | 1.862 | 1.026 | 0.158 | 1.704
cuda-16-2-multi-gpu | 2.039 | 0.088 | 0.036 | 1.915 | 0.726 | 0.242 | 1.673
cuda-8-4-multi-gpu | 1.927 | 0.078 | 0.03 | 1.819 | 0.472 | 0.158 | 1.661
cuda-4-8-multi-gpu | 3.053 | 0.086 | 0.033 | 2.934 | 1.487 | 0.149 | 2.785
cuda-2-16-multi-gpu | 5.341 | 0.079 | 0.03 | 5.232 | 3.753 | 0.177 | 5.055
cuda-1-32-multi-gpu | 9.671 | 0.085 | 0.037 | 9.549 | 8.204 | 0.167 | 9.382


### snap_pokec/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **2.092** | **0.1** | **0.034** | **1.958** | **1.822** | **0.215** | **1.743**
**cuda-bitmap-kernel-multi-gpu** | **2.036** | **0.092** | **0.028** | **1.916** | **1.784** | **0.204** | **1.712**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### snap_livejournal

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **2.328** | **0.145** | **0.05** | **2.133** | **1.812** | **0.433** | **1.7**
**cuda-bitmap-kernel-multi-gpu** | **2.498** | **0.147** | **0.065** | **2.286** | **1.885** | **0.518** | **1.768**
cuda-baseline-hybrid-multi-gpu | 2.959 | 0.15 | 0.054 | 2.755 | 1.861 | 0.41 | 2.345
cuda-baseline-multi-gpu | 3.054 | 0.155 | 0.057 | 2.842 | 1.267 | 0.407 | 2.435
cuda-32-1-multi-gpu | 3.586 | 0.156 | 0.064 | 3.366 | 1.539 | 0.711 | 2.655
cuda-16-2-multi-gpu | 3.932 | 0.15 | 0.046 | 3.736 | 1.739 | 0.742 | 2.994
cuda-8-4-multi-gpu | 5.321 | 0.148 | 0.048 | 5.125 | 3.253 | 0.494 | 4.631
cuda-4-8-multi-gpu | 8.424 | 0.151 | 0.047 | 8.226 | 6.504 | 0.423 | 7.803
cuda-2-16-multi-gpu | 15.103 | 0.152 | 0.05 | 14.901 | 12.833 | 0.674 | 14.227
cuda-1-32-multi-gpu | 26.891 | 0.15 | 0.046 | 26.695 | 25.032 | 0.35 | 26.345


### snap_livejournal/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **2.636** | **0.204** | **0.057** | **2.375** | **1.988** | **0.542** | **1.833**
**cuda-bitmap-kernel-multi-gpu** | **2.575** | **0.203** | **0.061** | **2.311** | **2.019** | **0.452** | **1.859**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### snap_orkut

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.35** | **0.73** | **0.149** | **2.471** | **2.726** | **0.411** | **2.06**
**cuda-bitmap-kernel-multi-gpu** | **3.388** | **0.716** | **0.124** | **2.548** | **2.679** | **0.313** | **2.235**
cuda-baseline-hybrid-multi-gpu | 8.786 | 0.722 | 0.206 | 7.858 | 6.876 | 0.402 | 7.456
cuda-baseline-multi-gpu | 9.38 | 0.741 | 0.143 | 8.496 | 7.443 | 0.324 | 8.172
cuda-32-1-multi-gpu | 13.141 | 0.727 | 0.121 | 12.293 | 11.024 | 0.305 | 11.988
cuda-16-2-multi-gpu | 16.509 | 0.72 | 0.119 | 15.670 | 14.572 | 0.329 | 15.341
cuda-8-4-multi-gpu | 24.391 | 0.722 | 0.132 | 23.537 | 22.735 | 0.295 | 23.242
cuda-4-8-multi-gpu | 41.33 | 0.724 | 0.12 | 40.486 | 39.515 | 0.351 | 40.135
cuda-2-16-multi-gpu | 74.599 | 0.762 | 0.117 | 73.720 | 72.631 | 0.326 | 73.394
cuda-1-32-multi-gpu | 135.98 | 0.784 | 0.121 | 135.075 | 133.968 | 0.37 | 134.705


### snap_orkut/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.578** | **0.834** | **0.131** | **2.613** | **2.916** | **0.352** | **2.261**
**cuda-bitmap-kernel-multi-gpu** | **3.626** | **0.84** | **0.154** | **2.632** | **3.021** | **0.301** | **2.331**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### snap_friendster

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
**cuda-bitmap-kernel-multi-gpu** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### snap_friendster/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
**cuda-bitmap-kernel-multi-gpu** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### webgraph_it

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **57.328** | **1.052** | **0.371** | **55.905** | **51.364** | **6.338** | **49.567**
**cuda-bitmap-kernel-multi-gpu** | **121.21** | **0.979** | **0.356** | **119.875** | **115.439** | **3.751** | **116.124**
cuda-baseline-hybrid-multi-gpu | 29.057 | 1.036 | 0.365 | 27.656 | 23.128 | 4.16 | 23.496
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | 474.222 | 1.232 | 0.36 | 472.630 | 468.647 | 4.038 | 468.592
cuda-8-4-multi-gpu | 245.36 | 1.084 | 0.366 | 243.910 | 239.987 | 3.727 | 240.183
cuda-4-8-multi-gpu | 135.591 | 1.05 | 0.377 | 134.164 | 127.568 | 6.088 | 128.076
cuda-2-16-multi-gpu | 89.32 | 1.049 | 0.407 | 87.864 | 80.874 | 6.447 | 81.417
cuda-1-32-multi-gpu | 76.454 | 1.055 | 0.365 | 75.034 | 68.189 | 6.24 | 68.794


### webgraph_it/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **14.098** | **2.291** | **0.828** | **10.979** | **6.618** | **6.023** | **4.956**
**cuda-bitmap-kernel-multi-gpu** | **191.494** | **2.248** | **0.965** | **188.281** | **184.541** | **4.66** | **183.621**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### webgraph_uk

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.971** | **0.267** | **0.128** | **3.576** | **1.870** | **1.478** | **2.098**
**cuda-bitmap-kernel-multi-gpu** | **4.16** | **0.256** | **0.117** | **3.787** | **1.954** | **1.47** | **2.317**
cuda-baseline-hybrid-multi-gpu | 5.354 | 0.25 | 0.121 | 4.983 | 3.031 | 1.745 | 3.238
cuda-baseline-multi-gpu | 175.037 | 0.275 | 0.119 | 174.643 | 173.341 | 1.523 | 173.12
cuda-32-1-multi-gpu | 8.108 | 0.247 | 0.121 | 7.740 | 6.081 | 1.515 | 6.225
cuda-16-2-multi-gpu | 5.998 | 0.247 | 0.117 | 5.634 | 4.026 | 1.449 | 4.185
cuda-8-4-multi-gpu | 5.397 | 0.245 | 0.138 | 5.014 | 2.828 | 2.02 | 2.994
cuda-4-8-multi-gpu | 4.63 | 0.25 | 0.119 | 4.261 | 2.343 | 1.63 | 2.631
cuda-2-16-multi-gpu | 4.544 | 0.25 | 0.147 | 4.147 | 2.065 | 1.693 | 2.454
cuda-1-32-multi-gpu | 4.63 | 0.256 | 0.129 | 4.245 | 2.131 | 1.463 | 2.782


### webgraph_uk/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **5.129** | **0.523** | **0.224** | **4.382** | **2.819** | **2.01** | **2.372**
**cuda-bitmap-kernel-multi-gpu** | **4.986** | **0.52** | **0.248** | **4.218** | **2.704** | **1.713** | **2.505**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### webgraph_eu

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **5.779** | **0.662** | **0.224** | **4.893** | **4.247** | **0.858** | **4.035**
**cuda-bitmap-kernel-multi-gpu** | **7.616** | **0.665** | **0.232** | **6.719** | **5.692** | **1.055** | **5.664**
cuda-baseline-hybrid-multi-gpu | 98.679 | 0.754 | 0.234 | 97.691 | 97.593 | 1.083 | 96.608
cuda-baseline-multi-gpu | 209.048 | 0.726 | 0.204 | 208.118 | 207.331 | 1.714 | 206.404
cuda-32-1-multi-gpu | 333.998 | 0.744 | 0.221 | 333.033 | 331.210 | 1.25 | 331.783
cuda-16-2-multi-gpu | 446.355 | 0.741 | 0.2 | 445.414 | 445.002 | 1.222 | 444.192
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### webgraph_eu/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **5.735** | **0.839** | **0.232** | **4.664** | **4.184** | **0.774** | **3.89**
**cuda-bitmap-kernel-multi-gpu** | **7.441** | **0.837** | **0.249** | **6.355** | **4.916** | **1.051** | **5.304**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### webgraph_twitter

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **28.323** | **7.255** | **1.347** | **19.721** | **22.404** | **3.921** | **15.8**
**cuda-bitmap-kernel-multi-gpu** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### webgraph_twitter/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **21.394** | **7.127** | **1.228** | **13.039** | **14.900** | **4.639** | **8.4**
**cuda-bitmap-kernel-multi-gpu** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### webgraph_webbase

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **27.251** | **0.847** | **0.414** | **25.990** | **13.437** | **11.551** | **14.439**
**cuda-bitmap-kernel-multi-gpu** | **/** | **/** | **/** | **/** | **/** | **9.024** | **/**
cuda-baseline-hybrid-multi-gpu | 22.93 | 0.843 | 0.408 | 21.679 | 9.791 | 11.659 | 10.02
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | 68.519 | 0.856 | 0.405 | 67.258 | 54.434 | 12.007 | 55.251
cuda-16-2-multi-gpu | 50.015 | 0.831 | 0.409 | 48.775 | 29.291 | 18.64 | 30.135
cuda-8-4-multi-gpu | 29.892 | 0.838 | 0.412 | 28.642 | 16.804 | 11.2 | 17.442
cuda-4-8-multi-gpu | 20.647 | 0.803 | 0.397 | 19.447 | 10.169 | 8.612 | 10.835
cuda-2-16-multi-gpu | 20.658 | 0.832 | 0.411 | 19.415 | 7.818 | 10.75 | 8.665
cuda-1-32-multi-gpu | 18.991 | 0.792 | 0.396 | 17.803 | 7.332 | 9.688 | 8.115


### webgraph_webbase/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **20.031** | **1.97** | **0.94** | **17.121** | **11.816** | **7.341** | **9.78**
**cuda-bitmap-kernel-multi-gpu** | **/** | **/** | **/** | **/** | **/** | **10.31** | **/**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### lfr_dataset

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.873** | **1.023** | **0.123** | **2.727** | **3.341** | **0.35** | **2.377**
**cuda-bitmap-kernel-multi-gpu** | **3.895** | **1.003** | **0.125** | **2.767** | **3.379** | **0.274** | **2.493**
cuda-baseline-hybrid-multi-gpu | 6.362 | 1.08 | 0.138 | 5.144 | 5.875 | 0.377 | 4.767
cuda-baseline-multi-gpu | 6.585 | 1.018 | 0.125 | 5.442 | 6.143 | 0.344 | 5.098
cuda-32-1-multi-gpu | 4.683 | 1.07 | 0.122 | 3.491 | 3.985 | 0.421 | 3.07
cuda-16-2-multi-gpu | 4.009 | 1.056 | 0.132 | 2.821 | 3.489 | 0.321 | 2.5
cuda-8-4-multi-gpu | 3.943 | 1.079 | 0.135 | 2.729 | 3.308 | 0.396 | 2.333
cuda-4-8-multi-gpu | 3.803 | 1.105 | 0.137 | 2.561 | 3.259 | 0.34 | 2.221
cuda-2-16-multi-gpu | 3.765 | 1.054 | 0.134 | 2.577 | 3.285 | 0.292 | 2.285
cuda-1-32-multi-gpu | 4.134 | 1.041 | 0.135 | 2.958 | 3.566 | 0.366 | 2.592


### lfr_dataset/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.513** | **0.843** | **0.125** | **2.545** | **2.925** | **0.342** | **2.203**
**cuda-bitmap-kernel-multi-gpu** | **3.514** | **0.841** | **0.122** | **2.551** | **3.031** | **0.312** | **2.239**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### lfr_graphs/n2400000_k100_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.967** | **1.047** | **0.121** | **2.799** | **3.509** | **0.393** | **2.406**
**cuda-bitmap-kernel-multi-gpu** | **3.748** | **1.064** | **0.122** | **2.562** | **3.338** | **0.22** | **2.342**
cuda-baseline-hybrid-multi-gpu | 6.341 | 1.065 | 0.12 | 5.156 | 5.901 | 0.24 | 4.916
cuda-baseline-multi-gpu | 6.621 | 1.019 | 0.122 | 5.480 | 6.118 | 0.353 | 5.127
cuda-32-1-multi-gpu | 4.339 | 1.042 | 0.121 | 3.176 | 3.844 | 0.234 | 2.942
cuda-16-2-multi-gpu | 3.971 | 1.046 | 0.133 | 2.792 | 3.430 | 0.239 | 2.553
cuda-8-4-multi-gpu | 3.805 | 1.025 | 0.12 | 2.660 | 3.377 | 0.235 | 2.425
cuda-4-8-multi-gpu | 3.693 | 1.025 | 0.12 | 2.548 | 3.250 | 0.271 | 2.277
cuda-2-16-multi-gpu | 3.761 | 1.067 | 0.12 | 2.574 | 3.305 | 0.256 | 2.318
cuda-1-32-multi-gpu | 4.032 | 1.079 | 0.122 | 2.831 | 3.663 | 0.232 | 2.599


### lfr_graphs/n2400000_k100_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.411** | **0.838** | **0.123** | **2.450** | **2.908** | **0.304** | **2.146**
**cuda-bitmap-kernel-multi-gpu** | **3.622** | **0.858** | **0.138** | **2.626** | **3.182** | **0.287** | **2.339**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### lfr_graphs/n3000000_k80_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.898** | **1.009** | **0.123** | **2.766** | **3.372** | **0.329** | **2.437**
**cuda-bitmap-kernel-multi-gpu** | **3.958** | **1.017** | **0.123** | **2.818** | **3.401** | **0.32** | **2.498**
cuda-baseline-hybrid-multi-gpu | 6.92 | 1.019 | 0.123 | 5.778 | 6.520 | 0.371 | 5.407
cuda-baseline-multi-gpu | 6.365 | 1.059 | 0.121 | 5.185 | 5.901 | 0.322 | 4.863
cuda-32-1-multi-gpu | 4.371 | 1.038 | 0.123 | 3.210 | 3.763 | 0.303 | 2.907
cuda-16-2-multi-gpu | 3.911 | 1.014 | 0.136 | 2.761 | 3.326 | 0.296 | 2.465
cuda-8-4-multi-gpu | 3.915 | 1.005 | 0.123 | 2.787 | 3.176 | 0.518 | 2.269
cuda-4-8-multi-gpu | 3.918 | 1.032 | 0.177 | 2.709 | 3.331 | 0.378 | 2.331
cuda-2-16-multi-gpu | 3.987 | 1.103 | 0.13 | 2.754 | 3.092 | 0.501 | 2.253
cuda-1-32-multi-gpu | 3.942 | 1.026 | 0.153 | 2.763 | 3.442 | 0.313 | 2.45


### lfr_graphs/n3000000_k80_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.46** | **0.852** | **0.125** | **2.483** | **2.808** | **0.321** | **2.162**
**cuda-bitmap-kernel-multi-gpu** | **3.629** | **0.868** | **0.122** | **2.639** | **3.080** | **0.333** | **2.306**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### lfr_graphs/n4000000_k60_C0dot1_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.985** | **1.047** | **0.131** | **2.807** | **3.264** | **0.473** | **2.334**
**cuda-bitmap-kernel-multi-gpu** | **4.18** | **1.019** | **0.161** | **3.000** | **3.409** | **0.523** | **2.477**
cuda-baseline-hybrid-multi-gpu | 6.428 | 1.034 | 0.13 | 5.264 | 5.845 | 0.441 | 4.823
cuda-baseline-multi-gpu | 6.481 | 1.031 | 0.13 | 5.320 | 5.931 | 0.427 | 4.893
cuda-32-1-multi-gpu | 4.426 | 1.02 | 0.131 | 3.275 | 3.828 | 0.356 | 2.919
cuda-16-2-multi-gpu | 4.078 | 1.02 | 0.127 | 2.931 | 3.435 | 0.4 | 2.531
cuda-8-4-multi-gpu | 3.928 | 1.026 | 0.132 | 2.770 | 3.228 | 0.479 | 2.291
cuda-4-8-multi-gpu | 3.828 | 1.055 | 0.128 | 2.645 | 3.265 | 0.394 | 2.251
cuda-2-16-multi-gpu | 3.972 | 1.058 | 0.13 | 2.784 | 3.361 | 0.376 | 2.408
cuda-1-32-multi-gpu | 4.024 | 1.02 | 0.129 | 2.875 | 3.364 | 0.53 | 2.345


### lfr_graphs/n4000000_k60_C0dot1_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.597** | **0.846** | **0.132** | **2.619** | **2.813** | **0.5** | **2.119**
**cuda-bitmap-kernel-multi-gpu** | **3.941** | **0.878** | **0.134** | **2.929** | **3.121** | **0.587** | **2.342**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### lfr_graphs/n4000000_k60_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.932** | **1.077** | **0.131** | **2.724** | **3.387** | **0.386** | **2.338**
**cuda-bitmap-kernel-multi-gpu** | **3.998** | **1.041** | **0.181** | **2.776** | **3.283** | **0.467** | **2.309**
cuda-baseline-hybrid-multi-gpu | 6.429 | 1.061 | 0.132 | 5.236 | 5.672 | 0.592 | 4.644
cuda-baseline-multi-gpu | 6.506 | 1.027 | 0.128 | 5.351 | 5.838 | 0.491 | 4.86
cuda-32-1-multi-gpu | 4.542 | 1.037 | 0.162 | 3.343 | 3.876 | 0.406 | 2.937
cuda-16-2-multi-gpu | 4.202 | 1.039 | 0.185 | 2.978 | 3.484 | 0.435 | 2.543
cuda-8-4-multi-gpu | 4.335 | 1.029 | 0.127 | 3.179 | 3.341 | 0.697 | 2.482
cuda-4-8-multi-gpu | 3.908 | 1.024 | 0.131 | 2.753 | 3.189 | 0.459 | 2.294
cuda-2-16-multi-gpu | 3.956 | 1.012 | 0.127 | 2.817 | 3.347 | 0.422 | 2.395
cuda-1-32-multi-gpu | 4.513 | 1.053 | 0.155 | 3.305 | 3.793 | 0.578 | 2.727


### lfr_graphs/n4000000_k60_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.689** | **0.845** | **0.134** | **2.710** | **2.841** | **0.58** | **2.13**
**cuda-bitmap-kernel-multi-gpu** | **3.627** | **0.853** | **0.133** | **2.641** | **2.999** | **0.403** | **2.238**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### lfr_graphs/n6000000_k40_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **4.346** | **1.061** | **0.163** | **3.122** | **3.383** | **0.715** | **2.407**
**cuda-bitmap-kernel-multi-gpu** | **4.165** | **1.044** | **0.162** | **2.959** | **3.411** | **0.711** | **2.248**
cuda-baseline-hybrid-multi-gpu | 6.634 | 1.076 | 0.184 | 5.374 | 5.815 | 0.695 | 4.679
cuda-baseline-multi-gpu | 6.519 | 1.032 | 0.155 | 5.332 | 5.784 | 0.557 | 4.775
cuda-32-1-multi-gpu | 4.654 | 1.037 | 0.155 | 3.462 | 3.831 | 0.57 | 2.892
cuda-16-2-multi-gpu | 4.514 | 1.063 | 0.162 | 3.289 | 3.608 | 0.682 | 2.607
cuda-8-4-multi-gpu | 4.248 | 1.045 | 0.158 | 3.045 | 3.380 | 0.65 | 2.395
cuda-4-8-multi-gpu | 4.047 | 1.065 | 0.158 | 2.824 | 3.239 | 0.565 | 2.259
cuda-2-16-multi-gpu | 4.2 | 1.037 | 0.156 | 3.007 | 3.290 | 0.654 | 2.353
cuda-1-32-multi-gpu | 4.294 | 1.036 | 0.148 | 3.110 | 3.438 | 0.703 | 2.407


### lfr_graphs/n6000000_k40_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **3.955** | **0.875** | **0.162** | **2.918** | **2.902** | **0.759** | **2.159**
**cuda-bitmap-kernel-multi-gpu** | **3.936** | **0.873** | **0.183** | **2.880** | **3.091** | **0.57** | **2.31**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### n12dot5_m80_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **20.721** | **10.779** | **1.994** | **7.948** | **16.769** | **1.804** | **6.144**
**cuda-bitmap-kernel-multi-gpu** | **20.518** | **10.543** | **1.987** | **7.988** | **16.576** | **1.517** | **6.471**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | 48.637 | 10.621 | 1.951 | 36.065 | 44.542 | 1.803 | 34.262
cuda-16-2-multi-gpu | 57.708 | 11.323 | 1.982 | 44.403 | 54.108 | 1.855 | 42.548
cuda-8-4-multi-gpu | 76.737 | 10.576 | 2.005 | 64.156 | 72.819 | 1.824 | 62.332
cuda-4-8-multi-gpu | 118.709 | 10.938 | 2.01 | 105.761 | 114.889 | 1.82 | 103.941
cuda-2-16-multi-gpu | 203.461 | 11.153 | 1.998 | 190.310 | 200.019 | 1.673 | 188.637
cuda-1-32-multi-gpu | 369.835 | 11.805 | 1.965 | 356.065 | 366.109 | 1.499 | 354.566


### n12dot5_m80_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **20.755** | **11.11** | **1.982** | **7.663** | **16.799** | **1.867** | **5.796**
**cuda-bitmap-kernel-multi-gpu** | **20.537** | **11.031** | **2.016** | **7.490** | **16.877** | **1.566** | **5.924**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### n16dot7_m60_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **22.55** | **10.017** | **2.328** | **10.205** | **18.817** | **2.229** | **7.976**
**cuda-bitmap-kernel-multi-gpu** | **21.461** | **10.561** | **2.298** | **8.602** | **17.733** | **1.995** | **6.607**
cuda-baseline-hybrid-multi-gpu | 465.726 | 10.976 | 2.348 | 452.402 | 463.479 | 2.24 | 450.162
cuda-baseline-multi-gpu | 448.008 | 10.2 | 2.307 | 435.501 | 443.341 | 1.999 | 433.502
cuda-32-1-multi-gpu | 51.642 | 10.461 | 2.302 | 38.879 | 47.180 | 2.51 | 36.369
cuda-16-2-multi-gpu | 60.593 | 10.018 | 2.329 | 48.246 | 56.653 | 2.045 | 46.201
cuda-8-4-multi-gpu | 84.152 | 10.992 | 2.317 | 70.843 | 79.706 | 2.211 | 68.632
cuda-4-8-multi-gpu | 128.92 | 10.362 | 2.321 | 116.237 | 124.690 | 1.99 | 114.247
cuda-2-16-multi-gpu | 224.788 | 10.681 | 2.283 | 211.824 | 220.044 | 2.789 | 209.035
cuda-1-32-multi-gpu | 400.098 | 11.081 | 2.312 | 386.705 | 395.803 | 2.202 | 384.503


### n16dot7_m60_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **20.509** | **10.154** | **2.32** | **8.035** | **16.920** | **1.956** | **6.079**
**cuda-bitmap-kernel-multi-gpu** | **21.662** | **10.443** | **2.304** | **8.915** | **17.510** | **2.423** | **6.492**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### n25_m40_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **21.724** | **9.889** | **2.711** | **9.124** | **17.749** | **2.871** | **6.253**
**cuda-bitmap-kernel-multi-gpu** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-multi-gpu | 321.415 | 9.886 | 2.663 | 308.866 | 318.534 | 2.876 | 305.99
cuda-baseline-multi-gpu | 312.195 | 9.808 | 2.645 | 299.742 | 307.194 | 2.742 | 297.0
cuda-32-1-multi-gpu | 49.311 | 9.956 | 2.677 | 36.678 | 44.494 | 2.848 | 33.83
cuda-16-2-multi-gpu | 59.827 | 10.193 | 2.669 | 46.965 | 54.498 | 3.399 | 43.566
cuda-8-4-multi-gpu | 81.183 | 9.972 | 2.705 | 68.506 | 75.779 | 3.595 | 64.911
cuda-4-8-multi-gpu | 124.786 | 9.878 | 2.703 | 112.205 | 120.020 | 2.826 | 109.379
cuda-2-16-multi-gpu | 214.041 | 10.28 | 2.732 | 201.029 | 209.141 | 2.844 | 198.185
cuda-1-32-multi-gpu | 384.267 | 10.307 | 2.697 | 371.263 | 378.831 | 3.532 | 367.731


### n25_m40_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **21.69** | **9.814** | **2.703** | **9.173** | **17.587** | **3.072** | **6.101**
**cuda-bitmap-kernel-multi-gpu** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /


### n50_m20_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **24.75** | **9.651** | **3.217** | **11.882** | **18.063** | **5.566** | **6.316**
**cuda-bitmap-kernel-multi-gpu** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-multi-gpu | 177.994 | 9.694 | 3.206 | 165.094 | 172.593 | 5.395 | 159.699
cuda-baseline-multi-gpu | 174.631 | 9.683 | 3.213 | 161.735 | 163.890 | 7.749 | 153.986
cuda-32-1-multi-gpu | 52.585 | 9.666 | 3.172 | 39.747 | 44.256 | 6.053 | 33.694
cuda-16-2-multi-gpu | 65.35 | 9.852 | 3.253 | 52.245 | 56.116 | 7.385 | 44.86
cuda-8-4-multi-gpu | 86.948 | 9.85 | 3.138 | 73.960 | 79.529 | 5.347 | 68.613
cuda-4-8-multi-gpu | 134.098 | 9.764 | 3.196 | 121.138 | 126.219 | 5.668 | 115.47
cuda-2-16-multi-gpu | 230.066 | 9.915 | 3.166 | 216.985 | 222.546 | 5.599 | 211.386
cuda-1-32-multi-gpu | 410.557 | 9.871 | 3.236 | 397.450 | 401.221 | 7.452 | 389.998


### n50_m20_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu** | **24.459** | **9.708** | **3.21** | **11.541** | **18.346** | **5.684** | **5.857**
**cuda-bitmap-kernel-multi-gpu** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-multi-gpu | / | / | / | / | / | / | /
cuda-baseline-multi-gpu | / | / | / | / | / | / | /
cuda-32-1-multi-gpu | / | / | / | / | / | / | /
cuda-16-2-multi-gpu | / | / | / | / | / | / | /
cuda-8-4-multi-gpu | / | / | / | / | / | / | /
cuda-4-8-multi-gpu | / | / | / | / | / | / | /
cuda-2-16-multi-gpu | / | / | / | / | / | / | /
cuda-1-32-multi-gpu | / | / | / | / | / | / | /