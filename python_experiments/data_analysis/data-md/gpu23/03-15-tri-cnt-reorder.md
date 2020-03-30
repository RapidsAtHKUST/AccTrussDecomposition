# O(E) tri count time


Unit: seconds


### snap_livejournal/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `0.299` | `/` | `0.174`
**sse-bsr-qfilter** | **0.277** | **0.446** | **0.197**
`naive-bitvec-2d` | `0.347` | `/` | `0.231`
**sse-eh-uint** | **0.297** | **0.354** | **0.232**
**sse-eh-hybrid** | **0.305** | **0.597** | **0.235**
**naive-bsr-scalar-merge** | **0.279** | **0.48** | **0.236**
**avx2-roaring** | **0.281** | **0.941** | **0.479**
avx2-bmerge | 0.253 | / | 0.487
avx2-hybrid | 0.281 | / | 0.505
avx2-lemire | 0.281 | / | 0.516
avx2-asm-tetzank | 0.299 | / | 0.52
sse-han-bmiss-sttni | 0.277 | / | 0.544
sse-han-qfilter | 0.275 | / | 0.563
naive-merge | 0.334 | / | 0.571
naive-hybrid | 0.336 | / | 0.58


### snap_livejournal/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `/` | `/` | `0.174`
`naive-bitvec-2d` | `/` | `/` | `0.241`
**sse-eh-hybrid** | **/** | **0.329** | **0.251**
**sse-bsr-qfilter** | **/** | **0.472** | **0.262**
**sse-eh-uint** | **/** | **0.362** | **0.264**
**naive-bsr-scalar-merge** | **/** | **0.468** | **0.329**
avx2-hybrid | / | / | 0.476
avx2-bmerge | / | / | 0.478
avx2-asm-tetzank | / | / | 0.504
avx2-lemire | / | / | 0.507
sse-han-qfilter | / | / | 0.513
sse-han-bmiss-sttni | / | / | 0.524
naive-merge | / | / | 0.558
**avx2-roaring** | **/** | **1.148** | **0.574**
naive-hybrid | / | / | 0.605


### snap_livejournal/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `0.298` | `/` | `0.231`
`naive-bitvec-2d` | `0.311` | `/` | `0.279`
**sse-eh-hybrid** | **0.278** | **0.371** | **0.282**
**sse-eh-uint** | **0.343** | **0.539** | **0.353**
**sse-bsr-qfilter** | **0.286** | **0.475** | **0.4**
**naive-bsr-scalar-merge** | **0.279** | **0.449** | **0.453**
avx2-hybrid | 0.279 | / | 0.534
avx2-asm-tetzank | 0.279 | / | 0.544
avx2-bmerge | 0.278 | / | 0.555
avx2-lemire | 0.279 | / | 0.56
sse-han-qfilter | 0.274 | / | 0.564
sse-han-bmiss-sttni | 0.279 | / | 0.593
naive-hybrid | 0.281 | / | 0.62
naive-merge | 0.276 | / | 0.622
**avx2-roaring** | **0.28** | **1.214** | **0.682**


### snap_livejournal/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `0.272` | `/` | `0.226`
**sse-eh-hybrid** | **0.267** | **0.378** | **0.263**
`naive-bitvec-2d` | `0.269` | `/` | `0.29`
**sse-eh-uint** | **0.275** | **0.371** | **0.353**
**sse-bsr-qfilter** | **0.278** | **0.471** | **0.366**
**naive-bsr-scalar-merge** | **0.26** | **0.482** | **0.421**
avx2-hybrid | 0.275 | / | 0.542
**avx2-roaring** | **0.279** | **1.176** | **0.549**
sse-han-qfilter | 0.265 | / | 0.551
avx2-asm-tetzank | 0.271 | / | 0.555
avx2-bmerge | 0.27 | / | 0.556
avx2-lemire | 0.259 | / | 0.559
sse-han-bmiss-sttni | 0.266 | / | 0.589
naive-merge | 0.269 | / | 0.604
naive-hybrid | 0.27 | / | 0.627


### snap_orkut/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `0.761` | `/` | `1.142`
**sse-bsr-qfilter** | **0.684** | **1.222** | **1.479**
`naive-bitvec-2d` | `0.823` | `/` | `1.52`
**sse-eh-hybrid** | **0.743** | **0.858** | **1.629**
**sse-eh-uint** | **0.738** | **0.834** | **1.75**
**naive-bsr-scalar-merge** | **0.715** | **1.267** | **1.974**
avx2-hybrid | 0.744 | / | 2.093
avx2-asm-tetzank | 0.737 | / | 2.112
avx2-bmerge | 0.685 | / | 2.14
avx2-lemire | 0.704 | / | 2.283
sse-han-bmiss-sttni | 0.698 | / | 2.293
sse-han-qfilter | 0.713 | / | 2.318
**avx2-roaring** | **0.733** | **2.296** | **2.59**
naive-merge | 0.829 | / | 2.768
naive-hybrid | 0.853 | / | 2.988


### snap_orkut/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `/` | `/` | `1.303`
`naive-bitvec-2d` | `/` | `/` | `1.856`
**sse-eh-uint** | **/** | **0.698** | **2.039**
**sse-eh-hybrid** | **/** | **0.733** | **2.04**
avx2-asm-tetzank | / | / | 2.165
avx2-hybrid | / | / | 2.17
avx2-bmerge | / | / | 2.193
**sse-bsr-qfilter** | **/** | **1.277** | **2.223**
avx2-lemire | / | / | 2.357
sse-han-qfilter | / | / | 2.358
sse-han-bmiss-sttni | / | / | 2.372
naive-merge | / | / | 3.048
**naive-bsr-scalar-merge** | **/** | **1.228** | **3.093**
naive-hybrid | / | / | 3.319
**avx2-roaring** | **/** | **2.279** | **3.781**


### snap_orkut/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `0.753` | `/` | `1.412`
`naive-bitvec-2d` | `0.752` | `/` | `1.782`
**sse-eh-hybrid** | **0.754** | **0.866** | **1.842**
**sse-eh-uint** | **0.728** | **0.758** | **1.966**
**sse-bsr-qfilter** | **0.769** | **1.255** | **2.313**
avx2-bmerge | 0.753 | / | 2.317
avx2-hybrid | 0.751 | / | 2.365
avx2-asm-tetzank | 0.748 | / | 2.426
sse-han-qfilter | 0.769 | / | 2.483
avx2-lemire | 0.763 | / | 2.505
sse-han-bmiss-sttni | 0.753 | / | 2.521
**naive-bsr-scalar-merge** | **0.751** | **1.394** | **2.953**
naive-merge | 0.752 | / | 2.978
naive-hybrid | 0.755 | / | 3.204
**avx2-roaring** | **0.83** | **2.556** | **3.314**


### snap_orkut/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `0.771` | `/` | `1.523`
**sse-eh-hybrid** | **0.767** | **1.02** | **1.837**
`naive-bitvec-2d` | `0.765` | `/` | `1.977`
**sse-eh-uint** | **0.754** | **0.924** | **2.154**
avx2-hybrid | 0.772 | / | 2.226
**sse-bsr-qfilter** | **0.761** | **1.607** | **2.241**
avx2-bmerge | 0.76 | / | 2.363
avx2-lemire | 0.758 | / | 2.381
sse-han-bmiss-sttni | 0.752 | / | 2.384
avx2-asm-tetzank | 0.769 | / | 2.462
sse-han-qfilter | 0.746 | / | 2.584
**naive-bsr-scalar-merge** | **0.772** | **1.425** | **2.823**
naive-merge | 0.791 | / | 3.109
**avx2-roaring** | **0.838** | **2.504** | **3.118**
naive-hybrid | 0.75 | / | 3.287


