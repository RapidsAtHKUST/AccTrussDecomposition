# Parallel Truss Decomposition

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
[host](host) | host cpp codes