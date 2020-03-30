# O(E) intersection count time


Unit: seconds


### snap_livejournal

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_livejournal/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-merge` | 0.000 | 0.382 | 0.124 | 0.506 | 874,536 | 955,500
`avx2-hybrid` | 0.000 | 0.392 | 0.111 | 0.503 | 874,028 | 948,900
`naive-bitvec-2d` | 0.000 | 0.454 | 0.146 | 0.6 | 798,172 | 1,035,532
`naive-bitvec` | 0.000 | 0.466 | 0.139 | 0.605 | 798,624 | 1,045,092
avx2-lemire | 0.000 | 0.524 | 0.127 | 0.651 | 896,940 | 978,180
sse-lemire | 0.000 | 0.559 | 0.133 | 0.692 | 896,928 | 976,708
**sse-han-bsr-scalar-galloping** | 5.058 | 0.586 | 0.125 | 5.769 | 1,474,904 | 1,602,628
**sse-han-bsr-sse-galloping** | 5.011 | 0.596 | 0.126 | 5.733 | 1,484,952 | 1,594,828
tetzank-avx2-asm | 0.000 | 0.662 | 0.138 | 0.8 | 897,224 | 976,676
`avx2-galloping-single` | 0.000 | 0.670 | 0.127 | 0.797 | 874,720 | 949,932
**sse-emptyheaded-layout-hybrid** | 3.13 | 0.698 | 0.117 | 3.945 | 1,297,384 | 1,414,708
**sse-emptyheaded-layout-uint** | 2.424 | 0.703 | 0.123 | 3.25 | 1,297,060 | 1,415,088
**sse-han-bsr-scalar-merge** | 4.794 | 0.718 | 0.133 | 5.645 | 1,498,068 | 1,608,928
**sse-han-bsr-qfilter** | 4.749 | 0.747 | 0.114 | 5.61 | 1,460,300 | 1,570,972
tetzank-avx | 0.000 | 0.863 | 0.125 | 0.988 | 898,412 | 974,944
tetzank-avx2 | 0.000 | 0.908 | 0.129 | 1.037 | 894,712 | 974,416
sse-han-bmiss-sttni | 0.000 | 0.935 | 0.139 | 1.074 | 854,324 | 934,880
**sse-han-bsr-sse-shuffle** | 4.843 | 1.010 | 0.118 | 5.971 | 1,473,388 | 1,590,000
sse-bm-lemire | 0.000 | 1.014 | 0.129 | 1.143 | 897,672 | 975,760
sse-han-qfilter | 0.000 | 1.233 | 0.132 | 1.365 | 866,360 | 943,512
sse-han-bmiss | 0.000 | 1.909 | 0.134 | 2.043 | 856,036 | 933,580
**avx2-roaring** | 9.229 | 6.684 | 0.131 | 16.044 | 2,486,084 | 1,701,864
**sse-roaring** | 8.192 | 7.110 | 0.129 | 15.431 | 2,479,224 | 1,527,820


### snap_livejournal/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-merge` | 0.000 | 0.406 | 0.152 | 0.558 | 874,972 | 956,168
`avx2-hybrid` | 0.000 | 0.420 | 0.156 | 0.576 | 875,412 | 954,992
avx2-lemire | 0.000 | 0.546 | 0.149 | 0.695 | 885,236 | 964,184
sse-lemire | 0.000 | 0.602 | 0.165 | 0.767 | 885,924 | 966,948
tetzank-avx2-asm | 0.000 | 0.708 | 0.16 | 0.868 | 887,388 | 966,144
`avx2-galloping-single` | 0.000 | 0.748 | 0.152 | 0.9 | 872,944 | 955,544
tetzank-avx2 | 0.000 | 0.751 | 0.151 | 0.902 | 884,924 | 969,500
**sse-emptyheaded-layout-uint** | 3.011 | 0.783 | 0.148 | 3.942 | 1,281,240 | 1,399,072
`naive-bitvec-2d` | 0.000 | 0.792 | 0.17 | 0.962 | 800,872 | 1,050,100
**sse-emptyheaded-layout-hybrid** | 2.684 | 0.817 | 0.167 | 3.668 | 1,283,460 | 1,396,852
tetzank-avx | 0.000 | 0.846 | 0.161 | 1.007 | 885,960 | 967,236
**sse-han-bsr-sse-galloping** | 4.681 | 0.932 | 0.148 | 5.761 | 1,472,700 | 1,620,716
sse-bm-lemire | 0.000 | 0.971 | 0.151 | 1.122 | 883,916 | 968,352
**sse-han-bsr-scalar-galloping** | 4.702 | 0.976 | 0.159 | 5.837 | 1,474,420 | 1,617,976
sse-han-bmiss-sttni | 0.000 | 1.030 | 0.157 | 1.187 | 878,032 | 958,672
**sse-han-bsr-scalar-merge** | 4.738 | 1.168 | 0.153 | 6.059 | 1,472,064 | 1,619,608
sse-han-qfilter | 0.000 | 1.228 | 0.146 | 1.374 | 876,368 | 957,304
**sse-han-bsr-qfilter** | 4.74 | 1.356 | 0.149 | 6.245 | 1,473,860 | 1,619,368
**sse-han-bsr-sse-shuffle** | 4.77 | 1.729 | 0.142 | 6.641 | 1,471,720 | 1,619,328
sse-han-bmiss | 0.000 | 1.847 | 0.151 | 1.998 | 873,236 | 955,440
`naive-bitvec` | 0.000 | 3.849 | 0.158 | 4.007 | 810,732 | 1,047,316
**avx2-roaring** | 18.411 | 13.928 | 0.16 | 32.499 | 3,785,568 | 929,396
**sse-roaring** | 18.886 | 14.053 | 0.158 | 33.097 | 3,770,380 | 1,159,016


### snap_livejournal/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_livejournal/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_livejournal/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-merge` | 0.000 | 0.427 | 0.154 | 0.581 | 1,712,500 | 2,204,596
`avx2-hybrid` | 0.000 | 0.446 | 0.154 | 0.6 | 1,667,676 | 2,124,780
`naive-bitvec-2d` | 0.000 | 0.498 | 0.168 | 0.666 | 799,276 | 1,312,400
avx2-lemire | 0.000 | 0.556 | 0.156 | 0.712 | 1,663,920 | 2,133,652
sse-lemire | 0.000 | 0.603 | 0.153 | 0.756 | 1,667,512 | 2,133,864
`naive-bitvec` | 0.000 | 0.642 | 0.154 | 0.796 | 798,428 | 1,266,024
tetzank-avx2-asm | 0.000 | 0.690 | 0.148 | 0.838 | 1,668,016 | 2,126,984
`avx2-galloping-single` | 0.000 | 0.746 | 0.172 | 0.918 | 1,667,444 | 2,132,996
**sse-emptyheaded-layout-hybrid** | 3.167 | 0.768 | 0.156 | 4.091 | 1,640,912 | 2,218,144
**sse-emptyheaded-layout-uint** | 2.493 | 0.772 | 0.127 | 3.392 | 1,646,528 | 2,188,560
tetzank-avx2 | 0.000 | 0.772 | 0.159 | 0.931 | 1,664,232 | 2,128,468
tetzank-avx | 0.000 | 0.834 | 0.168 | 1.002 | 1,733,664 | 2,177,336
**sse-han-bsr-sse-galloping** | 4.867 | 0.945 | 0.151 | 5.963 | 3,326,652 | 3,726,176
**sse-han-bsr-scalar-galloping** | 4.723 | 0.962 | 0.157 | 5.842 | 3,452,192 | 3,934,312
**sse-han-bsr-scalar-merge** | 4.64 | 1.064 | 0.148 | 5.852 | 3,452,768 | 3,948,756
sse-bm-lemire | 0.000 | 1.079 | 0.153 | 1.232 | 1,661,540 | 2,083,744
sse-han-bmiss-sttni | 0.000 | 1.085 | 0.15 | 1.235 | 1,696,864 | 2,176,596
**sse-han-bsr-qfilter** | 4.812 | 1.120 | 0.15 | 6.082 | 3,452,272 | 3,926,112
sse-han-qfilter | 0.000 | 1.291 | 0.153 | 1.444 | 1,672,248 | 2,128,840
**sse-han-bsr-sse-shuffle** | 5.067 | 1.481 | 0.151 | 6.699 | 3,403,896 | 3,887,052
sse-han-bmiss | 0.000 | 1.941 | 0.152 | 2.093 | 1,669,924 | 2,132,920
**avx2-roaring** | 11.865 | 9.596 | 0.141 | 21.602 | 4,075,776 | 3,261,956
**sse-roaring** | 13.422 | 10.301 | 0.143 | 23.866 | 3,961,212 | 3,067,860