### webgraph_eu/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **1.451** | **2.356** | **0.828**
**sse-eh-hybrid** | **1.575** | **1.04** | **1.469**
**sse-bsr-qfilter** | **1.466** | **1.569** | **2.013**
**naive-bsr-scalar-merge** | **1.589** | **1.632** | **2.017**
avx2-asm-tetzank | 1.442 | / | 17.444
avx2-hybrid | 1.54 | / | 21.528
avx2-bmerge | 1.477 | / | 21.743
`naive-bitvec` | `1.448` | `/` | `23.872`
**sse-eh-uint** | **1.567** | **1.369** | **25.583**
sse-han-qfilter | 1.452 | / | 27.562
naive-merge | 1.531 | / | 30.105
naive-hybrid | 1.532 | / | 36.806
`naive-bitvec-2d` | `1.562` | `/` | `37.574`
avx2-lemire | 1.511 | / | 48.153
sse-han-bmiss-sttni | 1.58 | / | 56.337


### webgraph_eu/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid** | **/** | **0.762** | **2.491**
**naive-bsr-scalar-merge** | **/** | **1.456** | **4.182**
**sse-bsr-qfilter** | **/** | **1.434** | **4.195**
**avx2-roaring** | **/** | **1.472** | **4.488**
avx2-hybrid | / | / | 22.877
`naive-bitvec` | `/` | `/` | `24.967`
avx2-bmerge | / | / | 28.808
**sse-eh-uint** | **/** | **1.146** | **33.184**
naive-hybrid | / | / | 38.441
`naive-bitvec-2d` | `/` | `/` | `38.82`
avx2-lemire | / | / | 52.074
naive-merge | / | / | 57.571
sse-han-qfilter | / | / | 70.043
sse-han-bmiss-sttni | / | / | 98.207
avx2-asm-tetzank | / | / | 125.103


### webgraph_eu/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid** | **1.515** | **1.064** | **1.436**
**sse-bsr-qfilter** | **1.734** | **1.754** | **2.529**
**naive-bsr-scalar-merge** | **1.51** | **1.525** | **2.729**
**avx2-roaring** | **1.613** | **2.642** | **4.095**
avx2-asm-tetzank | 1.628 | / | 18.419
avx2-hybrid | 1.487 | / | 21.989
avx2-bmerge | 1.499 | / | 21.995
`naive-bitvec` | `1.483` | `/` | `24.554`
**sse-eh-uint** | **1.616** | **1.181** | **25.593**
sse-han-qfilter | 1.502 | / | 27.464
naive-merge | 1.55 | / | 30.475
naive-hybrid | 1.504 | / | 37.103
`naive-bitvec-2d` | `1.509` | `/` | `37.87`
avx2-lemire | 1.543 | / | 49.124
sse-han-bmiss-sttni | 1.506 | / | 56.467


### webgraph_eu/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid** | **1.43** | **1.052** | **1.02**
**avx2-roaring** | **1.42** | **2.416** | **1.776**
**sse-bsr-qfilter** | **1.42** | **1.761** | **2.177**
**naive-bsr-scalar-merge** | **1.436** | **1.56** | **2.179**
avx2-asm-tetzank | 1.421 | / | 19.725
avx2-bmerge | 1.412 | / | 22.407
avx2-hybrid | 1.462 | / | 22.66
`naive-bitvec` | `1.452` | `/` | `25.132`
**sse-eh-uint** | **1.489** | **1.329** | **29.178**
sse-han-qfilter | 1.439 | / | 31.183
naive-merge | 1.419 | / | 34.291
naive-hybrid | 1.426 | / | 37.989
`naive-bitvec-2d` | `1.434` | `/` | `39.29`
avx2-lemire | 1.429 | / | 50.184
sse-han-bmiss-sttni | 1.422 | / | 60.231


### webgraph_uk/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `1.156` | `/` | `0.268`
**naive-bsr-scalar-merge** | **1.148** | **2.184** | **0.33**
**sse-bsr-qfilter** | **1.123** | **2.243** | **0.406**
`naive-bitvec-2d` | `1.243` | `/` | `0.474`
**sse-eh-hybrid** | **1.105** | **1.544** | **0.521**
**sse-eh-uint** | **1.108** | **1.643** | **0.56**
**avx2-roaring** | **1.164** | **2.551** | **0.602**
avx2-asm-tetzank | 1.142 | / | 1.704
avx2-bmerge | 1.117 | / | 1.718
sse-han-qfilter | 1.112 | / | 1.761
avx2-hybrid | 1.116 | / | 1.78
naive-merge | 1.262 | / | 1.79
naive-hybrid | 1.217 | / | 1.858
avx2-lemire | 1.117 | / | 1.887
sse-han-bmiss-sttni | 1.104 | / | 1.895


### webgraph_uk/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `/` | `/` | `0.27`
`naive-bitvec-2d` | `/` | `/` | `0.451`
**avx2-roaring** | **/** | **2.131** | **0.488**
**sse-bsr-qfilter** | **/** | **2.267** | **0.912**
**naive-bsr-scalar-merge** | **/** | **2.373** | **0.937**
**sse-eh-hybrid** | **/** | **1.228** | **1.442**
naive-hybrid | / | / | 1.838
avx2-hybrid | / | / | 1.891
**sse-eh-uint** | **/** | **1.454** | **2.746**
avx2-bmerge | / | / | 3.118
avx2-lemire | / | / | 3.891
naive-merge | / | / | 6.06
sse-han-qfilter | / | / | 9.096
sse-han-bmiss-sttni | / | / | 9.139
avx2-asm-tetzank | / | / | 29.845


### webgraph_uk/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `1.211` | `/` | `0.422`
**naive-bsr-scalar-merge** | **1.23** | **2.276** | **0.525**
**sse-eh-hybrid** | **1.231** | **1.678** | **0.53**
**sse-eh-uint** | **1.234** | **1.584** | **0.551**
`naive-bitvec-2d` | `1.22` | `/` | `0.551`
**sse-bsr-qfilter** | **1.235** | **2.458** | **0.732**
**avx2-roaring** | **1.229** | **3.709** | **1.005**
avx2-asm-tetzank | 1.273 | / | 1.792
naive-merge | 1.203 | / | 1.806
avx2-bmerge | 1.235 | / | 1.85
avx2-hybrid | 1.203 | / | 1.897
avx2-lemire | 1.213 | / | 1.918
naive-hybrid | 1.241 | / | 1.968
sse-han-qfilter | 1.213 | / | 1.973
sse-han-bmiss-sttni | 1.239 | / | 2.086


### webgraph_uk/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid** | **1.107** | **1.497** | **0.431**
**naive-bsr-scalar-merge** | **1.163** | **2.366** | **0.457**
**sse-bsr-qfilter** | **1.156** | **2.367** | **0.488**
`naive-bitvec` | `1.161` | `/` | `0.55`
**avx2-roaring** | **1.13** | **2.875** | **0.648**
**sse-eh-uint** | **1.125** | **1.589** | **0.719**
`naive-bitvec-2d` | `1.13` | `/` | `0.835`
naive-merge | 1.097 | / | 1.844
avx2-hybrid | 1.175 | / | 1.871
avx2-bmerge | 1.17 | / | 1.892
avx2-asm-tetzank | 1.1 | / | 1.897
naive-hybrid | 1.151 | / | 1.914
avx2-lemire | 1.165 | / | 1.957
sse-han-qfilter | 1.106 | / | 1.993
sse-han-bmiss-sttni | 1.144 | / | 2.088


### webgraph_webbase/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
avx2-asm-tetzank | / | / | /
`naive-bitvec` | `4.533` | `/` | `0.934`
**naive-bsr-scalar-merge** | **4.6** | **9.437** | **1.411**
**sse-bsr-qfilter** | **4.553** | **9.648** | **1.432**
**sse-eh-hybrid** | **4.578** | **6.86** | **1.534**
**sse-eh-uint** | **4.725** | **7.571** | **1.687**
`naive-bitvec-2d` | `4.701` | `/` | `1.815`
**avx2-roaring** | **4.53** | **14.937** | **2.014**
naive-hybrid | 4.707 | / | 5.998
sse-han-qfilter | 4.579 | / | 6.095
avx2-bmerge | 4.72 | / | 6.204
naive-merge | 4.747 | / | 6.302
avx2-hybrid | 4.553 | / | 6.358
avx2-lemire | 4.548 | / | 6.563
sse-han-bmiss-sttni | 4.497 | / | 6.588


### webgraph_webbase/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
avx2-asm-tetzank | / | / | /
`naive-bitvec` | `/` | `/` | `1.022`
**avx2-roaring** | **/** | **10.823** | **1.631**
`naive-bitvec-2d` | `/` | `/` | `2.155`
avx2-hybrid | / | / | 6.421
naive-hybrid | / | / | 6.733
**naive-bsr-scalar-merge** | **/** | **10.714** | **14.151**
**sse-bsr-qfilter** | **/** | **11.08** | **14.548**
**sse-eh-uint** | **/** | **6.819** | **46.151**
avx2-lemire | / | / | 56.089
avx2-bmerge | / | / | 79.338
naive-merge | / | / | 222.552
**sse-eh-hybrid** | **/** | **6.83** | **280.062**
sse-han-qfilter | / | / | 313.692
sse-han-bmiss-sttni | / | / | 363.626


