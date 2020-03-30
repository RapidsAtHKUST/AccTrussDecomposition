# O(E) tri count time


Unit: seconds


### rmat_v50m_e0.5g

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec-deg` | `4.76` | `/` | `6.505`
`naive-bitvec-2d-deg` | `4.809` | `/` | `6.953`
**sse-eh-hybrid-deg** | **4.826** | **4.594** | **7.892**
**sse-eh-uint-deg** | **4.875** | **4.516** | **8.069**
**sse-bsr-qfilter-deg** | **4.793** | **6.962** | **8.978**
**sse-bsr-galloping-deg** | **4.857** | **7.133** | **8.991**
sse-han-bmiss-sttni-deg | 4.781 | / | 9.275
avx2-bmerge-deg | 4.754 | / | 9.291
avx2-hybrid-deg | 5.034 | / | 9.388
**naive-bsr-galloping-deg** | **4.827** | **6.853** | **9.399**
sse-hybrid-deg | 4.824 | / | 9.51
**naive-bsr-scalar-merge-deg** | **4.829** | **6.857** | **9.573**
sse-han-qfilter-deg | 4.831 | / | 9.644
sse-han-bmiss-deg | 4.769 | / | 9.649
sse-bmerge-deg | 4.823 | / | 9.753
sse-lemire-deg | 4.797 | / | 9.805
**sse-bsr-shuffle-deg** | **4.814** | **7.01** | **9.983**
avx2-lemire-deg | 4.864 | / | 9.997
sse-lemire-high-deg | 4.787 | / | 10.034
avx2-tetzank-deg | 4.841 | / | 10.372
avx-tetzank-deg | 4.739 | / | 10.417
avx2-galloping-deg | 4.78 | / | 10.596
naive-merge-deg | 4.845 | / | 10.646
avx2-asm-tetzank-deg | 4.782 | / | 10.668
naive-hybrid-deg | 4.801 | / | 10.668
naive-pivot-deg | 4.822 | / | 10.745
naive-galloping-deg | 4.879 | / | 10.918
sse-pivot-deg | 4.901 | / | 10.945
avx2-pivot-deg | 4.734 | / | 11.333
**avx2-roaring-deg** | **4.793** | **24.53** | **15.322**
**sse-roaring-deg** | **4.784** | **24.304** | **15.335**
naive-hash-deg | 4.819 | / | 18.69
naive-hash-spp-deg | 4.844 | / | 25.34


### rmat_v5m_e0.5g

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-roaring-deg** | **3.451** | **5.054** | **21.298**
**avx2-roaring-deg** | **3.428** | **5.928** | **21.327**
`naive-bitvec-deg` | `3.461` | `/` | `23.65`
sse-han-bmiss-sttni-deg | 3.511 | / | 23.911
**sse-eh-hybrid-deg** | **3.511** | **3.25** | **24.118**
avx2-asm-tetzank-deg | 3.286 | / | 24.126
avx2-bmerge-deg | 3.533 | / | 24.135
avx2-hybrid-deg | 3.488 | / | 24.323
sse-han-qfilter-deg | 3.521 | / | 24.859
avx2-tetzank-deg | 3.492 | / | 24.959
avx-tetzank-deg | 3.508 | / | 25.714
avx2-lemire-deg | 3.486 | / | 26.097
sse-lemire-deg | 3.469 | / | 26.2
sse-lemire-high-deg | 3.499 | / | 26.366
sse-han-bmiss-deg | 3.482 | / | 26.8
sse-bmerge-deg | 3.475 | / | 27.408
sse-hybrid-deg | 3.622 | / | 27.434
`naive-bitvec-2d-deg` | `3.513` | `/` | `28.373`
**sse-eh-uint-deg** | **3.51** | **2.985** | **28.785**
**sse-bsr-qfilter-deg** | **3.514** | **5.403** | **31.697**
avx2-pivot-deg | 3.492 | / | 31.825
sse-pivot-deg | 3.471 | / | 33.286
**sse-bsr-shuffle-deg** | **3.505** | **5.335** | **33.533**
avx2-galloping-deg | 3.49 | / | 34.578
naive-pivot-deg | 3.489 | / | 36.357
naive-merge-deg | 3.479 | / | 36.622
**sse-bsr-galloping-deg** | **3.514** | **5.502** | **39.461**
**naive-bsr-scalar-merge-deg** | **3.482** | **5.304** | **39.509**
naive-hybrid-deg | 3.555 | / | 39.618
naive-galloping-deg | 3.463 | / | 39.642
**naive-bsr-galloping-deg** | **3.5** | **5.415** | **43.635**
naive-hash-deg | 3.44 | / | 127.883
naive-hash-spp-deg | 3.492 | / | 165.613


### rmat_v0.5m_e0.5g

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
naive-hash-spp-deg | / | / | /
**sse-eh-hybrid-deg** | **3.72** | **2.144** | **28.772**
**sse-bsr-shuffle-deg** | **3.677** | **3.574** | **46.159**
**sse-bsr-qfilter-deg** | **3.676** | **3.578** | **47.39**
**naive-bsr-scalar-merge-deg** | **3.717** | **3.66** | **64.799**
**sse-roaring-deg** | **3.755** | **1.3** | **66.097**
**avx2-roaring-deg** | **3.738** | **1.338** | **66.41**
avx2-asm-tetzank-deg | 3.833 | / | 80.197
**naive-bsr-galloping-deg** | **3.717** | **3.61** | **81.857**
**sse-bsr-galloping-deg** | **3.719** | **3.616** | **88.012**
`naive-bitvec-deg` | `3.807` | `/` | `88.882`
avx2-tetzank-deg | 3.715 | / | 93.97
avx-tetzank-deg | 3.714 | / | 99.766
avx2-hybrid-deg | 3.705 | / | 104.542
avx2-bmerge-deg | 3.7 | / | 104.596
sse-lemire-high-deg | 3.75 | / | 111.705
avx2-lemire-deg | 3.736 | / | 123.334
sse-lemire-deg | 3.719 | / | 125.456
**sse-eh-uint-deg** | **3.721** | **2.049** | **131.592**
`naive-bitvec-2d-deg` | `3.734` | `/` | `131.659`
sse-bmerge-deg | 3.732 | / | 133.308
sse-hybrid-deg | 3.739 | / | 133.367
sse-han-qfilter-deg | 3.737 | / | 136.319
sse-han-bmiss-sttni-deg | 3.806 | / | 141.927
sse-han-bmiss-deg | 3.72 | / | 174.791
avx2-pivot-deg | 3.737 | / | 194.376
avx2-galloping-deg | 3.7 | / | 197.044
sse-pivot-deg | 3.721 | / | 207.396
naive-merge-deg | 3.733 | / | 211.962
naive-pivot-deg | 3.72 | / | 223.806
naive-hybrid-deg | 3.74 | / | 245.984
naive-galloping-deg | 3.751 | / | 246.063
naive-hash-deg | 3.742 | / | 745.491


### rmat_v100m_e1g

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec-2d-deg` | `9.729` | `/` | `15.52`
`naive-bitvec-deg` | `9.847` | `/` | `15.522`
**sse-eh-hybrid-deg** | **10.291** | **9.665** | **17.192**
**sse-eh-uint-deg** | **9.779** | **9.07** | **17.606**
avx2-hybrid-deg | 10.839 | / | 18.761
sse-han-bmiss-sttni-deg | 9.858 | / | 19.095
avx2-bmerge-deg | 9.802 | / | 19.6
**sse-bsr-qfilter-deg** | **9.994** | **14.105** | **19.705**
sse-lemire-deg | 9.787 | / | 19.874
sse-han-qfilter-deg | 9.886 | / | 19.959
sse-hybrid-deg | 9.779 | / | 20.034
**naive-bsr-scalar-merge-deg** | **9.855** | **15.463** | **20.086**
avx2-tetzank-deg | 10.208 | / | 20.088
sse-han-bmiss-deg | 9.829 | / | 20.511
**sse-bsr-galloping-deg** | **9.842** | **14.075** | **20.563**
sse-bmerge-deg | 9.742 | / | 20.565
**naive-bsr-galloping-deg** | **9.93** | **15.114** | **20.573**
avx2-lemire-deg | 10.535 | / | 20.841
sse-lemire-high-deg | 9.837 | / | 21.35
avx-tetzank-deg | 10.595 | / | 21.697
naive-galloping-deg | 9.788 | / | 21.813
sse-pivot-deg | 9.777 | / | 22.03
naive-hybrid-deg | 9.807 | / | 22.037
**sse-bsr-shuffle-deg** | **9.987** | **15.035** | **22.256**
avx2-galloping-deg | 10.431 | / | 22.364
naive-pivot-deg | 9.859 | / | 22.579
naive-merge-deg | 9.997 | / | 22.593
avx2-asm-tetzank-deg | 9.764 | / | 22.713
avx2-pivot-deg | 9.973 | / | 22.893
naive-hash-deg | 9.819 | / | 41.376
naive-hash-spp-deg | 9.779 | / | 56.175
**sse-roaring-deg** | **9.71** | **120.275** | **378.168**
**avx2-roaring-deg** | **10.592** | **117.201** | **432.912**


