# Core Checking (eps = 0.2, mu = 5)


Unit: seconds


### small_snap_cit_patents

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.757** | **0.019** | **0.019** | **1.719** | **1.677** | **0.028** | **1.691**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.727** | **0.014** | **0.015** | **1.698** | **1.650** | **0.027** | **1.671**
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.745 | 0.015 | 0.016 | 1.714 | 1.697 | 0.028 | 1.686
cuda-baseline-multi-gpu-multi-pass | 1.729 | 0.019 | 0.018 | 1.692 | 1.680 | 0.028 | 1.664
cuda-32-1-multi-gpu-multi-pass | 1.716 | 0.014 | 0.016 | 1.686 | 1.665 | 0.029 | 1.657
cuda-16-2-multi-gpu-multi-pass | 1.677 | 0.015 | 0.016 | 1.646 | 1.630 | 0.027 | 1.619
cuda-8-4-multi-gpu-multi-pass | 1.728 | 0.016 | 0.017 | 1.695 | 1.679 | 0.029 | 1.666
cuda-4-8-multi-gpu-multi-pass | 1.746 | 0.015 | 0.018 | 1.713 | 1.683 | 0.037 | 1.676
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.078** | **0.005** | **0.012** | **0.061** | **0.059** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.078** | **0.009** | **0.014** | **0.055** | **0.057** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 0.057 | 0.005 | 0.011 | 0.041 | 0.040 | / | /
cuda-baseline-single-gpu-multi-pass | 0.06 | 0.006 | 0.012 | 0.042 | 0.036 | / | /
cuda-32-1-single-gpu-multi-pass | 0.053 | 0.006 | 0.012 | 0.035 | 0.036 | / | /
cuda-16-2-single-gpu-multi-pass | 0.057 | 0.006 | 0.012 | 0.039 | 0.040 | / | /
cuda-8-4-single-gpu-multi-pass | 0.058 | 0.005 | 0.014 | 0.039 | 0.042 | / | /
cuda-4-8-single-gpu-multi-pass | 0.051 | 0.008 | 0.008 | 0.035 | 0.034 | / | /


### small_snap_cit_patents/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.165** | **0.018** | **0.014** | **2.133** | **2.081** | **0.029** | **2.104**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.771** | **0.015** | **0.014** | **1.742** | **1.698** | **0.031** | **1.711**
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.792 | 0.014 | 0.014 | 1.764 | 1.741 | 0.028 | 1.736
cuda-baseline-multi-gpu-multi-pass | 1.688 | 0.012 | 0.016 | 1.660 | 1.635 | 0.028 | 1.632
cuda-32-1-multi-gpu-multi-pass | 1.814 | 0.014 | 0.014 | 1.786 | 1.765 | 0.03 | 1.756
cuda-16-2-multi-gpu-multi-pass | 1.709 | 0.015 | 0.018 | 1.676 | 1.664 | 0.026 | 1.65
cuda-8-4-multi-gpu-multi-pass | 1.744 | 0.016 | 0.015 | 1.713 | 1.690 | 0.031 | 1.682
cuda-4-8-multi-gpu-multi-pass | 1.802 | 0.014 | 0.015 | 1.773 | 1.754 | 0.031 | 1.742
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.079** | **0.007** | **0.012** | **0.060** | **0.061** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.077** | **0.009** | **0.01** | **0.058** | **0.054** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 0.057 | 0.008 | 0.012 | 0.037 | 0.041 | / | /
cuda-baseline-single-gpu-multi-pass | 0.06 | 0.009 | 0.01 | 0.041 | 0.044 | / | /
cuda-32-1-single-gpu-multi-pass | 0.062 | 0.008 | 0.013 | 0.041 | 0.045 | / | /
cuda-16-2-single-gpu-multi-pass | 0.05 | 0.006 | 0.004 | 0.040 | 0.035 | / | /
cuda-8-4-single-gpu-multi-pass | 0.065 | 0.008 | 0.012 | 0.045 | 0.048 | / | /
cuda-4-8-single-gpu-multi-pass | 0.058 | 0.007 | 0.012 | 0.039 | 0.042 | / | /


### small_snap_dblp

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.706** | **0.014** | **0.013** | **1.679** | **1.676** | **0.006** | **1.673**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.693** | **0.014** | **0.018** | **1.661** | **1.676** | **0.006** | **1.655**
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.704 | 0.016 | 0.015 | 1.673 | 1.690 | 0.006 | 1.667
cuda-baseline-multi-gpu-multi-pass | 1.748 | 0.015 | 0.019 | 1.714 | 1.736 | 0.005 | 1.709
cuda-32-1-multi-gpu-multi-pass | 1.71 | 0.014 | 0.018 | 1.678 | 1.695 | 0.006 | 1.672
cuda-16-2-multi-gpu-multi-pass | 1.719 | 0.015 | 0.024 | 1.680 | 1.706 | 0.005 | 1.675
cuda-8-4-multi-gpu-multi-pass | 1.687 | 0.016 | 0.017 | 1.654 | 1.673 | 0.005 | 1.649
cuda-4-8-multi-gpu-multi-pass | 1.701 | 0.014 | 0.014 | 1.673 | 1.688 | 0.005 | 1.668
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.032** | **0.005** | **0.011** | **0.016** | **0.027** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.038** | **0.006** | **0.012** | **0.020** | **0.032** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 0.033 | 0.006 | 0.011 | 0.016 | 0.030 | / | /
cuda-baseline-single-gpu-multi-pass | 0.034 | 0.006 | 0.012 | 0.016 | 0.032 | / | /
cuda-32-1-single-gpu-multi-pass | 0.036 | 0.006 | 0.011 | 0.019 | 0.033 | / | /
cuda-16-2-single-gpu-multi-pass | 0.027 | 0.005 | 0.006 | 0.016 | 0.024 | / | /
cuda-8-4-single-gpu-multi-pass | 0.036 | 0.006 | 0.012 | 0.018 | 0.033 | / | /
cuda-4-8-single-gpu-multi-pass | 0.037 | 0.006 | 0.012 | 0.019 | 0.034 | / | /


### small_snap_dblp/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.037** | **0.014** | **0.015** | **2.008** | **1.994** | **0.006** | **2.002**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.79** | **0.015** | **0.016** | **1.759** | **1.762** | **0.005** | **1.754**
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.735 | 0.021 | 0.015 | 1.699 | 1.723 | 0.006 | 1.693
cuda-baseline-multi-gpu-multi-pass | 1.755 | 0.017 | 0.015 | 1.723 | 1.744 | 0.004 | 1.719
cuda-32-1-multi-gpu-multi-pass | 1.76 | 0.016 | 0.012 | 1.732 | 1.748 | 0.005 | 1.727
cuda-16-2-multi-gpu-multi-pass | 1.712 | 0.013 | 0.012 | 1.687 | 1.699 | 0.007 | 1.68
cuda-8-4-multi-gpu-multi-pass | 1.763 | 0.013 | 0.014 | 1.736 | 1.747 | 0.009 | 1.727
cuda-4-8-multi-gpu-multi-pass | 1.694 | 0.013 | 0.018 | 1.663 | 1.680 | 0.006 | 1.657
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.037** | **0.006** | **0.011** | **0.020** | **0.032** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.037** | **0.006** | **0.013** | **0.018** | **0.031** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 0.034 | 0.006 | 0.011 | 0.017 | 0.031 | / | /
cuda-baseline-single-gpu-multi-pass | 0.036 | 0.006 | 0.012 | 0.018 | 0.033 | / | /
cuda-32-1-single-gpu-multi-pass | 0.037 | 0.006 | 0.011 | 0.020 | 0.034 | / | /
cuda-16-2-single-gpu-multi-pass | 0.034 | 0.006 | 0.011 | 0.017 | 0.031 | / | /
cuda-8-4-single-gpu-multi-pass | 0.034 | 0.006 | 0.011 | 0.017 | 0.032 | / | /
cuda-4-8-single-gpu-multi-pass | 0.027 | 0.005 | 0.004 | 0.018 | 0.024 | / | /


### small_snap_web_berkstan

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.664** | **0.015** | **0.012** | **1.637** | **1.634** | **0.007** | **1.63**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.75** | **0.017** | **0.016** | **1.717** | **1.697** | **0.007** | **1.71**
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.741 | 0.017 | 0.023 | 1.701 | 1.721 | 0.008 | 1.693
cuda-baseline-multi-gpu-multi-pass | 1.775 | 0.018 | 0.019 | 1.738 | 1.756 | 0.007 | 1.731
cuda-32-1-multi-gpu-multi-pass | 1.705 | 0.014 | 0.021 | 1.670 | 1.688 | 0.008 | 1.662
cuda-16-2-multi-gpu-multi-pass | 1.695 | 0.015 | 0.014 | 1.666 | 1.677 | 0.007 | 1.659
cuda-8-4-multi-gpu-multi-pass | 1.684 | 0.018 | 0.016 | 1.650 | 1.663 | 0.01 | 1.64
cuda-4-8-multi-gpu-multi-pass | 1.722 | 0.018 | 0.015 | 1.689 | 1.708 | 0.007 | 1.682
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.041** | **0.005** | **0.014** | **0.022** | **0.036** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.041** | **0.005** | **0.009** | **0.027** | **0.034** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 0.045 | 0.006 | 0.012 | 0.027 | 0.040 | / | /
cuda-baseline-single-gpu-multi-pass | 0.048 | 0.005 | 0.011 | 0.032 | 0.044 | / | /
cuda-32-1-single-gpu-multi-pass | 0.057 | 0.008 | 0.01 | 0.039 | 0.053 | / | /
cuda-16-2-single-gpu-multi-pass | 0.036 | 0.005 | 0.002 | 0.029 | 0.031 | / | /
cuda-8-4-single-gpu-multi-pass | 0.043 | 0.005 | 0.009 | 0.029 | 0.039 | / | /
cuda-4-8-single-gpu-multi-pass | 0.041 | 0.005 | 0.007 | 0.029 | 0.037 | / | /