### webgraph_webbase/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
avx2-asm-tetzank | / | / | /
`naive-bitvec` | `5.465` | `/` | `1.467`
`naive-bitvec-2d` | `7.288` | `/` | `2.336`
**sse-eh-hybrid** | **5.546** | **7.559** | **2.489**
**sse-eh-uint** | **5.446** | **7.324** | **2.622**
**naive-bsr-scalar-merge** | **5.413** | **9.705** | **2.717**
**sse-bsr-qfilter** | **5.43** | **10.056** | **2.796**
**avx2-roaring** | **5.437** | **22.94** | **4.142**
avx2-hybrid | 5.453 | / | 6.757
naive-merge | 5.531 | / | 6.865
avx2-bmerge | 5.482 | / | 6.933
sse-han-qfilter | 5.496 | / | 6.938
naive-hybrid | 6.11 | / | 7.052
sse-han-bmiss-sttni | 5.448 | / | 7.084
avx2-lemire | 5.421 | / | 7.173


### webgraph_webbase/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
avx2-asm-tetzank | / | / | /
**sse-eh-hybrid** | **4.92** | **8.063** | **1.701**
`naive-bitvec` | `4.765` | `/` | `1.859`
**sse-bsr-qfilter** | **4.768** | **10.212** | **2.239**
**naive-bsr-scalar-merge** | **4.75** | **9.773** | **2.392**
`naive-bitvec-2d` | `6.444` | `/` | `3.001`
**sse-eh-uint** | **4.803** | **7.427** | **3.023**
**avx2-roaring** | **4.743** | **18.212** | **3.052**
avx2-hybrid | 4.744 | / | 6.387
naive-merge | 4.903 | / | 6.454
sse-han-qfilter | 4.778 | / | 6.513
avx2-lemire | 4.745 | / | 6.561
avx2-bmerge | 4.726 | / | 6.67
naive-hybrid | 5.001 | / | 6.861
sse-han-bmiss-sttni | 4.738 | / | 7.132


### webgraph_it/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
naive-merge | / | / | /
avx2-asm-tetzank | / | / | /
avx2-bmerge | / | / | /
sse-han-bmiss-sttni | / | / | /
sse-han-qfilter | / | / | /
**naive-bsr-scalar-merge** | **4.223** | **7.725** | **1.124**
**sse-bsr-qfilter** | **4.234** | **7.672** | **1.25**
**avx2-roaring** | **4.256** | **8.122** | **1.707**
`naive-bitvec` | `4.287` | `/` | `2.137`
**sse-eh-hybrid** | **4.25** | **4.966** | **2.705**
**sse-eh-uint** | **4.263** | **4.991** | **3.294**
`naive-bitvec-2d` | `4.386` | `/` | `3.45`
avx2-hybrid | 4.206 | / | 7.461
naive-hybrid | 4.249 | / | 8.612
avx2-lemire | 4.246 | / | 9.259


### webgraph_it/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
naive-merge | / | / | /
avx2-asm-tetzank | / | / | /
avx2-bmerge | / | / | /
sse-han-bmiss-sttni | / | / | /
sse-han-qfilter | / | / | /
`naive-bitvec` | `/` | `/` | `3.174`
**avx2-roaring** | **/** | **3.689** | **3.974**
`naive-bitvec-2d` | `/` | `/` | `4.886`
naive-hybrid | / | / | 11.524
avx2-hybrid | / | / | 11.977
**sse-eh-hybrid** | **/** | **3.953** | **13.731**
**sse-bsr-qfilter** | **/** | **6.73** | **221.139**
**naive-bsr-scalar-merge** | **/** | **6.895** | **224.437**
**sse-eh-uint** | **/** | **5.091** | **537.273**
avx2-lemire | / | / | 578.021


### webgraph_it/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
naive-merge | / | / | /
avx2-asm-tetzank | / | / | /
avx2-bmerge | / | / | /
sse-han-bmiss-sttni | / | / | /
sse-han-qfilter | / | / | /
`naive-bitvec` | `4.942` | `/` | `2.673`
**sse-bsr-qfilter** | **4.831** | **7.703** | **2.909**
**naive-bsr-scalar-merge** | **4.888** | **7.547** | **3.018**
**sse-eh-hybrid** | **4.867** | **5.234** | **3.204**
**sse-eh-uint** | **4.91** | **4.98** | **3.767**
`naive-bitvec-2d` | `6.489` | `/` | `4.036`
**avx2-roaring** | **4.956** | **11.131** | **4.125**
avx2-hybrid | 4.848 | / | 7.892
naive-hybrid | 4.941 | / | 8.761
avx2-lemire | 4.935 | / | 9.777


### webgraph_it/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
naive-merge | / | / | /
avx2-asm-tetzank | / | / | /
avx2-bmerge | / | / | /
sse-han-bmiss-sttni | / | / | /
sse-han-qfilter | / | / | /
**sse-bsr-qfilter** | **3.74** | **7.727** | **2.173**
**naive-bsr-scalar-merge** | **3.776** | **7.458** | **2.191**
**sse-eh-hybrid** | **4.121** | **4.622** | **2.665**
**avx2-roaring** | **3.835** | **7.505** | **3.612**
`naive-bitvec` | `3.754` | `/` | `5.611`
**sse-eh-uint** | **3.84** | **5.097** | **6.695**
avx2-hybrid | 3.831 | / | 8.494
`naive-bitvec-2d` | `5.04` | `/` | `8.882`
naive-hybrid | 3.985 | / | 8.987
avx2-lemire | 3.786 | / | 10.026


### webgraph_twitter/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid** | **7.958** | **5.919** | **16.313**
**sse-bsr-qfilter** | **8.053** | **8.263** | **17.19**
`naive-bitvec` | `8.043` | `/` | `20.163`
**naive-bsr-scalar-merge** | **8.026** | **8.193** | **21.617**
**avx2-roaring** | **7.967** | **16.737** | **21.757**
avx2-asm-tetzank | 8.116 | / | 22.463
avx2-hybrid | 8.109 | / | 24.244
avx2-bmerge | 8.156 | / | 24.649
`naive-bitvec-2d` | `8.04` | `/` | `26.557`
avx2-lemire | 8.138 | / | 26.766
**sse-eh-uint** | **8.019** | **5.487** | **27.25**
sse-han-qfilter | 7.889 | / | 29.556
sse-han-bmiss-sttni | 8.09 | / | 29.908
naive-merge | 8.11 | / | 40.28
naive-hybrid | 8.569 | / | 43.952


### webgraph_twitter/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
avx2-hybrid | / | / | 46.364
avx2-lemire | / | / | 49.253
**avx2-roaring** | **/** | **15.796** | **53.194**
avx2-bmerge | / | / | 58.391
**sse-eh-uint** | **/** | **6.138** | **61.177**
**sse-eh-hybrid** | **/** | **6.254** | **63.215**
naive-hybrid | / | / | 76.933
**sse-bsr-qfilter** | **/** | **9.214** | **96.309**
sse-han-bmiss-sttni | / | / | 122.496
**naive-bsr-scalar-merge** | **/** | **9.218** | **125.361**
sse-han-qfilter | / | / | 131.81
naive-merge | / | / | 140.114
`naive-bitvec-2d` | `/` | `/` | `155.738`
avx2-asm-tetzank | / | / | 166.41
`naive-bitvec` | `/` | `/` | `288.053`