### rmat_v10m_e1g

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
sse-han-bmiss-sttni-deg | 6.789 | / | 51.247
`naive-bitvec-deg` | `6.755` | `/` | `51.855`
avx2-hybrid-deg | 6.725 | / | 52.171
avx2-asm-tetzank-deg | 7.11 | / | 52.202
avx2-bmerge-deg | 6.689 | / | 52.239
sse-han-qfilter-deg | 6.753 | / | 53.526
**avx2-roaring-deg** | **6.762** | **15.064** | **53.544**
avx2-tetzank-deg | 6.742 | / | 54.082
**sse-roaring-deg** | **6.724** | **13.622** | **54.466**
**sse-eh-hybrid-deg** | **6.756** | **6.194** | **55.009**
avx2-lemire-deg | 6.802 | / | 55.351
avx-tetzank-deg | 6.711 | / | 55.359
sse-lemire-deg | 6.774 | / | 56.047
sse-lemire-high-deg | 6.767 | / | 56.816
sse-han-bmiss-deg | 6.768 | / | 56.898
sse-bmerge-deg | 6.759 | / | 58.587
sse-hybrid-deg | 6.696 | / | 58.798
`naive-bitvec-2d-deg` | `6.717` | `/` | `61.656`
**sse-eh-uint-deg** | **6.741** | **5.871** | **63.03**
avx2-pivot-deg | 6.772 | / | 67.936
sse-pivot-deg | 6.754 | / | 70.556
**sse-bsr-qfilter-deg** | **6.782** | **10.871** | **70.982**
avx2-galloping-deg | 6.746 | / | 72.821
**sse-bsr-shuffle-deg** | **6.783** | **10.89** | **76.532**
naive-pivot-deg | 6.738 | / | 76.759
naive-merge-deg | 6.763 | / | 77.544
naive-galloping-deg | 6.708 | / | 83.396
naive-hybrid-deg | 6.727 | / | 83.594
**sse-bsr-galloping-deg** | **6.85** | **10.842** | **84.667**
**naive-bsr-scalar-merge-deg** | **6.74** | **10.829** | **88.483**
**naive-bsr-galloping-deg** | **6.783** | **10.939** | **95.983**
naive-hash-deg | 6.751 | / | 280.141
naive-hash-spp-deg | 6.737 | / | 350.451


