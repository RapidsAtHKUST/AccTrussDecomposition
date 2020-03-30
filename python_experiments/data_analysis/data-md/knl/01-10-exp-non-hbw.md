# O(E) intersection count time


Unit: seconds


### snap_livejournal

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
avx2-hybrid | 0.000 | 0.417 | 0.142 | 0.559
avx2-merge | 0.000 | 0.426 | 0.142 | 0.568
avx2-lemire | 0.000 | 0.579 | 0.136 | 0.715
sse-lemire | 0.000 | 0.609 | 0.091 | 0.7
tetzank-avx2-asm | 0.000 | 0.666 | 0.099 | 0.765
avx2-galloping-single | 0.000 | 0.724 | 0.134 | 0.858
sse-emptyheaded-layout-hybrid | 2.953 | 0.734 | 0.091 | 3.778
tetzank-avx2 | 0.000 | 0.741 | 0.135 | 0.876
sse-emptyheaded-layout-uint | 2.746 | 0.745 | 0.1 | 3.591
sse-han-bsr-scalar-galloping | 4.996 | 0.768 | 0.097 | 5.861
sse-han-bsr-sse-galloping | 4.943 | 0.769 | 0.127 | 5.839
tetzank-avx | 0.000 | 0.846 | 0.106 | 0.952
sse-han-bsr-scalar-merge | 4.976 | 0.902 | 0.139 | 6.017
sse-han-bsr-qfilter | 4.744 | 0.932 | 0.091 | 5.767
sse-bm-lemire | 0.000 | 0.958 | 0.143 | 1.101
sse-han-bmiss-sttni | 0.000 | 0.988 | 0.107 | 1.095
sse-han-qfilter | 0.000 | 1.214 | 0.141 | 1.355
sse-han-bsr-sse-shuffle | 5.125 | 1.235 | 0.091 | 6.451
sse-han-bmiss | 0.000 | 1.837 | 0.1 | 1.937
avx2-roaring | 10.59 | 7.426 | 0.106 | 18.122
sse-roaring | 10.144 | 7.862 | 0.132 | 18.138


### snap_livejournal/rev_deg

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
naive-bitvec-2d | 0.000 | 0.517 | 0.109 | 0.626
naive-bitvec | 0.000 | 0.722 | 0.161 | 0.883


### snap_orkut

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
avx2-hybrid | 0.000 | 2.674 | 0.349 | 3.023
avx2-merge | 0.000 | 2.751 | 0.291 | 3.042
tetzank-avx2-asm | 0.000 | 3.688 | 0.302 | 3.99
avx2-lemire | 0.000 | 3.868 | 0.304 | 4.172
sse-lemire | 0.000 | 4.255 | 0.303 | 4.558
tetzank-avx2 | 0.000 | 4.573 | 0.373 | 4.946
avx2-galloping-single | 0.000 | 4.969 | 0.388 | 5.357
sse-emptyheaded-layout-hybrid | 6.887 | 5.411 | 0.311 | 12.609
tetzank-avx | 0.000 | 5.458 | 0.372 | 5.83
sse-han-bmiss-sttni | 0.000 | 5.661 | 0.303 | 5.964
sse-emptyheaded-layout-uint | 7.06 | 5.683 | 0.347 | 13.09
sse-bm-lemire | 0.000 | 5.829 | 0.328 | 6.157
sse-han-bsr-sse-galloping | 13.197 | 5.939 | 0.309 | 19.445
sse-han-bsr-scalar-galloping | 13.817 | 6.030 | 0.306 | 20.153
sse-han-bsr-qfilter | 13.746 | 6.203 | 0.345 | 20.294
sse-han-bsr-scalar-merge | 13.243 | 6.234 | 0.312 | 19.789
sse-han-qfilter | 0.000 | 6.950 | 0.292 | 7.242
sse-han-bsr-sse-shuffle | 13.922 | 8.072 | 0.369 | 22.363
sse-han-bmiss | 0.000 | 10.641 | 0.364 | 11.005
sse-roaring | 23.328 | 21.354 | 0.308 | 44.99
avx2-roaring | 23.428 | 21.619 | 0.33 | 45.377