### snap_livejournal/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 0.458 | 0.145 | 0.603 | 1,724,612 | 2,237,800
`avx2-merge` | 0.000 | 0.473 | 0.145 | 0.618 | 1,667,992 | 2,146,016
avx2-lemire | 0.000 | 0.561 | 0.152 | 0.713 | 1,730,868 | 2,235,088
sse-lemire | 0.000 | 0.608 | 0.146 | 0.754 | 1,663,548 | 2,129,072
tetzank-avx2-asm | 0.000 | 0.702 | 0.147 | 0.849 | 1,667,296 | 2,130,600
`avx2-galloping-single` | 0.000 | 0.752 | 0.146 | 0.898 | 1,667,560 | 2,135,444
**sse-emptyheaded-layout-hybrid** | 3.105 | 0.772 | 0.139 | 4.016 | 1,630,476 | 2,187,036
**sse-emptyheaded-layout-uint** | 2.813 | 0.790 | 0.144 | 3.747 | 1,632,212 | 2,179,304
tetzank-avx2 | 0.000 | 0.797 | 0.138 | 0.935 | 1,665,212 | 2,142,124
`naive-bitvec-2d` | 0.000 | 0.812 | 0.175 | 0.987 | 801,116 | 1,212,148
tetzank-avx | 0.000 | 0.873 | 0.148 | 1.021 | 1,666,204 | 2,120,912
**sse-han-bsr-sse-galloping** | 4.734 | 0.873 | 0.146 | 5.753 | 3,294,776 | 3,609,388
**sse-han-bsr-scalar-galloping** | 4.644 | 0.914 | 0.141 | 5.699 | 3,358,520 | 3,771,884
sse-bm-lemire | 0.000 | 0.967 | 0.15 | 1.117 | 1,663,780 | 2,142,520
sse-han-bmiss-sttni | 0.000 | 1.076 | 0.144 | 1.22 | 1,709,244 | 2,199,772
**sse-han-bsr-scalar-merge** | 4.686 | 1.094 | 0.139 | 5.919 | 3,442,596 | 3,929,896
sse-han-qfilter | 0.000 | 1.221 | 0.146 | 1.367 | 1,663,124 | 2,121,912
**sse-han-bsr-qfilter** | 5.064 | 1.255 | 0.14 | 6.459 | 3,455,672 | 3,971,240
`naive-bitvec` | 0.000 | 1.373 | 0.155 | 1.528 | 830,564 | 1,351,300
**sse-han-bsr-sse-shuffle** | 4.872 | 1.516 | 0.149 | 6.537 | 3,455,212 | 3,969,468
sse-han-bmiss | 0.000 | 1.876 | 0.144 | 2.02 | 1,667,384 | 2,128,228
**avx2-roaring** | 10.893 | 9.174 | 0.139 | 20.206 | 3,840,224 | 2,820,472
**sse-roaring** | 11.727 | 9.448 | 0.134 | 21.309 | 3,780,332 | 2,670,024


### snap_orkut

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_orkut/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 2.682 | 0.346 | 3.028 | 2,119,264 | 2,158,432
`avx2-merge` | 0.000 | 2.725 | 0.355 | 3.08 | 2,119,604 | 2,168,160
`naive-bitvec-2d` | 0.000 | 3.275 | 0.386 | 3.661 | 2,209,548 | 2,245,720
tetzank-avx2-asm | 0.000 | 3.746 | 0.366 | 4.112 | 2,141,892 | 2,161,876
avx2-lemire | 0.000 | 3.893 | 0.351 | 4.244 | 2,118,324 | 2,151,352
sse-lemire | 0.000 | 4.290 | 0.329 | 4.619 | 2,116,008 | 2,154,164
**sse-han-bsr-sse-galloping** | 13.343 | 4.529 | 0.342 | 18.214 | 4,028,264 | 4,076,308
tetzank-avx2 | 0.000 | 4.540 | 0.352 | 4.892 | 2,116,696 | 2,152,336
**sse-han-bsr-scalar-galloping** | 13.3 | 4.691 | 0.35 | 18.341 | 4,029,212 | 4,076,044
`naive-bitvec` | 0.000 | 4.764 | 0.368 | 5.132 | 2,234,128 | 2,252,016
**sse-han-bsr-scalar-merge** | 13.638 | 4.888 | 0.389 | 18.915 | 4,034,360 | 4,075,976
`avx2-galloping-single` | 0.000 | 4.897 | 0.352 | 5.249 | 2,121,668 | 2,152,868
**sse-han-bsr-qfilter** | 14.367 | 5.066 | 0.35 | 19.783 | 4,048,292 | 4,066,684
tetzank-avx | 0.000 | 5.391 | 0.348 | 5.739 | 2,118,104 | 2,155,744
**sse-emptyheaded-layout-hybrid** | 6.935 | 5.490 | 0.345 | 12.77 | 3,168,516 | 3,204,112
sse-han-bmiss-sttni | 0.000 | 5.569 | 0.353 | 5.922 | 2,124,908 | 2,154,100
sse-bm-lemire | 0.000 | 5.697 | 0.349 | 6.046 | 2,124,108 | 2,155,828
**sse-emptyheaded-layout-uint** | 7.569 | 5.744 | 0.326 | 13.639 | 3,151,424 | 3,208,652
**sse-han-bsr-sse-shuffle** | 13.378 | 6.152 | 0.367 | 19.897 | 4,025,644 | 4,058,724
sse-han-qfilter | 0.000 | 6.836 | 0.353 | 7.189 | 2,120,752 | 2,155,156
sse-han-bmiss | 0.000 | 10.477 | 0.383 | 10.86 | 2,121,756 | 2,154,640
**sse-roaring** | 22.407 | 23.261 | 0.348 | 46.016 | 6,645,904 | 2,222,464
**avx2-roaring** | 22.327 | 23.381 | 0.357 | 46.065 | 6,627,756 | 2,220,020


### snap_orkut/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-merge` | 0.000 | 2.901 | 0.44 | 3.341 | 2,119,816 | 2,168,656
`avx2-hybrid` | 0.000 | 2.915 | 0.415 | 3.33 | 2,120,204 | 2,169,008
avx2-lemire | 0.000 | 4.115 | 0.419 | 4.534 | 2,120,452 | 2,154,208
tetzank-avx2-asm | 0.000 | 4.227 | 0.407 | 4.634 | 2,121,756 | 2,154,264
sse-lemire | 0.000 | 4.505 | 0.41 | 4.915 | 2,119,496 | 2,151,788
tetzank-avx2 | 0.000 | 5.150 | 0.435 | 5.585 | 2,120,516 | 2,153,164
`avx2-galloping-single` | 0.000 | 5.692 | 0.417 | 6.109 | 2,122,120 | 2,168,800
**sse-emptyheaded-layout-hybrid** | 7.475 | 5.834 | 0.41 | 13.719 | 3,177,200 | 3,226,056
**sse-emptyheaded-layout-uint** | 7.195 | 6.062 | 0.416 | 13.673 | 3,162,732 | 3,216,760
tetzank-avx | 0.000 | 6.110 | 0.428 | 6.538 | 2,127,184 | 2,155,428
sse-han-bmiss-sttni | 0.000 | 6.607 | 0.464 | 7.071 | 2,127,072 | 2,155,716
sse-bm-lemire | 0.000 | 6.921 | 0.427 | 7.348 | 2,123,820 | 2,171,964
**sse-han-bsr-sse-galloping** | 14.15 | 7.152 | 0.41 | 21.712 | 4,054,940 | 4,088,444
**sse-han-bsr-scalar-galloping** | 13.545 | 7.608 | 0.411 | 21.564 | 4,056,804 | 4,088,892
sse-han-qfilter | 0.000 | 7.994 | 0.43 | 8.424 | 2,121,776 | 2,152,244
**sse-han-bsr-qfilter** | 14.369 | 8.736 | 0.421 | 23.526 | 4,054,324 | 4,088,392
**sse-han-bsr-scalar-merge** | 13.379 | 9.258 | 0.392 | 23.029 | 4,055,224 | 4,088,816
**sse-han-bsr-sse-shuffle** | 14.547 | 12.405 | 0.415 | 27.367 | 4,078,068 | 4,096,156
sse-han-bmiss | 0.000 | 12.617 | 0.427 | 13.044 | 2,128,728 | 2,154,676
`naive-bitvec-2d` | 0.000 | 15.007 | 0.414 | 15.421 | 2,210,140 | 2,240,468
**avx2-roaring** | 31.275 | 33.935 | 0.474 | 65.684 | 8,224,148 | 2,185,200
**sse-roaring** | 32.329 | 34.198 | 0.412 | 66.939 | 8,222,968 | 2,185,264
`naive-bitvec` | 0.000 | 45.547 | 0.44 | 45.987 | 2,210,080 | 2,243,440


### snap_orkut/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_orkut/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_orkut/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-merge` | 0.000 | 2.752 | 0.402 | 3.154 | 3,103,104 | 3,283,468
`avx2-hybrid` | 0.000 | 2.777 | 0.38 | 3.157 | 3,157,960 | 3,401,788
`naive-bitvec-2d` | 0.000 | 3.487 | 0.378 | 3.865 | 2,233,844 | 2,523,976
tetzank-avx2-asm | 0.000 | 3.781 | 0.386 | 4.167 | 3,100,316 | 3,356,356
avx2-lemire | 0.000 | 3.978 | 0.395 | 4.373 | 3,151,312 | 3,422,136
sse-lemire | 0.000 | 4.362 | 0.393 | 4.755 | 3,101,972 | 3,437,536
tetzank-avx2 | 0.000 | 4.571 | 0.37 | 4.941 | 3,101,996 | 3,330,344
`avx2-galloping-single` | 0.000 | 5.308 | 0.385 | 5.693 | 3,147,936 | 3,490,088
tetzank-avx | 0.000 | 5.383 | 0.39 | 5.773 | 3,103,076 | 3,302,052
**sse-emptyheaded-layout-hybrid** | 7.514 | 5.544 | 0.395 | 13.453 | 3,828,072 | 4,173,076
`naive-bitvec` | 0.000 | 5.548 | 0.403 | 5.951 | 2,234,040 | 2,433,036
sse-han-bmiss-sttni | 0.000 | 5.602 | 0.388 | 5.99 | 3,221,840 | 3,483,368
sse-bm-lemire | 0.000 | 5.690 | 0.408 | 6.098 | 3,104,568 | 3,343,728
**sse-emptyheaded-layout-uint** | 6.992 | 5.800 | 0.404 | 13.196 | 3,713,072 | 4,000,520
**sse-han-bsr-sse-galloping** | 13.4 | 6.480 | 0.404 | 20.284 | 6,101,860 | 6,451,768
**sse-han-bsr-scalar-galloping** | 14.044 | 6.732 | 0.393 | 21.169 | 6,071,520 | 6,392,920
**sse-han-bsr-scalar-merge** | 13.38 | 6.817 | 0.42 | 20.617 | 6,063,440 | 6,298,876
**sse-han-bsr-qfilter** | 13.676 | 6.840 | 0.41 | 20.926 | 6,051,228 | 6,332,296
sse-han-qfilter | 0.000 | 6.856 | 0.374 | 7.23 | 3,217,756 | 3,455,796
**sse-han-bsr-sse-shuffle** | 14.06 | 8.712 | 0.374 | 23.146 | 6,083,780 | 6,391,764
sse-han-bmiss | 0.000 | 10.473 | 0.405 | 10.878 | 3,223,788 | 3,427,160
**avx2-roaring** | 28.607 | 24.988 | 0.381 | 53.976 | 8,124,240 | 3,702,424
**sse-roaring** | 27.981 | 25.811 | 0.362 | 54.154 | 8,261,196 | 3,799,172