### rmat_v1m_e1g

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
naive-hash-deg | / | / | /
naive-hash-spp-deg | / | / | /
**sse-eh-hybrid-deg** | **6.913** | **4.255** | **87.494**
**sse-bsr-shuffle-deg** | **7.252** | **6.865** | **130.542**
**sse-bsr-qfilter-deg** | **7.229** | **7.175** | **138.625**
**sse-roaring-deg** | **6.955** | **2.785** | **141.871**
**avx2-roaring-deg** | **6.949** | **2.553** | **141.987**
**naive-bsr-scalar-merge-deg** | **6.959** | **6.934** | **184.028**
avx2-asm-tetzank-deg | 7.118 | / | 192.084
`naive-bitvec-deg` | `7.332` | `/` | `214.42`
avx2-tetzank-deg | 6.963 | / | 222.42
**naive-bsr-galloping-deg** | **7.277** | **7.034** | **228.843**
avx-tetzank-deg | 7.189 | / | 235.13
**sse-bsr-galloping-deg** | **7.266** | **6.899** | **238.395**
avx2-bmerge-deg | 6.958 | / | 241.361
avx2-hybrid-deg | 7.003 | / | 241.819
sse-lemire-high-deg | 7.232 | / | 257.927
avx2-lemire-deg | 7.209 | / | 279.481
sse-lemire-deg | 7.274 | / | 283.91
sse-han-qfilter-deg | 6.972 | / | 301.449
**sse-eh-uint-deg** | **6.88** | **3.724** | **304.161**
sse-hybrid-deg | 6.984 | / | 304.19
sse-bmerge-deg | 6.959 | / | 304.376
sse-han-bmiss-sttni-deg | 7.309 | / | 305.649
`naive-bitvec-2d-deg` | `7.283` | `/` | `308.523`
sse-han-bmiss-deg | 7.047 | / | 377.639
avx2-pivot-deg | 6.93 | / | 421.504
avx2-galloping-deg | 6.946 | / | 434.543
sse-pivot-deg | 6.984 | / | 456.237
naive-merge-deg | 6.962 | / | 476.895
naive-pivot-deg | 7.298 | / | 500.347
naive-hybrid-deg | 7.299 | / | 550.05
naive-galloping-deg | 6.949 | / | 550.129


