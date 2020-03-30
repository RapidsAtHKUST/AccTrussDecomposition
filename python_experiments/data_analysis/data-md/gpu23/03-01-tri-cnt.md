# O(E) tri count time


Unit: seconds


### snap_livejournal

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec-deg` | `0.288` | `/` | `0.21`
`naive-bitvec-2d-deg` | `0.284` | `/` | `0.282`
**sse-eh-uint-deg** | **0.284** | **0.425** | **0.325**
**sse-eh-hybrid-deg** | **0.302** | **0.424** | **0.327**
**sse-bsr-qfilter-deg** | **0.284** | **0.564** | **0.408**
**sse-bsr-shuffle-deg** | **0.287** | **0.583** | **0.42**
**naive-bsr-scalar-merge-deg** | **0.272** | **0.596** | **0.454**
**sse-bsr-galloping-deg** | **0.288** | **0.599** | **0.482**
**naive-bsr-galloping-deg** | **0.291** | **0.588** | **0.504**
avx2-asm-tetzank-deg | 0.319 | / | 0.526
sse-lemire-kcore | 0.275 | / | 0.533
sse-hybrid-deg | 0.297 | / | 0.537
sse-han-qfilter-deg | 0.285 | / | 0.54
sse-han-bmiss-sttni-deg | 0.285 | / | 0.544
avx2-hybrid-deg | 0.285 | / | 0.549
avx2-bmerge-deg | 0.281 | / | 0.557
naive-hybrid-deg | 0.293 | / | 0.561
sse-bmerge-deg | 0.281 | / | 0.562
sse-lemire-high-deg | 0.283 | / | 0.562
sse-han-bmiss-deg | 0.274 | / | 0.566
avx2-lemire-deg | 0.303 | / | 0.568
avx-tetzank-deg | 0.291 | / | 0.568
sse-lemire-deg | 0.293 | / | 0.571
avx2-tetzank-deg | 0.331 | / | 0.578
naive-galloping-deg | 0.284 | / | 0.593
**sse-roaring-deg** | **0.279** | **1.931** | **0.6**
naive-merge-deg | 0.278 | / | 0.603
naive-pivot-deg | 0.287 | / | 0.617
avx2-galloping-deg | 0.289 | / | 0.625
**avx2-roaring-deg** | **0.313** | **1.903** | **0.637**
avx2-pivot-deg | 0.28 | / | 0.654
sse-pivot-deg | 0.296 | / | 0.668
naive-hash-deg | 0.278 | / | 0.826
naive-hash-spp-deg | 0.282 | / | 1.016


### snap_orkut

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec-deg` | `0.763` | `/` | `1.438`
`naive-bitvec-2d-deg` | `0.767` | `/` | `1.828`
**sse-eh-hybrid-deg** | **0.772** | **0.878** | **1.977**
**sse-eh-uint-deg** | **0.773** | **0.807** | **2.13**
**sse-bsr-qfilter-deg** | **0.76** | **1.354** | **2.385**
avx2-bmerge-deg | 0.724 | / | 2.424
avx2-hybrid-deg | 0.765 | / | 2.443
sse-bmerge-deg | 0.743 | / | 2.457
sse-han-bmiss-sttni-deg | 0.733 | / | 2.457
avx2-tetzank-deg | 0.783 | / | 2.488
**sse-bsr-shuffle-deg** | **0.769** | **1.407** | **2.501**
sse-hybrid-deg | 0.761 | / | 2.511
avx2-lemire-deg | 0.776 | / | 2.533
sse-lemire-high-deg | 0.766 | / | 2.537
sse-han-qfilter-deg | 0.765 | / | 2.557
avx2-asm-tetzank-deg | 0.835 | / | 2.559
sse-lemire-deg | 0.751 | / | 2.573
sse-lemire-kcore | 0.817 | / | 2.578
avx-tetzank-deg | 0.761 | / | 2.591
sse-han-bmiss-deg | 0.754 | / | 2.699
naive-pivot-deg | 0.773 | / | 3.004
avx2-galloping-deg | 0.758 | / | 3.049
**naive-bsr-scalar-merge-deg** | **0.756** | **1.312** | **3.083**
avx2-pivot-deg | 0.766 | / | 3.088
sse-pivot-deg | 0.757 | / | 3.101
naive-merge-deg | 0.772 | / | 3.15
**sse-bsr-galloping-deg** | **0.758** | **1.392** | **3.164**
naive-hybrid-deg | 0.742 | / | 3.315
**naive-bsr-galloping-deg** | **0.744** | **1.336** | **3.331**
naive-galloping-deg | 0.778 | / | 3.383
**avx2-roaring-deg** | **0.75** | **2.511** | **3.771**
**sse-roaring-deg** | **0.786** | **2.337** | **4.004**
naive-hash-deg | 0.812 | / | 5.181
naive-hash-spp-deg | 0.745 | / | 8.024