### webgraph_twitter/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid** | **8.054** | **5.565** | **17.712**
**avx2-roaring** | **8.053** | **17.195** | **21.078**
`naive-bitvec` | `7.943` | `/` | `21.435`
**sse-bsr-qfilter** | **7.811** | **8.839** | **23.564**
avx2-asm-tetzank | 7.944 | / | 23.841
avx2-bmerge | 7.985 | / | 24.442
avx2-hybrid | 8.413 | / | 25.538
avx2-lemire | 8.024 | / | 27.274
`naive-bitvec-2d` | `10.184` | `/` | `27.694`
**naive-bsr-scalar-merge** | **7.81** | **8.007** | **28.427**
**sse-eh-uint** | **7.997** | **5.706** | **29.27**
sse-han-qfilter | 7.916 | / | 30.351
sse-han-bmiss-sttni | 8.125 | / | 31.176
naive-merge | 7.87 | / | 41.792
naive-hybrid | 9.041 | / | 45.848


### webgraph_twitter/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid** | **5.82** | **5.492** | **21.304**
**avx2-roaring** | **5.922** | **20.058** | **28.123**
**sse-bsr-qfilter** | **5.729** | **8.27** | **28.727**
avx2-hybrid | 5.819 | / | 30.139
avx2-bmerge | 5.743 | / | 30.32
avx2-asm-tetzank | 5.814 | / | 30.743
avx2-lemire | 5.768 | / | 32.525
`naive-bitvec` | `5.773` | `/` | `32.614`
**naive-bsr-scalar-merge** | **5.806** | **8.371** | **34.953**
sse-han-qfilter | 5.846 | / | 38.291
**sse-eh-uint** | **5.687** | **5.499** | **38.576**
sse-han-bmiss-sttni | 5.7 | / | 38.792
`naive-bitvec-2d` | `7.865` | `/` | `43.917`
naive-merge | 5.822 | / | 50.718
naive-hybrid | 6.803 | / | 52.001


### snap_friendster/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec` | `15.879` | `/` | `37.498`
`naive-bitvec-2d` | `21.957` | `/` | `38.649`
**sse-bsr-qfilter** | **18.349** | **24.927** | **39.31**
sse-han-bmiss-sttni | 18.089 | / | 39.346
sse-han-qfilter | 18.432 | / | 41.262
**sse-eh-hybrid** | **19.227** | **14.998** | **41.296**
**sse-eh-uint** | **18.293** | **15.573** | **41.387**
avx2-bmerge | 18.849 | / | 41.583
avx2-hybrid | 18.634 | / | 41.729
avx2-lemire | 18.081 | / | 42.768
avx2-asm-tetzank | 18.774 | / | 43.721
**naive-bsr-scalar-merge** | **17.845** | **24.644** | **52.318**
naive-merge | 19.476 | / | 53.925
naive-hybrid | 24.603 | / | 58.287


### snap_friendster/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec-2d` | `/` | `/` | `49.524`
sse-han-bmiss-sttni | / | / | 50.146
avx2-bmerge | / | / | 50.635
avx2-hybrid | / | / | 50.788
sse-han-qfilter | / | / | 51.813
avx2-lemire | / | / | 53.053
avx2-asm-tetzank | / | / | 53.165
**sse-eh-uint** | **/** | **15.542** | **60.048**
**sse-eh-hybrid** | **/** | **15.449** | **60.105**
**sse-bsr-qfilter** | **/** | **26.001** | **64.265**
naive-merge | / | / | 71.319
naive-hybrid | / | / | 78.57
**naive-bsr-scalar-merge** | **/** | **25.722** | **84.876**
`naive-bitvec` | `/` | `/` | `154.266`


### snap_friendster/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec` | `16.117` | `/` | `41.368`
avx2-bmerge | 19.132 | / | 44.629
`naive-bitvec-2d` | `23.907` | `/` | `44.695`
sse-han-qfilter | 18.128 | / | 45.756
avx2-hybrid | 18.813 | / | 45.952
sse-han-bmiss-sttni | 20.749 | / | 46.044
**sse-eh-hybrid** | **19.134** | **15.456** | **46.444**
**sse-eh-uint** | **19.69** | **15.739** | **46.77**
avx2-lemire | 21.544 | / | 48.351
avx2-asm-tetzank | 18.515 | / | 49.323
**sse-bsr-qfilter** | **19.343** | **26.148** | **53.988**
naive-merge | 21.739 | / | 58.09
naive-hybrid | 23.424 | / | 62.148
**naive-bsr-scalar-merge** | **18.496** | **26.508** | **65.746**


### snap_friendster/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **/** | **/** | **/**
sse-han-bmiss-sttni | 20.897 | / | 45.619
avx2-bmerge | 19.522 | / | 47.666
`naive-bitvec-2d` | `21.957` | `/` | `47.758`
avx2-hybrid | 20.743 | / | 47.876
sse-han-qfilter | 21.717 | / | 48.307
`naive-bitvec` | `17.843` | `/` | `49.067`
avx2-lemire | 20.052 | / | 49.399
**sse-eh-hybrid** | **20.213** | **15.787** | **49.417**
**sse-eh-uint** | **20.071** | **14.879** | **50.144**
avx2-asm-tetzank | 19.92 | / | 52.022
**sse-bsr-qfilter** | **20.611** | **24.433** | **59.497**
naive-merge | 19.297 | / | 60.342
naive-hybrid | 22.844 | / | 64.332
**naive-bsr-scalar-merge** | **21.852** | **24.218** | **68.131**