### rmat_v200m_e2g

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring-deg** | **/** | **/** | **/**
**sse-roaring-deg** | **/** | **/** | **/**
`naive-bitvec-2d-deg` | `21.56` | `/` | `33.069`
`naive-bitvec-deg` | `21.086` | `/` | `36.553`
**sse-eh-hybrid-deg** | **26.243** | **18.958** | **36.821**
avx2-bmerge-deg | 27.216 | / | 37.983
**sse-eh-uint-deg** | **24.035** | **19.209** | **38.183**
sse-han-qfilter-deg | 26.295 | / | 39.428
avx2-hybrid-deg | 23.922 | / | 39.464
sse-han-bmiss-sttni-deg | 26.304 | / | 39.588
sse-hybrid-deg | 22.604 | / | 40.486
sse-bmerge-deg | 24.561 | / | 40.647
sse-han-bmiss-deg | 22.925 | / | 40.76
sse-lemire-deg | 26.026 | / | 42.263
avx2-lemire-deg | 25.332 | / | 42.859
**sse-bsr-qfilter-deg** | **26.351** | **32.102** | **43.279**
**naive-bsr-scalar-merge-deg** | **24.89** | **31.672** | **43.332**
**sse-bsr-galloping-deg** | **26.061** | **34.343** | **43.351**
avx2-tetzank-deg | 21.71 | / | 44.178
sse-lemire-high-deg | 26.525 | / | 44.617
avx-tetzank-deg | 22.942 | / | 44.826
**naive-bsr-galloping-deg** | **22.844** | **34.01** | **45.262**
naive-galloping-deg | 24.548 | / | 45.353
sse-pivot-deg | 23.133 | / | 45.902
naive-pivot-deg | 26.085 | / | 46.325
naive-merge-deg | 23.246 | / | 46.6
naive-hybrid-deg | 24.214 | / | 46.645
avx2-galloping-deg | 25.083 | / | 47.006
**sse-bsr-shuffle-deg** | **22.49** | **35.852** | **47.557**
avx2-asm-tetzank-deg | 23.859 | / | 48.03
avx2-pivot-deg | 23.362 | / | 48.917
naive-hash-deg | 24.727 | / | 88.443
naive-hash-spp-deg | 22.836 | / | 121.18