### webgraph_eu

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid-deg** | **1.518** | **0.959** | **1.544**
**sse-bsr-shuffle-deg** | **1.475** | **1.847** | **2.473**
**sse-bsr-qfilter-deg** | **1.494** | **1.603** | **2.66**
**naive-bsr-scalar-merge-deg** | **1.542** | **1.877** | **2.742**
**naive-bsr-galloping-deg** | **1.645** | **1.959** | **4.249**
**sse-bsr-galloping-deg** | **1.504** | **1.835** | **4.285**
**avx2-roaring-deg** | **1.552** | **2.494** | **4.512**
**sse-roaring-deg** | **1.517** | **1.782** | **4.531**
avx2-asm-tetzank-deg | 1.557 | / | 18.869
avx2-tetzank-deg | 1.52 | / | 21.157
avx-tetzank-deg | 1.604 | / | 22.019
sse-lemire-high-deg | 1.514 | / | 22.54
avx2-bmerge-deg | 1.577 | / | 23.386
avx2-hybrid-deg | 1.605 | / | 23.919
sse-bmerge-deg | 1.542 | / | 24.87
`naive-bitvec-deg` | `1.573` | `/` | `24.922`
sse-hybrid-deg | 1.489 | / | 25.111
**sse-eh-uint-deg** | **1.476** | **1.215** | **26.18**
sse-han-qfilter-deg | 1.481 | / | 27.649
naive-merge-deg | 1.52 | / | 30.062
sse-han-bmiss-deg | 1.591 | / | 34.438
naive-pivot-deg | 1.517 | / | 36.813
naive-hybrid-deg | 1.626 | / | 37.393
naive-galloping-deg | 1.549 | / | 37.795
`naive-bitvec-2d-deg` | `1.534` | `/` | `38.889`
avx2-lemire-deg | 1.514 | / | 46.399
sse-lemire-kcore | 1.423 | / | 49.234
sse-lemire-deg | 1.623 | / | 49.896
sse-han-bmiss-sttni-deg | 1.509 | / | 56.869
avx2-galloping-deg | 1.589 | / | 89.005
sse-pivot-deg | 1.517 | / | 137.353
naive-hash-spp-deg | 1.517 | / | 153.02
avx2-pivot-deg | 1.64 | / | 158.493
naive-hash-deg | 1.644 | / | 164.245