### small_snap_web_berkstan/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.834** | **0.017** | **0.016** | **1.801** | **1.806** | **0.006** | **1.795**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.809** | **0.016** | **0.015** | **1.778** | **1.766** | **0.007** | **1.771**
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.722 | 0.016 | 0.017 | 1.689 | 1.704 | 0.007 | 1.682
cuda-baseline-multi-gpu-multi-pass | 1.81 | 0.017 | 0.018 | 1.775 | 1.788 | 0.007 | 1.768
cuda-32-1-multi-gpu-multi-pass | 1.747 | 0.017 | 0.014 | 1.716 | 1.715 | 0.01 | 1.706
cuda-16-2-multi-gpu-multi-pass | 1.649 | 0.015 | 0.015 | 1.619 | 1.610 | 0.009 | 1.61
cuda-8-4-multi-gpu-multi-pass | 1.698 | 0.018 | 0.016 | 1.664 | 1.650 | 0.006 | 1.658
cuda-4-8-multi-gpu-multi-pass | 1.656 | 0.015 | 0.007 | 1.634 | 1.577 | 0.007 | 1.627
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.044** | **0.007** | **0.012** | **0.025** | **0.037** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.042** | **0.007** | **0.005** | **0.030** | **0.032** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 0.041 | 0.007 | 0.011 | 0.023 | 0.038 | / | /
cuda-baseline-single-gpu-multi-pass | 0.049 | 0.009 | 0.009 | 0.031 | 0.045 | / | /
cuda-32-1-single-gpu-multi-pass | 0.058 | 0.009 | 0.012 | 0.037 | 0.054 | / | /
cuda-16-2-single-gpu-multi-pass | 0.067 | 0.01 | 0.012 | 0.045 | 0.063 | / | /
cuda-8-4-single-gpu-multi-pass | 0.079 | 0.011 | 0.011 | 0.057 | 0.074 | / | /
cuda-4-8-single-gpu-multi-pass | 0.1 | 0.01 | 0.009 | 0.081 | 0.097 | / | /


### small_snap_web_notredame

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.759** | **0.014** | **0.015** | **1.730** | **1.726** | **0.006** | **1.724**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.666** | **0.013** | **0.017** | **1.636** | **1.619** | **0.005** | **1.631**
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.729 | 0.011 | 0.021 | 1.697 | 1.675 | 0.005 | 1.692
cuda-baseline-multi-gpu-multi-pass | 1.755 | 0.011 | 0.016 | 1.728 | 1.701 | 0.004 | 1.724
cuda-32-1-multi-gpu-multi-pass | 1.8 | 0.01 | 0.013 | 1.777 | 1.721 | 0.004 | 1.773
cuda-16-2-multi-gpu-multi-pass | 1.794 | 0.013 | 0.016 | 1.765 | 1.685 | 0.005 | 1.76
cuda-8-4-multi-gpu-multi-pass | 1.763 | 0.012 | 0.014 | 1.737 | 1.604 | 0.005 | 1.732
cuda-4-8-multi-gpu-multi-pass | 1.925 | 0.011 | 0.013 | 1.901 | 1.664 | 0.005 | 1.896
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.029** | **0.003** | **0.011** | **0.015** | **0.024** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.031** | **0.003** | **0.01** | **0.018** | **0.026** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 0.062 | 0.008 | 0.01 | 0.044 | 0.059 | / | /
cuda-baseline-single-gpu-multi-pass | 0.076 | 0.003 | 0.012 | 0.061 | 0.074 | / | /
cuda-32-1-single-gpu-multi-pass | 0.114 | 0.003 | 0.001 | 0.110 | 0.112 | / | /
cuda-16-2-single-gpu-multi-pass | 0.141 | 0.004 | 0.001 | 0.136 | 0.139 | / | /
cuda-8-4-single-gpu-multi-pass | 0.223 | 0.005 | 0.013 | 0.205 | 0.221 | / | /
cuda-4-8-single-gpu-multi-pass | 0.319 | 0.005 | 0.004 | 0.310 | 0.317 | / | /


### small_snap_web_notredame/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.746** | **0.01** | **0.012** | **1.724** | **1.697** | **0.005** | **1.719**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.754** | **0.011** | **0.014** | **1.729** | **1.704** | **0.005** | **1.724**
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.708 | 0.014 | 0.01 | 1.684 | 1.686 | 0.005 | 1.679
cuda-baseline-multi-gpu-multi-pass | 1.698 | 0.009 | 0.011 | 1.678 | 1.636 | 0.006 | 1.672
cuda-32-1-multi-gpu-multi-pass | 1.704 | 0.014 | 0.014 | 1.676 | 1.614 | 0.005 | 1.671
cuda-16-2-multi-gpu-multi-pass | 1.708 | 0.012 | 0.009 | 1.687 | 1.579 | 0.006 | 1.681
cuda-8-4-multi-gpu-multi-pass | 1.709 | 0.011 | 0.011 | 1.687 | 1.516 | 0.006 | 1.681
cuda-4-8-multi-gpu-multi-pass | 1.722 | 0.015 | 0.008 | 1.699 | 1.393 | 0.005 | 1.694
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.03** | **0.003** | **0.012** | **0.015** | **0.025** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.02** | **0.004** | **0.001** | **0.015** | **0.015** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 0.038 | 0.007 | 0.01 | 0.021 | 0.036 | / | /
cuda-baseline-single-gpu-multi-pass | 0.067 | 0.006 | 0.01 | 0.051 | 0.064 | / | /
cuda-32-1-single-gpu-multi-pass | 0.117 | 0.007 | 0.01 | 0.100 | 0.115 | / | /
cuda-16-2-single-gpu-multi-pass | 0.153 | 0.006 | 0.018 | 0.129 | 0.151 | / | /
cuda-8-4-single-gpu-multi-pass | 0.203 | 0.004 | 0.001 | 0.198 | 0.200 | / | /
cuda-4-8-single-gpu-multi-pass | 0.334 | 0.004 | 0.01 | 0.320 | 0.332 | / | /


### small_snap_web_stanford

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.75** | **0.012** | **0.015** | **1.723** | **1.704** | **0.005** | **1.718**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.749** | **0.014** | **0.013** | **1.722** | **1.725** | **0.005** | **1.717**
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.704 | 0.012 | 0.015 | 1.677 | 1.690 | 0.005 | 1.672
cuda-baseline-multi-gpu-multi-pass | 1.687 | 0.011 | 0.016 | 1.660 | 1.671 | 0.005 | 1.655
cuda-32-1-multi-gpu-multi-pass | 1.729 | 0.015 | 0.018 | 1.696 | 1.713 | 0.005 | 1.691
cuda-16-2-multi-gpu-multi-pass | 1.734 | 0.014 | 0.015 | 1.705 | 1.721 | 0.005 | 1.7
cuda-8-4-multi-gpu-multi-pass | 1.692 | 0.015 | 0.016 | 1.661 | 1.680 | 0.004 | 1.657
cuda-4-8-multi-gpu-multi-pass | 1.714 | 0.014 | 0.016 | 1.684 | 1.700 | 0.005 | 1.679
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.027** | **0.005** | **0.009** | **0.013** | **0.023** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.028** | **0.003** | **0.011** | **0.014** | **0.023** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 0.027 | 0.004 | 0.011 | 0.012 | 0.025 | / | /
cuda-baseline-single-gpu-multi-pass | 0.025 | 0.003 | 0.01 | 0.012 | 0.022 | / | /
cuda-32-1-single-gpu-multi-pass | 0.028 | 0.004 | 0.01 | 0.014 | 0.026 | / | /
cuda-16-2-single-gpu-multi-pass | 0.027 | 0.004 | 0.01 | 0.013 | 0.024 | / | /
cuda-8-4-single-gpu-multi-pass | 0.026 | 0.005 | 0.009 | 0.012 | 0.024 | / | /
cuda-4-8-single-gpu-multi-pass | 0.02 | 0.003 | 0.003 | 0.014 | 0.018 | / | /


### small_snap_web_stanford/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.737** | **0.011** | **0.015** | **1.711** | **1.694** | **0.005** | **1.706**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.722** | **0.014** | **0.013** | **1.695** | **1.671** | **0.005** | **1.69**
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.735 | 0.012 | 0.015 | 1.708 | 1.721 | 0.004 | 1.704
cuda-baseline-multi-gpu-multi-pass | 1.694 | 0.016 | 0.012 | 1.666 | 1.679 | 0.005 | 1.661
cuda-32-1-multi-gpu-multi-pass | 1.731 | 0.011 | 0.01 | 1.710 | 1.719 | 0.005 | 1.705
cuda-16-2-multi-gpu-multi-pass | 1.731 | 0.013 | 0.013 | 1.705 | 1.716 | 0.005 | 1.7
cuda-8-4-multi-gpu-multi-pass | 1.754 | 0.011 | 0.015 | 1.728 | 1.738 | 0.005 | 1.723
cuda-4-8-multi-gpu-multi-pass | 1.788 | 0.015 | 0.009 | 1.764 | 1.772 | 0.005 | 1.759
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.027** | **0.003** | **0.011** | **0.013** | **0.023** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.03** | **0.004** | **0.011** | **0.015** | **0.023** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 0.03 | 0.004 | 0.013 | 0.013 | 0.028 | / | /
cuda-baseline-single-gpu-multi-pass | 0.029 | 0.004 | 0.012 | 0.013 | 0.027 | / | /
cuda-32-1-single-gpu-multi-pass | 0.027 | 0.005 | 0.011 | 0.011 | 0.024 | / | /
cuda-16-2-single-gpu-multi-pass | 0.022 | 0.005 | 0.005 | 0.012 | 0.020 | / | /
cuda-8-4-single-gpu-multi-pass | 0.025 | 0.004 | 0.01 | 0.011 | 0.024 | / | /
cuda-4-8-single-gpu-multi-pass | 0.028 | 0.004 | 0.011 | 0.013 | 0.026 | / | /


### snap_pokec

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.835** | **0.071** | **0.036** | **1.728** | **1.743** | **0.017** | **1.711**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.87** | **0.069** | **0.033** | **1.768** | **1.763** | **0.018** | **1.75**
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.895 | 0.071 | 0.027 | 1.797 | 1.573 | 0.019 | 1.778
cuda-baseline-multi-gpu-multi-pass | 1.883 | 0.073 | 0.04 | 1.770 | 1.333 | 0.018 | 1.752
cuda-32-1-multi-gpu-multi-pass | 1.814 | 0.066 | 0.034 | 1.714 | 0.991 | 0.019 | 1.695
cuda-16-2-multi-gpu-multi-pass | 1.851 | 0.069 | 0.035 | 1.747 | 0.789 | 0.018 | 1.729
cuda-8-4-multi-gpu-multi-pass | 1.913 | 0.072 | 0.036 | 1.805 | 0.603 | 0.018 | 1.787
cuda-4-8-multi-gpu-multi-pass | 2.941 | 0.073 | 0.036 | 2.832 | 1.517 | 0.018 | 2.814
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.236** | **0.067** | **0.033** | **0.136** | **0.226** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.251** | **0.067** | **0.026** | **0.158** | **0.240** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 0.564 | 0.069 | 0.027 | 0.468 | 0.557 | / | /
cuda-baseline-single-gpu-multi-pass | 0.729 | 0.062 | 0.027 | 0.640 | 0.721 | / | /
cuda-32-1-single-gpu-multi-pass | 1.056 | 0.066 | 0.03 | 0.960 | 1.048 | / | /
cuda-16-2-single-gpu-multi-pass | 1.306 | 0.068 | 0.026 | 1.212 | 1.298 | / | /
cuda-8-4-single-gpu-multi-pass | 1.816 | 0.065 | 0.032 | 1.719 | 1.808 | / | /
cuda-4-8-single-gpu-multi-pass | 2.969 | 0.07 | 0.033 | 2.866 | 2.961 | / | /


