## Parallel Truss Decomposition

### Build

```zsh
cmake ${src-dir-path} -DBUILD_SERIAL=ON -DPLAYGROUND=OFF -DLEGACY_PKT_ALL=ON
```

* Some build options are as follows

```
option(USE_JEMALLOC "use jemalloc" ON)
option(PLAYGROUND "compile playground" ON)
option(USE_TCMALLOC "use tcmalloc" OFF)
option(BUILD_SERIAL "build serial codes" OFF)
option(LEGACY_PKT_ALL "build pkt all legacy codes" OFF)
```

### Files (Important)

Files | Comment
--- | ---
[util](util) | graph, log, stat, intersection, md5, print, timer, util, serialization
[extern_variables.cpp](opt_pkt/extern_variables.cpp) | extern variables
[local_buffer.h](util/primitives/local_buffer.h) | cache-aware local buffer
[iter_helper.h](opt_pkt/iter_helper.h), [iter_helper.cpp](opt_pkt/iter_helper.cpp) | level-iteration logics
[parallel_all_edge_cnc.h](opt_pkt/parallel_all_edge_cnc.h) | triangle-counting utils
[pkt_support_update_utils.h](opt_pkt/pkt_support_update_utils.h) | support-update utils
[radix_hash_map.h](util/containers/radix_hash_map.h) | radix-partitioning-based map
[set_utils.h](util/intersection/set_utils.h) | galloping-based set-intersection

### File Organizations

Folder | Commment
--- | ---
[pkt_parallel_org](pkt_parallel_org) | optimized orginal pkt (parallel ktruss decomposition)
[pkt_serial](pkt_serial) | serial optimized original kt
[related_work](related_work) | 2012-vldb-james-cheng-wc, 2014-pkdd-ros serial codes
[reordering_utils](reordering_utils) | reordering utils
[playground](playground) | test some language features
[cmake](cmake) | `findxxx` cmake files