### webgraph_uk

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec-deg` | `1.209` | `/` | `0.413`
**sse-roaring-deg** | **1.342** | **1.584** | **0.444**
**avx2-roaring-deg** | **1.22** | **1.675** | **0.496**
`naive-bitvec-2d-deg` | `1.212` | `/` | `0.544`
**sse-bsr-shuffle-deg** | **1.215** | **2.224** | **0.576**
**sse-eh-uint-deg** | **1.238** | **1.66** | **0.597**
**sse-eh-hybrid-deg** | **1.249** | **1.601** | **0.638**
**naive-bsr-scalar-merge-deg** | **1.213** | **2.249** | **0.642**
**sse-bsr-qfilter-deg** | **1.213** | **2.412** | **0.659**
**naive-bsr-galloping-deg** | **1.255** | **2.28** | **0.792**
**sse-bsr-galloping-deg** | **1.203** | **2.278** | **0.807**
avx2-hybrid-deg | 1.276 | / | 1.781
avx2-bmerge-deg | 1.206 | / | 1.877
sse-lemire-high-deg | 1.222 | / | 1.899
avx2-tetzank-deg | 1.216 | / | 1.914
sse-hybrid-deg | 1.212 | / | 1.927
naive-merge-deg | 1.222 | / | 1.936
naive-pivot-deg | 1.219 | / | 1.94
sse-han-bmiss-sttni-deg | 1.215 | / | 1.94
avx-tetzank-deg | 1.204 | / | 1.942
avx2-asm-tetzank-deg | 1.233 | / | 1.948
sse-bmerge-deg | 1.217 | / | 1.966
naive-hybrid-deg | 1.27 | / | 1.971
naive-galloping-deg | 1.202 | / | 1.988
sse-lemire-deg | 1.202 | / | 1.995
avx2-lemire-deg | 1.21 | / | 2.0
sse-han-qfilter-deg | 1.213 | / | 2.004
sse-han-bmiss-deg | 1.208 | / | 2.005
sse-lemire-kcore | 1.1 | / | 2.027
naive-hash-spp-deg | 1.206 | / | 2.096
avx2-galloping-deg | 1.2 | / | 2.151
sse-pivot-deg | 1.205 | / | 2.247
avx2-pivot-deg | 1.203 | / | 2.364
naive-hash-deg | 1.241 | / | 2.412


### webgraph_webbase

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring-deg** | **5.419** | **9.375** | **1.219**
**sse-roaring-deg** | **5.404** | **9.204** | **1.314**
`naive-bitvec-deg` | `5.422` | `/` | `1.465`
**sse-eh-hybrid-deg** | **5.453** | **7.333** | **1.849**
**naive-bsr-scalar-merge-deg** | **5.686** | **10.063** | **1.918**
**sse-eh-uint-deg** | **5.435** | **8.287** | **2.074**
**sse-bsr-qfilter-deg** | **5.456** | **10.742** | **2.093**
`naive-bitvec-2d-deg` | `5.451` | `/` | `2.312`
**sse-bsr-galloping-deg** | **5.471** | **10.708** | **2.352**
**sse-bsr-shuffle-deg** | **5.748** | **9.793** | **2.603**
**naive-bsr-galloping-deg** | **5.818** | **10.541** | **2.803**
avx2-hybrid-deg | 5.38 | / | 6.31
avx2-asm-tetzank-deg | 5.7 | / | 6.352
sse-lemire-high-deg | 5.452 | / | 6.362
sse-han-qfilter-deg | 5.453 | / | 6.446
sse-bmerge-deg | 5.438 | / | 6.505
naive-pivot-deg | 5.918 | / | 6.506
avx2-bmerge-deg | 5.603 | / | 6.513
naive-merge-deg | 5.437 | / | 6.536
sse-hybrid-deg | 5.632 | / | 6.637
sse-han-bmiss-deg | 5.446 | / | 6.69
avx-tetzank-deg | 5.876 | / | 6.74
avx2-tetzank-deg | 5.445 | / | 6.775
avx2-lemire-deg | 5.459 | / | 6.814
naive-hybrid-deg | 5.748 | / | 6.936
naive-galloping-deg | 6.08 | / | 7.008
sse-lemire-kcore | 4.752 | / | 7.052
sse-lemire-deg | 5.418 | / | 7.08
sse-han-bmiss-sttni-deg | 5.801 | / | 7.252
naive-hash-spp-deg | 5.831 | / | 7.424
avx2-galloping-deg | 5.656 | / | 7.608
sse-pivot-deg | 5.434 | / | 8.245
avx2-pivot-deg | 5.733 | / | 8.333
naive-hash-deg | 5.62 | / | 8.797


### webgraph_it

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec-deg` | `4.827` | `/` | `2.707`
**sse-bsr-qfilter-deg** | **5.266** | **8.313** | **2.846**
**naive-bsr-scalar-merge-deg** | **5.15** | **7.96** | **2.917**
**sse-eh-hybrid-deg** | **4.916** | **5.093** | **2.99**
**sse-bsr-shuffle-deg** | **4.937** | **7.844** | **3.028**
**avx2-roaring-deg** | **4.814** | **11.423** | **3.297**
**naive-bsr-galloping-deg** | **4.865** | **7.414** | **3.513**
**sse-bsr-galloping-deg** | **4.854** | **7.681** | **3.801**
`naive-bitvec-2d-deg` | `4.8` | `/` | `3.924`
**sse-eh-uint-deg** | **4.856** | **4.872** | **3.924**
**sse-roaring-deg** | **4.91** | **10.003** | **3.937**
avx2-asm-tetzank-deg | 4.849 | / | 7.524
sse-lemire-high-deg | 4.883 | / | 7.845
sse-bmerge-deg | 4.932 | / | 7.923
avx2-bmerge-deg | 4.858 | / | 8.004
avx2-tetzank-deg | 4.815 | / | 8.068
avx2-hybrid-deg | 4.924 | / | 8.198
naive-merge-deg | 4.945 | / | 8.233
avx-tetzank-deg | 4.854 | / | 8.274
sse-hybrid-deg | 4.841 | / | 8.32
naive-pivot-deg | 4.969 | / | 8.485
naive-hybrid-deg | 4.875 | / | 8.55
sse-han-qfilter-deg | 4.994 | / | 8.673
naive-galloping-deg | 5.283 | / | 9.006
sse-han-bmiss-deg | 5.049 | / | 9.172
avx2-lemire-deg | 4.899 | / | 9.325
sse-lemire-deg | 4.934 | / | 9.798
sse-han-bmiss-sttni-deg | 4.966 | / | 10.251
sse-lemire-kcore | 3.97 | / | 10.497
avx2-galloping-deg | 4.898 | / | 10.984
sse-pivot-deg | 4.9 | / | 13.936
avx2-pivot-deg | 4.881 | / | 14.726
naive-hash-spp-deg | 4.85 | / | 16.371
naive-hash-deg | 5.057 | / | 16.872


