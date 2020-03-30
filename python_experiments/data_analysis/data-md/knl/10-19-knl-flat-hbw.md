# O(E) intersection count Elapsed time


Unit: seconds


### snap_livejournal

file-name | 64 | 128 | 256
--- | --- | --- | ---
avx512-hybrid | 0.558 | 0.355 | 0.261


### snap_livejournal/rev_deg

file-name | 64 | 128 | 256
--- | --- | --- | ---
naive-bitvec | 0.680 | 0.564 | 0.681
naive-bitvec-2d | 0.779 | 0.552 | 0.503
naive-bitvec-hbw | 0.698 | 0.553 | 0.532
naive-bitvec-hbw-2d | 0.813 | 0.584 | 0.525


### snap_orkut

file-name | 64 | 128 | 256
--- | --- | --- | ---
avx512-hybrid | 3.597 | 2.275 | 1.756


### snap_orkut/rev_deg

file-name | 64 | 128 | 256
--- | --- | --- | ---
naive-bitvec | 4.139 | 4.068 | 6.420
naive-bitvec-2d | 5.114 | 3.849 | 3.676
naive-bitvec-hbw | 4.296 | 4.003 | 4.310
naive-bitvec-hbw-2d | 5.334 | 4.056 | 3.837


### webgraph_webbase

file-name | 64 | 128 | 256
--- | --- | --- | ---
avx512-hybrid | 4.732 | 3.440 | 3.166


### webgraph_webbase/rev_deg

file-name | 64 | 128 | 256
--- | --- | --- | ---
naive-bitvec | 5.756 | 4.433 | 4.378
naive-bitvec-2d | 7.945 | 6.086 | 5.707
naive-bitvec-hbw | 5.773 | 4.384 | 4.088
naive-bitvec-hbw-2d | 8.140 | 6.256 | 5.959


### webgraph_it

file-name | 64 | 128 | 256
--- | --- | --- | ---
avx512-hybrid | 14.783 | 11.252 | 10.734


### webgraph_it/rev_deg

file-name | 64 | 128 | 256
--- | --- | --- | ---
naive-bitvec | 14.151 | 12.167 | 12.379
naive-bitvec-2d | 20.299 | 17.290 | 17.093
naive-bitvec-hbw | 14.275 | 12.291 | 12.230
naive-bitvec-hbw-2d | 21.166 | 18.251 | 18.394


### webgraph_twitter

file-name | 64 | 128 | 256
--- | --- | --- | ---
avx512-hybrid | 93.216 | 62.233 | 52.969


### webgraph_twitter/rev_deg

file-name | 64 | 128 | 256
--- | --- | --- | ---
naive-bitvec | 70.949 | 79.852 | 138.268
naive-bitvec-2d | 91.171 | 77.191 | 89.230
naive-bitvec-hbw | 71.223 | 65.992 | 68.965
naive-bitvec-hbw-2d | 93.986 | 81.072 | 82.504


### snap_friendster

file-name | 64 | 128 | 256
--- | --- | --- | ---
avx512-hybrid | 72.273 | 44.656 | 34.050


### snap_friendster/rev_deg

file-name | 64 | 128 | 256
--- | --- | --- | ---
naive-bitvec | 223.773 | 297.375 | 398.961
naive-bitvec-2d | 132.644 | 102.502 | 116.454
naive-bitvec-hbw | 172.265 | 170.718 | 182.933
naive-bitvec-hbw-2d | 140.487 | 103.618 | 92.770