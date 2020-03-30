
### cuda-pkt-shrink-all-{GPU}()

Dataset | Prepare CPU time | Scan CPU time | Shrink CPU time | Copy CPU time | Sub process CPU time | Offloading Comp Time | Parallel K-Truss
--- | --- | --- | --- | --- | --- | --- | ---
WE | 1.774 | 3.246 | 3.731 | 0.900 | 13.532 | / | 27.879
WI | 6.104 | 18.027 | 239.851 | 14.115 | 94.559 | / | 389.603
TW | 10.595 | 12.755 | 63.799 | 6.507 | 70.620 | / | 182.074

### cuda-pkt-offload-{GPU}()

Dataset | Prepare CPU time | Scan CPU time | Shrink CPU time | Copy CPU time | Sub process CPU time | Offloading Comp Time | Parallel K-Truss
--- | --- | --- | --- | --- | --- | --- | ---
WE | 1.665 | 27.970 | 1.127 | 0.682 | 11.167 | 43.305 | 46.749
WI | 2.010 | 9.749 | 1.751 | 0.496 | 7.394 | 22.488 | 76.667
TW | 1.542 | 4.527 | 3.116 | 2.034 | 31.185 | 43.699 | 99.286

### cuda-pkt-offload-opt-{GPU}()

Dataset | Prepare CPU time | Scan CPU time | Shrink CPU time | Copy CPU time | Sub process CPU time | Offloading Comp Time | Parallel K-Truss
--- | --- | --- | --- | --- | --- | --- | ---
WE | 1.737 | 4.012 | 1.142 | 0.621 | 13.606 | 21.761 | 25.151
WI | 2.161 | 1.961 | 1.765 | 0.465 | 9.801 | 17.227 | 70.847
TW | 1.558 | 6.234 | 3.073 | 2.133 | 39.802 | 54.208 | 108.334
