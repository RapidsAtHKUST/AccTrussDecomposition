# Parallel Truss Decomposition

## Variables

var | comment
--- | ---
level_start_pos | CSR row-ptr for the `edge_offsets_level`
output (GPU-UM) / edge_offsets_level (host) | edge offsets 
final_result_output | 

## Invocation Codes

```
auto level = TrussDecompositionLevelsCPU(g, EdgeSupport, edgeIdToEdge,
                                        level_start_pos, edge_offsets_level, edge_off_org,
                                         edge_sup, edge_lst);
PKT_cuda(&g, edge_off_org, EdgeSupportCUDA, edge_lst,
         100, output, level_start_pos, &mem_stat, &time_stat, level);
```

## Dependencies

```
include_directories(${CMAKE_SOURCE_DIR}/../dependencies/libpopcnt)
```

## Build

```zsh
cmake ${src-dir-path} -DPLAYGROUND=OFF 
make -j
```

* Some build options are as follows

```
option(USE_JEMALLOC "use jemalloc" ON)
option(PLAYGROUND "compile playground" ON)
option(USE_TCMALLOC "use tcmalloc" OFF)
option(BUILD_CPU "build on cpu" OFF)
```

## File Organizations

Folder | Commment
--- | ---
[reordering_utils](reordering_utils) | reordering utils
[cmake](cmake) | `findxxx` cmake files
[host](opt_pkt) | host cpp codes