### snap_orkut/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 2.856 | 0.383 | 3.239 | 3,146,536 | 3,430,280
`avx2-merge` | 0.000 | 2.876 | 0.377 | 3.253 | 3,163,184 | 3,504,200
avx2-lemire | 0.000 | 4.048 | 0.379 | 4.427 | 3,132,788 | 3,402,028
tetzank-avx2-asm | 0.000 | 4.159 | 0.379 | 4.538 | 3,101,992 | 3,396,528
sse-lemire | 0.000 | 4.445 | 0.384 | 4.829 | 3,099,844 | 3,377,924
tetzank-avx2 | 0.000 | 4.986 | 0.385 | 5.371 | 3,106,152 | 3,414,896
`avx2-galloping-single` | 0.000 | 5.349 | 0.383 | 5.732 | 3,100,524 | 3,317,420
**sse-emptyheaded-layout-hybrid** | 7.451 | 5.767 | 0.381 | 13.599 | 3,826,104 | 4,112,120
tetzank-avx | 0.000 | 5.930 | 0.364 | 6.294 | 3,104,536 | 3,550,900
**sse-emptyheaded-layout-uint** | 6.971 | 5.973 | 0.397 | 13.341 | 3,712,956 | 4,070,292
**sse-han-bsr-sse-galloping** | 13.328 | 6.325 | 0.381 | 20.034 | 6,151,776 | 6,387,404
sse-han-bmiss-sttni | 0.000 | 6.383 | 0.39 | 6.773 | 3,252,968 | 3,467,024
**sse-han-bsr-scalar-galloping** | 14.274 | 6.497 | 0.361 | 21.132 | 6,299,772 | 6,639,680
sse-bm-lemire | 0.000 | 6.578 | 0.392 | 6.97 | 3,145,704 | 3,597,260
**sse-han-bsr-qfilter** | 14.07 | 7.073 | 0.363 | 21.506 | 6,195,016 | 6,394,308
**sse-han-bsr-scalar-merge** | 13.406 | 7.131 | 0.381 | 20.918 | 6,292,056 | 6,626,640
sse-han-qfilter | 0.000 | 7.620 | 0.38 | 8.0 | 3,252,112 | 3,535,172
`naive-bitvec-2d` | 0.000 | 8.336 | 0.401 | 8.737 | 2,234,080 | 2,560,000
**sse-han-bsr-sse-shuffle** | 13.853 | 9.301 | 0.392 | 23.546 | 6,304,540 | 6,591,436
sse-han-bmiss | 0.000 | 11.958 | 0.383 | 12.341 | 3,259,820 | 3,508,752
`naive-bitvec` | 0.000 | 15.497 | 0.41 | 15.907 | 2,234,016 | 2,485,272
**sse-roaring** | 23.137 | 23.626 | 0.387 | 47.15 | 7,312,672 | 3,545,012
**avx2-roaring** | 23.196 | 23.799 | 0.357 | 47.352 | 7,384,480 | 3,555,388


### webgraph_eu

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_eu/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-scalar-merge** | 13.434 | 8.481 | 0.492 | 22.407 | 5,494,368 | 5,581,896
**sse-han-bsr-sse-shuffle** | 13.677 | 8.747 | 0.478 | 22.902 | 5,496,616 | 5,583,256
**sse-han-bsr-qfilter** | 13.513 | 10.081 | 0.486 | 24.08 | 5,493,892 | 5,582,500
**sse-han-bsr-scalar-galloping** | 13.506 | 12.795 | 0.489 | 26.79 | 5,491,452 | 5,582,132
**sse-han-bsr-sse-galloping** | 13.441 | 15.168 | 0.521 | 29.13 | 5,501,752 | 5,595,644
**avx2-roaring** | 15.13 | 15.461 | 0.479 | 31.07 | 6,698,608 | 4,759,680
**sse-roaring** | 15.177 | 16.123 | 0.502 | 31.802 | 6,697,108 | 4,760,056
**sse-emptyheaded-layout-hybrid** | 8.453 | 18.095 | 0.483 | 27.031 | 4,955,416 | 5,045,088
tetzank-avx2-asm | 0.000 | 68.387 | 0.512 | 68.899 | 3,614,760 | 3,703,536
`avx2-hybrid` | 0.000 | 80.441 | 0.494 | 80.935 | 3,596,908 | 3,686,228
`avx2-merge` | 0.000 | 82.642 | 0.492 | 83.134 | 3,596,888 | 3,686,384
tetzank-avx2 | 0.000 | 84.572 | 0.488 | 85.06 | 3,612,228 | 3,701,552
`naive-bitvec` | 0.000 | 99.361 | 0.495 | 99.856 | 3,945,884 | 4,034,184
tetzank-avx | 0.000 | 101.120 | 0.499 | 101.619 | 3,613,784 | 3,701,264
sse-bm-lemire | 0.000 | 117.255 | 0.494 | 117.749 | 3,611,780 | 3,700,780
**sse-emptyheaded-layout-uint** | 9.225 | 131.668 | 0.484 | 141.377 | 5,549,188 | 5,649,724
`naive-bitvec-2d` | 0.000 | 168.292 | 0.496 | 168.788 | 3,945,612 | 4,033,284
avx2-lemire | 0.000 | 199.686 | 0.493 | 200.179 | 3,612,824 | 3,700,496
sse-han-qfilter | 0.000 | 200.976 | 0.499 | 201.475 | 3,613,000 | 3,699,804
sse-lemire | 0.000 | 224.705 | 0.504 | 225.209 | 3,613,204 | 3,702,100
sse-han-bmiss | 0.000 | 292.549 | 0.5 | 293.049 | 3,611,312 | 3,700,728
sse-han-bmiss-sttni | 0.000 | 299.183 | 0.486 | 299.669 | 3,610,928 | 3,700,496
`avx2-galloping-single` | 0.000 | 306.609 | 0.498 | 307.107 | 3,590,168 | 3,680,764


### webgraph_eu/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 84.307 | 0.56 | 84.867 | 3,603,516 | 3,699,952
`avx2-merge` | 0.000 | 86.816 | 0.511 | 87.327 | 3,602,132 | 3,697,596
tetzank-avx2-asm | 0.000 | 90.327 | 0.562 | 90.889 | 3,628,836 | 3,725,084
**sse-roaring** | 30.257 | 99.769 | 0.531 | 130.557 | 9,599,452 | 3,696,708
**avx2-roaring** | 29.909 | 100.149 | 0.509 | 130.567 | 9,596,984 | 3,689,340
tetzank-avx2 | 0.000 | 115.152 | 0.55 | 115.702 | 3,627,840 | 3,722,792
tetzank-avx | 0.000 | 138.771 | 0.53 | 139.301 | 3,629,212 | 3,724,888
sse-bm-lemire | 0.000 | 151.913 | 0.53 | 152.443 | 3,628,776 | 3,724,828
**sse-han-bsr-scalar-merge** | 13.985 | 159.890 | 0.532 | 174.407 | 6,445,924 | 6,546,300
**sse-emptyheaded-layout-hybrid** | 10.082 | 160.774 | 0.557 | 171.413 | 5,631,504 | 5,733,220
**sse-emptyheaded-layout-uint** | 9.361 | 168.402 | 0.513 | 178.276 | 5,570,412 | 5,670,220
**sse-han-bsr-sse-shuffle** | 14.02 | 173.933 | 0.53 | 188.483 | 6,447,072 | 6,550,680
**sse-han-bsr-scalar-galloping** | 13.753 | 182.893 | 0.572 | 197.218 | 6,445,948 | 6,546,856
**sse-han-bsr-qfilter** | 13.729 | 190.538 | 0.52 | 204.787 | 6,446,720 | 6,547,088
avx2-lemire | 0.000 | 199.352 | 0.526 | 199.878 | 3,629,464 | 3,725,928
**sse-han-bsr-sse-galloping** | 14.141 | 214.967 | 0.553 | 229.661 | 6,446,112 | 6,547,500
sse-lemire | 0.000 | 224.531 | 0.551 | 225.082 | 3,628,744 | 3,725,096
sse-han-qfilter | 0.000 | 260.199 | 0.566 | 260.765 | 3,629,012 | 3,726,028
`avx2-galloping-single` | 0.000 | 309.643 | 0.529 | 310.172 | 3,603,524 | 3,700,980
sse-han-bmiss-sttni | 0.000 | 341.112 | 0.529 | 341.641 | 3,628,192 | 3,723,496
sse-han-bmiss | 0.000 | 397.710 | 0.555 | 398.265 | 3,628,968 | 3,723,476
`naive-bitvec` | 0.000 | 691.177 | 0.532 | 691.709 | 3,953,936 | 4,049,732
`naive-bitvec-2d` | 0.000 | 696.328 | 0.563 | 696.891 | 3,952,072 | 4,047,416