### rmat_v20m_e2g

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
sse-han-bmiss-sttni-deg | 16.859 | / | 111.181
avx2-asm-tetzank-deg | 14.114 | / | 112.43
avx2-bmerge-deg | 14.763 | / | 113.364
`naive-bitvec-deg` | `16.093` | `/` | `113.448`
avx2-hybrid-deg | 15.197 | / | 113.797
sse-han-qfilter-deg | 16.691 | / | 114.88
avx2-tetzank-deg | 16.414 | / | 116.679
avx2-lemire-deg | 15.089 | / | 118.72
avx-tetzank-deg | 16.245 | / | 120.431
sse-lemire-deg | 16.504 | / | 120.792
**sse-eh-hybrid-deg** | **16.873** | **12.054** | **121.258**
sse-han-bmiss-deg | 16.84 | / | 122.463
sse-lemire-high-deg | 16.819 | / | 122.805
sse-bmerge-deg | 16.796 | / | 126.398
sse-hybrid-deg | 16.708 | / | 126.456
**avx2-roaring-deg** | **15.596** | **42.602** | **132.445**
**sse-roaring-deg** | **16.765** | **51.598** | **134.973**
**sse-eh-uint-deg** | **17.201** | **11.804** | **136.416**
`naive-bitvec-2d-deg` | `14.894` | `/` | `136.586`
avx2-pivot-deg | 14.808 | / | 144.943
sse-pivot-deg | 16.721 | / | 150.66
avx2-galloping-deg | 15.116 | / | 154.704
**sse-bsr-qfilter-deg** | **17.393** | **21.822** | **160.397**
naive-pivot-deg | 16.461 | / | 164.363
naive-merge-deg | 16.483 | / | 166.956
**sse-bsr-shuffle-deg** | **16.906** | **21.757** | **173.118**
naive-hybrid-deg | 16.496 | / | 178.262
naive-galloping-deg | 17.33 | / | 178.321
**sse-bsr-galloping-deg** | **16.848** | **21.553** | **181.318**
**naive-bsr-scalar-merge-deg** | **17.149** | **21.37** | **194.999**
**naive-bsr-galloping-deg** | **17.096** | **21.591** | **208.913**
naive-hash-deg | 14.802 | / | 487.169
naive-hash-spp-deg | 16.605 | / | 765.842


### rmat_v2m_e2g

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
avx2-galloping-deg | / | / | /
avx2-pivot-deg | / | / | /
naive-galloping-deg | / | / | /
naive-hash-deg | / | / | /
naive-hash-spp-deg | / | / | /
naive-hybrid-deg | / | / | /
naive-merge-deg | / | / | /
naive-pivot-deg | / | / | /
sse-han-bmiss-deg | / | / | /
sse-pivot-deg | / | / | /
**sse-eh-hybrid-deg** | **18.69** | **7.982** | **248.195**
**avx2-roaring-deg** | **16.672** | **6.821** | **299.892**
**sse-roaring-deg** | **17.009** | **6.332** | **302.245**
**sse-bsr-shuffle-deg** | **16.973** | **13.503** | **364.274**
**sse-bsr-qfilter-deg** | **17.699** | **13.669** | **369.49**
avx2-asm-tetzank-deg | 15.649 | / | 447.609
`naive-bitvec-deg` | `18.705` | `/` | `496.55`
avx2-tetzank-deg | 17.114 | / | 507.852
**naive-bsr-scalar-merge-deg** | **16.765** | **13.489** | **510.655**
avx-tetzank-deg | 16.594 | / | 529.633
avx2-bmerge-deg | 15.654 | / | 541.816
avx2-hybrid-deg | 16.828 | / | 542.161
sse-lemire-high-deg | 18.131 | / | 577.405
avx2-lemire-deg | 16.565 | / | 615.466
**naive-bsr-galloping-deg** | **17.057** | **13.56** | **623.975**
sse-lemire-deg | 18.946 | / | 625.028
**sse-bsr-galloping-deg** | **16.798** | **13.876** | **627.108**
sse-han-bmiss-sttni-deg | 16.707 | / | 637.196
sse-han-qfilter-deg | 16.572 | / | 643.765
sse-bmerge-deg | 17.09 | / | 673.626
sse-hybrid-deg | 18.275 | / | 674.065
**sse-eh-uint-deg** | **18.448** | **7.245** | **679.829**
`naive-bitvec-2d-deg` | `16.725` | `/` | `699.374`