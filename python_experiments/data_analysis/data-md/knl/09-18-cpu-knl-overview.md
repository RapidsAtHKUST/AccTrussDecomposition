# Core Checking (eps = 0.2, mu = 5)


Unit: seconds


### snap_pokec

file-name | 256
--- | ---
**baseline-avx512-merge** | **0.215**
naive-galloping-double | 0.217
naive-galloping-single | 0.237
**naive-hybrid** | **0.211**
naive-merge | 0.459
naive-hash | 0.598
naive-hash-spp | 0.615
**naive-bitvec** | **0.368**
**naive-bitvec-hbw** | **0.301**
naive-bitvec-2d | 0.243
naive-bitvec-hbw-2d | 0.296
avx512-galloping-double | 0.216
avx512-galloping-single | 0.197
**avx512-hybrid** | **0.181**
avx512-merge | 0.139


### snap_pokec/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **0.226**
naive-galloping-double | 0.23
naive-galloping-single | 0.281
**naive-hybrid** | **0.238**
naive-merge | 0.672
naive-hash | 0.523
naive-hash-spp | 0.534
**naive-bitvec** | **0.285**
**naive-bitvec-hbw** | **0.311**
naive-bitvec-2d | 0.236
naive-bitvec-hbw-2d | 0.267
avx512-galloping-double | 0.235
avx512-galloping-single | 0.209
**avx512-hybrid** | **0.185**
avx512-merge | 0.143


### snap_livejournal

file-name | 256
--- | ---
**baseline-avx512-merge** | **0.611**
naive-galloping-double | 0.759
naive-galloping-single | 0.668
**naive-hybrid** | **0.696**
naive-merge | 0.912
naive-hash | 2.74
naive-hash-spp | 2.03
**naive-bitvec** | **0.738**
**naive-bitvec-hbw** | **0.609**
naive-bitvec-2d | 0.629
naive-bitvec-hbw-2d | 0.754
avx512-galloping-double | 0.876
avx512-galloping-single | 0.661
**avx512-hybrid** | **0.356**
avx512-merge | 0.342


### snap_livejournal/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **0.6**
naive-galloping-double | 0.731
naive-galloping-single | 0.705
**naive-hybrid** | **0.708**
naive-merge | 1.02
naive-hash | 1.957
naive-hash-spp | 1.639
**naive-bitvec** | **0.815**
**naive-bitvec-hbw** | **0.638**
naive-bitvec-2d | 0.616
naive-bitvec-hbw-2d | 0.701
avx512-galloping-double | 0.851
avx512-galloping-single | 0.665
**avx512-hybrid** | **0.373**
avx512-merge | 0.367


### snap_orkut

file-name | 256
--- | ---
**baseline-avx512-merge** | **3.662**
naive-galloping-double | 5.323
naive-galloping-single | 4.903
**naive-hybrid** | **5.24**
naive-merge | 6.263
naive-hash | 22.889
naive-hash-spp | 15.043
**naive-bitvec** | **7.081**
**naive-bitvec-hbw** | **4.763**
naive-bitvec-2d | 4.413
naive-bitvec-hbw-2d | 4.583
avx512-galloping-double | 5.065
avx512-galloping-single | 4.325
**avx512-hybrid** | **2.052**
avx512-merge | 2.041


### snap_orkut/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **3.755**
naive-galloping-double | 5.694
naive-galloping-single | 5.304
**naive-hybrid** | **5.391**
naive-merge | 6.229
naive-hash | 24.267
naive-hash-spp | 11.422
**naive-bitvec** | **6.71**
**naive-bitvec-hbw** | **4.597**
naive-bitvec-2d | 4.053
naive-bitvec-hbw-2d | 4.153
avx512-galloping-double | 5.668
avx512-galloping-single | 4.654
**avx512-hybrid** | **2.147**
avx512-merge | 2.099


### snap_friendster

file-name | 256
--- | ---
**baseline-avx512-merge** | **69.631**
naive-galloping-double | 114.957
naive-galloping-single | 107.13
**naive-hybrid** | **107.563**
naive-merge | 107.498
naive-hash | 283.486
naive-hash-spp | 382.673
**naive-bitvec** | **719.626**
**naive-bitvec-hbw** | **793.571**
naive-bitvec-2d | 86.927
naive-bitvec-hbw-2d | 94.914
avx512-galloping-double | 108.864
avx512-galloping-single | 90.761
**avx512-hybrid** | **42.085**
avx512-merge | 41.861