### snap_pokec/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.879** | **0.079** | **0.028** | **1.772** | **1.767** | **0.019** | **1.753**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.933** | **0.079** | **0.033** | **1.821** | **1.808** | **0.02** | **1.801**
cuda-baseline-hybrid-multi-gpu-multi-pass | 1.925 | 0.084 | 0.032 | 1.809 | 1.740 | 0.022 | 1.787
cuda-baseline-multi-gpu-multi-pass | 1.884 | 0.079 | 0.035 | 1.770 | 1.261 | 0.02 | 1.75
cuda-32-1-multi-gpu-multi-pass | 1.808 | 0.074 | 0.031 | 1.703 | 0.966 | 0.019 | 1.684
cuda-16-2-multi-gpu-multi-pass | 1.799 | 0.073 | 0.025 | 1.701 | 0.675 | 0.019 | 1.682
cuda-8-4-multi-gpu-multi-pass | 1.848 | 0.077 | 0.035 | 1.736 | 0.476 | 0.025 | 1.711
cuda-4-8-multi-gpu-multi-pass | 2.976 | 0.074 | 0.035 | 2.867 | 1.516 | 0.024 | 2.843
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.256** | **0.076** | **0.033** | **0.147** | **0.246** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.266** | **0.075** | **0.033** | **0.158** | **0.255** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 0.482 | 0.074 | 0.027 | 0.381 | 0.472 | / | /
cuda-baseline-single-gpu-multi-pass | 0.848 | 0.075 | 0.033 | 0.740 | 0.842 | / | /
cuda-32-1-single-gpu-multi-pass | 1.087 | 0.072 | 0.026 | 0.989 | 1.079 | / | /
cuda-16-2-single-gpu-multi-pass | 1.266 | 0.074 | 0.027 | 1.165 | 1.258 | / | /
cuda-8-4-single-gpu-multi-pass | 1.808 | 0.076 | 0.032 | 1.700 | 1.800 | / | /
cuda-4-8-single-gpu-multi-pass | 3.005 | 0.074 | 0.026 | 2.905 | 2.997 | / | /


### snap_livejournal

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **1.947** | **0.125** | **0.047** | **1.775** | **1.792** | **0.041** | **1.734**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **1.996** | **0.133** | **0.051** | **1.812** | **1.822** | **0.04** | **1.772**
cuda-baseline-hybrid-multi-gpu-multi-pass | 2.508 | 0.139 | 0.061 | 2.308 | 1.775 | 0.043 | 2.265
cuda-baseline-multi-gpu-multi-pass | 2.819 | 0.139 | 0.048 | 2.632 | 1.299 | 0.05 | 2.582
cuda-32-1-multi-gpu-multi-pass | 2.863 | 0.133 | 0.048 | 2.682 | 1.415 | 0.039 | 2.643
cuda-16-2-multi-gpu-multi-pass | 3.247 | 0.134 | 0.047 | 3.066 | 1.753 | 0.052 | 3.014
cuda-8-4-multi-gpu-multi-pass | 4.828 | 0.134 | 0.05 | 4.644 | 3.245 | 0.047 | 4.597
cuda-4-8-multi-gpu-multi-pass | 8.125 | 0.14 | 0.062 | 7.923 | 6.545 | 0.056 | 7.867
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.507** | **0.131** | **0.044** | **0.332** | **0.487** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.697** | **0.134** | **0.043** | **0.520** | **0.661** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 1.329 | 0.137 | 0.057 | 1.135 | 1.311 | / | /
cuda-baseline-single-gpu-multi-pass | 2.087 | 0.133 | 0.047 | 1.907 | 2.057 | / | /
cuda-32-1-single-gpu-multi-pass | 2.826 | 0.138 | 0.059 | 2.629 | 2.808 | / | /
cuda-16-2-single-gpu-multi-pass | 3.429 | 0.132 | 0.048 | 3.249 | 3.410 | / | /
cuda-8-4-single-gpu-multi-pass | 4.913 | 0.133 | 0.047 | 4.733 | 4.894 | / | /
cuda-4-8-single-gpu-multi-pass | 8.282 | 0.13 | 0.046 | 8.106 | 8.251 | / | /


### snap_livejournal/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.2** | **0.161** | **0.078** | **1.961** | **1.991** | **0.068** | **1.893**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.106** | **0.166** | **0.071** | **1.869** | **1.887** | **0.047** | **1.822**
cuda-baseline-hybrid-multi-gpu-multi-pass | 2.349 | 0.172 | 0.066 | 2.111 | 1.924 | 0.072 | 2.039
cuda-baseline-multi-gpu-multi-pass | 2.293 | 0.168 | 0.06 | 2.065 | 0.841 | 0.07 | 1.995
cuda-32-1-multi-gpu-multi-pass | 2.5 | 0.166 | 0.055 | 2.279 | 1.168 | 0.054 | 2.225
cuda-16-2-multi-gpu-multi-pass | 3.303 | 0.171 | 0.063 | 3.069 | 1.783 | 0.066 | 3.003
cuda-8-4-multi-gpu-multi-pass | 4.935 | 0.169 | 0.061 | 4.705 | 3.516 | 0.067 | 4.638
cuda-4-8-multi-gpu-multi-pass | 8.171 | 0.175 | 0.061 | 7.935 | 6.679 | 0.054 | 7.881
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **0.635** | **0.161** | **0.05** | **0.424** | **0.602** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **0.694** | **0.161** | **0.056** | **0.477** | **0.662** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 1.444 | 0.168 | 0.059 | 1.217 | 1.414 | / | /
cuda-baseline-single-gpu-multi-pass | 2.565 | 0.164 | 0.055 | 2.346 | 2.547 | / | /
cuda-32-1-single-gpu-multi-pass | 2.884 | 0.158 | 0.055 | 2.671 | 2.853 | / | /
cuda-16-2-single-gpu-multi-pass | 3.442 | 0.164 | 0.052 | 3.226 | 3.419 | / | /
cuda-8-4-single-gpu-multi-pass | 5.06 | 0.159 | 0.05 | 4.851 | 5.029 | / | /
cuda-4-8-single-gpu-multi-pass | 8.332 | 0.156 | 0.054 | 8.122 | 8.302 | / | /


### snap_orkut

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.883** | **0.541** | **0.139** | **2.203** | **2.566** | **0.058** | **2.145**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **3.071** | **0.544** | **0.158** | **2.369** | **2.644** | **0.066** | **2.303**
cuda-baseline-hybrid-multi-gpu-multi-pass | 7.843 | 0.531 | 0.142 | 7.170 | 6.099 | 0.063 | 7.107
cuda-baseline-multi-gpu-multi-pass | 9.069 | 0.54 | 0.142 | 8.387 | 7.594 | 0.059 | 8.328
cuda-32-1-multi-gpu-multi-pass | 12.54 | 0.537 | 0.152 | 11.851 | 10.675 | 0.058 | 11.793
cuda-16-2-multi-gpu-multi-pass | 16.245 | 0.53 | 0.14 | 15.575 | 14.773 | 0.054 | 15.521
cuda-8-4-multi-gpu-multi-pass | 24.19 | 0.547 | 0.173 | 23.470 | 22.378 | 0.064 | 23.406
cuda-4-8-multi-gpu-multi-pass | 40.336 | 0.532 | 0.14 | 39.664 | 38.692 | 0.059 | 39.605
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.57** | **0.537** | **0.14** | **2.893** | **3.545** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **2.93** | **0.541** | **0.138** | **2.251** | **2.913** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 11.478 | 0.539 | 0.165 | 10.774 | 11.455 | / | /
cuda-baseline-single-gpu-multi-pass | 13.589 | 0.54 | 0.139 | 12.910 | 13.566 | / | /
cuda-32-1-single-gpu-multi-pass | 15.892 | 0.553 | 0.14 | 15.199 | 15.867 | / | /
cuda-16-2-single-gpu-multi-pass | 18.146 | 0.55 | 0.135 | 17.461 | 18.127 | / | /
cuda-8-4-single-gpu-multi-pass | 25.891 | 0.548 | 0.139 | 25.204 | 25.872 | / | /
cuda-4-8-single-gpu-multi-pass | 42.496 | 0.548 | 0.137 | 41.811 | 42.484 | / | /


### snap_orkut/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **3.035** | **0.652** | **0.132** | **2.251** | **2.709** | **0.073** | **2.178**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **3.214** | **0.641** | **0.138** | **2.435** | **2.742** | **0.076** | **2.359**
cuda-baseline-hybrid-multi-gpu-multi-pass | 6.121 | 0.662 | 0.134 | 5.325 | 4.403 | 0.07 | 5.255
cuda-baseline-multi-gpu-multi-pass | 11.475 | 0.651 | 0.134 | 10.690 | 9.698 | 0.074 | 10.616
cuda-32-1-multi-gpu-multi-pass | 12.7 | 0.683 | 0.127 | 11.890 | 11.045 | 0.071 | 11.819
cuda-16-2-multi-gpu-multi-pass | 16.412 | 0.681 | 0.126 | 15.605 | 15.004 | 0.064 | 15.541
cuda-8-4-multi-gpu-multi-pass | 24.51 | 0.653 | 0.128 | 23.729 | 23.165 | 0.069 | 23.66
cuda-4-8-multi-gpu-multi-pass | 41.367 | 0.666 | 0.14 | 40.561 | 39.778 | 0.076 | 40.485
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **2.644** | **0.666** | **0.145** | **1.833** | **2.620** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **2.791** | **0.656** | **0.13** | **2.005** | **2.763** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 16.23 | 0.684 | 0.129 | 15.417 | 16.206 | / | /
cuda-baseline-single-gpu-multi-pass | 21.963 | 0.657 | 0.13 | 21.176 | 21.940 | / | /
cuda-32-1-single-gpu-multi-pass | 14.928 | 0.675 | 0.135 | 14.118 | 14.916 | / | /
cuda-16-2-single-gpu-multi-pass | 17.578 | 0.678 | 0.156 | 16.744 | 17.553 | / | /
cuda-8-4-single-gpu-multi-pass | 25.759 | 0.682 | 0.129 | 24.948 | 25.736 | / | /
cuda-4-8-single-gpu-multi-pass | 42.996 | 0.691 | 0.125 | 42.180 | 42.981 | / | /


