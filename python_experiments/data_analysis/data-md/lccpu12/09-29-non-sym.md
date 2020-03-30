# O(E) intersection count time


Unit: seconds


### webgraph_webbase

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
avx2-galloping-single | 7.754 | 8.59 | 0.836
**avx2-hybrid** | **5.729** | **6.586** | **0.857**
avx2-galloping-single-non-sym-assign | 13.081 | 13.953 | 0.872
avx2-hybrid-non-sym-assign | 10.663 | 11.55 | 0.887


### webgraph_webbase/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
naive-bitvec-2d | 9.670 | 11.592 | 1.922
**naive-bitvec** | **5.440** | **6.81** | **1.37**
naive-bitvec-2d-non-sym-assign | 158.999 | 160.371 | 1.372
naive-bitvec-non-sym-assign | 213.904 | 215.342 | 1.438


### webgraph_it

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
avx2-galloping-single | 20.410 | 21.057 | 0.647
**avx2-hybrid** | **13.289** | **13.945** | **0.656**
avx2-galloping-single-non-sym-assign | 44.341 | 45.059 | 0.718
avx2-hybrid-non-sym-assign | 28.448 | 29.192 | 0.744


### webgraph_it/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
naive-bitvec-2d | 18.537 | 19.903 | 1.366
**naive-bitvec** | **13.934** | **15.518** | **1.584**
naive-bitvec-2d-non-sym-assign | 2263.084 | 2264.33 | 1.246
naive-bitvec-non-sym-assign | 2307.952 | 2309.397 | 1.445


### webgraph_twitter

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
avx2-galloping-single | 191.299 | 193.077 | 1.778
**avx2-hybrid** | **142.323** | **144.481** | **2.158**
avx2-galloping-single-non-sym-assign | 425.223 | 427.277 | 2.054
avx2-hybrid-non-sym-assign | 296.707 | 298.372 | 1.665


### webgraph_twitter/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
naive-bitvec-2d | 86.919 | 89.239 | 2.32
**naive-bitvec** | **81.623** | **83.907** | **2.284**
naive-bitvec-2d-non-sym-assign | 4132.666 | 4135.089 | 2.423
naive-bitvec-non-sym-assign | 5512.336 | 5514.237 | 1.901


### snap_friendster

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
avx2-galloping-single | 177.837 | 186.545 | 8.708
**avx2-hybrid** | **120.813** | **131.512** | **10.699**
avx2-galloping-single-non-sym-assign | 342.786 | 353.159 | 10.373
avx2-hybrid-non-sym-assign | 252.604 | 261.547 | 8.943


### snap_friendster/rev_deg

file-name | Elapsed Time | Core-Checking | Sim-Cal
--- | --- | --- | ---
naive-bitvec-2d | 138.408 | 148.907 | 10.499
**naive-bitvec** | **170.800** | **180.079** | **9.279**
naive-bitvec-2d-non-sym-assign | 346.212 | 356.091 | 9.879
naive-bitvec-non-sym-assign | 569.859 | 579.479 | 9.62