### rmat_v50m_e0.5g/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `4.919` | `/` | `6.367`
`naive-bitvec-2d` | `4.93` | `/` | `6.776`
**sse-eh-hybrid** | **4.884** | **4.522** | **7.398**
**sse-eh-uint** | **5.198** | **4.64** | **7.867**
sse-han-bmiss-sttni | 4.916 | / | 8.596
sse-han-qfilter | 4.932 | / | 8.723
**sse-bsr-qfilter** | **4.921** | **7.566** | **8.791**
avx2-bmerge | 4.935 | / | 8.984
**naive-bsr-scalar-merge** | **4.955** | **6.673** | **9.08**
avx2-lemire | 4.992 | / | 9.223
avx2-hybrid | 5.126 | / | 9.422
naive-merge | 4.885 | / | 9.8
avx2-asm-tetzank | 5.096 | / | 10.423
naive-hybrid | 4.974 | / | 10.687
**avx2-roaring** | **4.997** | **25.577** | **15.141**


### rmat_v50m_e0.5g/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec-2d` | `/` | `/` | `9.23`
avx2-hybrid | / | / | 10.375
**sse-eh-uint** | **/** | **4.684** | **10.514**
**sse-eh-hybrid** | **/** | **5.182** | **10.6**
avx2-bmerge | / | / | 10.817
avx2-lemire | / | / | 10.839
sse-han-bmiss-sttni | / | / | 11.346
sse-han-qfilter | / | / | 11.579
**sse-bsr-qfilter** | **/** | **7.444** | **12.369**
avx2-asm-tetzank | / | / | 12.482
naive-merge | / | / | 13.326
naive-hybrid | / | / | 13.606
**naive-bsr-scalar-merge** | **/** | **7.646** | **13.697**
`naive-bitvec` | `/` | `/` | `14.809`
**avx2-roaring** | **/** | **31.048** | **29.836**


### rmat_v50m_e0.5g/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `4.829` | `/` | `6.657`
`naive-bitvec-2d` | `5.286` | `/` | `7.057`
**sse-eh-hybrid** | **4.877** | **4.644** | **7.873**
**sse-eh-uint** | **4.834** | **4.837** | **8.077**
**sse-bsr-qfilter** | **4.823** | **7.085** | **9.075**
avx2-bmerge | 5.355 | / | 9.119
avx2-hybrid | 4.856 | / | 9.281
**naive-bsr-scalar-merge** | **4.843** | **7.043** | **9.604**
sse-han-bmiss-sttni | 4.835 | / | 9.61
sse-han-qfilter | 4.842 | / | 9.647
avx2-lemire | 4.864 | / | 9.807
naive-hybrid | 5.783 | / | 10.354
avx2-asm-tetzank | 4.833 | / | 10.521
naive-merge | 4.946 | / | 10.865
**avx2-roaring** | **4.892** | **25.125** | **15.296**


### rmat_v50m_e0.5g/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
`naive-bitvec` | `4.821` | `/` | `6.959`
`naive-bitvec-2d` | `6.063` | `/` | `7.428`
**sse-eh-uint** | **4.936** | **4.567** | **8.051**
**sse-eh-hybrid** | **4.911** | **4.54** | **8.334**
**sse-bsr-qfilter** | **4.9** | **6.882** | **9.357**
**naive-bsr-scalar-merge** | **4.779** | **6.834** | **9.447**
avx2-bmerge | 4.916 | / | 9.482
sse-han-bmiss-sttni | 4.991 | / | 9.652
avx2-hybrid | 4.983 | / | 9.743
sse-han-qfilter | 4.879 | / | 9.896
avx2-lemire | 4.941 | / | 10.048
naive-hybrid | 5.063 | / | 10.463
avx2-asm-tetzank | 4.792 | / | 10.928
naive-merge | 4.86 | / | 11.125
**avx2-roaring** | **4.955** | **25.649** | **18.259**


### rmat_v5m_e0.5g/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **3.5** | **5.957** | **21.54**
`naive-bitvec` | `3.611` | `/` | `23.562`
sse-han-bmiss-sttni | 3.546 | / | 23.922
avx2-asm-tetzank | 3.527 | / | 24.063
**sse-eh-hybrid** | **3.494** | **3.416** | **24.223**
avx2-hybrid | 3.532 | / | 24.286
avx2-bmerge | 3.507 | / | 24.41
sse-han-qfilter | 3.517 | / | 24.902
avx2-lemire | 3.552 | / | 25.911
`naive-bitvec-2d` | `3.656` | `/` | `28.343`
**sse-eh-uint** | **3.494** | **3.062** | **28.883**
**sse-bsr-qfilter** | **3.538** | **5.326** | **31.376**
naive-merge | 3.461 | / | 36.627
**naive-bsr-scalar-merge** | **3.525** | **5.368** | **38.489**
naive-hybrid | 4.066 | / | 39.677


### rmat_v5m_e0.5g/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
avx2-bmerge | / | / | 30.762
avx2-hybrid | / | / | 30.853
avx2-asm-tetzank | / | / | 31.034
sse-han-bmiss-sttni | / | / | 31.349
`naive-bitvec` | `/` | `/` | `31.933`
avx2-lemire | / | / | 32.734
sse-han-qfilter | / | / | 34.437
**sse-eh-hybrid** | **/** | **2.973** | **38.166**
`naive-bitvec-2d` | `/` | `/` | `38.942`
**avx2-roaring** | **/** | **7.064** | **39.322**
**sse-eh-uint** | **/** | **2.894** | **40.077**
**sse-bsr-qfilter** | **/** | **5.104** | **46.364**
naive-merge | / | / | 52.111
naive-hybrid | / | / | 55.601
**naive-bsr-scalar-merge** | **/** | **5.039** | **64.583**


### rmat_v5m_e0.5g/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **3.488** | **4.97** | **21.492**
`naive-bitvec` | `3.509` | `/` | `23.738`
sse-han-bmiss-sttni | 3.486 | / | 24.027
avx2-asm-tetzank | 3.475 | / | 24.193
avx2-bmerge | 3.484 | / | 24.378
**sse-eh-hybrid** | **3.514** | **3.202** | **24.448**
avx2-hybrid | 3.515 | / | 24.491
sse-han-qfilter | 3.498 | / | 24.889
avx2-lemire | 3.507 | / | 26.118
`naive-bitvec-2d` | `4.743` | `/` | `28.411`
**sse-eh-uint** | **3.559** | **3.043** | **29.124**
**sse-bsr-qfilter** | **3.492** | **5.427** | **31.866**
naive-merge | 3.485 | / | 36.85
**naive-bsr-scalar-merge** | **3.479** | **5.299** | **39.698**
naive-hybrid | 3.965 | / | 39.836