### snap_friendster

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **58.37** | **19.016** | **6.457** | **32.897** | **46.690** | **2.7** | **30.197**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **2.577** | **/**
cuda-baseline-hybrid-multi-gpu-multi-pass | 635.434 | 19.569 | 6.47 | 609.395 | 632.343 | 2.668 | 606.727
cuda-baseline-multi-gpu-multi-pass | 647.67 | 18.946 | 6.515 | 622.209 | 644.672 | 2.575 | 619.634
cuda-32-1-multi-gpu-multi-pass | 57.385 | 18.942 | 6.458 | 31.985 | 52.105 | 2.56 | 29.425
cuda-16-2-multi-gpu-multi-pass | 47.265 | 18.015 | 6.436 | 22.814 | 41.582 | 2.556 | 20.258
cuda-8-4-multi-gpu-multi-pass | 45.292 | 19.291 | 6.424 | 19.577 | 40.330 | 2.559 | 17.018
cuda-4-8-multi-gpu-multi-pass | 46.859 | 19.488 | 6.534 | 20.837 | 41.661 | 2.563 | 18.274
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **125.532** | **18.103** | **6.428** | **101.001** | **125.089** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 234.096 | 20.944 | 6.434 | 206.718 | 233.679 | / | /
cuda-16-2-single-gpu-multi-pass | 149.477 | 19.982 | 6.449 | 123.046 | 149.064 | / | /
cuda-8-4-single-gpu-multi-pass | 122.86 | 19.223 | 6.393 | 97.244 | 122.446 | / | /
cuda-4-8-single-gpu-multi-pass | 129.222 | 20.126 | 6.432 | 102.664 | 128.810 | / | /


### snap_friendster/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **76.649** | **16.308** | **5.307** | **55.034** | **74.054** | **2.101** | **52.933**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **2.172** | **/**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | 47.979 | 18.889 | 5.036 | 24.054 | 43.328 | 2.271 | 21.783
cuda-16-2-multi-gpu-multi-pass | 42.97 | 17.896 | 5.432 | 19.642 | 38.251 | 2.244 | 17.398
cuda-8-4-multi-gpu-multi-pass | 39.627 | 16.528 | 4.808 | 18.291 | 34.731 | 2.276 | 16.015
cuda-4-8-multi-gpu-multi-pass | 46.712 | 18.653 | 5.167 | 22.892 | 42.028 | 2.189 | 20.703
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **114.936** | **17.122** | **4.82** | **92.994** | **114.456** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 143.655 | 18.224 | 4.877 | 120.554 | 143.204 | / | /
cuda-16-2-single-gpu-multi-pass | 106.02 | 18.017 | 4.744 | 83.259 | 105.567 | / | /
cuda-8-4-single-gpu-multi-pass | 100.843 | 18.167 | 5.477 | 77.199 | 100.393 | / | /
cuda-4-8-single-gpu-multi-pass | 121.619 | 17.236 | 4.521 | 99.862 | 121.172 | / | /


### webgraph_it

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **53.919** | **1.004** | **0.418** | **52.497** | **51.554** | **0.364** | **52.133**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **225.666** | **0.944** | **0.358** | **224.364** | **216.542** | **0.339** | **224.025**
cuda-baseline-hybrid-multi-gpu-multi-pass | 25.18 | 0.958 | 0.361 | 23.861 | 22.848 | 0.362 | 23.499
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-16-2-multi-gpu-multi-pass | 475.505 | 1.163 | 0.362 | 473.980 | 474.582 | 0.357 | 473.623
cuda-8-4-multi-gpu-multi-pass | 245.788 | 1.07 | 0.36 | 244.358 | 243.547 | 0.401 | 243.957
cuda-4-8-multi-gpu-multi-pass | 131.545 | 0.989 | 0.361 | 130.195 | 129.293 | 0.35 | 129.845
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **397.797** | **1.02** | **0.377** | **396.400** | **397.591** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 47.333 | 1.027 | 0.355 | 45.951 | 47.171 | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | / | /


### webgraph_it/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **8.232** | **1.925** | **0.823** | **5.484** | **5.955** | **0.513** | **4.971**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **15.147** | **1.899** | **0.739** | **12.509** | **10.368** | **0.476** | **12.033**
cuda-baseline-hybrid-multi-gpu-multi-pass | 50.116 | 1.99 | 0.803 | 47.323 | 46.723 | 0.467 | 46.856
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-16-2-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-8-4-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **7.904** | **1.864** | **0.828** | **5.212** | **7.718** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **21.542** | **1.862** | **0.739** | **18.941** | **21.331** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 109.91 | 1.92 | 0.876 | 107.114 | 109.710 | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | / | /


### webgraph_uk

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.735** | **0.268** | **0.119** | **2.348** | **1.809** | **0.142** | **2.206**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.864** | **0.284** | **0.139** | **2.441** | **1.901** | **0.139** | **2.302**
cuda-baseline-hybrid-multi-gpu-multi-pass | 3.769 | 0.254 | 0.146 | 3.369 | 2.912 | 0.14 | 3.229
cuda-baseline-multi-gpu-multi-pass | 173.403 | 0.284 | 0.12 | 172.999 | 172.993 | 0.144 | 172.855
cuda-32-1-multi-gpu-multi-pass | 6.842 | 0.268 | 0.118 | 6.456 | 6.087 | 0.144 | 6.312
cuda-16-2-multi-gpu-multi-pass | 4.88 | 0.269 | 0.15 | 4.461 | 4.143 | 0.154 | 4.307
cuda-8-4-multi-gpu-multi-pass | 3.761 | 0.256 | 0.123 | 3.382 | 2.951 | 0.146 | 3.236
cuda-4-8-multi-gpu-multi-pass | 3.335 | 0.272 | 0.115 | 2.948 | 2.379 | 0.146 | 2.802
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **2.741** | **0.291** | **0.12** | **2.330** | **2.675** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.503** | **0.292** | **0.116** | **3.095** | **3.427** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 5.378 | 0.289 | 0.12 | 4.969 | 5.315 | / | /
cuda-baseline-single-gpu-multi-pass | 186.99 | 0.293 | 0.148 | 186.549 | 186.906 | / | /
cuda-32-1-single-gpu-multi-pass | 38.204 | 0.297 | 0.147 | 37.760 | 38.140 | / | /
cuda-16-2-single-gpu-multi-pass | 20.167 | 0.295 | 0.154 | 19.718 | 20.087 | / | /
cuda-8-4-single-gpu-multi-pass | 11.195 | 0.288 | 0.121 | 10.786 | 11.132 | / | /
cuda-4-8-single-gpu-multi-pass | 7.053 | 0.274 | 0.12 | 6.659 | 6.987 | / | /


### webgraph_uk/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **3.455** | **0.473** | **0.21** | **2.772** | **2.765** | **0.192** | **2.58**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **3.465** | **0.462** | **0.218** | **2.785** | **2.626** | **0.181** | **2.604**
cuda-baseline-hybrid-multi-gpu-multi-pass | 4.208 | 0.465 | 0.231 | 3.512 | 2.234 | 0.19 | 3.322
cuda-baseline-multi-gpu-multi-pass | 129.714 | 0.552 | 0.219 | 128.943 | 127.684 | 0.223 | 128.72
cuda-32-1-multi-gpu-multi-pass | 256.119 | 0.603 | 0.231 | 255.285 | 254.372 | 0.192 | 255.093
cuda-16-2-multi-gpu-multi-pass | 364.863 | 0.566 | 0.208 | 364.089 | 363.229 | 0.189 | 363.9
cuda-8-4-multi-gpu-multi-pass | 580.922 | 0.58 | 0.199 | 580.143 | 579.089 | 0.202 | 579.941
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **1.812** | **0.472** | **0.256** | **1.084** | **1.706** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **2.23** | **0.473** | **0.235** | **1.522** | **2.107** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 4.283 | 0.483 | 0.226 | 3.574 | 4.177 | / | /
cuda-baseline-single-gpu-multi-pass | 131.915 | 0.48 | 0.231 | 131.204 | 131.805 | / | /
cuda-32-1-single-gpu-multi-pass | 261.336 | 0.478 | 0.213 | 260.645 | 261.221 | / | /
cuda-16-2-single-gpu-multi-pass | 364.661 | 0.471 | 0.222 | 363.968 | 364.542 | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | / | /


### webgraph_eu

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **4.89** | **0.551** | **0.224** | **4.115** | **4.041** | **0.123** | **3.992**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **6.691** | **0.563** | **0.213** | **5.915** | **5.618** | **0.137** | **5.778**
cuda-baseline-hybrid-multi-gpu-multi-pass | 97.505 | 0.649 | 0.217 | 96.639 | 97.334 | 0.127 | 96.512
cuda-baseline-multi-gpu-multi-pass | 205.607 | 0.641 | 0.213 | 204.753 | 205.438 | 0.128 | 204.625
cuda-32-1-multi-gpu-multi-pass | 339.527 | 0.636 | 0.209 | 338.682 | 337.781 | 0.132 | 338.55
cuda-16-2-multi-gpu-multi-pass | 446.208 | 0.644 | 0.237 | 445.327 | 444.720 | 0.137 | 445.19
cuda-8-4-multi-gpu-multi-pass | 691.618 | 0.646 | 0.201 | 690.771 | 691.436 | 0.13 | 690.641
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **15.743** | **0.577** | **0.255** | **14.911** | **15.671** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **23.917** | **0.579** | **0.229** | **23.109** | **23.832** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 397.993 | 0.58 | 0.211 | 397.202 | 397.921 | / | /
cuda-baseline-single-gpu-multi-pass | 534.612 | 0.578 | 0.205 | 533.829 | 534.521 | / | /
cuda-32-1-single-gpu-multi-pass | 649.541 | 0.584 | 0.206 | 648.751 | 649.445 | / | /
cuda-16-2-single-gpu-multi-pass | 613.754 | 0.578 | 0.199 | 612.977 | 613.664 | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | / | /


### webgraph_eu/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **5.38** | **0.652** | **0.248** | **4.480** | **4.438** | **0.131** | **4.349**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **6.841** | **0.665** | **0.221** | **5.955** | **5.219** | **0.121** | **5.834**
cuda-baseline-hybrid-multi-gpu-multi-pass | 129.207 | 0.671 | 0.3 | 128.236 | 127.308 | 0.134 | 128.102
cuda-baseline-multi-gpu-multi-pass | 142.748 | 0.69 | 0.293 | 141.765 | 140.752 | 0.14 | 141.625
cuda-32-1-multi-gpu-multi-pass | 360.562 | 0.816 | 0.24 | 359.506 | 358.307 | 0.146 | 359.36
cuda-16-2-multi-gpu-multi-pass | 482.137 | 0.805 | 0.224 | 481.108 | 480.095 | 0.141 | 480.967
cuda-8-4-multi-gpu-multi-pass | 734.341 | 0.764 | 0.249 | 733.328 | 732.110 | 0.145 | 733.183
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **15.676** | **0.678** | **0.222** | **14.776** | **15.630** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **21.412** | **0.723** | **0.228** | **20.461** | **21.327** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 385.491 | 0.674 | 0.229 | 384.588 | 385.405 | / | /
cuda-baseline-single-gpu-multi-pass | 470.434 | 0.672 | 0.237 | 469.525 | 470.344 | / | /
cuda-32-1-single-gpu-multi-pass | 507.999 | 0.69 | 0.247 | 507.062 | 507.909 | / | /
cuda-16-2-single-gpu-multi-pass | 563.111 | 0.673 | 0.247 | 562.191 | 563.027 | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | / | /


### webgraph_twitter

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **23.351** | **5.039** | **1.286** | **17.026** | **20.223** | **0.808** | **16.218**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **52.691** | **5.433** | **1.282** | **45.976** | **50.960** | **0.724** | **45.252**
cuda-baseline-hybrid-multi-gpu-multi-pass | 619.221 | 4.937 | 1.367 | 612.917 | 617.822 | 0.731 | 612.186
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-16-2-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-8-4-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **100.64** | **5.236** | **1.23** | **94.174** | **100.429** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **169.691** | **4.792** | **1.387** | **163.512** | **169.453** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | / | /


### webgraph_twitter/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **12.682** | **5.603** | **1.143** | **5.936** | **9.660** | **1.408** | **4.528**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **29.496** | **0.851** | **1.15** | **27.495** | **22.756** | **1.393** | **26.102**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.777 | 1.166 | / | / | 1.491 | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-16-2-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-8-4-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **30.843** | **6.137** | **1.254** | **23.452** | **30.642** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **53.694** | **5.327** | **1.224** | **47.143** | **53.490** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | / | /


### webgraph_webbase

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **16.509** | **0.87** | **0.396** | **15.243** | **13.320** | **0.794** | **14.449**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **0.852** | **/**
cuda-baseline-hybrid-multi-gpu-multi-pass | 11.899 | 0.849 | 0.412 | 10.638 | 9.456 | 0.787 | 9.851
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | 57.04 | 0.828 | 0.413 | 55.799 | 54.179 | 0.801 | 54.998
cuda-16-2-multi-gpu-multi-pass | 32.132 | 0.855 | 0.414 | 30.863 | 29.238 | 0.789 | 30.074
cuda-8-4-multi-gpu-multi-pass | 19.201 | 0.862 | 0.417 | 17.922 | 16.069 | 0.792 | 17.13
cuda-4-8-multi-gpu-multi-pass | 13.194 | 0.836 | 0.397 | 11.961 | 10.193 | 0.816 | 11.145
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **89.941** | **0.893** | **0.398** | **88.650** | **89.533** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 18.282 | 0.966 | 0.41 | 16.906 | 17.895 | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 441.235 | 0.959 | 0.41 | 439.866 | 440.832 | / | /
cuda-16-2-single-gpu-multi-pass | 226.136 | 0.975 | 0.402 | 224.759 | 225.699 | / | /
cuda-8-4-single-gpu-multi-pass | 120.043 | 0.962 | 0.414 | 118.667 | 119.652 | / | /
cuda-4-8-single-gpu-multi-pass | 68.5 | 0.964 | 0.411 | 67.125 | 68.013 | / | /


### webgraph_webbase/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **12.811** | **0.655** | **0.878** | **11.278** | **9.827** | **1.422** | **9.856**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **1.414** | **/**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.497 | 0.873 | / | / | 1.467 | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-16-2-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-8-4-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-4-8-multi-gpu-multi-pass | / | / | / | / | / | / | /
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **12.898** | **1.82** | **0.885** | **10.193** | **12.369** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 27.478 | 1.971 | 0.891 | 24.616 | 27.058 | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-16-2-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-8-4-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-4-8-single-gpu-multi-pass | / | / | / | / | / | / | /


### lfr_dataset

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **3.308** | **0.755** | **0.123** | **2.430** | **3.109** | **0.066** | **2.364**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **3.442** | **0.757** | **0.122** | **2.563** | **3.053** | **0.064** | **2.499**
cuda-baseline-hybrid-multi-gpu-multi-pass | 5.975 | 0.78 | 0.125 | 5.070 | 5.828 | 0.061 | 5.009
cuda-baseline-multi-gpu-multi-pass | 6.014 | 0.774 | 0.16 | 5.080 | 5.784 | 0.063 | 5.017
cuda-32-1-multi-gpu-multi-pass | 3.968 | 0.761 | 0.131 | 3.076 | 3.619 | 0.065 | 3.011
cuda-16-2-multi-gpu-multi-pass | 3.456 | 0.765 | 0.128 | 2.563 | 3.133 | 0.063 | 2.5
cuda-8-4-multi-gpu-multi-pass | 3.232 | 0.751 | 0.125 | 2.356 | 2.925 | 0.06 | 2.296
cuda-4-8-multi-gpu-multi-pass | 3.214 | 0.749 | 0.121 | 2.344 | 2.874 | 0.068 | 2.276
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.235** | **0.772** | **0.122** | **2.341** | **3.215** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.095** | **0.783** | **0.124** | **3.188** | **4.068** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 7.121 | 0.765 | 0.123 | 6.233 | 7.097 | / | /
cuda-baseline-single-gpu-multi-pass | 7.184 | 0.769 | 0.127 | 6.288 | 7.159 | / | /
cuda-32-1-single-gpu-multi-pass | 9.013 | 0.768 | 0.173 | 8.072 | 8.991 | / | /
cuda-16-2-single-gpu-multi-pass | 5.472 | 0.803 | 0.122 | 4.547 | 5.450 | / | /
cuda-8-4-single-gpu-multi-pass | 3.786 | 0.754 | 0.121 | 2.911 | 3.762 | / | /
cuda-4-8-single-gpu-multi-pass | 3.095 | 0.757 | 0.132 | 2.206 | 3.071 | / | /


### lfr_dataset/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.593** | **0.187** | **0.141** | **2.265** | **2.046** | **0.104** | **2.161**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.666** | **0.18** | **0.148** | **2.338** | **2.221** | **0.101** | **2.237**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.118 | 0.147 | / | / | 0.101 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.122 | 0.189 | / | / | 0.094 | /
cuda-32-1-multi-gpu-multi-pass | 2.846 | 0.181 | 0.145 | 2.520 | 2.298 | 0.102 | 2.418
cuda-16-2-multi-gpu-multi-pass | 2.49 | 0.186 | 0.143 | 2.161 | 1.969 | 0.092 | 2.069
cuda-8-4-multi-gpu-multi-pass | 2.687 | 0.18 | 0.142 | 2.365 | 2.139 | 0.094 | 2.271
cuda-4-8-multi-gpu-multi-pass | 2.67 | 0.177 | 0.14 | 2.353 | 2.076 | 0.093 | 2.26
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **2.976** | **0.705** | **0.121** | **2.150** | **2.950** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.787** | **0.693** | **0.123** | **2.971** | **3.758** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 6.395 | 0.75 | 0.13 | 5.515 | 6.374 | / | /
cuda-baseline-single-gpu-multi-pass | 6.351 | 0.683 | 0.124 | 5.544 | 6.331 | / | /
cuda-32-1-single-gpu-multi-pass | 4.173 | 0.728 | 0.124 | 3.321 | 4.162 | / | /
cuda-16-2-single-gpu-multi-pass | 3.168 | 0.709 | 0.135 | 2.324 | 3.157 | / | /
cuda-8-4-single-gpu-multi-pass | 3.062 | 0.69 | 0.125 | 2.247 | 3.041 | / | /
cuda-4-8-single-gpu-multi-pass | 3.531 | 0.697 | 0.121 | 2.713 | 3.508 | / | /


### lfr_graphs/n2400000_k100_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **3.32** | **0.742** | **0.122** | **2.456** | **3.029** | **0.061** | **2.395**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **3.469** | **0.742** | **0.122** | **2.605** | **3.113** | **0.061** | **2.544**
cuda-baseline-hybrid-multi-gpu-multi-pass | 5.681 | 0.737 | 0.121 | 4.823 | 5.501 | 0.065 | 4.758
cuda-baseline-multi-gpu-multi-pass | 6.151 | 0.731 | 0.118 | 5.302 | 5.914 | 0.062 | 5.24
cuda-32-1-multi-gpu-multi-pass | 3.877 | 0.73 | 0.132 | 3.015 | 3.513 | 0.062 | 2.953
cuda-16-2-multi-gpu-multi-pass | 3.616 | 0.767 | 0.173 | 2.676 | 3.232 | 0.061 | 2.615
cuda-8-4-multi-gpu-multi-pass | 3.289 | 0.765 | 0.128 | 2.396 | 2.954 | 0.062 | 2.334
cuda-4-8-multi-gpu-multi-pass | 3.254 | 0.763 | 0.121 | 2.370 | 2.909 | 0.059 | 2.311
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.364** | **0.785** | **0.12** | **2.459** | **3.346** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.396** | **0.75** | **0.12** | **3.526** | **4.384** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 7.655 | 0.768 | 0.121 | 6.766 | 7.638 | / | /
cuda-baseline-single-gpu-multi-pass | 7.651 | 0.788 | 0.121 | 6.742 | 7.634 | / | /
cuda-32-1-single-gpu-multi-pass | 9.185 | 0.783 | 0.121 | 8.281 | 9.166 | / | /
cuda-16-2-single-gpu-multi-pass | 5.636 | 0.767 | 0.12 | 4.749 | 5.615 | / | /
cuda-8-4-single-gpu-multi-pass | 3.937 | 0.785 | 0.129 | 3.023 | 3.928 | / | /
cuda-4-8-single-gpu-multi-pass | 3.344 | 0.815 | 0.124 | 2.405 | 3.327 | / | /