### snap_orkut/rev_deg

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
naive-bitvec-2d | 0.000 | 3.603 | 0.323 | 3.926
naive-bitvec | 0.000 | 6.618 | 0.397 | 7.015


### webgraph_eu

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
sse-han-bsr-scalar-merge | 12.335 | 10.038 | 0.415 | 22.788
sse-emptyheaded-layout-hybrid | 7.609 | 10.402 | 0.427 | 18.438
sse-han-bsr-sse-shuffle | 12.334 | 12.483 | 0.409 | 25.226
sse-han-bsr-scalar-galloping | 12.504 | 13.095 | 0.43 | 26.029
sse-han-bsr-qfilter | 12.155 | 13.155 | 0.413 | 25.723
sse-han-bsr-sse-galloping | 12.229 | 15.613 | 0.417 | 28.259
avx2-roaring | 10.452 | 19.283 | 0.412 | 30.147
sse-roaring | 11.058 | 19.505 | 0.43 | 30.993
avx2-hybrid | 0.000 | 81.802 | 0.421 | 82.223
avx2-merge | 0.000 | 85.736 | 0.432 | 86.168
tetzank-avx2-asm | 0.000 | 91.652 | 0.417 | 92.069
tetzank-avx2 | 0.000 | 106.416 | 0.455 | 106.871
tetzank-avx | 0.000 | 127.873 | 0.455 | 128.328
sse-bm-lemire | 0.000 | 142.398 | 0.509 | 142.907
sse-emptyheaded-layout-uint | 9.293 | 155.650 | 0.454 | 165.397
avx2-lemire | 0.000 | 197.242 | 0.425 | 197.667
sse-lemire | 0.000 | 223.217 | 0.454 | 223.671
sse-han-qfilter | 0.000 | 239.137 | 0.439 | 239.576
avx2-galloping-single | 0.000 | 304.014 | 0.439 | 304.453
sse-han-bmiss-sttni | 0.000 | 327.265 | 0.421 | 327.686
sse-han-bmiss | 0.000 | 364.876 | 0.502 | 365.378


### webgraph_eu/rev_deg

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
naive-bitvec | 0.000 | 99.770 | 0.469 | 100.239
naive-bitvec-2d | 0.000 | 167.445 | 0.457 | 167.902


### webgraph_uk

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
sse-han-bsr-scalar-galloping | 20.879 | 0.917 | 0.284 | 22.08
sse-han-bsr-sse-galloping | 20.757 | 1.021 | 0.298 | 22.076
sse-han-bsr-scalar-merge | 20.88 | 1.278 | 0.344 | 22.502
sse-han-bsr-qfilter | 20.891 | 1.348 | 0.318 | 22.557
sse-han-bsr-sse-shuffle | 20.927 | 1.529 | 0.36 | 22.816
avx2-hybrid | 0.000 | 1.688 | 0.299 | 1.987
avx2-merge | 0.000 | 2.555 | 0.351 | 2.906
avx2-galloping-single | 0.000 | 2.904 | 0.34 | 3.244
avx2-lemire | 0.000 | 2.913 | 0.367 | 3.28
sse-lemire | 0.000 | 3.013 | 0.289 | 3.302
sse-emptyheaded-layout-hybrid | 12.244 | 4.499 | 0.289 | 17.032
sse-emptyheaded-layout-uint | 12.777 | 4.877 | 0.332 | 17.986
tetzank-avx2 | 0.000 | 8.048 | 0.304 | 8.352
tetzank-avx2-asm | 0.000 | 8.593 | 0.298 | 8.891
sse-roaring | 8.217 | 9.132 | 0.298 | 17.647
tetzank-avx | 0.000 | 9.187 | 0.302 | 9.489
avx2-roaring | 8.032 | 9.313 | 0.297 | 17.642
sse-bm-lemire | 0.000 | 10.098 | 0.313 | 10.411
sse-han-bmiss-sttni | 0.000 | 10.923 | 0.344 | 11.267
sse-han-qfilter | 0.000 | 11.293 | 0.297 | 11.59
sse-han-bmiss | 0.000 | 17.216 | 0.299 | 17.515


### webgraph_uk/rev_deg

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
naive-bitvec | 0.000 | 1.179 | 0.358 | 1.537
naive-bitvec-2d | 0.000 | 1.644 | 0.404 | 2.048