### webgraph_eu/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_eu/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_eu/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-scalar-merge** | 13.633 | 11.894 | 0.471 | 25.998 | 7,647,080 | 8,058,468
**sse-han-bsr-sse-shuffle** | 13.636 | 13.076 | 0.513 | 27.225 | 7,669,048 | 8,137,528
**sse-han-bsr-qfilter** | 12.831 | 14.444 | 0.498 | 27.773 | 7,686,424 | 8,017,640
**sse-han-bsr-scalar-galloping** | 12.689 | 17.091 | 0.52 | 30.3 | 7,702,820 | 8,032,360
**sse-emptyheaded-layout-hybrid** | 8.117 | 18.266 | 0.473 | 26.856 | 5,899,072 | 6,427,220
**sse-han-bsr-sse-galloping** | 13.017 | 20.207 | 0.497 | 33.721 | 7,636,380 | 8,073,688
**sse-roaring** | 18.964 | 24.809 | 0.467 | 44.24 | 8,224,024 | 7,350,768
**avx2-roaring** | 19.282 | 25.623 | 0.506 | 45.411 | 8,221,940 | 7,324,504
`avx2-hybrid` | 0.000 | 80.491 | 0.507 | 80.998 | 4,572,244 | 5,046,580
tetzank-avx2-asm | 0.000 | 80.833 | 0.478 | 81.311 | 4,572,812 | 5,045,736
`avx2-merge` | 0.000 | 82.004 | 0.492 | 82.496 | 4,576,908 | 5,055,200
tetzank-avx2 | 0.000 | 85.106 | 0.505 | 85.611 | 4,586,768 | 5,087,484
`naive-bitvec` | 0.000 | 99.379 | 0.48 | 99.859 | 3,954,728 | 4,498,348
tetzank-avx | 0.000 | 99.722 | 0.45 | 100.172 | 4,572,288 | 5,070,488
sse-bm-lemire | 0.000 | 116.615 | 0.498 | 117.113 | 4,621,372 | 5,156,844
**sse-emptyheaded-layout-uint** | 8.859 | 131.041 | 0.496 | 140.396 | 6,225,316 | 6,751,008
`naive-bitvec-2d` | 0.000 | 167.638 | 0.55 | 168.188 | 3,954,620 | 4,502,228
avx2-lemire | 0.000 | 198.399 | 0.509 | 198.908 | 4,574,908 | 5,061,276
sse-han-qfilter | 0.000 | 199.521 | 0.481 | 200.002 | 5,088,608 | 5,595,824
sse-lemire | 0.000 | 223.731 | 0.49 | 224.221 | 4,608,380 | 5,093,548
sse-han-bmiss | 0.000 | 290.023 | 0.483 | 290.506 | 5,094,748 | 5,560,896
sse-han-bmiss-sttni | 0.000 | 297.704 | 0.44 | 298.144 | 4,698,272 | 5,244,276
`avx2-galloping-single` | 0.000 | 305.968 | 0.517 | 306.485 | 4,569,108 | 5,062,068


### webgraph_eu/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-scalar-merge** | 12.581 | 11.674 | 0.453 | 24.708 | 7,861,504 | 8,192,888
**sse-han-bsr-scalar-galloping** | 12.861 | 13.986 | 0.451 | 27.298 | 7,755,224 | 8,218,804
**sse-han-bsr-sse-shuffle** | 12.467 | 16.103 | 0.51 | 29.08 | 7,810,380 | 8,215,720
**sse-han-bsr-sse-galloping** | 12.586 | 16.420 | 0.442 | 29.448 | 7,831,684 | 8,179,084
**sse-han-bsr-qfilter** | 12.551 | 16.542 | 0.453 | 29.546 | 7,648,584 | 8,167,652
**avx2-roaring** | 15.293 | 24.210 | 0.47 | 39.973 | 7,465,152 | 6,046,860
**sse-roaring** | 14.864 | 24.249 | 0.511 | 39.624 | 7,561,216 | 6,217,632
`avx2-hybrid` | 0.000 | 82.435 | 0.452 | 82.887 | 4,570,352 | 5,057,300
`avx2-merge` | 0.000 | 85.245 | 0.458 | 85.703 | 4,568,804 | 5,075,116
tetzank-avx2-asm | 0.000 | 89.986 | 0.5 | 90.486 | 4,573,164 | 5,071,972
tetzank-avx2 | 0.000 | 109.941 | 0.493 | 110.434 | 4,572,868 | 5,025,616
`naive-bitvec` | 0.000 | 122.924 | 0.482 | 123.406 | 3,954,912 | 4,494,068
tetzank-avx | 0.000 | 131.412 | 0.468 | 131.88 | 4,573,156 | 5,056,924
sse-bm-lemire | 0.000 | 143.536 | 0.468 | 144.004 | 4,568,620 | 5,084,872
**sse-emptyheaded-layout-hybrid** | 8.758 | 155.856 | 0.455 | 165.069 | 6,580,676 | 7,120,524
**sse-emptyheaded-layout-uint** | 8.718 | 163.899 | 0.458 | 173.075 | 6,225,940 | 6,759,352
`naive-bitvec-2d` | 0.000 | 185.688 | 0.48 | 186.168 | 3,954,688 | 4,481,080
avx2-lemire | 0.000 | 199.233 | 0.451 | 199.684 | 4,571,280 | 5,083,008
sse-lemire | 0.000 | 224.182 | 0.532 | 224.714 | 4,601,856 | 5,094,632
sse-han-qfilter | 0.000 | 245.563 | 0.492 | 246.055 | 5,090,772 | 5,585,600
`avx2-galloping-single` | 0.000 | 306.088 | 0.49 | 306.578 | 4,585,784 | 5,017,720
sse-han-bmiss-sttni | 0.000 | 332.952 | 0.49 | 333.442 | 4,740,096 | 5,288,024
sse-han-bmiss | 0.000 | 375.203 | 0.487 | 375.69 | 5,078,148 | 5,578,468


### webgraph_uk

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_uk/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 0.000 | 1.102 | 0.37 | 1.472 | 3,602,044 | 3,824,688
`avx2-hybrid` | 0.000 | 1.285 | 0.368 | 1.653 | 3,027,952 | 3,211,532
**sse-han-bsr-sse-galloping** | 21.398 | 1.390 | 0.347 | 23.135 | 6,028,528 | 6,207,764
**sse-han-bsr-sse-shuffle** | 21.616 | 1.408 | 0.355 | 23.379 | 6,027,300 | 6,211,696
**sse-han-bsr-scalar-galloping** | 22.131 | 1.410 | 0.345 | 23.886 | 6,027,868 | 6,209,096
**sse-han-bsr-scalar-merge** | 21.385 | 1.427 | 0.356 | 23.168 | 6,027,704 | 6,212,236
**sse-han-bsr-qfilter** | 21.25 | 1.452 | 0.372 | 23.074 | 6,026,856 | 6,211,200
`avx2-merge` | 0.000 | 1.623 | 0.389 | 2.012 | 3,005,116 | 3,233,348
`naive-bitvec-2d` | 0.000 | 1.637 | 0.37 | 2.007 | 3,603,352 | 3,824,444
avx2-lemire | 0.000 | 2.480 | 0.36 | 2.84 | 3,031,568 | 3,245,660
`avx2-galloping-single` | 0.000 | 2.567 | 0.362 | 2.929 | 3,025,724 | 3,208,316
sse-lemire | 0.000 | 2.617 | 0.365 | 2.982 | 3,029,972 | 3,259,224
**sse-emptyheaded-layout-hybrid** | 12.956 | 2.931 | 0.361 | 16.248 | 4,895,424 | 5,080,928
**sse-emptyheaded-layout-uint** | 13.037 | 3.199 | 0.374 | 16.61 | 4,910,672 | 5,117,304
tetzank-avx2 | 0.000 | 4.959 | 0.373 | 5.332 | 3,032,320 | 3,252,724
tetzank-avx | 0.000 | 5.520 | 0.379 | 5.899 | 3,032,264 | 3,255,744
sse-bm-lemire | 0.000 | 5.889 | 0.401 | 6.29 | 3,030,900 | 3,247,512
sse-han-bmiss-sttni | 0.000 | 7.275 | 0.363 | 7.638 | 3,031,020 | 3,213,100
tetzank-avx2-asm | 0.000 | 7.412 | 0.372 | 7.784 | 3,032,072 | 3,217,040
sse-han-qfilter | 0.000 | 7.659 | 0.368 | 8.027 | 3,031,180 | 3,215,524
sse-han-bmiss | 0.000 | 12.360 | 0.393 | 12.753 | 3,032,236 | 3,239,016
**avx2-roaring** | 14.793 | 12.832 | 0.33 | 27.955 | 5,941,368 | 4,046,036
**sse-roaring** | 14.708 | 13.103 | 0.383 | 28.194 | 5,940,244 | 4,046,400


### webgraph_uk/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 1.740 | 0.397 | 2.137 | 2,998,196 | 3,203,400
**sse-han-bsr-scalar-galloping** | 21.782 | 2.052 | 0.379 | 24.213 | 6,050,764 | 6,223,800
**sse-han-bsr-sse-galloping** | 21.874 | 2.213 | 0.385 | 24.472 | 6,050,436 | 6,223,608
`avx2-merge` | 0.000 | 2.427 | 0.371 | 2.798 | 3,017,940 | 3,202,576
**sse-han-bsr-scalar-merge** | 22.121 | 2.730 | 0.376 | 25.227 | 6,050,016 | 6,223,420
avx2-lemire | 0.000 | 2.739 | 0.385 | 3.124 | 3,034,364 | 3,210,136
sse-lemire | 0.000 | 2.901 | 0.368 | 3.269 | 3,034,396 | 3,208,060
**sse-han-bsr-qfilter** | 22.937 | 2.924 | 0.364 | 26.225 | 6,050,168 | 6,223,572
**sse-han-bsr-sse-shuffle** | 21.519 | 3.247 | 0.369 | 25.135 | 6,050,696 | 6,223,852
`avx2-galloping-single` | 0.000 | 3.291 | 0.382 | 3.673 | 3,027,668 | 3,202,608
**sse-emptyheaded-layout-uint** | 13.381 | 4.730 | 0.38 | 18.491 | 4,915,044 | 5,089,432
**sse-emptyheaded-layout-hybrid** | 14.467 | 4.900 | 0.373 | 19.74 | 4,973,232 | 5,147,916
tetzank-avx2 | 0.000 | 7.326 | 0.375 | 7.701 | 3,032,976 | 3,206,776
tetzank-avx2-asm | 0.000 | 8.416 | 0.386 | 8.802 | 3,033,220 | 3,206,896
tetzank-avx | 0.000 | 8.456 | 0.381 | 8.837 | 3,033,492 | 3,207,216
sse-bm-lemire | 0.000 | 9.208 | 0.379 | 9.587 | 3,033,020 | 3,207,796
sse-han-bmiss-sttni | 0.000 | 10.184 | 0.393 | 10.577 | 3,032,448 | 3,206,884
`naive-bitvec` | 0.000 | 10.643 | 0.37 | 11.013 | 3,604,456 | 3,786,288
sse-han-qfilter | 0.000 | 10.736 | 0.385 | 11.121 | 3,032,404 | 3,208,044
`naive-bitvec-2d` | 0.000 | 12.271 | 0.388 | 12.659 | 3,604,492 | 3,833,648
sse-han-bmiss | 0.000 | 15.980 | 0.38 | 16.36 | 3,032,944 | 3,206,368
**sse-roaring** | 21.858 | 21.237 | 0.374 | 43.469 | 7,495,060 | 3,319,456
**avx2-roaring** | 21.935 | 22.062 | 0.37 | 44.367 | 7,495,228 | 3,316,412