### lfr_graphs/n2400000_k100_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.702** | **0.187** | **0.144** | **2.371** | **2.157** | **0.094** | **2.277**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.783** | **0.186** | **0.141** | **2.456** | **2.200** | **0.099** | **2.357**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.124 | 0.185 | / | / | 0.09 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.122 | 0.187 | / | / | 0.088 | /
cuda-32-1-multi-gpu-multi-pass | 2.785 | 0.171 | 0.141 | 2.473 | 2.332 | 0.09 | 2.383
cuda-16-2-multi-gpu-multi-pass | 2.696 | 0.192 | 0.17 | 2.334 | 2.123 | 0.092 | 2.242
cuda-8-4-multi-gpu-multi-pass | 2.596 | 0.179 | 0.143 | 2.274 | 2.085 | 0.091 | 2.183
cuda-4-8-multi-gpu-multi-pass | 2.628 | 0.183 | 0.137 | 2.308 | 2.048 | 0.083 | 2.225
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.612** | **0.732** | **0.183** | **2.697** | **3.594** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.0** | **0.681** | **0.12** | **3.199** | **3.976** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 7.144 | 0.69 | 0.13 | 6.324 | 7.125 | / | /
cuda-baseline-single-gpu-multi-pass | 7.083 | 0.702 | 0.121 | 6.260 | 7.062 | / | /
cuda-32-1-single-gpu-multi-pass | 4.694 | 0.694 | 0.119 | 3.881 | 4.675 | / | /
cuda-16-2-single-gpu-multi-pass | 3.447 | 0.689 | 0.12 | 2.638 | 3.439 | / | /
cuda-8-4-single-gpu-multi-pass | 3.209 | 0.67 | 0.119 | 2.420 | 3.189 | / | /
cuda-4-8-single-gpu-multi-pass | 3.746 | 0.693 | 0.121 | 2.932 | 3.730 | / | /


### lfr_graphs/n3000000_k80_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **3.253** | **0.763** | **0.125** | **2.365** | **2.981** | **0.058** | **2.307**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **3.499** | **0.773** | **0.165** | **2.561** | **3.174** | **0.067** | **2.494**
cuda-baseline-hybrid-multi-gpu-multi-pass | 5.856 | 0.763 | 0.124 | 4.969 | 5.616 | 0.071 | 4.898
cuda-baseline-multi-gpu-multi-pass | 6.1 | 0.729 | 0.124 | 5.247 | 5.924 | 0.065 | 5.182
cuda-32-1-multi-gpu-multi-pass | 4.113 | 0.767 | 0.138 | 3.208 | 3.687 | 0.066 | 3.142
cuda-16-2-multi-gpu-multi-pass | 3.331 | 0.746 | 0.122 | 2.463 | 2.990 | 0.063 | 2.4
cuda-8-4-multi-gpu-multi-pass | 3.274 | 0.77 | 0.122 | 2.382 | 2.954 | 0.061 | 2.321
cuda-4-8-multi-gpu-multi-pass | 3.23 | 0.771 | 0.122 | 2.337 | 2.871 | 0.06 | 2.277
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.229** | **0.767** | **0.125** | **2.337** | **3.199** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **4.201** | **0.788** | **0.131** | **3.282** | **4.173** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 7.15 | 0.777 | 0.124 | 6.249 | 7.126 | / | /
cuda-baseline-single-gpu-multi-pass | 7.179 | 0.761 | 0.122 | 6.296 | 7.155 | / | /
cuda-32-1-single-gpu-multi-pass | 8.837 | 0.771 | 0.147 | 7.919 | 8.813 | / | /
cuda-16-2-single-gpu-multi-pass | 5.422 | 0.752 | 0.124 | 4.546 | 5.399 | / | /
cuda-8-4-single-gpu-multi-pass | 3.826 | 0.783 | 0.121 | 2.922 | 3.805 | / | /
cuda-4-8-single-gpu-multi-pass | 3.431 | 0.816 | 0.124 | 2.491 | 3.407 | / | /


### lfr_graphs/n3000000_k80_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.566** | **0.186** | **0.144** | **2.236** | **1.994** | **0.102** | **2.134**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **3.471** | **0.188** | **0.142** | **3.141** | **3.015** | **0.097** | **3.044**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.118 | 0.146 | / | / | 0.095 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.115 | 0.145 | / | / | 0.09 | /
cuda-32-1-multi-gpu-multi-pass | 2.633 | 0.18 | 0.141 | 2.312 | 2.035 | 0.098 | 2.214
cuda-16-2-multi-gpu-multi-pass | 2.654 | 0.185 | 0.14 | 2.329 | 2.096 | 0.105 | 2.224
cuda-8-4-multi-gpu-multi-pass | 2.636 | 0.183 | 0.144 | 2.309 | 2.026 | 0.099 | 2.21
cuda-4-8-multi-gpu-multi-pass | 2.638 | 0.178 | 0.141 | 2.319 | 1.947 | 0.096 | 2.223
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.018** | **0.711** | **0.126** | **2.181** | **3.005** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.81** | **0.702** | **0.137** | **2.971** | **3.796** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 7.379 | 0.713 | 0.122 | 6.544 | 7.360 | / | /
cuda-baseline-single-gpu-multi-pass | 6.355 | 0.693 | 0.134 | 5.528 | 6.334 | / | /
cuda-32-1-single-gpu-multi-pass | 4.167 | 0.736 | 0.123 | 3.308 | 4.157 | / | /
cuda-16-2-single-gpu-multi-pass | 3.127 | 0.715 | 0.127 | 2.285 | 3.108 | / | /
cuda-8-4-single-gpu-multi-pass | 3.112 | 0.716 | 0.122 | 2.274 | 3.091 | / | /
cuda-4-8-single-gpu-multi-pass | 3.575 | 0.724 | 0.123 | 2.728 | 3.555 | / | /


### lfr_graphs/n4000000_k60_C0dot1_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **3.247** | **0.738** | **0.13** | **2.379** | **2.937** | **0.073** | **2.306**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **3.405** | **0.799** | **0.132** | **2.474** | **3.136** | **0.065** | **2.409**
cuda-baseline-hybrid-multi-gpu-multi-pass | 5.962 | 0.752 | 0.131 | 5.079 | 5.358 | 0.079 | 5.0
cuda-baseline-multi-gpu-multi-pass | 7.036 | 0.779 | 0.143 | 6.114 | 6.722 | 0.072 | 6.042
cuda-32-1-multi-gpu-multi-pass | 3.878 | 0.756 | 0.144 | 2.978 | 3.492 | 0.067 | 2.911
cuda-16-2-multi-gpu-multi-pass | 3.533 | 0.806 | 0.128 | 2.599 | 3.187 | 0.068 | 2.531
cuda-8-4-multi-gpu-multi-pass | 3.359 | 0.786 | 0.131 | 2.442 | 3.011 | 0.077 | 2.365
cuda-4-8-multi-gpu-multi-pass | 3.371 | 0.796 | 0.132 | 2.443 | 2.979 | 0.071 | 2.372
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.07** | **0.777** | **0.134** | **2.159** | **3.043** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.767** | **0.777** | **0.13** | **2.860** | **3.732** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 6.658 | 0.769 | 0.133 | 5.756 | 6.644 | / | /
cuda-baseline-single-gpu-multi-pass | 6.667 | 0.772 | 0.132 | 5.763 | 6.639 | / | /
cuda-32-1-single-gpu-multi-pass | 8.522 | 0.774 | 0.13 | 7.618 | 8.493 | / | /
cuda-16-2-single-gpu-multi-pass | 5.262 | 0.833 | 0.13 | 4.299 | 5.233 | / | /
cuda-8-4-single-gpu-multi-pass | 3.761 | 0.761 | 0.146 | 2.854 | 3.730 | / | /
cuda-4-8-single-gpu-multi-pass | 3.158 | 0.797 | 0.166 | 2.195 | 3.129 | / | /


### lfr_graphs/n4000000_k60_C0dot1_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.65** | **0.183** | **0.151** | **2.316** | **2.053** | **0.129** | **2.187**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.779** | **0.191** | **0.148** | **2.440** | **2.276** | **0.117** | **2.323**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.12 | 0.165 | / | / | 0.107 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.116 | 0.152 | / | / | 0.122 | /
cuda-32-1-multi-gpu-multi-pass | 2.718 | 0.185 | 0.149 | 2.384 | 2.214 | 0.109 | 2.275
cuda-16-2-multi-gpu-multi-pass | 2.598 | 0.185 | 0.196 | 2.217 | 2.074 | 0.115 | 2.102
cuda-8-4-multi-gpu-multi-pass | 2.638 | 0.19 | 0.153 | 2.295 | 1.961 | 0.119 | 2.176
cuda-4-8-multi-gpu-multi-pass | 2.73 | 0.184 | 0.15 | 2.396 | 2.058 | 0.111 | 2.285
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **2.748** | **0.684** | **0.133** | **1.931** | **2.721** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.406** | **0.73** | **0.13** | **2.546** | **3.388** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 5.61 | 0.706 | 0.17 | 4.734 | 5.579 | / | /
cuda-baseline-single-gpu-multi-pass | 5.534 | 0.697 | 0.129 | 4.708 | 5.507 | / | /
cuda-32-1-single-gpu-multi-pass | 3.73 | 0.746 | 0.132 | 2.852 | 3.704 | / | /
cuda-16-2-single-gpu-multi-pass | 2.938 | 0.708 | 0.129 | 2.101 | 2.917 | / | /
cuda-8-4-single-gpu-multi-pass | 2.82 | 0.723 | 0.133 | 1.964 | 2.792 | / | /
cuda-4-8-single-gpu-multi-pass | 3.433 | 0.731 | 0.13 | 2.572 | 3.405 | / | /


### lfr_graphs/n4000000_k60_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **3.364** | **0.758** | **0.129** | **2.477** | **3.004** | **0.066** | **2.411**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **3.431** | **0.762** | **0.128** | **2.541** | **3.157** | **0.061** | **2.48**
cuda-baseline-hybrid-multi-gpu-multi-pass | 5.815 | 0.752 | 0.134 | 4.929 | 5.553 | 0.071 | 4.858
cuda-baseline-multi-gpu-multi-pass | 5.926 | 0.764 | 0.131 | 5.031 | 5.707 | 0.077 | 4.954
cuda-32-1-multi-gpu-multi-pass | 3.862 | 0.758 | 0.133 | 2.971 | 3.485 | 0.066 | 2.905
cuda-16-2-multi-gpu-multi-pass | 3.513 | 0.773 | 0.13 | 2.610 | 3.171 | 0.079 | 2.531
cuda-8-4-multi-gpu-multi-pass | 3.343 | 0.819 | 0.13 | 2.394 | 2.993 | 0.07 | 2.324
cuda-4-8-multi-gpu-multi-pass | 3.36 | 0.78 | 0.13 | 2.450 | 3.047 | 0.071 | 2.379
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **3.015** | **0.798** | **0.128** | **2.089** | **2.985** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.767** | **0.765** | **0.133** | **2.869** | **3.736** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 6.68 | 0.773 | 0.134 | 5.773 | 6.649 | / | /
cuda-baseline-single-gpu-multi-pass | 6.584 | 0.812 | 0.133 | 5.639 | 6.569 | / | /
cuda-32-1-single-gpu-multi-pass | 8.53 | 0.787 | 0.131 | 7.612 | 8.498 | / | /
cuda-16-2-single-gpu-multi-pass | 5.174 | 0.771 | 0.129 | 4.274 | 5.144 | / | /
cuda-8-4-single-gpu-multi-pass | 3.615 | 0.76 | 0.13 | 2.725 | 3.591 | / | /
cuda-4-8-single-gpu-multi-pass | 3.042 | 0.768 | 0.143 | 2.131 | 3.023 | / | /