### webgraph_webbase

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
sse-han-bsr-scalar-galloping | 79.329 | 3.828 | 1.028 | 84.185
avx2-hybrid | 0.000 | 4.621 | 1.047 | 5.668
sse-han-bsr-sse-galloping | 78.545 | 6.341 | 0.985 | 85.871
avx2-lemire | 0.000 | 8.576 | 0.988 | 9.564
avx2-galloping-single | 0.000 | 8.750 | 1.033 | 9.783
sse-lemire | 0.000 | 8.912 | 1.048 | 9.96
sse-han-bsr-qfilter | 79.971 | 11.125 | 0.993 | 92.089
sse-han-bsr-scalar-merge | 78.993 | 11.656 | 0.98 | 91.629
sse-emptyheaded-layout-uint | 54.246 | 11.665 | 1.056 | 66.967
sse-emptyheaded-layout-hybrid | 52.977 | 13.625 | 1.056 | 67.658
sse-han-bsr-sse-shuffle | 79.162 | 14.425 | 1.063 | 94.65
avx2-merge | 0.000 | 26.933 | 1.058 | 27.991
avx2-roaring | 50.046 | 47.088 | 1.002 | 98.136
sse-roaring | 50.322 | 47.786 | 1.058 | 99.166
tetzank-avx2 | 0.000 | 98.595 | 0.995 | 99.59
tetzank-avx | 0.000 | 109.036 | 1.087 | 110.123
sse-bm-lemire | 0.000 | 115.342 | 1.068 | 116.41
tetzank-avx2-asm | 0.000 | 119.646 | 1.07 | 120.716
sse-han-bmiss-sttni | 0.000 | 122.638 | 1.116 | 123.754
sse-han-qfilter | 0.000 | 124.739 | 1.052 | 125.791
sse-han-bmiss | 0.000 | 192.735 | 1.146 | 193.881


### webgraph_webbase/rev_deg

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
naive-bitvec | 0.000 | 4.235 | 1.188 | 5.423
naive-bitvec-2d | 0.000 | 5.629 | 1.189 | 6.818


### webgraph_it

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
sse-han-bsr-scalar-galloping | 63.528 | 5.358 | 1.114 | 70.0
avx2-hybrid | 0.000 | 14.377 | 1.129 | 15.506
sse-han-bsr-sse-galloping | 64.011 | 19.597 | 1.141 | 84.749
avx2-lemire | 0.000 | 24.176 | 1.138 | 25.314
sse-lemire | 0.000 | 26.394 | 1.118 | 27.512
avx2-galloping-single | 0.000 | 28.175 | 1.135 | 29.31
sse-roaring | 21.354 | 29.495 | 1.142 | 51.991
avx2-roaring | 21.102 | 29.791 | 1.096 | 51.989
sse-emptyheaded-layout-uint | 38.272 | 33.984 | 1.057 | 73.313
sse-emptyheaded-layout-hybrid | 40.956 | 36.322 | 1.113 | 78.391
sse-han-bsr-qfilter | 63.721 | 78.669 | 1.148 | 143.538
sse-han-bsr-scalar-merge | 64.342 | 90.360 | 1.136 | 155.838
sse-han-bsr-sse-shuffle | 64.187 | 118.350 | 1.163 | 183.7
avx2-merge | 0.000 | 457.450 | 1.147 | 458.597
tetzank-avx2-asm | 0.000 | 901.888 | 1.146 | 903.034
tetzank-avx2 | 0.000 | 1150.627 | 1.129 | 1151.756
sse-han-bmiss-sttni | 0.000 | 1381.918 | 1.099 | 1383.017
tetzank-avx | 0.000 | 1405.834 | 1.146 | 1406.98
sse-bm-lemire | 0.000 | 1617.127 | 1.111 | 1618.238
sse-han-qfilter | 0.000 | 1642.310 | 1.113 | 1643.423
sse-han-bmiss | 0.000 | 2773.107 | 1.149 | 2774.256


### webgraph_it/rev_deg

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
naive-bitvec | 0.000 | 11.755 | 1.281 | 13.036
naive-bitvec-2d | 0.000 | 17.414 | 1.282 | 18.696