### rmat_v5m_e0.5g/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **3.497** | **5.814** | **22.446**
**sse-eh-hybrid** | **3.391** | **3.061** | **25.088**
avx2-asm-tetzank | 3.322 | / | 25.873
`naive-bitvec` | `3.322` | `/` | `25.906`
sse-han-bmiss-sttni | 3.385 | / | 25.948
avx2-bmerge | 3.373 | / | 25.958
avx2-hybrid | 3.36 | / | 26.069
sse-han-qfilter | 3.378 | / | 26.903
avx2-lemire | 3.412 | / | 27.259
**sse-eh-uint** | **3.334** | **2.978** | **32.033**
`naive-bitvec-2d` | `3.479` | `/` | `32.274`
**sse-bsr-qfilter** | **3.321** | **5.415** | **34.326**
naive-merge | 3.309 | / | 39.129
naive-hybrid | 3.406 | / | 41.918
**naive-bsr-scalar-merge** | **3.311** | **5.399** | **43.152**


### rmat_v0.5m_e0.5g/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid** | **3.766** | **2.195** | **28.189**
**sse-bsr-qfilter** | **3.733** | **3.548** | **47.874**
**naive-bsr-scalar-merge** | **3.718** | **3.519** | **64.044**
**avx2-roaring** | **3.7** | **1.336** | **65.916**
avx2-asm-tetzank | 3.788 | / | 80.377
`naive-bitvec` | `3.702` | `/` | `90.217`
avx2-bmerge | 3.701 | / | 104.128
avx2-hybrid | 3.728 | / | 104.449
avx2-lemire | 3.743 | / | 123.559
`naive-bitvec-2d` | `3.847` | `/` | `132.273`
**sse-eh-uint** | **3.728** | **2.091** | **132.488**
sse-han-qfilter | 3.779 | / | 136.76
sse-han-bmiss-sttni | 3.711 | / | 143.072
naive-merge | 3.721 | / | 217.415
naive-hybrid | 3.87 | / | 245.179


### rmat_v0.5m_e0.5g/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **/** | **1.115** | **60.83**
**sse-eh-hybrid** | **/** | **2.413** | **72.47**
**sse-bsr-qfilter** | **/** | **3.225** | **108.537**
avx2-asm-tetzank | / | / | 122.385
`naive-bitvec` | `/` | `/` | `125.851`
avx2-bmerge | / | / | 141.227
avx2-hybrid | / | / | 143.687
avx2-lemire | / | / | 163.708
**naive-bsr-scalar-merge** | **/** | **3.187** | **165.799**
`naive-bitvec-2d` | `/` | `/` | `180.665`
**sse-eh-uint** | **/** | **1.779** | **203.048**
sse-han-qfilter | / | / | 207.683
sse-han-bmiss-sttni | / | / | 209.213
naive-merge | / | / | 320.804
naive-hybrid | / | / | 362.877


### rmat_v0.5m_e0.5g/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid** | **3.724** | **2.128** | **28.97**
**sse-bsr-qfilter** | **3.783** | **3.501** | **48.079**
**naive-bsr-scalar-merge** | **3.865** | **3.581** | **64.769**
**avx2-roaring** | **3.807** | **1.076** | **65.45**
avx2-asm-tetzank | 3.742 | / | 80.047
`naive-bitvec` | `3.719` | `/` | `89.194`
avx2-hybrid | 3.935 | / | 103.449
avx2-bmerge | 3.747 | / | 103.735
avx2-lemire | 3.897 | / | 123.024
**sse-eh-uint** | **3.879** | **1.991** | **131.607**
`naive-bitvec-2d` | `4.948` | `/` | `131.96`
sse-han-qfilter | 3.821 | / | 136.178
sse-han-bmiss-sttni | 3.906 | / | 142.529
naive-merge | 3.817 | / | 217.313
naive-hybrid | 4.231 | / | 245.969


### rmat_v0.5m_e0.5g/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid** | **3.471** | **2.141** | **29.422**
**sse-bsr-qfilter** | **3.586** | **3.607** | **53.988**
**avx2-roaring** | **3.715** | **1.006** | **58.821**
**naive-bsr-scalar-merge** | **3.592** | **3.362** | **71.751**
avx2-asm-tetzank | 3.607 | / | 99.158
`naive-bitvec` | `3.392` | `/` | `115.352`
avx2-bmerge | 3.55 | / | 120.537
avx2-hybrid | 3.62 | / | 121.079
avx2-lemire | 3.637 | / | 137.797
**sse-eh-uint** | **3.623** | **1.949** | **159.739**
sse-han-qfilter | 3.507 | / | 166.473
`naive-bitvec-2d` | `4.426` | `/` | `169.806`
sse-han-bmiss-sttni | 3.387 | / | 171.927
naive-merge | 3.545 | / | 249.144
naive-hybrid | 3.646 | / | 280.276


### rmat_v100m_e1g/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec` | `10.205` | `/` | `14.432`
`naive-bitvec-2d` | `14.389` | `/` | `14.605`
**sse-eh-hybrid** | **11.961** | **9.439** | **16.143**
**sse-eh-uint** | **11.367** | **9.562** | **16.437**
**naive-bsr-scalar-merge** | **15.068** | **13.102** | **18.729**
sse-han-bmiss-sttni | 11.54 | / | 18.858
**sse-bsr-qfilter** | **12.747** | **17.014** | **18.959**
avx2-bmerge | 12.582 | / | 19.064
avx2-hybrid | 12.186 | / | 19.313
sse-han-qfilter | 11.938 | / | 19.561
avx2-asm-tetzank | 12.326 | / | 20.193
avx2-lemire | 12.125 | / | 20.226
naive-merge | 12.033 | / | 21.681
naive-hybrid | 14.385 | / | 22.119


### rmat_v100m_e1g/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec-2d` | `/` | `/` | `20.952`
avx2-hybrid | / | / | 21.621
avx2-bmerge | / | / | 22.79
**sse-eh-hybrid** | **/** | **10.108** | **23.09**
sse-han-bmiss-sttni | / | / | 23.243
avx2-lemire | / | / | 23.574
**sse-eh-uint** | **/** | **9.831** | **23.906**
sse-han-qfilter | / | / | 24.219
avx2-asm-tetzank | / | / | 25.902
**sse-bsr-qfilter** | **/** | **14.447** | **26.69**
naive-merge | / | / | 28.217
naive-hybrid | / | / | 28.511
**naive-bsr-scalar-merge** | **/** | **14.239** | **29.757**
`naive-bitvec` | `/` | `/` | `40.564`


### rmat_v100m_e1g/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec` | `10.017` | `/` | `15.26`
`naive-bitvec-2d` | `16.358` | `/` | `16.408`
**sse-eh-hybrid** | **10.518** | **9.147** | **17.306**
**sse-eh-uint** | **10.332** | **9.66** | **17.495**
sse-han-bmiss-sttni | 9.825 | / | 18.927
avx2-bmerge | 9.798 | / | 19.108
avx2-hybrid | 9.789 | / | 19.384
**naive-bsr-scalar-merge** | **10.553** | **14.231** | **19.935**
**sse-bsr-qfilter** | **10.715** | **14.043** | **20.007**
sse-han-qfilter | 10.535 | / | 20.083
avx2-lemire | 9.816 | / | 20.373
avx2-asm-tetzank | 9.853 | / | 21.985
naive-hybrid | 12.96 | / | 22.008
naive-merge | 9.745 | / | 22.369