### webgraph_twitter

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid-deg** | **8.818** | **5.808** | **17.747**
`naive-bitvec-deg` | `7.977` | `/` | `21.427`
**sse-bsr-qfilter-deg** | **8.909** | **8.083** | **23.637**
avx2-asm-tetzank-deg | 8.771 | / | 24.002
avx2-bmerge-deg | 8.383 | / | 24.675
**sse-bsr-shuffle-deg** | **8.612** | **8.844** | **24.748**
avx2-tetzank-deg | 8.691 | / | 25.218
avx2-hybrid-deg | 8.529 | / | 25.269
avx-tetzank-deg | 8.922 | / | 26.344
avx2-lemire-deg | 8.086 | / | 26.845
sse-lemire-high-deg | 8.502 | / | 27.242
**naive-bsr-scalar-merge-deg** | **8.712** | **8.433** | **27.63**
`naive-bitvec-2d-deg` | `7.828` | `/` | `27.689`
sse-lemire-deg | 8.928 | / | 27.799
sse-bmerge-deg | 8.008 | / | 29.618
sse-hybrid-deg | 7.933 | / | 29.734
**sse-eh-uint-deg** | **8.028** | **5.618** | **29.887**
**sse-bsr-galloping-deg** | **8.094** | **8.351** | **30.412**
sse-han-qfilter-deg | 7.725 | / | 30.437
**naive-bsr-galloping-deg** | **8.045** | **8.058** | **30.796**
sse-han-bmiss-sttni-deg | 8.625 | / | 31.658
sse-lemire-kcore | 6.274 | / | 32.475
sse-han-bmiss-deg | 8.493 | / | 36.19
avx2-pivot-deg | 8.145 | / | 39.095
avx2-galloping-deg | 8.589 | / | 39.568
sse-pivot-deg | 8.152 | / | 40.678
naive-merge-deg | 8.099 | / | 41.41
naive-pivot-deg | 8.115 | / | 42.052
naive-hybrid-deg | 7.817 | / | 45.764
naive-galloping-deg | 9.048 | / | 46.377
**avx2-roaring-deg** | **7.958** | **14.137** | **52.754**
**sse-roaring-deg** | **7.914** | **14.165** | **53.39**
naive-hash-deg | 8.936 | / | 115.335
naive-hash-spp-deg | 8.777 | / | 170.545


### snap_friendster

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring-deg** | **/** | **/** | **/**
**sse-roaring-deg** | **/** | **/** | **/**
`naive-bitvec-deg` | `15.791` | `/` | `40.579`
`naive-bitvec-2d-deg` | `15.842` | `/` | `41.516`
avx2-bmerge-deg | 19.028 | / | 43.008
sse-han-bmiss-sttni-deg | 16.948 | / | 43.915
avx2-hybrid-deg | 18.501 | / | 44.905
avx2-tetzank-deg | 16.596 | / | 45.928
sse-han-qfilter-deg | 16.897 | / | 46.295
sse-hybrid-deg | 16.576 | / | 46.801
**sse-eh-hybrid-deg** | **16.17** | **14.752** | **46.842**
sse-lemire-high-deg | 16.145 | / | 47.088
avx2-lemire-deg | 20.763 | / | 47.134
sse-han-bmiss-deg | 16.282 | / | 47.217
**sse-eh-uint-deg** | **16.028** | **14.844** | **47.586**
sse-bmerge-deg | 17.232 | / | 47.914
sse-lemire-deg | 15.924 | / | 48.147
avx2-asm-tetzank-deg | 23.406 | / | 48.637
avx-tetzank-deg | 16.021 | / | 48.652
sse-lemire-kcore | 16.943 | / | 48.743
**sse-bsr-qfilter-deg** | **17.138** | **26.157** | **54.55**
naive-pivot-deg | 16.784 | / | 56.415
avx2-galloping-deg | 20.92 | / | 56.555
naive-merge-deg | 16.014 | / | 56.721
sse-pivot-deg | 17.492 | / | 57.163
avx2-pivot-deg | 18.852 | / | 58.287
naive-hybrid-deg | 16.044 | / | 59.994
naive-galloping-deg | 16.03 | / | 60.054
**sse-bsr-shuffle-deg** | **17.535** | **25.126** | **60.969**
**sse-bsr-galloping-deg** | **16.469** | **24.69** | **61.075**
**naive-bsr-scalar-merge-deg** | **19.596** | **25.277** | **64.245**
**naive-bsr-galloping-deg** | **16.389** | **25.285** | **68.548**
naive-hash-deg | 15.745 | / | 106.344
naive-hash-spp-deg | 15.952 | / | 175.116