### lfr_graphs/n4000000_k60_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.695** | **0.185** | **0.152** | **2.358** | **2.059** | **0.128** | **2.23**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.697** | **0.184** | **0.149** | **2.364** | **2.178** | **0.126** | **2.238**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.12 | 0.158 | / | / | 0.115 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.123 | 0.149 | / | / | 0.121 | /
cuda-32-1-multi-gpu-multi-pass | 2.67 | 0.189 | 0.151 | 2.330 | 2.186 | 0.111 | 2.219
cuda-16-2-multi-gpu-multi-pass | 2.591 | 0.182 | 0.148 | 2.261 | 2.000 | 0.117 | 2.144
cuda-8-4-multi-gpu-multi-pass | 2.562 | 0.19 | 0.161 | 2.211 | 2.010 | 0.111 | 2.1
cuda-4-8-multi-gpu-multi-pass | 2.716 | 0.193 | 0.15 | 2.373 | 2.055 | 0.116 | 2.257
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **2.828** | **0.726** | **0.129** | **1.973** | **2.795** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.384** | **0.704** | **0.127** | **2.553** | **3.366** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 5.576 | 0.74 | 0.132 | 4.704 | 5.561 | / | /
cuda-baseline-single-gpu-multi-pass | 5.578 | 0.713 | 0.178 | 4.687 | 5.551 | / | /
cuda-32-1-single-gpu-multi-pass | 3.752 | 0.712 | 0.129 | 2.911 | 3.727 | / | /
cuda-16-2-single-gpu-multi-pass | 2.903 | 0.7 | 0.132 | 2.071 | 2.872 | / | /
cuda-8-4-single-gpu-multi-pass | 2.817 | 0.697 | 0.143 | 1.977 | 2.789 | / | /
cuda-4-8-single-gpu-multi-pass | 3.425 | 0.703 | 0.133 | 2.589 | 3.397 | / | /


### lfr_graphs/n6000000_k40_C0dot3_Bin

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **3.287** | **0.811** | **0.159** | **2.317** | **2.894** | **0.093** | **2.224**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **3.5** | **0.793** | **0.151** | **2.556** | **3.167** | **0.081** | **2.475**
cuda-baseline-hybrid-multi-gpu-multi-pass | 5.651 | 0.771 | 0.161 | 4.719 | 5.342 | 0.094 | 4.625
cuda-baseline-multi-gpu-multi-pass | 5.699 | 0.764 | 0.155 | 4.780 | 5.357 | 0.091 | 4.689
cuda-32-1-multi-gpu-multi-pass | 3.951 | 0.822 | 0.16 | 2.969 | 3.556 | 0.087 | 2.882
cuda-16-2-multi-gpu-multi-pass | 3.648 | 0.772 | 0.157 | 2.719 | 3.228 | 0.089 | 2.63
cuda-8-4-multi-gpu-multi-pass | 3.941 | 0.816 | 0.162 | 2.963 | 3.607 | 0.085 | 2.878
cuda-4-8-multi-gpu-multi-pass | 3.393 | 0.783 | 0.158 | 2.452 | 3.002 | 0.088 | 2.364
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **2.645** | **0.797** | **0.156** | **1.692** | **2.614** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.572** | **0.82** | **0.159** | **2.593** | **3.525** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 6.28 | 0.788 | 0.158 | 5.334 | 6.241 | / | /
cuda-baseline-single-gpu-multi-pass | 6.26 | 0.798 | 0.153 | 5.309 | 6.221 | / | /
cuda-32-1-single-gpu-multi-pass | 8.025 | 0.775 | 0.158 | 7.092 | 7.983 | / | /
cuda-16-2-single-gpu-multi-pass | 4.907 | 0.815 | 0.163 | 3.929 | 4.873 | / | /
cuda-8-4-single-gpu-multi-pass | 3.439 | 0.855 | 0.153 | 2.431 | 3.418 | / | /
cuda-4-8-single-gpu-multi-pass | 2.839 | 0.81 | 0.156 | 1.873 | 2.818 | / | /


### lfr_graphs/n6000000_k40_C0dot3_Bin/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **2.704** | **0.188** | **0.178** | **2.338** | **2.106** | **0.152** | **2.186**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **2.824** | **0.19** | **0.174** | **2.460** | **2.244** | **0.145** | **2.315**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 0.123 | 0.191 | / | / | 0.16 | /
cuda-baseline-multi-gpu-multi-pass | / | 0.129 | 0.205 | / | / | 0.148 | /
cuda-32-1-multi-gpu-multi-pass | 2.83 | 0.2 | 0.177 | 2.453 | 2.243 | 0.147 | 2.306
cuda-16-2-multi-gpu-multi-pass | 2.57 | 0.188 | 0.181 | 2.201 | 1.887 | 0.148 | 2.053
cuda-8-4-multi-gpu-multi-pass | 2.722 | 0.193 | 0.216 | 2.313 | 1.973 | 0.161 | 2.152
cuda-4-8-multi-gpu-multi-pass | 2.688 | 0.188 | 0.209 | 2.291 | 1.983 | 0.146 | 2.145
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **2.503** | **0.749** | **0.159** | **1.595** | **2.480** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **3.214** | **0.736** | **0.154** | **2.324** | **3.185** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 4.712 | 0.735 | 0.159 | 3.818 | 4.673 | / | /
cuda-baseline-single-gpu-multi-pass | 4.718 | 0.72 | 0.159 | 3.839 | 4.682 | / | /
cuda-32-1-single-gpu-multi-pass | 3.225 | 0.729 | 0.159 | 2.337 | 3.204 | / | /
cuda-16-2-single-gpu-multi-pass | 2.75 | 0.725 | 0.156 | 1.869 | 2.711 | / | /
cuda-8-4-single-gpu-multi-pass | 2.79 | 0.712 | 0.154 | 1.924 | 2.751 | / | /
cuda-4-8-single-gpu-multi-pass | 3.385 | 0.737 | 0.158 | 2.490 | 3.348 | / | /


### n12dot5_m80_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.068** | **8.352** | **1.975** | **6.741** | **14.238** | **0.617** | **6.124**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **17.619** | **8.788** | **1.981** | **6.850** | **14.718** | **0.64** | **6.21**
cuda-baseline-hybrid-multi-gpu-multi-pass | 599.355 | 8.231 | 1.971 | 589.153 | 597.177 | 0.604 | 588.549
cuda-baseline-multi-gpu-multi-pass | 570.159 | 8.866 | 1.926 | 559.367 | 566.411 | 0.571 | 558.796
cuda-32-1-multi-gpu-multi-pass | 46.153 | 9.323 | 1.951 | 34.879 | 43.595 | 0.595 | 34.284
cuda-16-2-multi-gpu-multi-pass | 54.572 | 9.126 | 2.013 | 43.433 | 51.811 | 0.63 | 42.803
cuda-8-4-multi-gpu-multi-pass | 73.846 | 8.311 | 2.003 | 63.532 | 71.228 | 0.606 | 62.926
cuda-4-8-multi-gpu-multi-pass | 115.789 | 8.424 | 1.934 | 105.431 | 113.041 | 0.582 | 104.849
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **25.191** | **8.661** | **1.996** | **14.534** | **25.145** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **25.156** | **9.268** | **1.985** | **13.903** | **25.072** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 70.955 | 9.097 | 2.008 | 59.850 | 70.910 | / | /
cuda-16-2-single-gpu-multi-pass | 67.255 | 8.966 | 1.937 | 56.352 | 67.175 | / | /
cuda-8-4-single-gpu-multi-pass | 86.764 | 8.591 | 1.973 | 76.200 | 86.688 | / | /
cuda-4-8-single-gpu-multi-pass | 139.253 | 8.271 | 1.987 | 128.995 | 139.207 | / | /


### n12dot5_m80_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **16.79** | **1.56** | **1.932** | **13.298** | **13.102** | **1.591** | **11.707**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **16.829** | **1.58** | **1.928** | **13.321** | **12.905** | **1.662** | **11.659**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 1.52 | 2.014 | / | / | 1.561 | /
cuda-baseline-multi-gpu-multi-pass | / | 1.508 | 2.021 | / | / | 1.711 | /
cuda-32-1-multi-gpu-multi-pass | 41.517 | 1.584 | 2.007 | 37.926 | 37.749 | 1.595 | 36.331
cuda-16-2-multi-gpu-multi-pass | 50.217 | 1.872 | 1.923 | 46.422 | 46.899 | 1.452 | 44.97
cuda-8-4-multi-gpu-multi-pass | 70.594 | 2.195 | 2.011 | 66.388 | 66.843 | 1.687 | 64.701
cuda-4-8-multi-gpu-multi-pass | 114.237 | 2.192 | 1.97 | 110.075 | 110.282 | 1.656 | 108.419
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **24.644** | **8.41** | **1.971** | **14.263** | **24.566** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **25.618** | **8.615** | **1.952** | **15.051** | **25.531** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 70.124 | 8.706 | 2.002 | 59.416 | 70.045 | / | /
cuda-16-2-single-gpu-multi-pass | 67.423 | 8.395 | 1.972 | 57.056 | 67.350 | / | /
cuda-8-4-single-gpu-multi-pass | 88.348 | 8.842 | 1.968 | 77.538 | 88.267 | / | /
cuda-4-8-single-gpu-multi-pass | 139.344 | 8.214 | 2.002 | 129.128 | 139.261 | / | /