### snap_friendster/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **71.906**
naive-galloping-double | 119.758
naive-galloping-single | 112.385
**naive-hybrid** | **107.629**
naive-merge | 107.526
naive-hash | 244.321
naive-hash-spp | 236.952
**naive-bitvec** | **405.446**
**naive-bitvec-hbw** | **423.329**
naive-bitvec-2d | 123.796
naive-bitvec-hbw-2d | 128.904
avx512-galloping-double | 114.783
avx512-galloping-single | 94.605
**avx512-hybrid** | **41.165**
avx512-merge | 40.752


### webgraph_it

file-name | 256
--- | ---
**baseline-avx512-merge** | **607.267**
naive-galloping-double | 19.335
naive-galloping-single | 17.811
**naive-hybrid** | **30.362**
naive-merge | 1553.956
naive-hash | /
naive-hash-spp | /
**naive-bitvec** | **/**
**naive-bitvec-hbw** | **/**
naive-bitvec-2d | /
naive-bitvec-hbw-2d | /
avx512-galloping-double | 38.401
avx512-galloping-single | 26.009
**avx512-hybrid** | **11.852**
avx512-merge | 448.927


### webgraph_it/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **548.905**
naive-galloping-double | 21.643
naive-galloping-single | 20.196
**naive-hybrid** | **25.14**
naive-merge | 716.567
naive-hash | /
naive-hash-spp | 122.331
**naive-bitvec** | **13.64**
**naive-bitvec-hbw** | **13.563**
naive-bitvec-2d | 18.43
naive-bitvec-hbw-2d | 19.53
avx512-galloping-double | 40.055
avx512-galloping-single | 28.0
**avx512-hybrid** | **12.386**
avx512-merge | 280.342


### webgraph_uk

file-name | 256
--- | ---
**baseline-avx512-merge** | **3.412**
naive-galloping-double | 2.195
naive-galloping-single | 2.009
**naive-hybrid** | **4.316**
naive-merge | 9.913
naive-hash | 45.056
naive-hash-spp | 76.811
**naive-bitvec** | **14.773**
**naive-bitvec-hbw** | **14.838**
naive-bitvec-2d | 18.127
naive-bitvec-hbw-2d | 19.333
avx512-galloping-double | 4.069
avx512-galloping-single | 2.803
**avx512-hybrid** | **1.389**
avx512-merge | 2.053


### webgraph_uk/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **2.433**
naive-galloping-double | 2.15
naive-galloping-single | 2.074
**naive-hybrid** | **2.526**
naive-merge | 5.498
naive-hash | 89.409
naive-hash-spp | 6.445
**naive-bitvec** | **1.605**
**naive-bitvec-hbw** | **1.622**
naive-bitvec-2d | 2.018
naive-bitvec-hbw-2d | 2.133
avx512-galloping-double | 3.949
avx512-galloping-single | 2.721
**avx512-hybrid** | **1.276**
avx512-merge | 1.358


### webgraph_eu

file-name | 256
--- | ---
**baseline-avx512-merge** | **94.492**
naive-galloping-double | 189.607
naive-galloping-single | 161.945
**naive-hybrid** | **121.488**
naive-merge | 140.406
naive-hash | 858.048
naive-hash-spp | 686.066
**naive-bitvec** | **127.191**
**naive-bitvec-hbw** | **126.331**
naive-bitvec-2d | 181.021
naive-bitvec-hbw-2d | 195.7
avx512-galloping-double | 466.601
avx512-galloping-single | 290.636
**avx512-hybrid** | **44.712**
avx512-merge | 48.034


### webgraph_eu/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **84.712**
naive-galloping-double | 187.98
naive-galloping-single | 161.129
**naive-hybrid** | **119.219**
naive-merge | 128.062
naive-hash | 1812.794
naive-hash-spp | 530.799
**naive-bitvec** | **100.286**
**naive-bitvec-hbw** | **99.981**
naive-bitvec-2d | 152.071
naive-bitvec-hbw-2d | 165.533
avx512-galloping-double | 467.236
avx512-galloping-single | 290.282
**avx512-hybrid** | **40.738**
avx512-merge | 42.005


### webgraph_twitter

file-name | 256
--- | ---
**baseline-avx512-merge** | **1014.537**
naive-galloping-double | 134.991
naive-galloping-single | 128.08
**naive-hybrid** | **165.361**
naive-merge | 1659.387
naive-hash | /
naive-hash-spp | 1912.838
**naive-bitvec** | **683.756**
**naive-bitvec-hbw** | **406.098**
naive-bitvec-2d | 380.795
naive-bitvec-hbw-2d | 394.219
avx512-galloping-double | 131.488
avx512-galloping-single | 108.729
**avx512-hybrid** | **54.461**
avx512-merge | 597.845


