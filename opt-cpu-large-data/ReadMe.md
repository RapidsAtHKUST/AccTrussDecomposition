## Parallel Truss Decomposition

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
[reordering_utils](reordering_utils) | reordering utils
[cmake](cmake) | `findxxx` cmake files