### webgraph_uk/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_uk/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_uk/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 0.000 | 1.068 | 0.387 | 1.455 | 3,587,820 | 4,206,136
`avx2-hybrid` | 0.000 | 1.344 | 0.388 | 1.732 | 4,030,992 | 4,618,956
**sse-han-bsr-scalar-galloping** | 21.73 | 1.584 | 0.403 | 23.717 | 8,121,000 | 8,788,472
`naive-bitvec-2d` | 0.000 | 1.587 | 0.403 | 1.99 | 3,592,600 | 4,214,488
`avx2-merge` | 0.000 | 1.628 | 0.381 | 2.009 | 3,984,368 | 4,576,412
**sse-han-bsr-scalar-merge** | 21.099 | 1.674 | 0.396 | 23.169 | 8,080,156 | 8,703,156
**sse-han-bsr-sse-galloping** | 20.782 | 1.728 | 0.413 | 22.923 | 8,049,684 | 8,624,508
**sse-han-bsr-qfilter** | 20.764 | 1.847 | 0.407 | 23.018 | 7,965,760 | 8,480,880
**sse-han-bsr-sse-shuffle** | 21.525 | 1.860 | 0.373 | 23.758 | 8,053,632 | 8,666,284
`avx2-galloping-single` | 0.000 | 2.687 | 0.375 | 3.062 | 3,987,652 | 4,551,364
avx2-lemire | 0.000 | 2.693 | 0.391 | 3.084 | 3,987,540 | 4,558,156
sse-lemire | 0.000 | 2.791 | 0.39 | 3.181 | 3,988,044 | 4,556,648
**sse-emptyheaded-layout-hybrid** | 12.69 | 2.799 | 0.384 | 15.873 | 5,975,612 | 6,612,708
**sse-emptyheaded-layout-uint** | 13.453 | 3.095 | 0.396 | 16.944 | 5,578,172 | 6,239,328
tetzank-avx2 | 0.000 | 5.052 | 0.391 | 5.443 | 4,047,800 | 4,653,864
tetzank-avx | 0.000 | 5.443 | 0.4 | 5.843 | 3,984,252 | 4,566,640
sse-bm-lemire | 0.000 | 6.211 | 0.412 | 6.623 | 4,045,952 | 4,639,780
sse-han-qfilter | 0.000 | 7.638 | 0.379 | 8.017 | 4,246,940 | 4,816,472
sse-han-bmiss-sttni | 0.000 | 7.801 | 0.396 | 8.197 | 4,245,364 | 4,858,500
tetzank-avx2-asm | 0.000 | 8.195 | 0.393 | 8.588 | 4,021,596 | 4,624,748
sse-han-bmiss | 0.000 | 11.873 | 0.391 | 12.264 | 4,236,744 | 4,842,824
**sse-roaring** | 24.704 | 20.309 | 0.382 | 45.395 | 9,303,148 | 7,446,896
**avx2-roaring** | 24.085 | 22.054 | 0.374 | 46.513 | 9,233,632 | 7,329,704


### webgraph_uk/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-scalar-merge** | 21.998 | 1.151 | 0.353 | 23.502 | 7,907,312 | 8,366,056
**sse-han-bsr-scalar-galloping** | 21.556 | 1.151 | 0.384 | 23.091 | 7,896,996 | 8,358,732
**sse-han-bsr-sse-galloping** | 21.773 | 1.224 | 0.369 | 23.366 | 7,974,984 | 8,504,076
**sse-han-bsr-qfilter** | 21.574 | 1.310 | 0.374 | 23.258 | 7,960,552 | 8,476,460
**sse-han-bsr-sse-shuffle** | 22.561 | 1.321 | 0.36 | 24.242 | 7,936,052 | 8,465,892
`avx2-hybrid` | 0.000 | 1.588 | 0.371 | 1.959 | 3,989,816 | 4,571,572
`avx2-merge` | 0.000 | 2.150 | 0.371 | 2.521 | 3,986,584 | 4,576,228
`naive-bitvec` | 0.000 | 2.341 | 0.364 | 2.705 | 3,604,320 | 4,227,716
avx2-lemire | 0.000 | 2.561 | 0.401 | 2.962 | 3,989,004 | 4,595,680
sse-lemire | 0.000 | 2.706 | 0.381 | 3.087 | 3,989,364 | 4,598,584
`avx2-galloping-single` | 0.000 | 2.839 | 0.386 | 3.225 | 3,993,140 | 4,577,704
`naive-bitvec-2d` | 0.000 | 3.598 | 0.366 | 3.964 | 3,604,292 | 4,248,568
**sse-emptyheaded-layout-hybrid** | 13.659 | 3.769 | 0.377 | 17.805 | 5,935,496 | 6,567,440
**sse-emptyheaded-layout-uint** | 13.715 | 3.994 | 0.358 | 18.067 | 5,581,252 | 6,238,648
tetzank-avx2 | 0.000 | 7.653 | 0.396 | 8.049 | 4,025,624 | 4,630,572
tetzank-avx | 0.000 | 8.149 | 0.391 | 8.54 | 3,988,960 | 4,598,040
sse-bm-lemire | 0.000 | 8.735 | 0.388 | 9.123 | 3,996,836 | 4,605,268
tetzank-avx2-asm | 0.000 | 8.903 | 0.377 | 9.28 | 3,988,880 | 4,587,916
sse-han-bmiss-sttni | 0.000 | 10.197 | 0.378 | 10.575 | 4,255,588 | 4,862,652
sse-han-qfilter | 0.000 | 11.342 | 0.375 | 11.717 | 4,274,000 | 4,847,616
**sse-roaring** | 13.763 | 13.108 | 0.377 | 27.248 | 7,169,104 | 5,370,992
**avx2-roaring** | 13.352 | 13.849 | 0.382 | 27.583 | 7,152,844 | 5,427,632
sse-han-bmiss | 0.000 | 17.483 | 0.386 | 17.869 | 4,263,940 | 4,838,784


### webgraph_webbase

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_webbase/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 3.692 | 1.169 | 4.861 | 11,555,268 | 12,638,752
`naive-bitvec` | 0.000 | 3.914 | 1.167 | 5.081 | 15,244,844 | 16,300,528
`naive-bitvec-2d` | 0.000 | 5.625 | 1.198 | 6.823 | 15,248,736 | 16,229,404
`avx2-galloping-single` | 0.000 | 7.917 | 1.324 | 9.241 | 11,555,144 | 12,591,768
**sse-han-bsr-sse-galloping** | 96.659 | 8.148 | 1.324 | 106.131 | 24,471,900 | 25,465,964
**sse-han-bsr-scalar-galloping** | 97.755 | 8.582 | 1.192 | 107.529 | 24,471,532 | 25,421,276
**sse-han-bsr-qfilter** | 95.182 | 9.211 | 1.22 | 105.613 | 24,470,724 | 25,452,916
**sse-han-bsr-scalar-merge** | 96.428 | 9.250 | 1.396 | 107.074 | 24,471,176 | 25,436,336
**sse-han-bsr-sse-shuffle** | 96.28 | 9.739 | 1.25 | 107.269 | 24,472,040 | 25,468,284
`avx2-merge` | 0.000 | 13.706 | 1.201 | 14.907 | 11,555,184 | 12,569,052
avx2-lemire | 0.000 | 20.103 | 1.234 | 21.337 | 11,562,832 | 12,563,128
sse-lemire | 0.000 | 20.452 | 1.198 | 21.65 | 11,562,872 | 12,585,648
**sse-emptyheaded-layout-uint** | 71.498 | 21.714 | 1.209 | 94.421 | 20,168,024 | 21,156,244
tetzank-avx2 | 0.000 | 42.254 | 1.215 | 43.469 | 11,563,136 | 12,575,640
tetzank-avx | 0.000 | 45.538 | 1.207 | 46.745 | 11,563,736 | 12,695,680
sse-bm-lemire | 0.000 | 48.303 | 1.267 | 49.57 | 11,563,320 | 12,651,548
sse-han-bmiss-sttni | 0.000 | 54.689 | 1.232 | 55.921 | 11,562,708 | 12,582,976
sse-han-qfilter | 0.000 | 58.275 | 1.216 | 59.491 | 11,563,036 | 12,647,572
tetzank-avx2-asm | 0.000 | 66.504 | 1.264 | 67.768 | 11,563,016 | 12,541,744
**sse-roaring** | 94.185 | 71.653 | 1.334 | 167.172 | 27,198,460 | 18,234,292
**avx2-roaring** | 96.264 | 74.691 | 1.427 | 172.382 | 27,199,344 | 18,260,344
sse-han-bmiss | 0.000 | 85.780 | 1.224 | 87.004 | 11,562,980 | 12,607,964


