### Dynamic Graph

struct | size | meaning
--- | --- | ---
aii_s | 2m+1 | doubly linked list
xaii_s | n+1 | modified rowptr of CSR
supports | m |
ids | 2m+1 | map aii[] to edge_t[] space (idx)

### Dynamic Graph Initialization

this stage is filtering valid edges (support > 0)

1. count and assign edge `(u,v)` where `u < v`
2. prefix sum on the `xaii` array