### webgraph_twitter/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **811.017**
naive-galloping-double | 158.059
naive-galloping-single | 150.032
**naive-hybrid** | **169.527**
naive-merge | 1283.188
naive-hash | /
naive-hash-spp | 371.187
**naive-bitvec** | **139.683**
**naive-bitvec-hbw** | **70.513**
naive-bitvec-2d | 90.484
naive-bitvec-hbw-2d | 83.289
avx512-galloping-double | 155.084
avx512-galloping-single | 125.531
**avx512-hybrid** | **65.243**
avx512-merge | 486.037


### webgraph_webbase

file-name | 256
--- | ---
**baseline-avx512-merge** | **37.668**
naive-galloping-double | 6.714
naive-galloping-single | 6.166
**naive-hybrid** | **10.529**
naive-merge | 109.579
naive-hash | 935.264
naive-hash-spp | 876.057
**naive-bitvec** | **173.746**
**naive-bitvec-hbw** | **173.009**
naive-bitvec-2d | 171.934
naive-bitvec-hbw-2d | 173.293
avx512-galloping-double | 12.391
avx512-galloping-single | 8.565
**avx512-hybrid** | **4.12**
avx512-merge | 24.014


### webgraph_webbase/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **24.721**
naive-galloping-double | 6.763
naive-galloping-single | 6.342
**naive-hybrid** | **7.037**
naive-merge | 49.133
naive-hash | /
naive-hash-spp | 31.201
**naive-bitvec** | **5.572**
**naive-bitvec-hbw** | **5.2**
naive-bitvec-2d | 6.861
naive-bitvec-hbw-2d | 7.067
avx512-galloping-double | 12.288
avx512-galloping-single | 8.702
**avx512-hybrid** | **4.246**
avx512-merge | 12.742


### n12dot5_m80_1billion_edge

file-name | 256
--- | ---
**baseline-avx512-merge** | **38.847**
naive-galloping-double | 60.936
naive-galloping-single | 57.858
**naive-hybrid** | **59.323**
naive-merge | 71.707
naive-hash | 260.996
naive-hash-spp | 107.529
**naive-bitvec** | **176.138**
**naive-bitvec-hbw** | **88.056**
naive-bitvec-2d | 62.129
naive-bitvec-hbw-2d | 46.982
avx512-galloping-double | 56.874
avx512-galloping-single | 46.83
**avx512-hybrid** | **22.013**
avx512-merge | 21.703


### n12dot5_m80_1billion_edge/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **38.453**
naive-galloping-double | 60.982
naive-galloping-single | 57.749
**naive-hybrid** | **59.198**
naive-merge | 71.453
naive-hash | 284.591
naive-hash-spp | 107.623
**naive-bitvec** | **175.234**
**naive-bitvec-hbw** | **87.576**
naive-bitvec-2d | 62.035
naive-bitvec-hbw-2d | 46.802
avx512-galloping-double | 56.785
avx512-galloping-single | 46.726
**avx512-hybrid** | **21.859**
avx512-merge | 21.133


### n16dot7_m60_1billion_edge

file-name | 256
--- | ---
**baseline-avx512-merge** | **31.617**
naive-galloping-double | 47.297
naive-galloping-single | 45.044
**naive-hybrid** | **46.203**
naive-merge | 56.563
naive-hash | 265.339
naive-hash-spp | 84.516
**naive-bitvec** | **132.784**
**naive-bitvec-hbw** | **69.928**
naive-bitvec-2d | 40.839
naive-bitvec-hbw-2d | 33.113
avx512-galloping-double | 44.279
avx512-galloping-single | 36.72
**avx512-hybrid** | **18.235**
avx512-merge | 17.809


### n16dot7_m60_1billion_edge/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **31.432**
naive-galloping-double | 47.186
naive-galloping-single | 44.896
**naive-hybrid** | **46.141**
naive-merge | 56.418
naive-hash | 293.456
naive-hash-spp | 84.487
**naive-bitvec** | **132.377**
**naive-bitvec-hbw** | **69.551**
naive-bitvec-2d | 40.951
naive-bitvec-hbw-2d | 32.998
avx512-galloping-double | 44.338
avx512-galloping-single | 36.769
**avx512-hybrid** | **18.28**
avx512-merge | 17.655