### webgraph_twitter

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
tetzank-avx | 0.000 | / | / | /
avx2-hybrid | 0.000 | 79.105 | 1.716 | 80.821
sse-han-bsr-sse-galloping | 66.716 | 109.566 | 1.677 | 177.959
sse-han-bsr-scalar-galloping | 66.904 | 109.806 | 1.705 | 178.415
avx2-galloping-single | 0.000 | 142.275 | 1.661 | 143.936
sse-emptyheaded-layout-hybrid | 40.91 | 208.458 | 1.687 | 251.055
avx2-roaring | 156.22 | 217.563 | 1.683 | 375.466
sse-roaring | 155.508 | 218.272 | 1.68 | 375.46
avx2-lemire | 0.000 | 301.484 | 1.704 | 303.188
sse-lemire | 0.000 | 310.600 | 1.682 | 312.282
sse-emptyheaded-layout-uint | 41.198 | 382.817 | 1.702 | 425.717
avx2-merge | 0.000 | 629.228 | 1.658 | 630.886
sse-han-bsr-qfilter | 66.229 | 1227.240 | 1.689 | 1295.158
sse-han-bsr-scalar-merge | 66.509 | 1287.481 | 1.667 | 1355.657
tetzank-avx2 | 0.000 | 1668.397 | 1.679 | 1670.076
sse-han-bsr-sse-shuffle | 68.08 | 1822.954 | 1.672 | 1892.706
sse-bm-lemire | 0.000 | 1938.263 | 1.658 | 1939.921
sse-han-bmiss-sttni | 0.000 | 1993.648 | 1.688 | 1995.336
tetzank-avx2-asm | 0.000 | 2053.902 | 1.686 | 2055.588
sse-han-qfilter | 0.000 | 2297.092 | 1.661 | 2298.753
sse-han-bmiss | 0.000 | 3301.725 | 1.666 | 3303.391


### webgraph_twitter/rev_deg

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
naive-bitvec-2d | 0.000 | 90.094 | 1.783 | 91.877
naive-bitvec | 0.000 | 144.843 | 1.756 | 146.599


### snap_friendster

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
avx2-roaring | 0.000 | / | / | /
sse-roaring | 0.000 | / | / | /
avx2-merge | 0.000 | 51.263 | 5.467 | 56.73
avx2-hybrid | 0.000 | 52.055 | 5.423 | 57.478
tetzank-avx2-asm | 0.000 | 57.358 | 5.413 | 62.771
tetzank-avx2 | 0.000 | 70.952 | 5.424 | 76.376
avx2-lemire | 0.000 | 81.164 | 5.464 | 86.628
tetzank-avx | 0.000 | 84.792 | 5.41 | 90.202
sse-han-bmiss-sttni | 0.000 | 85.828 | 5.549 | 91.377
sse-lemire | 0.000 | 90.025 | 5.398 | 95.423
sse-bm-lemire | 0.000 | 94.102 | 5.421 | 99.523
avx2-galloping-single | 0.000 | 104.133 | 5.398 | 109.531
sse-han-qfilter | 0.000 | 105.658 | 5.38 | 111.038
sse-emptyheaded-layout-uint | 127.531 | 119.685 | 5.383 | 252.599
sse-emptyheaded-layout-hybrid | 122.352 | 119.988 | 9.123 | 251.463
sse-han-bsr-qfilter | 234.17 | 126.460 | 5.552 | 366.182
sse-han-bsr-sse-galloping | 233.258 | 136.472 | 5.385 | 375.115
sse-han-bsr-scalar-galloping | 235.867 | 143.726 | 5.399 | 384.992
sse-han-bsr-scalar-merge | 237.538 | 145.261 | 5.453 | 388.252
sse-han-bmiss | 0.000 | 163.149 | 5.431 | 168.58
sse-han-bsr-sse-shuffle | 235.953 | 187.670 | 5.48 | 429.103


### snap_friendster/rev_deg

file-name | LayoutTransform | SetInterTime | SimCal | TotalCoreCheck
--- | --- | --- | --- | ---
naive-bitvec-2d | 0.000 | 117.168 | 5.551 | 122.719
naive-bitvec | 0.000 | 404.205 | 5.459 | 409.664