### rmat_v100m_e1g/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec` | `10.274` | `/` | `17.746`
`naive-bitvec-2d` | `14.851` | `/` | `18.686`
**sse-eh-uint** | **10.509** | **9.034** | **19.011**
**sse-eh-hybrid** | **10.676** | **9.524** | **19.701**
avx2-bmerge | 10.074 | / | 20.534
sse-han-bmiss-sttni | 10.042 | / | 20.679
avx2-hybrid | 10.456 | / | 20.713
avx2-lemire | 10.258 | / | 20.895
sse-han-qfilter | 10.67 | / | 21.367
**sse-bsr-qfilter** | **13.723** | **13.794** | **22.418**
**naive-bsr-scalar-merge** | **11.173** | **14.335** | **23.317**
avx2-asm-tetzank | 10.585 | / | 23.39
naive-merge | 10.477 | / | 23.854
naive-hybrid | 13.137 | / | 24.57


### rmat_v10m_e1g/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
naive-merge | / | / | /
avx2-asm-tetzank | / | / | /
avx2-bmerge | / | / | /
avx2-lemire | / | / | /
avx2-hybrid | / | / | /
sse-han-bmiss-sttni | / | / | /
sse-han-qfilter | / | / | /
**sse-eh-uint** | **/** | **/** | **/**
**sse-eh-hybrid** | **/** | **/** | **/**
**sse-bsr-qfilter** | **/** | **/** | **/**
**naive-bsr-scalar-merge** | **/** | **/** | **/**
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec` | `/` | `/` | `/`
`naive-bitvec-2d` | `/` | `/` | `/`
naive-hybrid | 8.968 | / | 83.586


### rmat_v10m_e1g/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
avx2-hybrid | / | / | 67.755
avx2-bmerge | / | / | 67.898
avx2-asm-tetzank | / | / | 68.402
sse-han-bmiss-sttni | / | / | 68.595
avx2-lemire | / | / | 71.64
sse-han-qfilter | / | / | 75.563
`naive-bitvec` | `/` | `/` | `79.763`
**sse-eh-hybrid** | **/** | **5.677** | **85.72**
**sse-eh-uint** | **/** | **5.517** | **87.532**
`naive-bitvec-2d` | `/` | `/` | `89.33`
**sse-bsr-qfilter** | **/** | **11.018** | **104.68**
**avx2-roaring** | **/** | **19.518** | **105.175**
naive-merge | / | / | 112.712
naive-hybrid | / | / | 119.66
**naive-bsr-scalar-merge** | **/** | **10.438** | **143.836**


### rmat_v10m_e1g/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
sse-han-bmiss-sttni | 6.747 | / | 50.904
`naive-bitvec` | `6.748` | `/` | `51.84`
avx2-asm-tetzank | 6.705 | / | 52.118
avx2-hybrid | 6.784 | / | 52.368
avx2-bmerge | 6.757 | / | 52.565
sse-han-qfilter | 6.749 | / | 53.41
**avx2-roaring** | **6.804** | **13.229** | **53.411**
**sse-eh-hybrid** | **6.722** | **6.162** | **54.547**
avx2-lemire | 6.776 | / | 55.45
`naive-bitvec-2d` | `9.405` | `/` | `61.929`
**sse-eh-uint** | **6.763** | **5.973** | **63.627**
**sse-bsr-qfilter** | **6.763** | **10.665** | **71.264**
naive-merge | 6.74 | / | 77.852
naive-hybrid | 8.217 | / | 83.896
**naive-bsr-scalar-merge** | **6.725** | **10.88** | **88.788**


### rmat_v10m_e1g/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
sse-han-bmiss-sttni | 6.685 | / | 54.433
**avx2-roaring** | **7.097** | **13.536** | **54.79**
avx2-asm-tetzank | 7.094 | / | 55.434
avx2-bmerge | 6.798 | / | 55.513
avx2-hybrid | 6.905 | / | 55.636
`naive-bitvec` | `6.718` | `/` | `56.214`
sse-han-qfilter | 6.695 | / | 56.911
**sse-eh-hybrid** | **6.743** | **6.295** | **57.333**
avx2-lemire | 6.741 | / | 58.186
**sse-eh-uint** | **6.849** | **6.1** | **66.463**
`naive-bitvec-2d` | `9.44` | `/` | `68.737`
**sse-bsr-qfilter** | **7.05** | **11.17** | **76.226**
naive-merge | 6.678 | / | 81.967
naive-hybrid | 8.252 | / | 87.252
**naive-bsr-scalar-merge** | **6.774** | **11.143** | **94.073**


### rmat_v1m_e1g/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
naive-merge | / | / | /
avx2-asm-tetzank | / | / | /
avx2-bmerge | / | / | /
avx2-lemire | / | / | /
naive-hybrid | / | / | /
avx2-hybrid | / | / | /
sse-han-bmiss-sttni | / | / | /
sse-han-qfilter | / | / | /
**sse-eh-uint** | **/** | **/** | **/**
**sse-eh-hybrid** | **/** | **/** | **/**
**sse-bsr-qfilter** | **/** | **/** | **/**
**naive-bsr-scalar-merge** | **/** | **/** | **/**
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec` | `/` | `/` | `/`
`naive-bitvec-2d` | `/` | `/` | `/`