### n25_m40_1billion_edge

file-name | 256
--- | ---
**baseline-avx512-merge** | **24.693**
naive-galloping-double | 33.438
naive-galloping-single | 31.974
**naive-hybrid** | **32.741**
naive-merge | 41.053
naive-hash | 315.506
naive-hash-spp | 61.368
**naive-bitvec** | **90.867**
**naive-bitvec-hbw** | **50.44**
naive-bitvec-2d | 24.828
naive-bitvec-hbw-2d | 21.781
avx512-galloping-double | 31.505
avx512-galloping-single | 26.536
**avx512-hybrid** | **14.806**
avx512-merge | 14.327


### n25_m40_1billion_edge/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **24.625**
naive-galloping-double | 33.279
naive-galloping-single | 31.997
**naive-hybrid** | **32.817**
naive-merge | 41.024
naive-hash | 355.37
naive-hash-spp | 61.232
**naive-bitvec** | **90.727**
**naive-bitvec-hbw** | **50.361**
naive-bitvec-2d | 24.83
naive-bitvec-hbw-2d | 21.633
avx512-galloping-double | 31.672
avx512-galloping-single | 26.493
**avx512-hybrid** | **14.736**
avx512-merge | 14.39


### n50_m20_1billion_edge

file-name | 256
--- | ---
**baseline-avx512-merge** | **17.957**
naive-galloping-double | 19.355
naive-galloping-single | 19.108
**naive-hybrid** | **19.563**
naive-merge | 24.856
naive-hash | 466.929
naive-hash-spp | 38.013
**naive-bitvec** | **50.773**
**naive-bitvec-hbw** | **29.898**
naive-bitvec-2d | 14.739
naive-bitvec-hbw-2d | 13.322
avx512-galloping-double | 18.735
avx512-galloping-single | 16.461
**avx512-hybrid** | **11.149**
avx512-merge | 11.072


### n50_m20_1billion_edge/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **17.898**
naive-galloping-double | 19.244
naive-galloping-single | 19.178
**naive-hybrid** | **19.643**
naive-merge | 24.663
naive-hash | 460.84
naive-hash-spp | 37.783
**naive-bitvec** | **50.213**
**naive-bitvec-hbw** | **29.593**
naive-bitvec-2d | 14.766
naive-bitvec-hbw-2d | 13.363
avx512-galloping-double | 18.757
avx512-galloping-single | 16.558
**avx512-hybrid** | **11.301**
avx512-merge | 11.137


### lfr_graphs/n2400000_k100_C0dot3_Bin

file-name | 256
--- | ---
**baseline-avx512-merge** | **2.671**
naive-galloping-double | 3.78
naive-galloping-single | 3.383
**naive-hybrid** | **3.442**
naive-merge | 3.368
naive-hash | 16.437
naive-hash-spp | 18.132
**naive-bitvec** | **8.149**
**naive-bitvec-hbw** | **5.973**
naive-bitvec-2d | 4.796
naive-bitvec-hbw-2d | 4.874
avx512-galloping-double | 5.558
avx512-galloping-single | 4.111
**avx512-hybrid** | **1.714**
avx512-merge | 1.781


### lfr_graphs/n2400000_k100_C0dot3_Bin/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **/**
naive-galloping-double | 7.557
naive-galloping-single | 0.002
**naive-hybrid** | **0.002**
naive-merge | 0.002
naive-hash | 0.002
naive-hash-spp | /
**naive-bitvec** | **0.002**
**naive-bitvec-hbw** | **0.014**
naive-bitvec-2d | 8.906
naive-bitvec-hbw-2d | 0.002
avx512-galloping-double | 0.001
avx512-galloping-single | /
**avx512-hybrid** | **5.595**
avx512-merge | 0.002


### lfr_graphs/n3000000_k80_C0dot3_Bin

file-name | 256
--- | ---
**baseline-avx512-merge** | **2.48**
naive-galloping-double | 3.277
naive-galloping-single | 3.069
**naive-hybrid** | **3.257**
naive-merge | 3.195
naive-hash | 15.749
naive-hash-spp | 17.525
**naive-bitvec** | **8.294**
**naive-bitvec-hbw** | **5.913**
naive-bitvec-2d | 4.468
naive-bitvec-hbw-2d | 4.607
avx512-galloping-double | 4.991
avx512-galloping-single | 3.461
**avx512-hybrid** | **1.707**
avx512-merge | 1.592


