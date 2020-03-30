### pkt-inter-legacy-(PKT-I)

Dataset | Tri time | Sync Time | Shrink Time | Scan Time | Proc Time | Total computation cost
--- | --- | --- | --- | --- | --- | ---
WE | 69.093 | 8.093 | 0.0 | 84.191 | 598.467 | 759.844
WI | 7.825 | 1.191 | 0.0 | 74.473 | 2296.787 | 2380.276
TW | 63.186 | 0.355 | 0.0 | 43.873 | 2233.894 | 2341.308

### pkt-inter-handle-skew-(+GA)

Dataset | Tri time | Sync Time | Shrink Time | Scan Time | Proc Time | Total computation cost
--- | --- | --- | --- | --- | --- | ---
WE | 69.017 | 7.691 | 0.0 | 81.932 | 755.676 | 914.316
WI | 7.664 | 1.478 | 0.0 | 80.214 | 119.239 | 208.595
TW | 63.246 | 0.294 | 0.0 | 42.56 | 430.892 | 536.992

### pkt-inter-handle-skew-vec-(+GA/Vec)

Dataset | Tri time | Sync Time | Shrink Time | Scan Time | Proc Time | Total computation cost
--- | --- | --- | --- | --- | --- | ---
WE | 69.12 | 5.709 | 0.0 | 84.263 | 615.186 | 774.278
WI | 7.704 | 1.633 | 0.0 | 78.354 | 113.7 | 201.39100000000002
TW | 63.278 | 0.3 | 0.0 | 41.097 | 348.922 | 453.59700000000004

### pkt-no-shrink-(+GA/Vec)

Dataset | Tri time | Sync Time | Shrink Time | Scan Time | Proc Time | Total computation cost
--- | --- | --- | --- | --- | --- | ---
WE | 3.532 | 5.167 | 0.022 | 78.112 | 658.224 | 745.15
WI | 4.275 | 2.059 | 0.021 | 80.176 | 111.787 | 198.374
TW | 61.779 | 0.366 | 0.075 | 43.628 | 360.09 | 466.115

### pkt-no-tc-(+Shrink)

Dataset | Tri time | Sync Time | Shrink Time | Scan Time | Proc Time | Total computation cost
--- | --- | --- | --- | --- | --- | ---
WE | 3.518 | 4.491 | 1.3 | 83.837 | 638.562 | 731.828
WI | 4.298 | 2.414 | 5.811 | 84.765 | 105.992 | 203.335
TW | 61.786 | 0.274 | 11.88 | 45.167 | 189.553 | 308.831

### pkt-no-incurr-(+TC)

Dataset | Tri time | Sync Time | Shrink Time | Scan Time | Proc Time | Total computation cost
--- | --- | --- | --- | --- | --- | ---
WE | 3.479 | 6.03 | 1.327 | 84.99 | 97.492 | 193.403
WI | 4.305 | 2.261 | 5.761 | 85.204 | 98.478 | 196.063
TW | 61.774 | 0.274 | 11.865 | 46.104 | 194.64 | 314.827

### pkt-no-first-last-cut-(+InCurr)

Dataset | Tri time | Sync Time | Shrink Time | Scan Time | Proc Time | Total computation cost
--- | --- | --- | --- | --- | --- | ---
WE | 3.438 | 5.749 | 1.223 | 79.014 | 75.22 | 164.725
WI | 4.313 | 2.799 | 5.939 | 78.75 | 76.633 | 168.49
TW | 61.665 | 0.326 | 11.951 | 43.517 | 195.153 | 312.782

### pkt-no-bucket-(+FirstLastOpt)

Dataset | Tri time | Sync Time | Shrink Time | Scan Time | Proc Time | Total computation cost
--- | --- | --- | --- | --- | --- | ---
WE | 3.509 | 6.161 | 1.292 | 79.881 | 78.628 | 169.55
WI | 4.357 | 4.954 | 5.758 | 78.878 | 73.417 | 167.417
TW | 61.909 | 12.281 | 12.708 | 59.135 | 1102.071 | 1248.273

### pkt-scan-bmp-(+SCAN-BMP)

Dataset | Tri time | Sync Time | Shrink Time | Scan Time | Proc Time | Total computation cost
--- | --- | --- | --- | --- | --- | ---
WE | 3.475 | 7.501 | 1.187 | 105.053 | 78.896 | 196.194
WI | 4.275 | 0.613 | 5.702 | 11.746 | 72.089 | 94.48
TW | 62.152 | 2.45 | 12.477 | 13.035 | 518.635 | 608.926

### pkt-inter-shrink-(+Bucket)

Dataset | Tri time | Sync Time | Shrink Time | Scan Time | Proc Time | Total computation cost
--- | --- | --- | --- | --- | --- | ---
WE | 3.507 | 2.198 | 1.15 | 10.922 | 71.53 | 89.378
WI | 4.304 | 0.31 | 5.827 | 4.736 | 70.659 | 85.889
TW | 62.377 | 0.306 | 11.352 | 6.621 | 203.809 | 284.632