### webgraph_webbase/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 5.103 | 1.134 | 6.237 | 12,522,408 | 13,479,552
**sse-han-bsr-scalar-galloping** | 84.486 | 8.505 | 1.16 | 94.151 | 24,559,140 | 25,515,384
avx2-lemire | 0.000 | 9.102 | 1.297 | 10.399 | 11,571,660 | 12,704,296
sse-lemire | 0.000 | 9.499 | 1.327 | 10.826 | 11,573,068 | 12,556,844
`avx2-galloping-single` | 0.000 | 9.999 | 1.187 | 11.186 | 12,541,220 | 13,516,228
**sse-han-bsr-sse-galloping** | 85.003 | 12.269 | 1.142 | 98.414 | 24,562,608 | 25,517,504
**sse-emptyheaded-layout-uint** | 61.991 | 13.753 | 1.22 | 76.964 | 20,185,912 | 21,141,812
**sse-emptyheaded-layout-hybrid** | 75.693 | 16.590 | 1.377 | 93.66 | 20,350,596 | 21,318,268
**sse-han-bsr-qfilter** | 84.117 | 24.622 | 1.164 | 109.903 | 24,559,764 | 25,515,900
**sse-han-bsr-scalar-merge** | 84.387 | 25.852 | 1.206 | 111.445 | 24,561,448 | 25,516,444
`avx2-merge` | 0.000 | 25.896 | 1.168 | 27.064 | 12,508,812 | 13,483,760
**sse-han-bsr-sse-shuffle** | 83.41 | 33.058 | 1.274 | 117.742 | 24,560,820 | 25,516,624
tetzank-avx2 | 0.000 | 93.915 | 1.377 | 95.292 | 11,572,932 | 12,528,020
tetzank-avx | 0.000 | 105.910 | 1.27 | 107.18 | 11,570,284 | 12,525,444
tetzank-avx2-asm | 0.000 | 107.152 | 1.43 | 108.582 | 11,572,448 | 12,532,308
**sse-roaring** | 114.051 | 109.119 | 1.273 | 224.443 | 33,658,876 | 13,430,192
**avx2-roaring** | 121.8 | 112.873 | 1.374 | 236.047 | 33,662,596 | 13,868,004
sse-bm-lemire | 0.000 | 114.074 | 1.351 | 115.425 | 11,572,568 | 12,527,012
sse-han-bmiss-sttni | 0.000 | 117.525 | 1.221 | 118.746 | 12,687,088 | 13,662,880
sse-han-qfilter | 0.000 | 124.770 | 1.199 | 125.969 | 12,689,860 | 13,664,376
`naive-bitvec-2d` | 0.000 | 150.205 | 1.157 | 151.362 | 15,237,672 | 16,207,704
sse-han-bmiss | 0.000 | 192.014 | 1.213 | 193.227 | 12,691,780 | 13,663,396
`naive-bitvec` | 0.000 | 243.887 | 1.234 | 245.121 | 15,229,872 | 16,204,640


### webgraph_webbase/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_webbase/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_webbase/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 0.000 | 3.532 | 1.204 | 4.736 | 15,249,724 | 17,209,752
`avx2-hybrid` | 0.000 | 3.869 | 1.149 | 5.018 | 12,548,096 | 14,556,536
`naive-bitvec-2d` | 0.000 | 5.232 | 1.166 | 6.398 | 15,251,304 | 17,311,628
**sse-han-bsr-scalar-galloping** | 79.441 | 5.822 | 1.264 | 86.527 | 26,607,248 | 28,201,880
**sse-han-bsr-sse-galloping** | 79.888 | 6.221 | 1.195 | 87.304 | 26,608,624 | 28,223,952
`avx2-galloping-single` | 0.000 | 8.273 | 1.199 | 9.472 | 12,529,984 | 14,490,508
**sse-han-bsr-scalar-merge** | 80.056 | 9.587 | 1.137 | 90.78 | 26,534,808 | 28,051,240
**sse-han-bsr-qfilter** | 79.902 | 9.778 | 1.175 | 90.855 | 26,526,988 | 27,970,844
**sse-han-bsr-sse-shuffle** | 79.632 | 11.160 | 1.24 | 92.032 | 26,524,856 | 27,930,500
`avx2-merge` | 0.000 | 13.006 | 1.16 | 14.166 | 12,529,708 | 14,179,896
avx2-lemire | 0.000 | 22.301 | 1.198 | 23.499 | 12,529,680 | 14,492,784
sse-lemire | 0.000 | 22.930 | 1.213 | 24.143 | 12,528,332 | 14,244,912
**sse-emptyheaded-layout-uint** | 55.873 | 23.155 | 1.179 | 80.207 | 21,179,136 | 23,076,448
tetzank-avx2 | 0.000 | 41.632 | 1.17 | 42.802 | 12,593,284 | 14,842,744
tetzank-avx | 0.000 | 44.613 | 1.129 | 45.742 | 12,562,964 | 14,534,064
sse-bm-lemire | 0.000 | 46.516 | 1.174 | 47.69 | 12,599,420 | 14,724,820
sse-han-bmiss-sttni | 0.000 | 56.738 | 1.213 | 57.951 | 12,726,764 | 14,519,896
sse-han-qfilter | 0.000 | 59.675 | 1.201 | 60.876 | 12,739,768 | 14,530,768
tetzank-avx2-asm | 0.000 | 66.259 | 1.196 | 67.455 | 12,529,872 | 14,309,048
sse-han-bmiss | 0.000 | 87.740 | 1.214 | 88.954 | 12,739,496 | 14,558,240
**avx2-roaring** | 137.458 | 115.795 | 1.201 | 254.454 | 41,187,560 | 33,805,388
**sse-roaring** | 136.234 | 117.808 | 1.167 | 255.209 | 41,153,212 | 33,773,668


### webgraph_webbase/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 4.436 | 1.142 | 5.578 | 12,529,180 | 14,761,288
**sse-han-bsr-sse-galloping** | 81.121 | 4.628 | 1.297 | 87.046 | 26,568,220 | 28,397,476
**sse-han-bsr-scalar-galloping** | 81.017 | 4.691 | 1.157 | 86.865 | 26,399,608 | 28,176,992
**sse-han-bsr-scalar-merge** | 81.352 | 6.969 | 1.137 | 89.458 | 26,564,932 | 28,490,576
**sse-han-bsr-qfilter** | 81.443 | 7.227 | 1.126 | 89.796 | 26,443,872 | 28,249,200
`naive-bitvec` | 0.000 | 7.801 | 1.197 | 8.998 | 15,252,596 | 17,495,608
**sse-han-bsr-sse-shuffle** | 81.911 | 8.210 | 1.153 | 91.274 | 26,567,208 | 28,467,160
`avx2-galloping-single` | 0.000 | 8.540 | 1.283 | 9.823 | 12,526,632 | 14,779,480
avx2-lemire | 0.000 | 9.464 | 1.15 | 10.614 | 12,562,132 | 14,778,044
sse-lemire | 0.000 | 9.739 | 1.098 | 10.837 | 12,530,496 | 14,662,996
`naive-bitvec-2d` | 0.000 | 11.558 | 1.176 | 12.734 | 15,251,076 | 17,499,428
**sse-emptyheaded-layout-hybrid** | 57.571 | 11.754 | 1.163 | 70.488 | 21,272,300 | 23,589,800
**sse-emptyheaded-layout-uint** | 56.396 | 12.014 | 1.147 | 69.557 | 21,199,500 | 23,473,544
`avx2-merge` | 0.000 | 14.903 | 1.095 | 15.998 | 12,559,460 | 14,788,172
tetzank-avx2 | 0.000 | 51.171 | 1.145 | 52.316 | 12,531,728 | 14,636,172
tetzank-avx | 0.000 | 58.953 | 1.195 | 60.148 | 12,530,176 | 14,503,580
tetzank-avx2-asm | 0.000 | 60.435 | 1.233 | 61.668 | 12,599,272 | 14,717,644
sse-bm-lemire | 0.000 | 62.201 | 1.184 | 63.385 | 12,522,888 | 14,673,304
sse-han-bmiss-sttni | 0.000 | 66.105 | 1.237 | 67.342 | 12,797,848 | 15,042,520
sse-han-qfilter | 0.000 | 74.099 | 1.192 | 75.291 | 12,790,344 | 14,881,480
**avx2-roaring** | 79.667 | 78.022 | 1.144 | 158.833 | 30,764,612 | 15,588,744
**sse-roaring** | 80.441 | 78.487 | 1.145 | 160.073 | 30,707,336 | 15,460,608
sse-han-bmiss | 0.000 | 116.764 | 1.153 | 117.917 | 12,761,580 | 14,967,140