### lfr_graphs/n3000000_k80_C0dot3_Bin/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **0.002**
naive-galloping-double | 0.001
naive-galloping-single | 0.001
**naive-hybrid** | **0.002**
naive-merge | 4.676
naive-hash | /
naive-hash-spp | 0.002
**naive-bitvec** | **0.002**
**naive-bitvec-hbw** | **0.002**
naive-bitvec-2d | 0.002
naive-bitvec-hbw-2d | 0.002
avx512-galloping-double | 0.002
avx512-galloping-single | /
**avx512-hybrid** | **0.001**
avx512-merge | 0.001


### lfr_graphs/n4000000_k60_C0dot1_Bin

file-name | 256
--- | ---
**baseline-avx512-merge** | **2.31**
naive-galloping-double | 2.838
naive-galloping-single | 2.669
**naive-hybrid** | **3.042**
naive-merge | 2.89
naive-hash | 15.092
naive-hash-spp | 16.46
**naive-bitvec** | **8.408**
**naive-bitvec-hbw** | **5.918**
naive-bitvec-2d | 4.117
naive-bitvec-hbw-2d | 4.18
avx512-galloping-double | 4.144
avx512-galloping-single | 2.976
**avx512-hybrid** | **1.7**
avx512-merge | 1.55


### lfr_graphs/n4000000_k60_C0dot1_Bin/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **/**
naive-galloping-double | 0.002
naive-galloping-single | 0.002
**naive-hybrid** | **3.325**
naive-merge | 0.002
naive-hash | 0.002
naive-hash-spp | 2.879
**naive-bitvec** | **/**
**naive-bitvec-hbw** | **0.002**
naive-bitvec-2d | 0.002
naive-bitvec-hbw-2d | 0.002
avx512-galloping-double | 0.002
avx512-galloping-single | 0.002
**avx512-hybrid** | **0.001**
avx512-merge | 0.001


### lfr_graphs/n4000000_k60_C0dot3_Bin

file-name | 256
--- | ---
**baseline-avx512-merge** | **2.323**
naive-galloping-double | 2.823
naive-galloping-single | 2.617
**naive-hybrid** | **2.97**
naive-merge | 2.987
naive-hash | 14.954
naive-hash-spp | 16.565
**naive-bitvec** | **8.526**
**naive-bitvec-hbw** | **5.983**
naive-bitvec-2d | 4.235
naive-bitvec-hbw-2d | 4.304
avx512-galloping-double | 4.077
avx512-galloping-single | 3.011
**avx512-hybrid** | **1.59**
avx512-merge | 1.504


### lfr_graphs/n4000000_k60_C0dot3_Bin/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **0.002**
naive-galloping-double | 0.002
naive-galloping-single | 3.196
**naive-hybrid** | **0.002**
naive-merge | 0.002
naive-hash | 0.002
naive-hash-spp | 0.002
**naive-bitvec** | **0.002**
**naive-bitvec-hbw** | **0.002**
naive-bitvec-2d | 0.002
naive-bitvec-hbw-2d | 0.017
avx512-galloping-double | 0.002
avx512-galloping-single | /
**avx512-hybrid** | **5.138**
avx512-merge | 0.002


### lfr_graphs/n6000000_k40_C0dot3_Bin

file-name | 256
--- | ---
**baseline-avx512-merge** | **2.195**
naive-galloping-double | 2.375
naive-galloping-single | 2.252
**naive-hybrid** | **2.725**
naive-merge | 2.661
naive-hash | 13.972
naive-hash-spp | 15.6
**naive-bitvec** | **8.429**
**naive-bitvec-hbw** | **5.997**
naive-bitvec-2d | 3.822
naive-bitvec-hbw-2d | 3.922
avx512-galloping-double | 3.224
avx512-galloping-single | 2.517
**avx512-hybrid** | **1.469**
avx512-merge | 1.549


### lfr_graphs/n6000000_k40_C0dot3_Bin/rev_deg

file-name | 256
--- | ---
**baseline-avx512-merge** | **0.001**
naive-galloping-double | 0.002
naive-galloping-single | 0.001
**naive-hybrid** | **/**
naive-merge | 0.002
naive-hash | 0.002
naive-hash-spp | 0.002
**naive-bitvec** | **/**
**naive-bitvec-hbw** | **0.002**
naive-bitvec-2d | /
naive-bitvec-hbw-2d | 0.002
avx512-galloping-double | /
avx512-galloping-single | 0.002
**avx512-hybrid** | **0.002**
avx512-merge | 0.002