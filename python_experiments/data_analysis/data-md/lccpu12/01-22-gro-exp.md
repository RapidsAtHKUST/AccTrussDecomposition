# O(E) intersection count time


Unit: seconds


### snap_livejournal

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_livejournal/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-merge` | 0.000 | 0.888 | 0.208 | 1.096 | 684,504 | 755,996
sse-lemire | 0.000 | 0.893 | 0.207 | 1.1 | 684,216 | 738,992
`avx2-hybrid` | 0.000 | 0.904 | 0.195 | 1.099 | 684,116 | 757,664
avx2-lemire | 0.000 | 0.941 | 0.221 | 1.162 | 684,448 | 751,260
tetzank-avx2 | 0.000 | 0.990 | 0.152 | 1.142 | 685,056 | 750,344
tetzank-avx2-asm | 0.000 | 0.996 | 0.19 | 1.186 | 684,112 | 740,452
sse-bm-lemire | 0.000 | 1.030 | 0.22 | 1.25 | 684,316 | 752,684
`naive-bitvec` | 3.233 | 1.071 | 0.27 | 4.574 | 750,868 | 872,900
sse-han-qfilter | 0.000 | 1.098 | 0.166 | 1.264 | 684,892 | 738,520
sse-han-bmiss-sttni | 0.000 | 1.101 | 0.179 | 1.28 | 683,692 | 756,664
`naive-bitvec-2d` | 4.134 | 1.197 | 0.209 | 5.54 | 749,872 | 872,280
tetzank-avx | 0.000 | 1.221 | 0.185 | 1.406 | 684,224 | 739,964
sse-han-bmiss | 0.000 | 1.292 | 0.222 | 1.514 | 684,844 | 742,432
**sse-han-bsr-qfilter** | 1.8 | 1.322 | 0.202 | 3.324 | 1,370,244 | 1,430,912
**sse-emptyheaded-layout-hybrid** | 1.287 | 1.355 | 0.198 | 2.84 | 1,108,940 | 1,228,260
`avx2-galloping-single` | 0.000 | 1.356 | 0.228 | 1.584 | 684,852 | 753,536
**sse-han-bsr-sse-shuffle** | 1.554 | 1.426 | 0.151 | 3.131 | 1,370,296 | 1,434,612
**sse-emptyheaded-layout-uint** | 1.264 | 1.436 | 0.177 | 2.877 | 1,108,728 | 1,228,212
**sse-han-bsr-sse-galloping** | 1.572 | 1.538 | 0.157 | 3.267 | 1,370,896 | 1,445,488
**sse-han-bsr-scalar-merge** | 2.146 | 1.703 | 0.177 | 4.026 | 1,371,872 | 1,420,308
**sse-han-bsr-scalar-galloping** | 1.95 | 1.753 | 0.226 | 3.929 | 1,371,292 | 1,437,268
**avx2-roaring** | 6.719 | 7.610 | 0.478 | 14.807 | 2,423,876 | 876,908
**sse-roaring** | 6.227 | 8.724 | 0.474 | 15.425 | 2,423,832 | 882,460


### snap_livejournal/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 5.271 | 1.157 | 0.252 | 6.68 | 750,360 | 873,644
avx2-lemire | 0.000 | 1.224 | 0.185 | 1.409 | 684,140 | 737,112
`naive-bitvec-2d` | 6.254 | 1.265 | 0.221 | 7.74 | 749,884 | 872,948
sse-lemire | 0.000 | 1.315 | 0.228 | 1.543 | 684,272 | 742,100
`avx2-merge` | 0.000 | 1.337 | 0.249 | 1.586 | 683,516 | 741,244
`avx2-hybrid` | 0.000 | 1.346 | 0.215 | 1.561 | 685,408 | 738,964
tetzank-avx2 | 0.000 | 1.358 | 0.213 | 1.571 | 684,992 | 737,088
sse-bm-lemire | 0.000 | 1.375 | 0.267 | 1.642 | 684,628 | 738,664
tetzank-avx2-asm | 0.000 | 1.386 | 0.202 | 1.588 | 683,380 | 744,016
sse-han-qfilter | 0.000 | 1.455 | 0.245 | 1.7 | 684,080 | 739,804
sse-han-bmiss-sttni | 0.000 | 1.539 | 0.204 | 1.743 | 684,948 | 739,580
tetzank-avx | 0.000 | 1.576 | 0.198 | 1.774 | 684,500 | 738,148
sse-han-bmiss | 0.000 | 1.734 | 0.245 | 1.979 | 684,224 | 742,108
**sse-emptyheaded-layout-uint** | 1.043 | 1.950 | 0.264 | 3.257 | 1,110,636 | 1,224,392
**sse-emptyheaded-layout-hybrid** | 1.102 | 2.051 | 0.19 | 3.343 | 1,110,032 | 1,224,892
`avx2-galloping-single` | 0.000 | 2.129 | 0.229 | 2.358 | 685,000 | 743,080
**sse-han-bsr-qfilter** | 1.958 | 2.683 | 0.211 | 4.852 | 1,373,052 | 1,423,836
**sse-han-bsr-sse-shuffle** | 1.936 | 2.691 | 0.262 | 4.889 | 1,372,980 | 1,431,940
**sse-han-bsr-scalar-merge** | 2.163 | 3.004 | 0.187 | 5.354 | 1,376,904 | 1,433,508
**sse-han-bsr-sse-galloping** | 1.661 | 3.025 | 0.3 | 4.986 | 1,372,900 | 1,431,268
**sse-han-bsr-scalar-galloping** | 1.793 | 3.174 | 0.195 | 5.162 | 1,379,528 | 1,436,400
**avx2-roaring** | 10.569 | 15.988 | 0.833 | 27.39 | 3,781,664 | 970,868
**sse-roaring** | 12.578 | 16.762 | 0.561 | 29.901 | 3,781,676 | 962,840


### snap_livejournal/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_livejournal/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_livejournal/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 1.282 | 1.018 | 0.194 | 2.494 | 743,236 | 870,452
avx2-lemire | 0.000 | 1.045 | 0.158 | 1.203 | 683,916 | 735,948
sse-bm-lemire | 0.000 | 1.101 | 0.182 | 1.283 | 683,936 | 742,588
sse-lemire | 0.000 | 1.118 | 0.164 | 1.282 | 685,112 | 738,580
tetzank-avx2 | 0.000 | 1.153 | 0.166 | 1.319 | 684,096 | 744,552
`avx2-merge` | 0.000 | 1.174 | 0.184 | 1.358 | 684,144 | 736,944
`avx2-hybrid` | 0.000 | 1.243 | 0.194 | 1.437 | 684,536 | 740,992
tetzank-avx2-asm | 0.000 | 1.248 | 0.165 | 1.413 | 684,132 | 742,868
`naive-bitvec-2d` | 1.464 | 1.268 | 0.229 | 2.961 | 746,148 | 874,416
sse-han-qfilter | 0.000 | 1.295 | 0.215 | 1.51 | 684,968 | 744,724
sse-han-bmiss-sttni | 0.000 | 1.357 | 0.163 | 1.52 | 684,284 | 745,088
sse-han-bmiss | 0.000 | 1.403 | 0.17 | 1.573 | 684,732 | 738,696
tetzank-avx | 0.000 | 1.407 | 0.251 | 1.658 | 683,996 | 737,616
`avx2-galloping-single` | 0.000 | 1.574 | 0.196 | 1.77 | 683,528 | 740,812
**sse-emptyheaded-layout-hybrid** | 1.243 | 1.610 | 0.177 | 3.03 | 1,109,864 | 1,224,436
**sse-emptyheaded-layout-uint** | 1.245 | 1.810 | 0.161 | 3.216 | 1,109,700 | 1,223,860
**sse-han-bsr-qfilter** | 2.114 | 1.898 | 0.17 | 4.182 | 1,372,896 | 1,423,236
**sse-han-bsr-sse-shuffle** | 2.069 | 2.125 | 0.215 | 4.409 | 1,371,688 | 1,441,092
**sse-han-bsr-sse-galloping** | 1.951 | 2.393 | 0.171 | 4.515 | 1,371,948 | 1,435,804
**sse-han-bsr-scalar-galloping** | 1.861 | 2.506 | 0.155 | 4.522 | 1,372,004 | 1,419,416
**sse-han-bsr-scalar-merge** | 2.087 | 2.527 | 0.177 | 4.791 | 1,372,784 | 1,427,504
**sse-roaring** | 8.127 | 7.370 | 0.338 | 15.835 | 3,029,712 | 918,968
**avx2-roaring** | 8.739 | 7.391 | 0.33 | 16.46 | 3,029,748 | 911,692


### snap_livejournal/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 1.035 | 0.164 | 1.199 | 684,148 | 752,704
`avx2-merge` | 0.000 | 1.086 | 0.195 | 1.281 | 683,600 | 756,200
sse-lemire | 0.000 | 1.107 | 0.225 | 1.332 | 684,340 | 753,488
avx2-lemire | 0.000 | 1.111 | 0.2 | 1.311 | 684,532 | 754,724
`naive-bitvec` | 4.402 | 1.135 | 0.224 | 5.761 | 750,752 | 875,252
tetzank-avx2-asm | 0.000 | 1.238 | 0.198 | 1.436 | 684,064 | 751,516
sse-han-bmiss-sttni | 0.000 | 1.240 | 0.192 | 1.432 | 684,144 | 752,888
`naive-bitvec-2d` | 3.926 | 1.255 | 0.211 | 5.392 | 750,752 | 874,524
tetzank-avx2 | 0.000 | 1.255 | 0.186 | 1.441 | 684,644 | 735,760
sse-bm-lemire | 0.000 | 1.279 | 0.185 | 1.464 | 684,616 | 744,888
sse-han-qfilter | 0.000 | 1.329 | 0.166 | 1.495 | 684,668 | 741,468
tetzank-avx | 0.000 | 1.385 | 0.213 | 1.598 | 683,656 | 737,212
sse-han-bmiss | 0.000 | 1.416 | 0.22 | 1.636 | 684,656 | 744,472
**sse-emptyheaded-layout-hybrid** | 1.306 | 1.619 | 0.175 | 3.1 | 1,109,464 | 1,230,352
`avx2-galloping-single` | 0.000 | 1.622 | 0.203 | 1.825 | 684,412 | 745,032
**sse-emptyheaded-layout-uint** | 1.165 | 1.632 | 0.172 | 2.969 | 1,110,572 | 1,229,700
**sse-han-bsr-qfilter** | 1.72 | 1.749 | 0.174 | 3.643 | 1,372,112 | 1,429,696
**sse-han-bsr-sse-shuffle** | 1.875 | 2.093 | 0.216 | 4.184 | 1,372,508 | 1,426,248
**sse-han-bsr-sse-galloping** | 1.752 | 2.325 | 0.198 | 4.275 | 1,371,748 | 1,419,560
**sse-han-bsr-scalar-merge** | 1.802 | 2.523 | 0.169 | 4.494 | 1,372,512 | 1,424,276
**sse-han-bsr-scalar-galloping** | 2.001 | 2.576 | 0.192 | 4.769 | 1,371,996 | 1,434,308
**sse-roaring** | 5.665 | 9.526 | 0.762 | 15.953 | 2,804,112 | 1,493,772
**avx2-roaring** | 5.854 | 10.571 | 0.569 | 16.994 | 2,804,112 | 1,482,040


### snap_orkut

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_orkut/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 12.605 | 6.390 | 0.542 | 19.537 | 2,168,360 | 2,223,484
avx2-lemire | 0.000 | 7.026 | 0.54 | 7.566 | 2,124,676 | 2,156,724
sse-lemire | 0.000 | 7.242 | 0.447 | 7.689 | 2,124,712 | 2,152,296
`avx2-hybrid` | 0.000 | 7.644 | 0.507 | 8.151 | 2,123,724 | 2,154,720
`avx2-merge` | 0.000 | 7.780 | 0.467 | 8.247 | 2,123,740 | 2,157,108
tetzank-avx2-asm | 0.000 | 7.842 | 0.443 | 8.285 | 2,124,660 | 2,154,740
`naive-bitvec-2d` | 12.95 | 7.878 | 0.568 | 21.396 | 2,168,368 | 2,225,116
tetzank-avx2 | 0.000 | 8.315 | 0.427 | 8.742 | 2,124,620 | 2,157,296
sse-han-bmiss-sttni | 0.000 | 8.820 | 0.479 | 9.299 | 2,124,820 | 2,156,712
**sse-han-bsr-qfilter** | 4.932 | 9.021 | 0.516 | 14.469 | 4,028,760 | 4,055,984
sse-bm-lemire | 0.000 | 9.085 | 0.552 | 9.637 | 2,124,700 | 2,154,816
sse-han-qfilter | 0.000 | 9.804 | 0.487 | 10.291 | 2,124,740 | 2,156,396
**sse-emptyheaded-layout-hybrid** | 2.742 | 10.338 | 0.475 | 13.555 | 3,165,292 | 3,205,408
tetzank-avx | 0.000 | 10.350 | 0.452 | 10.802 | 2,124,652 | 2,155,560
**sse-han-bsr-sse-shuffle** | 5.83 | 10.445 | 0.446 | 16.721 | 4,028,756 | 4,057,736
**sse-emptyheaded-layout-uint** | 2.588 | 10.558 | 0.547 | 13.693 | 3,154,888 | 3,195,016
sse-han-bmiss | 0.000 | 11.062 | 0.478 | 11.54 | 2,124,852 | 2,158,128
`avx2-galloping-single` | 0.000 | 11.682 | 0.551 | 12.233 | 2,123,720 | 2,155,140
**sse-han-bsr-sse-galloping** | 4.772 | 12.131 | 0.505 | 17.408 | 4,028,748 | 4,062,004
**sse-han-bsr-scalar-merge** | 5.176 | 13.340 | 0.544 | 19.06 | 4,028,700 | 4,055,360
**sse-han-bsr-scalar-galloping** | 4.968 | 14.009 | 0.457 | 19.434 | 4,028,788 | 4,057,340
**avx2-roaring** | 16.995 | 26.565 | 1.022 | 44.582 | 6,629,192 | 2,468,552
**sse-roaring** | 15.054 | 30.469 | 1.141 | 46.664 | 6,629,236 | 2,460,756


### snap_orkut/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 12.564 | 6.467 | 0.58 | 19.611 | 2,168,368 | 2,224,320
`naive-bitvec-2d` | 12.869 | 7.642 | 0.521 | 21.032 | 2,168,240 | 2,224,784
avx2-lemire | 0.000 | 9.682 | 0.625 | 10.307 | 2,124,816 | 2,153,440
sse-lemire | 0.000 | 9.719 | 0.598 | 10.317 | 2,124,764 | 2,152,092
`avx2-merge` | 0.000 | 10.131 | 0.587 | 10.718 | 2,123,768 | 2,152,284
`avx2-hybrid` | 0.000 | 10.200 | 0.658 | 10.858 | 2,123,692 | 2,150,448
tetzank-avx2 | 0.000 | 10.587 | 0.708 | 11.295 | 2,124,780 | 2,152,836
tetzank-avx2-asm | 0.000 | 10.602 | 0.596 | 11.198 | 2,124,776 | 2,154,068
sse-han-bmiss-sttni | 0.000 | 10.947 | 0.642 | 11.589 | 2,125,016 | 2,152,644
sse-han-qfilter | 0.000 | 11.316 | 0.609 | 11.925 | 2,124,952 | 2,153,628
sse-bm-lemire | 0.000 | 11.754 | 0.55 | 12.304 | 2,124,760 | 2,153,472
sse-han-bmiss | 0.000 | 12.578 | 0.585 | 13.163 | 2,124,972 | 2,151,416
tetzank-avx | 0.000 | 12.926 | 0.674 | 13.6 | 2,124,788 | 2,152,288
**sse-emptyheaded-layout-hybrid** | 2.572 | 13.217 | 0.6 | 16.389 | 3,169,012 | 3,210,276
**sse-emptyheaded-layout-uint** | 2.876 | 13.732 | 0.598 | 17.206 | 3,156,304 | 3,195,204
`avx2-galloping-single` | 0.000 | 15.062 | 0.769 | 15.831 | 2,123,728 | 2,152,060
**sse-han-bsr-qfilter** | 4.626 | 17.778 | 0.615 | 23.019 | 4,045,848 | 4,071,988
**sse-han-bsr-sse-shuffle** | 5.583 | 20.961 | 0.524 | 27.068 | 4,045,972 | 4,072,604
**sse-han-bsr-sse-galloping** | 5.073 | 21.964 | 0.56 | 27.597 | 4,045,756 | 4,072,868
**sse-han-bsr-scalar-merge** | 4.753 | 24.382 | 0.565 | 29.7 | 4,045,916 | 4,072,620
**sse-han-bsr-scalar-galloping** | 5.061 | 25.254 | 0.673 | 30.988 | 4,045,912 | 4,074,332
**sse-roaring** | 22.302 | 48.059 | 1.023 | 71.384 | 8,253,916 | 2,571,276
**avx2-roaring** | 19.597 | 51.004 | 1.241 | 71.842 | 8,253,948 | 2,564,676


### snap_orkut/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_orkut/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_orkut/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 9.02 | 6.427 | 0.588 | 16.035 | 2,168,356 | 2,226,100
avx2-lemire | 0.000 | 6.851 | 0.477 | 7.328 | 2,124,688 | 2,152,012
sse-lemire | 0.000 | 7.298 | 0.454 | 7.752 | 2,124,708 | 2,154,516
`avx2-merge` | 0.000 | 8.184 | 0.47 | 8.654 | 2,123,732 | 2,153,144
`avx2-hybrid` | 0.000 | 8.248 | 0.561 | 8.809 | 2,123,744 | 2,152,912
`naive-bitvec-2d` | 7.574 | 8.263 | 0.541 | 16.378 | 2,168,348 | 2,223,820
tetzank-avx2-asm | 0.000 | 8.795 | 0.45 | 9.245 | 2,124,692 | 2,154,824
tetzank-avx2 | 0.000 | 8.801 | 0.447 | 9.248 | 2,124,668 | 2,154,668
sse-bm-lemire | 0.000 | 8.971 | 0.454 | 9.425 | 2,124,616 | 2,153,656
sse-han-bmiss-sttni | 0.000 | 10.048 | 0.584 | 10.632 | 2,124,840 | 2,155,076
sse-han-qfilter | 0.000 | 10.452 | 0.537 | 10.989 | 2,124,820 | 2,154,256
**sse-emptyheaded-layout-hybrid** | 2.792 | 10.877 | 0.42 | 14.089 | 3,167,372 | 3,206,696
tetzank-avx | 0.000 | 11.065 | 0.482 | 11.547 | 2,124,628 | 2,154,368
**sse-emptyheaded-layout-uint** | 2.815 | 11.409 | 0.415 | 14.639 | 3,154,492 | 3,193,280
sse-han-bmiss | 0.000 | 11.867 | 0.588 | 12.455 | 2,124,840 | 2,154,288
`avx2-galloping-single` | 0.000 | 12.487 | 0.551 | 13.038 | 2,123,732 | 2,153,536
**sse-han-bsr-qfilter** | 4.936 | 13.306 | 0.528 | 18.77 | 4,034,816 | 4,060,996
**sse-han-bsr-sse-shuffle** | 5.024 | 16.357 | 0.572 | 21.953 | 4,034,908 | 4,063,656
**sse-han-bsr-sse-galloping** | 5.07 | 17.630 | 0.526 | 23.226 | 4,034,868 | 4,061,332
**sse-han-bsr-scalar-merge** | 4.415 | 19.425 | 0.516 | 24.356 | 4,034,836 | 4,061,160
**sse-han-bsr-scalar-galloping** | 5.441 | 21.534 | 0.546 | 27.521 | 4,034,884 | 4,063,840
**sse-roaring** | 15.556 | 29.104 | 0.835 | 45.495 | 7,213,436 | 2,508,072
**avx2-roaring** | 22.627 | 37.831 | 1.288 | 61.746 | 7,213,572 | 2,477,552


### snap_orkut/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 11.218 | 6.204 | 0.538 | 17.96 | 2,168,348 | 2,222,548
`naive-bitvec-2d` | 10.748 | 7.734 | 0.638 | 19.12 | 2,168,360 | 2,225,576
avx2-lemire | 0.000 | 7.896 | 0.743 | 8.639 | 2,124,808 | 2,155,644
sse-lemire | 0.000 | 8.362 | 0.615 | 8.977 | 2,124,736 | 2,156,204
`avx2-hybrid` | 0.000 | 8.448 | 0.516 | 8.964 | 2,123,736 | 2,155,840
`avx2-merge` | 0.000 | 8.516 | 0.569 | 9.085 | 2,123,736 | 2,156,856
tetzank-avx2-asm | 0.000 | 9.076 | 0.757 | 9.833 | 2,124,756 | 2,156,284
tetzank-avx2 | 0.000 | 9.414 | 0.546 | 9.96 | 2,124,768 | 2,157,244
sse-han-bmiss-sttni | 0.000 | 9.705 | 0.513 | 10.218 | 2,124,920 | 2,156,528
sse-bm-lemire | 0.000 | 10.369 | 0.528 | 10.897 | 2,124,800 | 2,157,364
sse-han-qfilter | 0.000 | 10.406 | 0.641 | 11.047 | 2,124,936 | 2,157,396
sse-han-bmiss | 0.000 | 11.605 | 0.592 | 12.197 | 2,124,936 | 2,157,172
**sse-emptyheaded-layout-hybrid** | 2.49 | 11.686 | 0.52 | 14.696 | 3,166,924 | 3,207,628
**sse-emptyheaded-layout-uint** | 2.756 | 11.687 | 0.497 | 14.94 | 3,156,248 | 3,197,960
tetzank-avx | 0.000 | 11.732 | 0.63 | 12.362 | 2,124,760 | 2,156,468
**sse-han-bsr-qfilter** | 4.854 | 12.638 | 0.727 | 18.219 | 4,037,520 | 4,063,932
`avx2-galloping-single` | 0.000 | 13.401 | 0.483 | 13.884 | 2,123,720 | 2,155,384
**sse-han-bsr-sse-shuffle** | 4.892 | 15.260 | 0.485 | 20.637 | 4,037,496 | 4,069,280
**sse-han-bsr-sse-galloping** | 5.432 | 17.921 | 0.506 | 23.859 | 4,037,432 | 4,064,132
**sse-han-bsr-scalar-merge** | 4.964 | 19.615 | 0.547 | 25.126 | 4,037,496 | 4,066,364
**sse-han-bsr-scalar-galloping** | 5.396 | 20.620 | 0.536 | 26.552 | 4,037,540 | 4,062,768
**sse-roaring** | 15.043 | 30.080 | 0.859 | 45.982 | 6,424,744 | 2,785,332
**avx2-roaring** | 14.954 | 30.683 | 0.923 | 46.56 | 6,424,684 | 2,794,584


### webgraph_eu

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_eu/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-qfilter** | 4.813 | 11.490 | 0.717 | 17.02 | 5,485,920 | 5,600,020
**sse-han-bsr-sse-shuffle** | 5.246 | 12.230 | 0.712 | 18.188 | 5,484,504 | 5,579,484
**sse-han-bsr-scalar-merge** | 5.287 | 12.280 | 0.786 | 18.353 | 5,484,780 | 5,570,020
**avx2-roaring** | 13.665 | 13.148 | 1.115 | 27.928 | 6,683,268 | 3,889,188
**sse-roaring** | 13.561 | 14.714 | 1.087 | 29.362 | 6,683,212 | 3,877,536
**sse-han-bsr-scalar-galloping** | 5.392 | 17.981 | 0.765 | 24.138 | 5,484,724 | 5,593,152
**sse-han-bsr-sse-galloping** | 5.925 | 18.797 | 0.773 | 25.495 | 5,484,892 | 5,584,280
**sse-emptyheaded-layout-hybrid** | 3.089 | 22.445 | 0.999 | 26.533 | 4,927,264 | 5,028,388
tetzank-avx2 | 0.000 | 98.771 | 0.749 | 99.52 | 3,595,416 | 3,693,888
`avx2-hybrid` | 0.000 | 101.863 | 0.92 | 102.783 | 3,589,224 | 3,693,768
`avx2-merge` | 0.000 | 102.621 | 1.018 | 103.639 | 3,588,252 | 3,693,392
tetzank-avx2-asm | 0.000 | 103.209 | 0.788 | 103.997 | 3,595,556 | 3,707,900
sse-bm-lemire | 0.000 | 111.067 | 1.106 | 112.173 | 3,596,432 | 3,705,924
**sse-emptyheaded-layout-uint** | 3.407 | 124.532 | 0.959 | 128.898 | 5,519,588 | 5,602,184
`naive-bitvec` | 30.751 | 125.757 | 0.847 | 157.355 | 3,753,420 | 3,864,704
tetzank-avx | 0.000 | 139.798 | 0.715 | 140.513 | 3,596,264 | 3,708,156
sse-han-qfilter | 0.000 | 153.015 | 0.684 | 153.699 | 3,596,348 | 3,706,376
avx2-lemire | 0.000 | 173.884 | 0.825 | 174.709 | 3,595,228 | 3,695,768
sse-han-bmiss | 0.000 | 196.383 | 0.754 | 197.137 | 3,594,840 | 3,680,888
sse-lemire | 0.000 | 200.615 | 0.773 | 201.388 | 3,595,760 | 3,694,896
`naive-bitvec-2d` | 33.396 | 214.659 | 0.964 | 249.019 | 3,753,212 | 3,849,196
sse-han-bmiss-sttni | 0.000 | 268.905 | 0.771 | 269.676 | 3,595,660 | 3,698,844
`avx2-galloping-single` | 0.000 | 386.561 | 0.964 | 387.525 | 3,589,116 | 3,701,968


### webgraph_eu/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 49.061 | 132.389 | 0.987 | 182.437 | 3,753,348 | 3,855,172
`avx2-hybrid` | 0.000 | 132.592 | 1.056 | 133.648 | 3,591,224 | 3,701,804
`avx2-merge` | 0.000 | 135.041 | 0.909 | 135.95 | 3,589,068 | 3,688,884
tetzank-avx2-asm | 0.000 | 145.149 | 1.037 | 146.186 | 3,605,128 | 3,714,540
**avx2-roaring** | 20.172 | 145.461 | 1.386 | 167.019 | 9,585,084 | 4,062,240
**sse-roaring** | 25.115 | 145.970 | 1.392 | 172.477 | 9,584,612 | 4,060,308
tetzank-avx2 | 0.000 | 150.018 | 0.856 | 150.874 | 3,603,612 | 3,687,448
**sse-han-bsr-scalar-merge** | 6.744 | 151.005 | 0.907 | 158.656 | 6,400,532 | 6,482,368
sse-bm-lemire | 0.000 | 159.954 | 0.852 | 160.806 | 3,602,164 | 3,690,712
**sse-han-bsr-qfilter** | 7.406 | 164.099 | 0.812 | 172.317 | 6,399,752 | 6,504,100
**sse-han-bsr-sse-shuffle** | 7.37 | 168.619 | 0.882 | 176.871 | 6,399,176 | 6,491,416
**sse-emptyheaded-layout-hybrid** | 3.87 | 170.688 | 0.816 | 175.374 | 5,585,596 | 5,690,984
**sse-emptyheaded-layout-uint** | 3.65 | 173.313 | 0.922 | 177.885 | 5,532,948 | 5,610,244
avx2-lemire | 0.000 | 186.176 | 0.896 | 187.072 | 3,603,580 | 3,717,412
tetzank-avx | 0.000 | 204.320 | 0.979 | 205.299 | 3,602,536 | 3,702,604
`naive-bitvec-2d` | 52.019 | 211.272 | 1.16 | 264.451 | 3,753,476 | 3,858,612
sse-lemire | 0.000 | 215.132 | 0.795 | 215.927 | 3,603,072 | 3,699,904
sse-han-qfilter | 0.000 | 217.470 | 0.908 | 218.378 | 3,604,808 | 3,713,576
**sse-han-bsr-scalar-galloping** | 6.369 | 237.540 | 1.027 | 244.936 | 6,401,044 | 6,511,008
**sse-han-bsr-sse-galloping** | 7.293 | 246.297 | 1.036 | 254.626 | 6,402,944 | 6,511,724
sse-han-bmiss | 0.000 | 263.950 | 0.903 | 264.853 | 3,603,536 | 3,708,716
sse-han-bmiss-sttni | 0.000 | 324.110 | 0.781 | 324.891 | 3,603,908 | 3,693,128
`avx2-galloping-single` | 0.000 | 393.516 | 0.861 | 394.377 | 3,589,224 | 3,681,220


### webgraph_eu/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_eu/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_eu/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-qfilter** | 5.067 | 18.009 | 0.946 | 24.022 | 5,537,860 | 5,644,976
**sse-han-bsr-sse-shuffle** | 5.463 | 19.477 | 0.783 | 25.723 | 5,537,288 | 5,643,236
**sse-han-bsr-scalar-merge** | 4.987 | 19.620 | 0.911 | 25.518 | 5,537,068 | 5,639,704
**sse-emptyheaded-layout-hybrid** | 3.495 | 24.550 | 1.088 | 29.133 | 4,937,376 | 5,022,204
**sse-han-bsr-scalar-galloping** | 4.893 | 27.541 | 0.834 | 33.268 | 5,537,516 | 5,639,192
**sse-han-bsr-sse-galloping** | 4.544 | 28.835 | 0.803 | 34.182 | 5,537,836 | 5,636,228
**avx2-roaring** | 10.528 | 29.164 | 1.145 | 40.837 | 7,312,780 | 4,512,068
**sse-roaring** | 13.051 | 29.845 | 1.004 | 43.9 | 7,312,684 | 4,519,492
tetzank-avx2 | 0.000 | 103.220 | 0.837 | 104.057 | 3,595,936 | 3,699,248
`avx2-hybrid` | 0.000 | 103.790 | 0.775 | 104.565 | 3,588,720 | 3,680,792
`avx2-merge` | 0.000 | 106.258 | 0.801 | 107.059 | 3,588,632 | 3,686,052
tetzank-avx2-asm | 0.000 | 106.287 | 0.721 | 107.008 | 3,595,460 | 3,692,284
sse-bm-lemire | 0.000 | 115.416 | 0.722 | 116.138 | 3,595,652 | 3,700,420
**sse-emptyheaded-layout-uint** | 3.198 | 128.729 | 0.735 | 132.662 | 5,519,828 | 5,614,420
`naive-bitvec` | 24.517 | 132.827 | 0.916 | 158.26 | 3,753,628 | 3,850,992
tetzank-avx | 0.000 | 143.536 | 0.738 | 144.274 | 3,595,236 | 3,703,676
sse-han-qfilter | 0.000 | 163.766 | 0.731 | 164.497 | 3,595,924 | 3,691,764
avx2-lemire | 0.000 | 176.933 | 0.717 | 177.65 | 3,595,952 | 3,691,352
sse-han-bmiss | 0.000 | 199.138 | 0.827 | 199.965 | 3,596,312 | 3,695,856
sse-lemire | 0.000 | 201.031 | 0.709 | 201.74 | 3,595,648 | 3,702,452
`naive-bitvec-2d` | 23.391 | 218.551 | 0.892 | 242.834 | 3,753,268 | 3,860,856
sse-han-bmiss-sttni | 0.000 | 272.005 | 0.713 | 272.718 | 3,595,424 | 3,692,240
`avx2-galloping-single` | 0.000 | 380.172 | 0.79 | 380.962 | 3,588,488 | 3,697,056


### webgraph_eu/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-qfilter** | 6.021 | 17.868 | 0.733 | 24.622 | 5,510,996 | 5,599,016
**sse-han-bsr-scalar-merge** | 5.238 | 18.331 | 0.832 | 24.401 | 5,510,520 | 5,595,752
**sse-han-bsr-sse-shuffle** | 4.673 | 20.566 | 0.836 | 26.075 | 5,510,568 | 5,620,252
**sse-han-bsr-scalar-galloping** | 4.921 | 22.785 | 0.938 | 28.644 | 5,510,780 | 5,600,732
**sse-han-bsr-sse-galloping** | 5.524 | 23.997 | 0.916 | 30.437 | 5,510,636 | 5,590,896
**avx2-roaring** | 12.327 | 28.898 | 1.072 | 42.297 | 6,534,972 | 5,384,316
**sse-roaring** | 12.902 | 29.712 | 1.098 | 43.712 | 6,534,984 | 5,264,252
`avx2-hybrid` | 0.000 | 101.561 | 0.664 | 102.225 | 3,588,788 | 3,672,244
`avx2-merge` | 0.000 | 105.527 | 0.79 | 106.317 | 3,589,092 | 3,681,516
tetzank-avx2 | 0.000 | 122.314 | 0.657 | 122.971 | 3,596,128 | 3,694,348
`naive-bitvec` | 33.701 | 132.981 | 1.067 | 167.749 | 3,753,404 | 3,860,164
tetzank-avx2-asm | 0.000 | 135.292 | 0.94 | 136.232 | 3,596,224 | 3,693,384
sse-bm-lemire | 0.000 | 139.880 | 0.829 | 140.709 | 3,596,268 | 3,685,432
**sse-emptyheaded-layout-hybrid** | 3.64 | 150.844 | 0.839 | 155.323 | 5,540,360 | 5,624,160
**sse-emptyheaded-layout-uint** | 3.684 | 156.445 | 1.089 | 161.218 | 5,521,684 | 5,613,384
tetzank-avx | 0.000 | 174.943 | 0.668 | 175.611 | 3,595,996 | 3,696,976
avx2-lemire | 0.000 | 177.922 | 1.003 | 178.925 | 3,596,216 | 3,684,880
sse-han-qfilter | 0.000 | 194.930 | 0.863 | 195.793 | 3,594,968 | 3,695,012
sse-lemire | 0.000 | 203.389 | 0.858 | 204.247 | 3,595,108 | 3,684,360
`naive-bitvec-2d` | 38.748 | 218.448 | 0.871 | 258.067 | 3,753,648 | 3,850,148
sse-han-bmiss | 0.000 | 247.730 | 0.931 | 248.661 | 3,595,488 | 3,698,544
sse-han-bmiss-sttni | 0.000 | 301.424 | 0.971 | 302.395 | 3,596,400 | 3,687,108
`avx2-galloping-single` | 0.000 | 395.645 | 0.771 | 396.416 | 3,589,484 | 3,676,932


### webgraph_uk

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_uk/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-sse-galloping** | 9.485 | 1.616 | 0.453 | 11.554 | 6,007,464 | 6,239,588
**sse-han-bsr-scalar-galloping** | 8.544 | 1.697 | 0.713 | 10.954 | 6,012,132 | 6,244,332
**sse-han-bsr-scalar-merge** | 8.912 | 1.740 | 0.527 | 11.179 | 6,009,172 | 6,245,024
**sse-han-bsr-sse-shuffle** | 9.245 | 1.764 | 0.447 | 11.456 | 6,007,712 | 6,241,828
`avx2-hybrid` | 0.000 | 1.851 | 0.551 | 2.402 | 3,012,480 | 3,278,564
**sse-han-bsr-qfilter** | 8.601 | 2.331 | 0.615 | 11.547 | 6,012,352 | 6,183,200
`avx2-merge` | 0.000 | 2.493 | 0.806 | 3.299 | 3,012,960 | 3,232,772
avx2-lemire | 0.000 | 2.829 | 0.854 | 3.683 | 3,015,244 | 3,253,444
sse-lemire | 0.000 | 2.917 | 0.78 | 3.697 | 3,015,080 | 3,236,468
`naive-bitvec` | 20.567 | 3.254 | 0.887 | 24.708 | 3,283,856 | 3,531,156
`naive-bitvec-2d` | 18.364 | 3.623 | 0.902 | 22.889 | 3,283,876 | 3,527,104
`avx2-galloping-single` | 0.000 | 3.898 | 0.72 | 4.618 | 3,012,960 | 3,202,408
**sse-emptyheaded-layout-uint** | 5.266 | 4.197 | 0.583 | 10.046 | 4,892,148 | 5,103,240
**sse-emptyheaded-layout-hybrid** | 4.904 | 4.387 | 0.597 | 9.888 | 4,875,736 | 5,117,752
tetzank-avx2 | 0.000 | 4.576 | 0.572 | 5.148 | 3,014,724 | 3,247,440
sse-bm-lemire | 0.000 | 4.784 | 0.443 | 5.227 | 3,015,124 | 3,218,012
tetzank-avx | 0.000 | 5.296 | 0.49 | 5.786 | 3,015,156 | 3,239,552
sse-han-qfilter | 0.000 | 5.777 | 0.553 | 6.33 | 3,015,488 | 3,246,096
sse-han-bmiss | 0.000 | 5.992 | 0.53 | 6.522 | 3,015,048 | 3,213,036
sse-han-bmiss-sttni | 0.000 | 6.182 | 0.502 | 6.684 | 3,015,356 | 3,209,896
**sse-roaring** | 18.944 | 6.345 | 0.609 | 25.898 | 5,926,096 | 3,381,996
**avx2-roaring** | 14.66 | 7.447 | 0.574 | 22.681 | 5,926,176 | 3,385,148
tetzank-avx2-asm | 0.000 | 8.220 | 0.657 | 8.877 | 3,014,612 | 3,242,596


### webgraph_uk/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 2.864 | 0.509 | 3.373 | 3,012,524 | 3,231,636
`naive-bitvec` | 21.356 | 3.333 | 0.733 | 25.422 | 3,283,560 | 3,552,396
avx2-lemire | 0.000 | 3.385 | 0.492 | 3.877 | 3,014,648 | 3,204,184
sse-lemire | 0.000 | 3.452 | 0.438 | 3.89 | 3,014,868 | 3,240,472
**sse-han-bsr-sse-galloping** | 8.524 | 3.607 | 0.456 | 12.587 | 6,031,672 | 6,181,880
**sse-han-bsr-scalar-galloping** | 8.429 | 3.633 | 0.498 | 12.56 | 6,031,864 | 6,209,788
**sse-han-bsr-qfilter** | 7.684 | 3.722 | 0.486 | 11.892 | 6,031,972 | 6,189,740
`avx2-merge` | 0.000 | 3.879 | 0.53 | 4.409 | 3,012,440 | 3,236,260
`naive-bitvec-2d` | 23.288 | 3.888 | 0.89 | 28.066 | 3,283,840 | 3,537,324
**sse-han-bsr-scalar-merge** | 8.116 | 4.148 | 0.467 | 12.731 | 6,031,808 | 6,193,192
`avx2-galloping-single` | 0.000 | 4.380 | 0.461 | 4.841 | 3,013,084 | 3,248,308
**sse-han-bsr-sse-shuffle** | 7.521 | 4.390 | 0.511 | 12.422 | 6,032,012 | 6,199,252
**sse-emptyheaded-layout-uint** | 4.792 | 5.478 | 0.488 | 10.758 | 4,892,668 | 5,065,180
**sse-emptyheaded-layout-hybrid** | 4.53 | 6.008 | 0.487 | 11.025 | 4,951,352 | 5,150,724
tetzank-avx2 | 0.000 | 8.614 | 0.492 | 9.106 | 3,014,256 | 3,221,908
sse-han-qfilter | 0.000 | 9.447 | 0.641 | 10.088 | 3,014,964 | 3,248,596
sse-han-bmiss-sttni | 0.000 | 9.486 | 0.501 | 9.987 | 3,014,372 | 3,215,940
sse-bm-lemire | 0.000 | 9.783 | 0.573 | 10.356 | 3,015,032 | 3,265,420
sse-han-bmiss | 0.000 | 10.537 | 0.549 | 11.086 | 3,014,368 | 3,179,452
tetzank-avx | 0.000 | 11.077 | 0.557 | 11.634 | 3,014,460 | 3,232,288
tetzank-avx2-asm | 0.000 | 11.724 | 0.529 | 12.253 | 3,014,416 | 3,231,960
**sse-roaring** | 16.825 | 18.221 | 1.059 | 36.105 | 7,478,960 | 3,489,940
**avx2-roaring** | 21.239 | 19.063 | 1.203 | 41.505 | 7,478,740 | 3,478,900


### webgraph_uk/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_uk/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_uk/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 2.173 | 0.832 | 3.005 | 3,013,020 | 3,269,668
`naive-bitvec` | 11.351 | 2.621 | 0.66 | 14.632 | 3,283,852 | 3,499,736
`avx2-merge` | 0.000 | 2.742 | 0.871 | 3.613 | 3,012,976 | 3,265,900
avx2-lemire | 0.000 | 3.190 | 0.909 | 4.099 | 3,015,168 | 3,259,804
`naive-bitvec-2d` | 10.069 | 3.220 | 0.577 | 13.866 | 3,283,892 | 3,534,860
sse-lemire | 0.000 | 3.519 | 0.897 | 4.416 | 3,015,188 | 3,249,292
`avx2-galloping-single` | 0.000 | 4.475 | 0.562 | 5.037 | 3,012,876 | 3,235,152
**sse-han-bsr-scalar-galloping** | 7.798 | 4.481 | 0.597 | 12.876 | 6,023,940 | 6,223,944
**sse-han-bsr-sse-galloping** | 7.613 | 4.531 | 0.582 | 12.726 | 6,023,992 | 6,259,784
**sse-han-bsr-scalar-merge** | 7.78 | 4.580 | 0.589 | 12.949 | 6,023,980 | 6,235,800
**sse-han-bsr-sse-shuffle** | 8.461 | 4.640 | 0.573 | 13.674 | 6,023,928 | 6,242,484
**sse-han-bsr-qfilter** | 8.175 | 4.687 | 0.592 | 13.454 | 6,023,724 | 6,283,768
tetzank-avx2 | 0.000 | 4.788 | 0.581 | 5.369 | 3,015,216 | 3,268,112
sse-bm-lemire | 0.000 | 4.968 | 0.559 | 5.527 | 3,015,000 | 3,258,532
**sse-emptyheaded-layout-hybrid** | 5.095 | 5.045 | 0.535 | 10.675 | 4,922,012 | 5,155,936
**sse-emptyheaded-layout-uint** | 4.642 | 5.096 | 0.493 | 10.231 | 4,891,852 | 5,091,672
tetzank-avx | 0.000 | 5.619 | 0.568 | 6.187 | 3,014,820 | 3,271,072
sse-han-qfilter | 0.000 | 5.952 | 0.623 | 6.575 | 3,015,368 | 3,205,800
sse-han-bmiss | 0.000 | 6.396 | 0.562 | 6.958 | 3,015,308 | 3,210,248
sse-han-bmiss-sttni | 0.000 | 6.506 | 0.659 | 7.165 | 3,015,400 | 3,204,640
tetzank-avx2-asm | 0.000 | 8.048 | 0.538 | 8.586 | 3,015,324 | 3,243,280
**avx2-roaring** | 23.509 | 15.076 | 1.128 | 39.713 | 8,250,520 | 3,573,492
**sse-roaring** | 15.656 | 20.098 | 0.74 | 36.494 | 8,250,820 | 3,572,448


### webgraph_uk/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 2.253 | 0.831 | 3.084 | 3,012,980 | 3,257,892
**sse-han-bsr-sse-shuffle** | 8.662 | 2.838 | 0.974 | 12.474 | 6,014,152 | 6,184,608
**sse-han-bsr-sse-galloping** | 8.402 | 2.886 | 1.029 | 12.317 | 6,014,008 | 6,181,480
avx2-lemire | 0.000 | 3.040 | 1.087 | 4.127 | 3,015,288 | 3,282,552
`avx2-merge` | 0.000 | 3.051 | 1.056 | 4.107 | 3,013,000 | 3,279,660
**sse-han-bsr-qfilter** | 7.783 | 3.067 | 0.96 | 11.81 | 6,014,144 | 6,196,340
`naive-bitvec` | 16.449 | 3.136 | 0.711 | 20.296 | 3,283,848 | 3,520,316
**sse-han-bsr-scalar-galloping** | 8.82 | 3.179 | 1.042 | 13.041 | 6,013,880 | 6,199,928
**sse-han-bsr-scalar-merge** | 7.981 | 3.243 | 0.913 | 12.137 | 6,014,488 | 6,197,376
sse-lemire | 0.000 | 3.250 | 1.223 | 4.473 | 3,015,336 | 3,282,444
`naive-bitvec-2d` | 19.004 | 3.850 | 0.871 | 23.725 | 3,283,644 | 3,513,924
`avx2-galloping-single` | 0.000 | 3.910 | 0.719 | 4.629 | 3,012,972 | 3,202,624
**sse-emptyheaded-layout-hybrid** | 5.395 | 5.576 | 0.858 | 11.829 | 4,910,728 | 5,098,056
**sse-emptyheaded-layout-uint** | 4.693 | 5.987 | 0.614 | 11.294 | 4,891,676 | 5,143,348
tetzank-avx2 | 0.000 | 6.866 | 0.665 | 7.531 | 3,015,168 | 3,286,804
sse-bm-lemire | 0.000 | 7.537 | 0.703 | 8.24 | 3,015,148 | 3,284,608
sse-han-qfilter | 0.000 | 7.709 | 0.611 | 8.32 | 3,015,280 | 3,276,176
sse-han-bmiss | 0.000 | 8.399 | 0.658 | 9.057 | 3,014,672 | 3,271,936
tetzank-avx | 0.000 | 8.441 | 0.606 | 9.047 | 3,014,792 | 3,250,284
sse-han-bmiss-sttni | 0.000 | 8.458 | 0.57 | 9.028 | 3,014,816 | 3,192,968
**sse-roaring** | 17.441 | 10.230 | 1.011 | 28.682 | 6,126,832 | 3,689,152
tetzank-avx2-asm | 0.000 | 10.979 | 0.658 | 11.637 | 3,015,132 | 3,298,632
**avx2-roaring** | 15.891 | 11.255 | 0.861 | 28.007 | 6,126,900 | 3,698,216


### webgraph_webbase

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_webbase/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 6.373 | 2.004 | 8.377 | 11,542,020 | 12,731,932
**sse-han-bsr-scalar-galloping** | 40.959 | 7.599 | 1.405 | 49.963 | 24,454,560 | 25,580,696
**sse-han-bsr-scalar-merge** | 44.118 | 9.021 | 1.635 | 54.774 | 24,454,824 | 25,702,828
**sse-han-bsr-sse-galloping** | 40.132 | 9.249 | 2.067 | 51.448 | 24,455,824 | 25,551,900
**sse-han-bsr-qfilter** | 43.562 | 10.015 | 1.633 | 55.21 | 24,455,108 | 25,439,940
`naive-bitvec` | 87.124 | 10.896 | 2.627 | 100.647 | 13,272,204 | 14,239,232
**sse-han-bsr-sse-shuffle** | 41.654 | 11.201 | 1.442 | 54.297 | 24,455,476 | 25,489,664
`avx2-galloping-single` | 0.000 | 11.425 | 1.934 | 13.359 | 11,542,076 | 12,641,996
`naive-bitvec-2d` | 82.119 | 12.751 | 2.524 | 97.394 | 13,272,408 | 14,264,480
`avx2-merge` | 0.000 | 15.043 | 2.167 | 17.21 | 11,541,020 | 13,031,468
sse-lemire | 0.000 | 18.224 | 1.679 | 19.903 | 11,547,540 | 12,725,604
avx2-lemire | 0.000 | 18.719 | 2.023 | 20.742 | 11,547,528 | 12,941,752
**sse-emptyheaded-layout-uint** | 30.425 | 20.172 | 1.734 | 52.331 | 20,148,244 | 21,461,164
tetzank-avx2 | 0.000 | 35.747 | 1.884 | 37.631 | 11,547,680 | 12,887,940
sse-bm-lemire | 0.000 | 39.655 | 1.485 | 41.14 | 11,546,368 | 12,690,808
tetzank-avx | 0.000 | 42.752 | 1.829 | 44.581 | 11,548,032 | 12,528,460
**sse-roaring** | 66.186 | 44.561 | 2.583 | 113.33 | 27,182,340 | 13,626,196
sse-han-qfilter | 0.000 | 45.021 | 1.817 | 46.838 | 11,547,800 | 12,692,396
sse-han-bmiss | 0.000 | 48.502 | 1.685 | 50.187 | 11,547,792 | 12,681,452
sse-han-bmiss-sttni | 0.000 | 48.776 | 1.79 | 50.566 | 11,546,444 | 12,852,536
**avx2-roaring** | 72.997 | 50.778 | 2.87 | 126.645 | 27,183,068 | 13,635,780
tetzank-avx2-asm | 0.000 | 87.272 | 2.059 | 89.331 | 11,547,016 | 12,583,712


### webgraph_webbase/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`avx2-hybrid` | 0.000 | 9.939 | 2.082 | 12.021 | 11,547,136 | 12,723,004
sse-lemire | 0.000 | 11.433 | 1.942 | 13.375 | 11,552,124 | 12,910,080
`naive-bitvec` | 105.349 | 11.687 | 2.702 | 119.738 | 13,271,984 | 14,322,900
avx2-lemire | 0.000 | 11.840 | 1.827 | 13.667 | 11,552,676 | 12,777,244
`naive-bitvec-2d` | 98.345 | 14.216 | 3.527 | 116.088 | 13,272,408 | 14,218,916
**sse-han-bsr-scalar-galloping** | 42.18 | 14.216 | 2.293 | 58.689 | 24,534,820 | 25,668,384
`avx2-galloping-single` | 0.000 | 15.629 | 1.817 | 17.446 | 11,545,964 | 12,859,952
**sse-han-bsr-sse-galloping** | 37.145 | 17.545 | 1.803 | 56.493 | 24,537,120 | 25,772,896
**sse-emptyheaded-layout-uint** | 30.826 | 18.134 | 2.339 | 51.299 | 20,156,128 | 21,192,268
**sse-emptyheaded-layout-hybrid** | 30.305 | 19.086 | 2.185 | 51.576 | 20,324,776 | 21,636,588
**sse-han-bsr-qfilter** | 38.421 | 27.551 | 2.004 | 67.976 | 24,533,856 | 26,101,456
**sse-han-bsr-scalar-merge** | 40.402 | 31.450 | 1.866 | 73.718 | 24,533,668 | 25,692,040
`avx2-merge` | 0.000 | 32.526 | 1.901 | 34.427 | 11,546,076 | 13,113,220
**sse-han-bsr-sse-shuffle** | 40.335 | 37.529 | 1.984 | 79.848 | 24,535,096 | 25,967,096
**sse-roaring** | 87.787 | 71.369 | 4.46 | 163.616 | 33,640,124 | 14,504,444
**avx2-roaring** | 78.635 | 80.755 | 4.054 | 163.444 | 33,641,340 | 14,206,768
tetzank-avx2 | 0.000 | 105.823 | 1.991 | 107.814 | 11,552,160 | 13,008,280
sse-han-qfilter | 0.000 | 106.680 | 1.988 | 108.668 | 11,552,860 | 12,606,568
sse-han-bmiss-sttni | 0.000 | 106.947 | 1.793 | 108.74 | 11,552,604 | 12,865,444
sse-bm-lemire | 0.000 | 113.599 | 2.095 | 115.694 | 11,551,968 | 13,156,928
sse-han-bmiss | 0.000 | 115.127 | 2.089 | 117.216 | 11,552,316 | 13,123,760
tetzank-avx | 0.000 | 132.281 | 1.916 | 134.197 | 11,549,328 | 12,730,716
tetzank-avx2-asm | 0.000 | 155.015 | 1.84 | 156.855 | 11,549,812 | 12,717,332


### webgraph_webbase/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_webbase/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_webbase/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 49.507 | 8.976 | 2.446 | 60.929 | 13,272,200 | 14,312,484
`avx2-hybrid` | 0.000 | 9.037 | 1.892 | 10.929 | 11,541,852 | 12,577,052
`naive-bitvec-2d` | 57.719 | 11.095 | 2.025 | 70.839 | 13,272,192 | 14,271,740
**sse-han-bsr-scalar-galloping** | 55.531 | 13.347 | 1.617 | 70.495 | 24,496,312 | 25,521,572
`avx2-galloping-single` | 0.000 | 14.598 | 1.929 | 16.527 | 11,542,036 | 12,554,284
**sse-han-bsr-sse-galloping** | 53.991 | 15.500 | 1.608 | 71.099 | 24,496,172 | 25,455,724
**sse-han-bsr-qfilter** | 48.247 | 16.880 | 1.673 | 66.8 | 24,496,192 | 25,509,332
`avx2-merge` | 0.000 | 17.918 | 1.916 | 19.834 | 11,541,956 | 12,524,064
**sse-han-bsr-scalar-merge** | 47.032 | 18.147 | 1.826 | 67.005 | 24,496,380 | 25,464,784
**sse-han-bsr-sse-shuffle** | 53.117 | 20.964 | 2.005 | 76.086 | 24,496,228 | 25,479,784
sse-lemire | 0.000 | 21.902 | 1.878 | 23.78 | 11,547,128 | 12,531,580
avx2-lemire | 0.000 | 21.993 | 2.181 | 24.174 | 11,547,048 | 12,603,664
**sse-emptyheaded-layout-uint** | 33.195 | 25.430 | 1.733 | 60.358 | 20,147,976 | 21,200,440
tetzank-avx2 | 0.000 | 38.862 | 1.861 | 40.723 | 11,547,460 | 12,561,008
sse-bm-lemire | 0.000 | 43.385 | 1.901 | 45.286 | 11,547,248 | 12,528,396
tetzank-avx | 0.000 | 45.579 | 1.819 | 47.398 | 11,547,496 | 12,654,100
sse-han-qfilter | 0.000 | 49.868 | 2.248 | 52.116 | 11,547,440 | 12,551,236
sse-han-bmiss | 0.000 | 50.266 | 1.944 | 52.21 | 11,547,484 | 12,635,760
sse-han-bmiss-sttni | 0.000 | 50.618 | 1.859 | 52.477 | 11,547,328 | 12,581,092
**avx2-roaring** | 92.43 | 73.768 | 5.035 | 171.233 | 40,139,344 | 18,788,168
**sse-roaring** | 123.197 | 77.158 | 4.418 | 204.773 | 40,138,260 | 18,864,044
tetzank-avx2-asm | 0.000 | 88.395 | 1.782 | 90.177 | 11,546,744 | 12,565,680


### webgraph_webbase/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_it

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_it/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-scalar-galloping** | 24.188 | 9.744 | 1.846 | 35.778 | 20,393,812 | 20,857,412
**sse-han-bsr-sse-galloping** | 29.771 | 11.610 | 1.438 | 42.819 | 20,393,808 | 20,875,544
`avx2-hybrid` | 0.000 | 18.018 | 1.872 | 19.89 | 11,059,116 | 11,567,132
`naive-bitvec` | 83.279 | 22.731 | 3.117 | 109.127 | 11,664,636 | 12,193,880
`naive-bitvec-2d` | 87.923 | 28.460 | 2.758 | 119.141 | 11,664,136 | 12,207,256
**sse-roaring** | 42.649 | 28.780 | 2.362 | 73.791 | 19,324,412 | 11,976,744
**avx2-roaring** | 35.45 | 30.901 | 2.349 | 68.7 | 19,324,868 | 11,974,580
**sse-emptyheaded-layout-hybrid** | 19.445 | 31.393 | 1.549 | 52.387 | 17,303,308 | 17,675,824
`avx2-galloping-single` | 0.000 | 34.917 | 1.296 | 36.213 | 11,059,716 | 11,560,196
**sse-han-bsr-qfilter** | 31.609 | 38.192 | 1.904 | 71.705 | 20,395,224 | 20,929,468
**sse-han-bsr-scalar-merge** | 28.262 | 41.617 | 1.834 | 71.713 | 20,394,824 | 20,923,864
**sse-han-bsr-sse-shuffle** | 25.693 | 54.644 | 2.237 | 82.574 | 20,393,276 | 20,895,416
avx2-lemire | 0.000 | 132.141 | 1.756 | 133.897 | 11,102,516 | 11,630,104
sse-lemire | 0.000 | 136.228 | 1.626 | 137.854 | 11,106,004 | 11,611,816
**sse-emptyheaded-layout-uint** | 17.236 | 138.813 | 1.618 | 157.667 | 17,226,200 | 17,654,292
`avx2-merge` | 0.000 | 217.344 | 2.019 | 219.363 | 11,059,956 | 11,580,360
sse-han-bmiss-sttni | 0.000 | 742.721 | 1.534 | 744.255 | 11,105,668 | 11,681,464
tetzank-avx2 | 0.000 | 742.844 | 1.466 | 744.31 | 11,105,668 | 11,627,912
sse-bm-lemire | 0.000 | 798.910 | 1.6 | 800.51 | 11,104,536 | 11,556,612
sse-han-qfilter | 0.000 | 823.464 | 1.672 | 825.136 | 11,105,788 | 11,557,512
sse-han-bmiss | 0.000 | 842.522 | 1.922 | 844.444 | 11,105,224 | 11,518,116
tetzank-avx | 0.000 | 983.458 | 1.911 | 985.369 | 11,102,240 | 11,555,068
tetzank-avx2-asm | 0.000 | 1282.605 | 1.456 | 1284.061 | 11,104,948 | 11,653,116


### webgraph_it/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 60.488 | 21.905 | 2.651 | 85.044 | 11,664,644 | 12,224,504
**sse-han-bsr-sse-galloping** | 27.635 | 24.574 | 1.683 | 53.892 | 20,616,876 | 20,999,472
**sse-han-bsr-scalar-galloping** | 29.889 | 24.852 | 1.666 | 56.407 | 20,616,796 | 21,209,412
`naive-bitvec-2d` | 54.601 | 27.105 | 2.253 | 83.959 | 11,664,676 | 12,208,156
`avx2-hybrid` | 0.000 | 29.165 | 1.677 | 30.842 | 11,059,320 | 11,647,020
**sse-emptyheaded-layout-hybrid** | 19.819 | 44.479 | 1.685 | 65.983 | 17,542,316 | 18,067,048
`avx2-galloping-single` | 0.000 | 45.975 | 1.543 | 47.518 | 11,060,316 | 11,510,584
**sse-han-bsr-qfilter** | 29.499 | 79.927 | 1.59 | 111.016 | 20,618,752 | 21,160,700
**avx2-roaring** | 57.374 | 82.168 | 3.83 | 143.372 | 24,533,088 | 12,361,196
**sse-roaring** | 54.324 | 83.426 | 2.951 | 140.701 | 24,533,004 | 12,290,704
avx2-lemire | 0.000 | 92.484 | 1.84 | 94.324 | 11,113,900 | 11,543,964
sse-lemire | 0.000 | 96.993 | 1.668 | 98.661 | 11,110,972 | 11,535,372
**sse-han-bsr-scalar-merge** | 29.568 | 97.505 | 1.671 | 128.744 | 20,618,252 | 21,020,556
**sse-emptyheaded-layout-uint** | 20.051 | 102.829 | 1.628 | 124.508 | 17,247,868 | 17,789,732
**sse-han-bsr-sse-shuffle** | 29.96 | 136.176 | 1.594 | 167.73 | 20,616,152 | 21,058,036
`avx2-merge` | 0.000 | 330.195 | 1.536 | 331.731 | 11,059,972 | 11,548,908
sse-han-bmiss-sttni | 0.000 | 917.224 | 1.699 | 918.923 | 11,107,724 | 11,564,100
tetzank-avx2 | 0.000 | 1055.127 | 1.531 | 1056.658 | 11,114,908 | 11,580,888
sse-han-qfilter | 0.000 | 1082.411 | 1.563 | 1083.974 | 11,114,300 | 11,580,732
sse-han-bmiss | 0.000 | 1101.957 | 1.709 | 1103.666 | 11,118,520 | 11,708,776
sse-bm-lemire | 0.000 | 1131.694 | 1.634 | 1133.328 | 11,108,532 | 11,556,756
tetzank-avx2-asm | 0.000 | 1336.517 | 1.671 | 1338.188 | 11,121,656 | 11,674,892
tetzank-avx | 0.000 | 1475.032 | 1.687 | 1476.719 | 11,122,744 | 11,577,200


### webgraph_it/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_it/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_it/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 37.087 | 19.400 | 1.672 | 58.159 | 11,664,616 | 12,174,160
**sse-han-bsr-scalar-galloping** | 32.654 | 21.139 | 1.646 | 55.439 | 20,493,816 | 20,961,940
`avx2-hybrid` | 0.000 | 22.119 | 1.823 | 23.942 | 11,060,016 | 11,578,988
**sse-han-bsr-sse-galloping** | 30.769 | 22.697 | 1.702 | 55.168 | 20,491,976 | 21,056,672
`naive-bitvec-2d` | 47.222 | 26.729 | 1.707 | 75.658 | 11,664,632 | 12,105,468
**sse-emptyheaded-layout-hybrid** | 21.854 | 34.718 | 1.826 | 58.398 | 17,386,320 | 17,911,876
`avx2-galloping-single` | 0.000 | 40.296 | 1.52 | 41.816 | 11,059,532 | 11,631,728
**sse-han-bsr-qfilter** | 33.443 | 49.617 | 1.493 | 84.553 | 20,490,504 | 21,001,392
**sse-roaring** | 70.879 | 51.623 | 2.545 | 125.047 | 25,988,580 | 12,481,808
**avx2-roaring** | 72.668 | 58.670 | 3.851 | 135.189 | 25,988,696 | 12,468,104
**sse-han-bsr-scalar-merge** | 31.263 | 59.077 | 2.421 | 92.761 | 20,491,284 | 20,974,972
**sse-han-bsr-sse-shuffle** | 32.522 | 76.485 | 1.622 | 110.629 | 20,491,672 | 21,003,188
avx2-lemire | 0.000 | 127.965 | 1.841 | 129.806 | 11,105,168 | 11,576,596
sse-lemire | 0.000 | 137.389 | 1.636 | 139.025 | 11,104,812 | 11,586,056
**sse-emptyheaded-layout-uint** | 22.018 | 144.687 | 1.885 | 168.59 | 17,225,224 | 17,613,464
`avx2-merge` | 0.000 | 222.128 | 2.004 | 224.132 | 11,059,624 | 11,576,624
sse-han-bmiss-sttni | 0.000 | 741.821 | 1.74 | 743.561 | 11,105,804 | 11,564,372
tetzank-avx2 | 0.000 | 770.194 | 1.95 | 772.144 | 11,098,976 | 11,590,752
sse-bm-lemire | 0.000 | 829.978 | 1.827 | 831.805 | 11,102,028 | 11,597,636
sse-han-qfilter | 0.000 | 864.308 | 1.589 | 865.897 | 11,105,340 | 11,556,980
sse-han-bmiss | 0.000 | 886.850 | 1.887 | 888.737 | 11,102,232 | 11,577,320
tetzank-avx | 0.000 | 1009.291 | 1.618 | 1010.909 | 11,105,540 | 11,592,968
tetzank-avx2-asm | 0.000 | 1302.054 | 1.64 | 1303.694 | 11,102,436 | 11,608,784


### webgraph_it/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-han-bsr-sse-galloping** | 30.737 | 12.621 | 2.419 | 45.777 | 20,414,112 | 20,924,604
**sse-han-bsr-scalar-galloping** | 29.269 | 12.686 | 1.853 | 43.808 | 20,414,604 | 20,861,872
`naive-bitvec` | 62.303 | 21.495 | 2.416 | 86.214 | 11,664,508 | 12,206,716
`avx2-hybrid` | 0.000 | 21.510 | 2.215 | 23.725 | 11,059,520 | 11,584,584
`naive-bitvec-2d` | 53.647 | 28.544 | 2.181 | 84.372 | 11,664,696 | 12,177,556
**sse-roaring** | 40.38 | 35.194 | 2.553 | 78.127 | 18,987,928 | 12,103,700
**avx2-roaring** | 38.223 | 38.480 | 2.836 | 79.539 | 18,988,456 | 12,125,940
`avx2-galloping-single` | 0.000 | 38.592 | 1.709 | 40.301 | 11,059,964 | 11,618,820
**sse-emptyheaded-layout-hybrid** | 23.035 | 38.844 | 2.28 | 64.159 | 17,369,744 | 17,868,900
**sse-han-bsr-qfilter** | 30.181 | 41.568 | 1.696 | 73.445 | 20,412,840 | 20,766,452
**sse-han-bsr-scalar-merge** | 30.975 | 47.301 | 1.846 | 80.122 | 20,415,216 | 20,805,292
avx2-lemire | 0.000 | 55.877 | 2.31 | 58.187 | 11,105,088 | 11,584,316
sse-lemire | 0.000 | 59.032 | 2.109 | 61.141 | 11,102,184 | 11,632,972
**sse-emptyheaded-layout-uint** | 18.034 | 67.498 | 2.293 | 87.825 | 17,225,952 | 17,774,124
**sse-han-bsr-sse-shuffle** | 30.621 | 68.654 | 1.988 | 101.263 | 20,414,488 | 20,938,652
`avx2-merge` | 0.000 | 203.069 | 1.567 | 204.636 | 11,059,428 | 11,605,700
sse-han-bmiss-sttni | 0.000 | 623.195 | 1.787 | 624.982 | 11,102,440 | 11,537,428
tetzank-avx2 | 0.000 | 733.928 | 2.007 | 735.935 | 11,101,720 | 11,666,392
sse-han-qfilter | 0.000 | 737.054 | 2.231 | 739.285 | 11,101,936 | 11,483,852
sse-han-bmiss | 0.000 | 750.348 | 2.031 | 752.379 | 11,102,484 | 11,607,916
sse-bm-lemire | 0.000 | 781.680 | 2.182 | 783.862 | 11,098,788 | 11,597,124
tetzank-avx2-asm | 0.000 | 904.409 | 1.948 | 906.357 | 11,100,436 | 11,619,296
tetzank-avx | 0.000 | 1040.809 | 1.543 | 1042.352 | 11,110,412 | 11,620,560


### webgraph_twitter

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_twitter/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_twitter/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 172.078 | 107.524 | 3.919 | 283.521 | 13,461,036 | 13,754,584
`naive-bitvec-2d` | 131.17 | 112.750 | 3.304 | 247.224 | 13,460,932 | 13,758,284
`avx2-hybrid` | 0.000 | 300.844 | 5.278 | 306.122 | 12,854,648 | 13,104,368
**sse-emptyheaded-layout-hybrid** | 23.919 | 335.957 | 4.32 | 364.196 | 20,885,748 | 21,183,144
avx2-lemire | 0.000 | 340.975 | 4.16 | 345.135 | 12,901,600 | 13,200,780
sse-lemire | 0.000 | 345.209 | 4.258 | 349.467 | 12,901,712 | 13,201,584
`avx2-galloping-single` | 0.000 | 404.649 | 4.234 | 408.883 | 12,858,152 | 13,083,748
**sse-emptyheaded-layout-uint** | 24.213 | 448.316 | 4.416 | 476.945 | 19,874,892 | 20,092,748
**sse-han-bsr-sse-galloping** | 37.875 | 526.082 | 4.506 | 568.463 | 24,925,384 | 25,175,616
**sse-han-bsr-scalar-galloping** | 47.684 | 559.002 | 3.995 | 610.681 | 24,927,568 | 25,149,652
**avx2-roaring** | 220.586 | 672.999 | 8.777 | 902.362 | 69,782,716 | 16,877,304
**sse-roaring** | 226.106 | 732.840 | 9.643 | 968.589 | 69,782,984 | 16,660,592
`avx2-merge` | 0.000 | 1083.107 | 4.918 | 1088.025 | 12,853,296 | 13,093,776
sse-han-bmiss-sttni | 0.000 | 1874.698 | 4.443 | 1879.141 | 12,897,024 | 13,120,668
**sse-han-bsr-qfilter** | 42.613 | 1950.218 | 4.178 | 1997.009 | 24,925,152 | 25,176,816
tetzank-avx2 | 0.000 | 2202.223 | 4.41 | 2206.633 | 12,902,692 | 13,140,584
sse-han-qfilter | 0.000 | 2229.829 | 4.242 | 2234.071 | 12,900,696 | 13,140,952
sse-han-bmiss | 0.000 | 2229.975 | 4.76 | 2234.735 | 12,898,056 | 13,120,952
**sse-han-bsr-scalar-merge** | 42.507 | 2367.625 | 4.11 | 2414.242 | 24,928,388 | 25,166,332
sse-bm-lemire | 0.000 | 2414.232 | 4.721 | 2418.953 | 12,899,392 | 13,190,616
tetzank-avx2-asm | 0.000 | 2653.667 | 4.42 | 2658.087 | 12,901,744 | 13,177,364
tetzank-avx | 0.000 | 2860.176 | 4.811 | 2864.987 | 12,902,888 | 13,212,180
**sse-han-bsr-sse-shuffle** | 39.121 | 3261.012 | 4.708 | 3304.841 | 24,923,952 | 25,170,176


### webgraph_twitter/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_twitter/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### webgraph_twitter/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
`naive-bitvec` | 105.478 | 102.809 | 3.473 | 211.76 | 13,461,072 | 13,736,372
`naive-bitvec-2d` | 83.03 | 119.516 | 3.113 | 205.659 | 13,461,304 | 13,728,404
`avx2-hybrid` | 0.000 | 190.682 | 3.339 | 194.021 | 12,851,392 | 13,151,908
**sse-roaring** | 129.317 | 253.367 | 5.226 | 387.91 | 43,416,464 | 15,067,648
**avx2-roaring** | 100.37 | 256.348 | 5.084 | 361.802 | 43,417,696 | 15,044,448
**sse-han-bsr-sse-galloping** | 30.982 | 289.240 | 3.59 | 323.812 | 24,221,008 | 24,499,600
**sse-emptyheaded-layout-hybrid** | 26.268 | 298.316 | 3.465 | 328.049 | 20,701,464 | 21,010,936
`avx2-galloping-single` | 0.000 | 306.302 | 3.124 | 309.426 | 12,851,120 | 13,145,484
**sse-han-bsr-scalar-galloping** | 31.237 | 346.307 | 3.41 | 380.954 | 24,222,592 | 24,494,900
sse-lemire | 0.000 | 388.964 | 2.765 | 391.729 | 12,881,016 | 13,153,072
avx2-lemire | 0.000 | 389.155 | 3.185 | 392.34 | 12,880,400 | 13,203,640
**sse-emptyheaded-layout-uint** | 25.538 | 464.847 | 3.035 | 493.42 | 19,802,948 | 20,094,736
`avx2-merge` | 0.000 | 503.900 | 3.211 | 507.111 | 12,851,100 | 13,140,360
**sse-han-bsr-qfilter** | 30.21 | 781.270 | 3.321 | 814.801 | 24,222,108 | 24,497,396
**sse-han-bsr-scalar-merge** | 38.311 | 943.556 | 3.214 | 985.081 | 24,221,532 | 24,507,756
**sse-han-bsr-sse-shuffle** | 31.514 | 1178.596 | 3.119 | 1213.229 | 24,221,584 | 24,487,636
tetzank-avx2 | 0.000 | 1343.745 | 3.159 | 1346.904 | 12,880,600 | 13,160,076
sse-han-bmiss-sttni | 0.000 | 1437.936 | 2.887 | 1440.823 | 12,880,480 | 13,153,776
sse-bm-lemire | 0.000 | 1475.509 | 3.349 | 1478.858 | 12,880,224 | 13,170,404
tetzank-avx | 0.000 | 1656.487 | 3.077 | 1659.564 | 12,879,220 | 13,188,072
sse-han-bmiss | 0.000 | 1665.892 | 3.22 | 1669.112 | 12,879,824 | 13,184,648
sse-han-qfilter | 0.000 | 1673.991 | 3.199 | 1677.19 | 12,880,608 | 13,167,144
tetzank-avx2-asm | 0.000 | 2625.125 | 2.96 | 2628.085 | 12,880,296 | 13,182,612


### webgraph_twitter/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
**sse-emptyheaded-layout-hybrid** | 21.704 | 273.897 | 3.807 | 299.408 | 20,826,156 | 21,088,428
**sse-emptyheaded-layout-uint** | 26.218 | 326.167 | 3.756 | 356.141 | 19,853,320 | 20,098,592


### snap_friendster

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_friendster/gro

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_friendster/cache

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
sse-han-bmiss-sttni | 0.000 | 159.650 | 13.742 | 173.392 | 34,190,088 | 35,096,968
`naive-bitvec-2d` | 254.799 | 162.362 | 12.923 | 430.084 | 36,017,840 | 36,925,864
`avx2-merge` | 0.000 | 167.656 | 14.374 | 182.03 | 34,189,532 | 35,127,736
`avx2-hybrid` | 0.000 | 168.923 | 14.568 | 183.491 | 34,189,524 | 35,151,572
sse-lemire | 0.000 | 169.280 | 14.755 | 184.035 | 34,190,012 | 35,153,336
avx2-lemire | 0.000 | 169.539 | 14.561 | 184.1 | 34,189,984 | 35,121,904
sse-han-qfilter | 0.000 | 170.288 | 14.604 | 184.892 | 34,190,028 | 35,124,700
tetzank-avx2-asm | 0.000 | 178.473 | 16.261 | 194.734 | 34,189,992 | 35,150,552
sse-bm-lemire | 0.000 | 181.901 | 14.559 | 196.46 | 34,189,992 | 35,160,608
sse-han-bmiss | 0.000 | 186.868 | 13.787 | 200.655 | 34,190,088 | 35,123,176
tetzank-avx2 | 0.000 | 187.891 | 16.406 | 204.297 | 34,189,988 | 35,142,488
tetzank-avx | 0.000 | 223.850 | 16.376 | 240.226 | 34,189,784 | 35,109,332
**sse-han-bsr-qfilter** | 124.011 | 235.235 | 14.552 | 373.798 | 68,437,828 | 69,331,856
`naive-bitvec` | 268.297 | 237.755 | 12.2 | 518.252 | 36,017,616 | 36,934,752
**sse-emptyheaded-layout-hybrid** | 74.295 | 237.817 | 13.964 | 326.076 | 52,665,168 | 53,552,816
`avx2-galloping-single` | 0.000 | 249.272 | 13.843 | 263.115 | 34,189,488 | 35,150,260
**sse-emptyheaded-layout-uint** | 60.244 | 267.917 | 15.676 | 343.837 | 52,664,956 | 53,609,468
**sse-han-bsr-sse-shuffle** | 120.81 | 318.672 | 13.963 | 453.445 | 68,437,664 | 69,350,256
**sse-han-bsr-sse-galloping** | 124.366 | 331.602 | 14.698 | 470.666 | 68,437,864 | 69,419,928
**sse-han-bsr-scalar-merge** | 134.071 | 388.355 | 14.064 | 536.49 | 68,437,776 | 69,301,176
**sse-han-bsr-scalar-galloping** | 128.82 | 416.643 | 13.823 | 559.286 | 68,437,840 | 69,451,124
**sse-roaring** | 925.923 | 1322.632 | 29.419 | 2277.974 | 263,790,888 | 50,507,480
**avx2-roaring** | 797.446 | 1395.909 | 35.55 | 2228.905 | 263,790,756 | 50,529,308


### snap_friendster/dfs

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_friendster/bfsr

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---


### snap_friendster/hybrid

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---
avx2-lemire | 0.000 | 162.249 | 13.45 | 175.699 | 34,190,008 | 35,136,776
tetzank-avx2-asm | 0.000 | 163.371 | 14.3 | 177.671 | 34,189,988 | 35,126,944
sse-han-bmiss-sttni | 0.000 | 167.113 | 13.356 | 180.469 | 34,190,092 | 35,144,584
sse-lemire | 0.000 | 168.939 | 13.781 | 182.72 | 34,190,012 | 35,135,080
`avx2-merge` | 0.000 | 171.132 | 13.71 | 184.842 | 34,189,532 | 35,121,912
`avx2-hybrid` | 0.000 | 174.103 | 13.59 | 187.693 | 34,189,536 | 35,165,544
sse-bm-lemire | 0.000 | 176.367 | 12.509 | 188.876 | 34,190,000 | 35,137,288
sse-han-qfilter | 0.000 | 177.034 | 15.102 | 192.136 | 34,190,080 | 35,118,008
tetzank-avx2 | 0.000 | 182.162 | 13.649 | 195.811 | 34,189,960 | 35,148,728
`naive-bitvec-2d` | 268.063 | 185.753 | 14.733 | 468.549 | 36,017,808 | 36,967,668
sse-han-bmiss | 0.000 | 202.335 | 13.249 | 215.584 | 34,190,076 | 35,135,108
tetzank-avx | 0.000 | 217.899 | 13.461 | 231.36 | 34,189,964 | 35,135,176
**sse-han-bsr-qfilter** | 116.373 | 241.828 | 13.285 | 371.486 | 68,437,204 | 69,402,456
**sse-emptyheaded-layout-hybrid** | 61.867 | 248.023 | 13.111 | 323.001 | 52,665,104 | 53,510,516
`avx2-galloping-single` | 0.000 | 250.039 | 13.376 | 263.415 | 34,189,532 | 35,155,084
`naive-bitvec` | 273.966 | 255.260 | 14.578 | 543.804 | 36,017,624 | 36,953,528
**sse-emptyheaded-layout-uint** | 74.661 | 257.202 | 13.535 | 345.398 | 52,665,108 | 53,495,844
**sse-han-bsr-sse-shuffle** | 103.984 | 328.104 | 14.084 | 446.172 | 68,437,244 | 69,385,108
**sse-han-bsr-sse-galloping** | 122.723 | 343.114 | 13.317 | 479.154 | 68,437,200 | 69,401,620
**sse-han-bsr-scalar-galloping** | 118.752 | 405.081 | 11.639 | 535.472 | 68,437,208 | 69,392,468
**sse-han-bsr-scalar-merge** | 101.392 | 427.005 | 13.366 | 541.763 | 68,437,192 | 69,411,852
**avx2-roaring** | 606.686 | 1079.808 | 35.655 | 1722.149 | 192,632,240 | 84,219,972
**sse-roaring** | 717.647 | 1105.513 | 33.496 | 1856.656 | 192,632,312 | 84,035,108


### snap_friendster/slashburn

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck | Step3 - LabelNonCore (KB) | Step4 - output to the disk (KB)
--- | --- | --- | --- | --- | --- | ---