### rmat_v1m_e1g/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
naive-hybrid | / | / | /
**avx2-roaring** | **/** | **2.443** | **160.051**
**sse-eh-hybrid** | **/** | **5.42** | **216.487**
avx2-asm-tetzank | / | / | 294.46
**sse-bsr-qfilter** | **/** | **6.538** | **301.042**
`naive-bitvec` | `/` | `/` | `304.117`
avx2-bmerge | / | / | 330.799
avx2-hybrid | / | / | 332.196
avx2-lemire | / | / | 374.472
`naive-bitvec-2d` | `/` | `/` | `434.603`
sse-han-bmiss-sttni | / | / | 439.891
**naive-bsr-scalar-merge** | **/** | **6.344** | **445.905**
sse-han-qfilter | / | / | 451.803
**sse-eh-uint** | **/** | **3.666** | **465.187**
naive-merge | / | / | 712.401


### rmat_v1m_e1g/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid** | **6.928** | **4.342** | **86.667**
**sse-bsr-qfilter** | **6.956** | **7.127** | **135.606**
**avx2-roaring** | **6.949** | **2.35** | **141.299**
**naive-bsr-scalar-merge** | **6.936** | **6.945** | **183.99**
avx2-asm-tetzank | 7.016 | / | 191.287
`naive-bitvec` | `6.929` | `/` | `213.068`
avx2-bmerge | 7.278 | / | 239.554
avx2-hybrid | 7.352 | / | 239.776
avx2-lemire | 6.984 | / | 278.996
sse-han-qfilter | 7.253 | / | 300.146
**sse-eh-uint** | **6.929** | **3.675** | **304.36**
sse-han-bmiss-sttni | 7.254 | / | 306.945
`naive-bitvec-2d` | `10.116` | `/` | `309.537`
naive-merge | 6.939 | / | 487.577
naive-hybrid | 11.136 | / | 550.427


### rmat_v1m_e1g/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**sse-eh-hybrid** | **6.796** | **4.226** | **92.828**
**avx2-roaring** | **6.798** | **2.25** | **127.159**
**sse-bsr-qfilter** | **6.771** | **6.841** | **149.953**
**naive-bsr-scalar-merge** | **6.82** | **6.94** | **202.992**
avx2-asm-tetzank | 6.818 | / | 239.813
`naive-bitvec` | `6.845` | `/` | `273.891`
avx2-hybrid | 6.813 | / | 281.078
avx2-bmerge | 6.953 | / | 283.264
avx2-lemire | 7.064 | / | 313.49
sse-han-qfilter | 6.852 | / | 361.197
sse-han-bmiss-sttni | 6.865 | / | 366.514
**sse-eh-uint** | **6.882** | **3.835** | **367.263**
`naive-bitvec-2d` | `9.303` | `/` | `392.94`
naive-merge | 6.899 | / | 550.482
naive-hybrid | 8.93 | / | 617.245


### rmat_v200m_e2g/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
naive-merge | / | / | /
avx2-asm-tetzank | / | / | /
avx2-bmerge | / | / | /
avx2-lemire | / | / | /
naive-hybrid | / | / | /
avx2-hybrid | / | / | /
sse-han-bmiss-sttni | / | / | /
sse-han-qfilter | / | / | /
**sse-eh-uint** | **/** | **/** | **/**
**sse-eh-hybrid** | **/** | **/** | **/**
**sse-bsr-qfilter** | **/** | **/** | **/**
**naive-bsr-scalar-merge** | **/** | **/** | **/**
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec` | `/` | `/` | `/`
`naive-bitvec-2d` | `/` | `/` | `/`


### rmat_v200m_e2g/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec-2d` | `/` | `/` | `46.948`
sse-han-bmiss-sttni | / | / | 47.172
avx2-lemire | / | / | 47.518
avx2-hybrid | / | / | 47.66
avx2-bmerge | / | / | 48.003
**sse-eh-hybrid** | **/** | **18.645** | **50.112**
sse-han-qfilter | / | / | 50.92
**sse-eh-uint** | **/** | **19.326** | **51.473**
avx2-asm-tetzank | / | / | 55.065
**sse-bsr-qfilter** | **/** | **29.679** | **58.015**
naive-merge | / | / | 59.575
**naive-bsr-scalar-merge** | **/** | **28.785** | **63.005**
naive-hybrid | / | / | 63.26
`naive-bitvec` | `/` | `/` | `110.876`


### rmat_v200m_e2g/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec` | `21.707` | `/` | `36.095`
**sse-eh-hybrid** | **24.791** | **18.597** | **36.756**
**sse-eh-uint** | **25.318** | **19.35** | **37.366**
`naive-bitvec-2d` | `34.821` | `/` | `37.865`
avx2-bmerge | 26.436 | / | 41.076
avx2-lemire | 24.904 | / | 41.107
sse-han-qfilter | 26.324 | / | 41.769
avx2-hybrid | 24.814 | / | 42.1
sse-han-bmiss-sttni | 23.267 | / | 42.1
**sse-bsr-qfilter** | **23.935** | **35.465** | **43.488**
**naive-bsr-scalar-merge** | **26.754** | **34.968** | **44.291**
avx2-asm-tetzank | 24.212 | / | 46.77
naive-merge | 28.976 | / | 47.125
naive-hybrid | 32.175 | / | 49.765


### rmat_v200m_e2g/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
**avx2-roaring** | **/** | **/** | **/**
**sse-eh-hybrid** | **24.782** | **18.752** | **40.199**
`naive-bitvec` | `22.557` | `/` | `40.62`
**sse-eh-uint** | **25.259** | **18.493** | **40.721**
`naive-bitvec-2d` | `27.554` | `/` | `40.896`
avx2-bmerge | 25.605 | / | 42.398
sse-han-bmiss-sttni | 26.966 | / | 43.095
avx2-hybrid | 25.679 | / | 43.264
sse-han-qfilter | 26.086 | / | 43.499
avx2-lemire | 25.109 | / | 43.566
avx2-asm-tetzank | 25.862 | / | 45.811
**sse-bsr-qfilter** | **24.11** | **35.974** | **48.473**
**naive-bsr-scalar-merge** | **25.433** | **29.743** | **48.537**
naive-merge | 27.014 | / | 49.564
naive-hybrid | 29.393 | / | 51.891


### rmat_v20m_e2g/gro

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
naive-merge | / | / | /
avx2-asm-tetzank | / | / | /
avx2-bmerge | / | / | /
avx2-lemire | / | / | /
naive-hybrid | / | / | /
avx2-hybrid | / | / | /
sse-han-bmiss-sttni | / | / | /
sse-han-qfilter | / | / | /
**sse-eh-uint** | **/** | **/** | **/**
**sse-eh-hybrid** | **/** | **/** | **/**
**sse-bsr-qfilter** | **/** | **/** | **/**
**naive-bsr-scalar-merge** | **/** | **/** | **/**
**avx2-roaring** | **/** | **/** | **/**
`naive-bitvec` | `/` | `/` | `/`
`naive-bitvec-2d` | `/` | `/` | `/`


### rmat_v20m_e2g/org

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
avx2-hybrid | / | / | 150.202
avx2-bmerge | / | / | 150.721
sse-han-bmiss-sttni | / | / | 152.139
avx2-asm-tetzank | / | / | 152.37
avx2-lemire | / | / | 157.691
sse-han-qfilter | / | / | 167.544
**sse-eh-hybrid** | **/** | **13.075** | **191.173**
**sse-eh-uint** | **/** | **12.997** | **192.141**
`naive-bitvec-2d` | `/` | `/` | `207.56`
`naive-bitvec` | `/` | `/` | `212.455`
**sse-bsr-qfilter** | **/** | **24.119** | **236.575**
naive-merge | / | / | 246.836
naive-hybrid | / | / | 260.512
**naive-bsr-scalar-merge** | **/** | **22.533** | **319.984**
**avx2-roaring** | **/** | **104.1** | **408.861**


### rmat_v20m_e2g/deg

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
sse-han-bmiss-sttni | 17.074 | / | 110.049
avx2-asm-tetzank | 16.553 | / | 112.583
avx2-bmerge | 16.595 | / | 113.362
avx2-hybrid | 16.621 | / | 113.39
`naive-bitvec` | `17.147` | `/` | `113.966`
sse-han-qfilter | 17.754 | / | 115.031
avx2-lemire | 16.593 | / | 119.649
**sse-eh-hybrid** | **17.754** | **11.83** | **121.06**
**avx2-roaring** | **14.065** | **37.657** | **131.793**
**sse-eh-uint** | **17.445** | **11.793** | **135.219**
`naive-bitvec-2d` | `20.885` | `/` | `138.331`
**sse-bsr-qfilter** | **18.557** | **21.73** | **160.229**
naive-merge | 16.62 | / | 167.49
naive-hybrid | 20.491 | / | 179.704
**naive-bsr-scalar-merge** | **17.973** | **21.662** | **195.012**


### rmat_v20m_e2g/kcore

file-name | Reorder | LayoutTransform | TriCnt
--- | --- | --- | ---
avx2-hybrid | 17.994 | / | 128.934
sse-han-bmiss-sttni | 18.276 | / | 129.152
avx2-bmerge | 17.893 | / | 129.93
avx2-asm-tetzank | 17.268 | / | 131.063
avx2-lemire | 16.823 | / | 133.541
**sse-eh-hybrid** | **17.858** | **11.877** | **134.31**
sse-han-qfilter | 18.096 | / | 134.812
`naive-bitvec` | `16.107` | `/` | `136.884`
**avx2-roaring** | **15.066** | **38.726** | **140.039**
**sse-eh-uint** | **18.575** | **11.717** | **155.544**
`naive-bitvec-2d` | `19.046` | `/` | `169.265`
naive-merge | 17.004 | / | 187.486
**sse-bsr-qfilter** | **18.156** | **21.675** | **188.195**
naive-hybrid | 19.617 | / | 195.72
**naive-bsr-scalar-merge** | **18.572** | **21.076** | **220.363**