### n16dot7_m60_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.435** | **8.195** | **2.358** | **6.882** | **14.971** | **0.771** | **6.111**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **17.599** | **8.138** | **2.345** | **7.116** | **15.029** | **0.755** | **6.361**
cuda-baseline-hybrid-multi-gpu-multi-pass | 461.99 | 8.585 | 2.304 | 451.101 | 461.167 | 0.762 | 450.339
cuda-baseline-multi-gpu-multi-pass | 444.018 | 8.392 | 2.335 | 433.291 | 440.585 | 0.788 | 432.503
cuda-32-1-multi-gpu-multi-pass | 47.849 | 8.351 | 2.317 | 37.181 | 44.701 | 0.802 | 36.379
cuda-16-2-multi-gpu-multi-pass | 57.83 | 8.117 | 2.302 | 47.411 | 54.792 | 0.754 | 46.657
cuda-8-4-multi-gpu-multi-pass | 81.191 | 8.769 | 2.313 | 70.109 | 78.409 | 0.767 | 69.342
cuda-4-8-multi-gpu-multi-pass | 127.04 | 8.933 | 2.292 | 115.815 | 124.123 | 0.771 | 115.044
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **23.281** | **8.579** | **2.325** | **12.377** | **23.179** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **22.767** | **8.215** | **2.356** | **12.196** | **22.654** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 64.446 | 8.734 | 2.3 | 53.412 | 64.347 | / | /
cuda-16-2-single-gpu-multi-pass | 66.704 | 8.266 | 2.35 | 56.088 | 66.615 | / | /
cuda-8-4-single-gpu-multi-pass | 89.631 | 8.481 | 2.319 | 78.831 | 89.541 | / | /
cuda-4-8-single-gpu-multi-pass | 140.276 | 9.032 | 2.318 | 128.926 | 140.175 | / | /


### n16dot7_m60_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.465** | **1.627** | **2.334** | **13.504** | **13.276** | **1.832** | **11.672**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **17.677** | **1.593** | **2.31** | **13.774** | **13.497** | **1.839** | **11.935**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 1.547 | 2.381 | / | / | 1.88 | /
cuda-baseline-multi-gpu-multi-pass | / | 1.542 | 2.365 | / | / | 1.873 | /
cuda-32-1-multi-gpu-multi-pass | 43.803 | 1.611 | 2.309 | 39.883 | 39.796 | 1.845 | 38.038
cuda-16-2-multi-gpu-multi-pass | 54.263 | 2.071 | 2.338 | 49.854 | 50.152 | 2.008 | 47.846
cuda-8-4-multi-gpu-multi-pass | 76.362 | 2.271 | 2.34 | 71.751 | 72.046 | 1.949 | 69.802
cuda-4-8-multi-gpu-multi-pass | 122.645 | 2.203 | 2.343 | 118.099 | 118.425 | 1.9 | 116.199
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **22.596** | **8.84** | **2.34** | **11.416** | **22.495** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **23.485** | **8.22** | **2.296** | **12.969** | **23.371** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 63.79 | 7.994 | 2.311 | 53.485 | 63.690 | / | /
cuda-16-2-single-gpu-multi-pass | 67.909 | 8.804 | 2.299 | 56.806 | 67.810 | / | /
cuda-8-4-single-gpu-multi-pass | 89.533 | 8.425 | 2.357 | 78.751 | 89.433 | / | /
cuda-4-8-single-gpu-multi-pass | 143.544 | 8.514 | 2.302 | 132.728 | 143.446 | / | /


### n25_m40_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **18.432** | **8.111** | **2.788** | **7.533** | **16.377** | **1.017** | **6.516**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **19.436** | **8.629** | **2.679** | **8.128** | **17.205** | **1.011** | **7.117**
cuda-baseline-hybrid-multi-gpu-multi-pass | 318.547 | 8.124 | 2.7 | 307.723 | 317.435 | 1.024 | 306.699
cuda-baseline-multi-gpu-multi-pass | 309.508 | 8.204 | 2.686 | 298.618 | 304.697 | 0.978 | 297.64
cuda-32-1-multi-gpu-multi-pass | 45.422 | 8.034 | 2.69 | 34.698 | 42.329 | 1.009 | 33.689
cuda-16-2-multi-gpu-multi-pass | 55.591 | 7.991 | 2.682 | 44.918 | 52.297 | 1.008 | 43.91
cuda-8-4-multi-gpu-multi-pass | 77.515 | 8.526 | 2.718 | 66.271 | 74.188 | 1.089 | 65.182
cuda-4-8-multi-gpu-multi-pass | 122.492 | 8.137 | 2.662 | 111.693 | 119.233 | 1.007 | 110.686
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **21.658** | **8.137** | **2.704** | **10.817** | **21.518** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **28.647** | **7.982** | **2.741** | **17.924** | **28.496** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 57.451 | 8.508 | 2.704 | 46.239 | 57.318 | / | /
cuda-16-2-single-gpu-multi-pass | 61.669 | 7.951 | 2.696 | 51.022 | 61.539 | / | /
cuda-8-4-single-gpu-multi-pass | 83.443 | 7.609 | 2.68 | 73.154 | 83.308 | / | /
cuda-4-8-single-gpu-multi-pass | 131.98 | 7.85 | 2.692 | 121.438 | 131.869 | / | /


### n25_m40_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **18.189** | **1.44** | **2.69** | **14.059** | **13.976** | **2.174** | **11.885**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **18.681** | **1.591** | **2.696** | **14.394** | **14.789** | **2.171** | **12.223**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | 1.596 | 2.725 | / | / | 2.105 | /
cuda-baseline-multi-gpu-multi-pass | / | 1.586 | 2.744 | / | / | 2.128 | /
cuda-32-1-multi-gpu-multi-pass | 41.602 | 1.643 | 2.709 | 37.250 | 37.251 | 2.251 | 34.999
cuda-16-2-multi-gpu-multi-pass | 51.843 | 2.004 | 2.685 | 47.154 | 47.437 | 2.182 | 44.972
cuda-8-4-multi-gpu-multi-pass | 72.874 | 2.301 | 2.65 | 67.923 | 68.862 | 2.145 | 65.778
cuda-4-8-multi-gpu-multi-pass | 117.699 | 2.265 | 2.732 | 112.702 | 113.421 | 2.247 | 110.455
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **21.051** | **8.427** | **2.7** | **9.924** | **20.935** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **28.912** | **8.078** | **2.687** | **18.147** | **28.751** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 61.526 | 1.789 | 2.743 | 56.994 | 61.393 | / | /
cuda-16-2-single-gpu-multi-pass | 65.718 | 1.774 | 2.716 | 61.228 | 65.579 | / | /
cuda-8-4-single-gpu-multi-pass | 87.059 | 1.727 | 2.674 | 82.658 | 86.919 | / | /
cuda-4-8-single-gpu-multi-pass | 136.591 | 1.767 | 2.717 | 132.107 | 136.488 | / | /


### n50_m20_1billion_edge

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.353** | **7.671** | **3.163** | **6.519** | **15.462** | **1.398** | **5.121**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **91.067** | **1.913** | **3.214** | **85.940** | **89.326** | **1.413** | **84.527**
cuda-baseline-hybrid-multi-gpu-multi-pass | 171.943 | 7.695 | 3.215 | 161.033 | 170.380 | 1.396 | 159.637
cuda-baseline-multi-gpu-multi-pass | 164.363 | 7.33 | 3.052 | 153.981 | 160.363 | 1.266 | 152.715
cuda-32-1-multi-gpu-multi-pass | 42.382 | 7.435 | 3.186 | 31.761 | 38.763 | 2.579 | 29.182
cuda-16-2-multi-gpu-multi-pass | 58.304 | 8.182 | 3.17 | 46.952 | 54.476 | 1.399 | 45.553
cuda-8-4-multi-gpu-multi-pass | 80.657 | 7.733 | 3.197 | 69.727 | 77.047 | 1.418 | 68.309
cuda-4-8-multi-gpu-multi-pass | 129.122 | 8.34 | 3.216 | 117.566 | 125.278 | 1.425 | 116.141
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **20.529** | **7.979** | **3.244** | **9.306** | **20.318** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **369.169** | **8.202** | **3.213** | **357.754** | **368.912** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | 532.855 | 7.749 | 3.114 | 521.992 | 532.638 | / | /
cuda-baseline-single-gpu-multi-pass | 582.274 | 8.06 | 3.2 | 571.014 | 582.085 | / | /
cuda-32-1-single-gpu-multi-pass | 51.612 | 8.011 | 3.202 | 40.399 | 51.413 | / | /
cuda-16-2-single-gpu-multi-pass | 60.186 | 7.745 | 3.233 | 49.208 | 59.986 | / | /
cuda-8-4-single-gpu-multi-pass | 83.83 | 7.312 | 3.24 | 73.278 | 83.619 | / | /
cuda-4-8-single-gpu-multi-pass | 132.484 | 7.89 | 3.188 | 121.406 | 132.277 | / | /


### n50_m20_1billion_edge/rev_deg

file-name | Core-Checking Time (Both) | bin-search cost (CPU) | sim-cal-cost (CPU) | Real Comp & Data Transfer Time (GPU) | Remove Data-Transfer Time (Both) | Task Init Time | Real GPU Time Removing Task Init (GPU)
--- | --- | --- | --- | --- | --- | --- | ---
**cuda-bitmap-warp-per-vertex-multi-gpu-multi-pass** | **17.512** | **1.428** | **3.198** | **12.886** | **14.776** | **2.519** | **10.367**
**cuda-bitmap-kernel-multi-gpu-multi-pass** | **99.679** | **1.841** | **3.299** | **94.539** | **96.834** | **2.645** | **91.894**
cuda-baseline-hybrid-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-multi-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-multi-gpu-multi-pass | 42.478 | 1.718 | 3.199 | 37.561 | 37.730 | 2.549 | 35.012
cuda-16-2-multi-gpu-multi-pass | 54.074 | 1.85 | 3.13 | 49.094 | 49.370 | 2.539 | 46.555
cuda-8-4-multi-gpu-multi-pass | 78.003 | 2.228 | 3.19 | 72.585 | 73.304 | 2.67 | 69.915
cuda-4-8-multi-gpu-multi-pass | 125.128 | 2.081 | 3.192 | 119.855 | 119.771 | 2.575 | 117.28
**cuda-bitmap-warp-per-vertex-single-gpu-multi-pass** | **24.602** | **1.785** | **3.151** | **19.666** | **24.381** | **/** | **/**
**cuda-bitmap-kernel-single-gpu-multi-pass** | **/** | **/** | **/** | **/** | **/** | **/** | **/**
cuda-baseline-hybrid-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-baseline-single-gpu-multi-pass | / | / | / | / | / | / | /
cuda-32-1-single-gpu-multi-pass | 56.822 | 1.822 | 3.206 | 51.794 | 56.608 | / | /
cuda-16-2-single-gpu-multi-pass | 66.474 | 1.764 | 3.203 | 61.507 | 66.253 | / | /
cuda-8-4-single-gpu-multi-pass | 89.131 | 1.795 | 3.18 | 84.156 | 88.868 | / | /
cuda-4-8-single-gpu-multi-pass | 138.82 | 1.819 | 3.214 | 133.787 | 138.609 | / | /