### webgraph_it

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_it/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-scalar-galloping** | 63.314 | 6.530 | 1.267 | 71.111 | 20,409,568 | 20,800,500
**sse-han-bsr-sse-galloping** | 63.077 | 8.140 | 1.226 | 72.443 | 20,409,680 | 20,879,088
`naive-bitvec` | 0.000 | 11.193 | 1.254 | 12.447 | 12,361,560 | 12,751,480
`avx2-hybrid` | 0.000 | 12.659 | 1.234 | 13.893 | 11,073,008 | 11,462,468
`naive-bitvec-2d` | 0.000 | 17.207 | 1.24 | 18.447 | 12,361,464 | 12,864,056
`avx2-galloping-single` | 0.000 | 26.682 | 1.34 | 28.022 | 11,073,428 | 11,460,652
**sse-emptyheaded-layout-hybrid** | 40.5 | 28.429 | 1.231 | 70.16 | 17,342,204 | 17,740,460
**avx2-roaring** | 43.016 | 37.695 | 1.251 | 81.962 | 19,340,148 | 13,540,840
**sse-han-bsr-qfilter** | 64.793 | 37.931 | 1.276 | 104.0 | 20,409,536 | 20,797,184
**sse-roaring** | 43.585 | 38.123 | 1.287 | 82.995 | 19,339,072 | 14,236,576
**sse-han-bsr-scalar-merge** | 64.736 | 40.549 | 1.242 | 106.527 | 20,410,056 | 20,800,812
**sse-han-bsr-sse-shuffle** | 64.753 | 49.913 | 1.229 | 115.895 | 20,410,500 | 20,904,932
avx2-lemire | 0.000 | 148.157 | 1.26 | 149.417 | 11,129,140 | 11,517,540
sse-lemire | 0.000 | 150.424 | 1.251 | 151.675 | 11,128,848 | 11,509,428
**sse-emptyheaded-layout-uint** | 39.903 | 152.486 | 1.399 | 193.788 | 17,258,100 | 17,649,136
`avx2-merge` | 0.000 | 286.407 | 1.311 | 287.718 | 11,073,364 | 11,464,156
tetzank-avx2 | 0.000 | 722.952 | 1.237 | 724.189 | 11,129,228 | 11,519,140
tetzank-avx | 0.000 | 822.073 | 1.386 | 823.459 | 11,126,048 | 11,521,612
sse-bm-lemire | 0.000 | 840.197 | 1.248 | 841.445 | 11,124,072 | 11,513,112
sse-han-bmiss-sttni | 0.000 | 868.146 | 1.249 | 869.395 | 11,128,368 | 11,519,288
tetzank-avx2-asm | 0.000 | 873.307 | 1.394 | 874.701 | 11,129,904 | 11,518,688
sse-han-qfilter | 0.000 | 998.279 | 1.277 | 999.556 | 11,128,608 | 11,518,420
sse-han-bmiss | 0.000 | 1446.002 | 1.323 | 1447.325 | 11,128,800 | 11,517,564


### webgraph_it/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-scalar-galloping** | 65.536 | 13.047 | 1.27 | 79.853 | 21,827,064 | 22,181,100
**sse-han-bsr-sse-galloping** | 65.174 | 13.880 | 1.337 | 80.391 | 21,826,836 | 22,249,056
`avx2-hybrid` | 0.000 | 20.658 | 1.19 | 21.848 | 12,041,508 | 12,389,960
`avx2-galloping-single` | 0.000 | 37.896 | 1.251 | 39.147 | 12,074,756 | 12,422,672
**sse-emptyheaded-layout-hybrid** | 41.873 | 38.269 | 1.246 | 81.388 | 18,570,552 | 18,927,372
**avx2-roaring** | 60.559 | 75.187 | 1.327 | 137.073 | 24,607,332 | 12,029,448
**sse-roaring** | 60.671 | 76.948 | 1.308 | 138.927 | 24,688,996 | 12,058,160
**sse-han-bsr-qfilter** | 64.883 | 85.083 | 1.339 | 151.305 | 21,842,916 | 22,196,524
avx2-lemire | 0.000 | 89.967 | 1.296 | 91.263 | 12,081,072 | 12,428,956
**sse-han-bsr-scalar-merge** | 65.186 | 90.283 | 1.292 | 156.761 | 21,589,904 | 21,943,200
sse-lemire | 0.000 | 92.200 | 1.261 | 93.461 | 12,075,028 | 12,422,488
**sse-emptyheaded-layout-uint** | 40.264 | 99.427 | 1.285 | 140.976 | 18,286,708 | 18,637,996
**sse-han-bsr-sse-shuffle** | 65.281 | 127.993 | 1.337 | 194.611 | 21,840,200 | 22,196,152
`avx2-merge` | 0.000 | 369.765 | 1.249 | 371.014 | 12,105,592 | 12,451,816
`naive-bitvec-2d` | 0.000 | 434.779 | 1.27 | 436.049 | 12,361,264 | 12,707,420
`naive-bitvec` | 0.000 | 450.838 | 1.299 | 452.137 | 12,361,596 | 12,707,356
tetzank-avx2-asm | 0.000 | 911.221 | 1.335 | 912.556 | 12,145,784 | 12,500,164
tetzank-avx2 | 0.000 | 928.214 | 1.304 | 929.518 | 12,083,236 | 12,430,324
tetzank-avx | 0.000 | 1088.598 | 1.312 | 1089.91 | 12,083,128 | 12,428,684
sse-han-bmiss-sttni | 0.000 | 1097.177 | 1.242 | 1098.419 | 12,298,448 | 12,653,204
sse-bm-lemire | 0.000 | 1124.178 | 1.362 | 1125.54 | 12,137,244 | 12,484,568
sse-han-qfilter | 0.000 | 1317.533 | 1.281 | 1318.814 | 12,565,168 | 12,931,212
sse-han-bmiss | 0.000 | 2033.825 | 1.267 | 2035.092 | 12,574,512 | 12,943,140


### webgraph_it/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_it/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_it/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-scalar-galloping** | 62.734 | 9.515 | 1.25 | 73.499 | 22,583,524 | 23,562,032
`naive-bitvec` | 0.000 | 11.147 | 1.309 | 12.456 | 12,363,492 | 13,361,788
**sse-han-bsr-sse-galloping** | 63.608 | 12.591 | 1.224 | 77.423 | 22,577,928 | 23,539,972
`avx2-hybrid` | 0.000 | 14.074 | 1.307 | 15.381 | 12,057,364 | 12,969,072
`naive-bitvec-2d` | 0.000 | 17.085 | 1.325 | 18.41 | 12,363,332 | 13,337,944
**sse-emptyheaded-layout-hybrid** | 39.394 | 27.841 | 1.19 | 68.425 | 18,390,360 | 19,399,724
`avx2-galloping-single` | 0.000 | 28.947 | 1.273 | 30.22 | 12,053,472 | 12,906,916
**sse-han-bsr-qfilter** | 63.518 | 47.176 | 1.309 | 112.003 | 22,556,796 | 23,438,128
**sse-han-bsr-scalar-merge** | 62.954 | 49.120 | 1.33 | 113.404 | 22,603,552 | 23,620,492
**avx2-roaring** | 71.047 | 62.631 | 1.19 | 134.868 | 26,942,360 | 19,945,136
**sse-roaring** | 72.569 | 62.648 | 1.292 | 136.509 | 26,936,332 | 19,959,084
**sse-han-bsr-sse-shuffle** | 63.252 | 65.152 | 1.216 | 129.62 | 22,584,748 | 23,378,544
avx2-lemire | 0.000 | 149.409 | 1.339 | 150.748 | 12,072,480 | 12,963,556
sse-lemire | 0.000 | 151.172 | 1.255 | 152.427 | 12,082,808 | 13,071,956
**sse-emptyheaded-layout-uint** | 38.047 | 152.434 | 1.245 | 191.726 | 18,227,432 | 19,227,468
`avx2-merge` | 0.000 | 290.595 | 1.296 | 291.891 | 12,046,080 | 12,920,864
tetzank-avx2 | 0.000 | 733.057 | 1.268 | 734.325 | 12,068,760 | 12,946,980
tetzank-avx | 0.000 | 834.206 | 1.237 | 835.443 | 12,072,688 | 12,910,920
sse-bm-lemire | 0.000 | 850.814 | 1.288 | 852.102 | 12,064,296 | 12,940,528
sse-han-bmiss-sttni | 0.000 | 879.038 | 1.289 | 880.327 | 12,474,896 | 13,436,152
tetzank-avx2-asm | 0.000 | 893.484 | 1.191 | 894.675 | 12,072,724 | 12,989,292
sse-han-qfilter | 0.000 | 1016.834 | 1.294 | 1018.128 | 12,522,192 | 13,413,280
sse-han-bmiss | 0.000 | 1465.349 | 1.19 | 1466.539 | 12,511,768 | 13,467,252


### webgraph_it/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-scalar-galloping** | 64.994 | 6.164 | 1.242 | 72.4 | 22,494,648 | 23,510,624
**sse-han-bsr-sse-galloping** | 65.166 | 6.732 | 1.225 | 73.123 | 22,448,988 | 23,408,792
`avx2-hybrid` | 0.000 | 13.809 | 1.24 | 15.049 | 12,040,420 | 12,876,992
`naive-bitvec` | 0.000 | 22.517 | 1.215 | 23.732 | 12,363,368 | 13,286,528
`avx2-galloping-single` | 0.000 | 27.864 | 1.216 | 29.08 | 12,037,404 | 12,890,804
**sse-emptyheaded-layout-hybrid** | 41.415 | 33.559 | 1.255 | 76.229 | 18,369,644 | 19,342,828
**sse-roaring** | 34.163 | 34.016 | 1.242 | 69.421 | 19,900,688 | 14,093,624
**avx2-roaring** | 34.33 | 34.417 | 1.227 | 69.974 | 20,041,100 | 14,222,416
`naive-bitvec-2d` | 0.000 | 34.866 | 1.293 | 36.159 | 12,363,160 | 13,326,284
**sse-han-bsr-qfilter** | 65.741 | 40.470 | 1.225 | 107.436 | 22,428,748 | 23,270,936
**sse-han-bsr-scalar-merge** | 66.864 | 42.155 | 1.268 | 110.287 | 22,517,596 | 23,496,224
avx2-lemire | 0.000 | 57.189 | 1.204 | 58.393 | 12,063,820 | 12,888,544
sse-lemire | 0.000 | 59.137 | 1.179 | 60.316 | 12,104,964 | 13,018,740
**sse-han-bsr-sse-shuffle** | 65.893 | 60.898 | 1.191 | 127.982 | 22,452,712 | 23,411,460
**sse-emptyheaded-layout-uint** | 39.795 | 64.724 | 1.277 | 105.796 | 18,220,408 | 19,243,188
`avx2-merge` | 0.000 | 252.718 | 1.33 | 254.048 | 12,039,640 | 12,875,956
tetzank-avx2-asm | 0.000 | 600.894 | 1.211 | 602.105 | 12,068,580 | 12,865,996
tetzank-avx2 | 0.000 | 634.122 | 1.266 | 635.388 | 12,105,228 | 12,966,500
sse-han-bmiss-sttni | 0.000 | 742.379 | 1.177 | 743.556 | 12,550,956 | 13,356,492
tetzank-avx | 0.000 | 750.062 | 1.198 | 751.26 | 12,156,420 | 13,046,100
sse-bm-lemire | 0.000 | 763.173 | 1.244 | 764.417 | 12,066,576 | 12,935,420
sse-han-qfilter | 0.000 | 904.056 | 1.204 | 905.26 | 12,198,012 | 13,157,044
sse-han-bmiss | 0.000 | 1420.820 | 1.196 | 1422.016 | 12,591,508 | 13,421,500


### webgraph_twitter

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_twitter/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_twitter/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 110.774 | 2.047 | 112.821 | 13,832,884 | 14,540,976
avx2-lemire | 0.000 | 185.080 | 2.051 | 187.131 | 13,904,284 | 14,192,240
`avx2-galloping-single` | 0.000 | 193.746 | 2.036 | 195.782 | 13,835,544 | 14,526,976
sse-lemire | 0.000 | 195.852 | 2.002 | 197.854 | 13,859,184 | 14,160,308
**sse-emptyheaded-layout-hybrid** | 43.606 | 201.713 | 2.089 | 247.408 | 22,885,468 | 23,180,516
**sse-han-bsr-sse-galloping** | 71.761 | 236.825 | 2.108 | 310.694 | 27,425,696 | 28,111,828
**sse-han-bsr-scalar-galloping** | 72.462 | 242.805 | 2.084 | 317.351 | 27,552,624 | 28,233,748
**sse-emptyheaded-layout-uint** | 41.743 | 273.564 | 1.996 | 317.303 | 20,731,400 | 20,991,160
**avx2-roaring** | 278.467 | 522.863 | 2.035 | 803.365 | 69,509,512 | 13,631,624
**sse-roaring** | 274.065 | 523.467 | 2.113 | 799.645 | 69,511,864 | 13,603,420
`avx2-merge` | 0.000 | 585.339 | 2.076 | 587.415 | 13,836,444 | 14,532,792
`naive-bitvec-2d` | 0.000 | 1637.739 | 2.071 | 1639.81 | 14,169,332 | 14,913,944
tetzank-avx2-asm | 0.000 | 1705.776 | 2.077 | 1707.853 | 13,820,960 | 14,120,344
tetzank-avx2 | 0.000 | 1779.577 | 2.096 | 1781.673 | 13,834,156 | 14,137,652
**sse-han-bsr-qfilter** | 72.308 | 2078.839 | 2.035 | 2153.182 | 27,574,332 | 28,267,908
tetzank-avx | 0.000 | 2096.555 | 2.076 | 2098.631 | 13,835,252 | 14,132,768
sse-han-bmiss-sttni | 0.000 | 2133.815 | 2.128 | 2135.943 | 14,352,516 | 15,031,428
**sse-han-bsr-scalar-merge** | 71.354 | 2212.329 | 2.088 | 2285.771 | 27,800,876 | 28,265,988
sse-bm-lemire | 0.000 | 2268.509 | 2.062 | 2270.571 | 13,813,392 | 14,115,472
sse-han-qfilter | 0.000 | 2562.825 | 2.065 | 2564.89 | 14,353,100 | 15,052,428
**sse-han-bsr-sse-shuffle** | 72.18 | 3279.679 | 2.007 | 3353.866 | 27,415,780 | 28,108,376


### webgraph_twitter/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_twitter/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_twitter/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec-2d` | 0.000 | 85.603 | 1.899 | 87.502 | 14,167,164 | 14,872,488
`avx2-hybrid` | 0.000 | 89.227 | 1.811 | 91.038 | 13,833,336 | 14,498,552
**sse-han-bsr-sse-galloping** | 68.318 | 129.343 | 1.824 | 199.485 | 26,427,504 | 27,149,508
**sse-han-bsr-scalar-galloping** | 67.575 | 133.207 | 1.779 | 202.561 | 26,913,864 | 27,594,276
`naive-bitvec` | 0.000 | 136.721 | 1.941 | 138.662 | 14,166,188 | 14,905,836
`avx2-galloping-single` | 0.000 | 161.686 | 1.924 | 163.61 | 13,833,680 | 14,519,572
**sse-roaring** | 164.465 | 201.511 | 1.817 | 367.793 | 44,328,644 | 28,008,204
**avx2-roaring** | 164.608 | 201.685 | 1.76 | 368.053 | 44,432,972 | 28,218,492
**sse-emptyheaded-layout-hybrid** | 42.836 | 237.848 | 1.75 | 282.434 | 21,815,612 | 22,457,160
avx2-lemire | 0.000 | 349.432 | 1.897 | 351.329 | 13,833,844 | 14,501,928
sse-lemire | 0.000 | 359.393 | 1.835 | 361.228 | 13,868,576 | 14,517,668
**sse-emptyheaded-layout-uint** | 40.887 | 425.063 | 1.875 | 467.825 | 20,864,848 | 21,534,088
`avx2-merge` | 0.000 | 518.669 | 1.846 | 520.515 | 13,831,652 | 14,512,820
**sse-han-bsr-qfilter** | 66.999 | 795.814 | 1.922 | 864.735 | 26,655,204 | 27,352,896
**sse-han-bsr-scalar-merge** | 67.391 | 811.940 | 1.871 | 881.202 | 26,386,044 | 27,089,772
**sse-han-bsr-sse-shuffle** | 67.655 | 1104.859 | 1.811 | 1174.325 | 27,458,908 | 28,035,944
tetzank-avx2 | 0.000 | 1322.722 | 1.8 | 1324.522 | 13,833,564 | 14,464,048
tetzank-avx | 0.000 | 1472.921 | 1.822 | 1474.743 | 13,846,084 | 14,517,272
sse-bm-lemire | 0.000 | 1500.522 | 1.832 | 1502.354 | 13,900,960 | 14,588,552
sse-han-bmiss-sttni | 0.000 | 1586.973 | 1.823 | 1588.796 | 14,347,436 | 14,990,804
tetzank-avx2-asm | 0.000 | 1741.892 | 2.004 | 1743.896 | 13,844,156 | 14,523,512
sse-han-qfilter | 0.000 | 1801.688 | 1.872 | 1803.56 | 14,266,732 | 14,959,540
sse-han-bmiss | 0.000 | 2517.058 | 1.811 | 2518.869 | 14,337,376 | 14,976,120


### webgraph_twitter/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-emptyheaded-layout-hybrid** | 42.712 | 192.141 | 1.918 | 236.771 | 22,045,332 | 22,698,728
**sse-emptyheaded-layout-uint** | 41.966 | 228.112 | 1.9 | 271.978 | 20,942,244 | 21,633,768
tetzank-avx2 | 0.000 | 1870.221 | 1.859 | 1872.08 | 13,867,968 | 14,564,416
tetzank-avx | 0.000 | 2238.099 | 1.873 | 2239.972 | 13,882,800 | 14,612,260


### snap_friendster

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_friendster/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_friendster/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-merge` | 0.000 | 51.939 | 5.935 | 57.874 | 35,180,112 | 36,620,624
`avx2-hybrid` | 0.000 | 52.787 | 5.806 | 58.593 | 35,177,908 | 36,635,712
tetzank-avx2-asm | 0.000 | 58.396 | 6.161 | 64.557 | 34,199,468 | 35,246,504
tetzank-avx2 | 0.000 | 72.421 | 6.012 | 78.433 | 34,211,268 | 35,215,228
`naive-bitvec-2d` | 0.000 | 81.373 | 5.838 | 87.211 | 38,110,196 | 39,609,432
avx2-lemire | 0.000 | 82.538 | 5.927 | 88.465 | 34,196,224 | 35,242,256
tetzank-avx | 0.000 | 86.126 | 6.058 | 92.184 | 34,197,708 | 35,245,208
sse-han-bmiss-sttni | 0.000 | 87.073 | 5.98 | 93.053 | 35,243,740 | 36,676,044
sse-lemire | 0.000 | 91.488 | 6.04 | 97.528 | 34,198,960 | 35,242,228
sse-bm-lemire | 0.000 | 96.319 | 5.977 | 102.296 | 34,202,340 | 35,225,796
`avx2-galloping-single` | 0.000 | 106.817 | 6.04 | 112.857 | 35,174,448 | 36,612,684
sse-han-qfilter | 0.000 | 106.926 | 5.826 | 112.752 | 35,240,148 | 36,663,748
**sse-emptyheaded-layout-hybrid** | 129.307 | 123.072 | 6.049 | 258.428 | 52,677,552 | 53,724,088
**sse-emptyheaded-layout-uint** | 127.173 | 127.608 | 5.916 | 260.697 | 52,676,052 | 53,723,912
**sse-han-bsr-qfilter** | 244.397 | 133.003 | 5.878 | 383.278 | 70,640,132 | 71,869,204
**sse-han-bsr-sse-galloping** | 245.68 | 141.995 | 5.726 | 393.401 | 70,621,988 | 71,762,580
**sse-han-bsr-scalar-galloping** | 245.377 | 151.227 | 5.898 | 402.502 | 70,539,264 | 71,990,360
**sse-han-bsr-scalar-merge** | 245.94 | 152.010 | 5.81 | 403.76 | 70,614,936 | 72,050,616
sse-han-bmiss | 0.000 | 165.609 | 5.922 | 171.531 | 35,241,624 | 36,686,180
**sse-han-bsr-sse-shuffle** | 244.929 | 194.871 | 5.783 | 445.583 | 70,628,484 | 71,916,060
`naive-bitvec` | 0.000 | 771.390 | 5.756 | 777.146 | 38,111,032 | 39,592,228


### snap_friendster/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_friendster/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_friendster/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_friendster/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---