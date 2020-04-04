cmake_minimum_required(VERSION 3.6)
project(truss_decomposition_large_data)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)
## To allow CMake to locate our Find*.cmake files
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

## Show Compilation Commands
option(DUMP_COMPILATION_TO_FILE "dump compilation to files" ON)
if (NOT DUMP_COMPILATION_TO_FILE)
    set(CMAKE_VERBOSE_MAKEFILE ON)
else ()
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # dump compilation commands to compile_commands.json
endif ()

add_compile_options(-O3 -g -march=native)
#add_compile_options(-Wall -O0 -g -march=native)
add_definitions(-DUSE_LOG -DTIME_RESULTS)
option(USE_JEMALLOC "use jemalloc" ON)
option(PLAYGROUND "compile playground" ON)
option(USE_TCMALLOC "use tcmalloc" OFF)
option(BUILD_SERIAL "build serial codes" OFF)
option(LEGACY_PKT_ALL "build pkt all legacy codes" OFF)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else ()
    # icpc
    if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Intel")
        message(icpc)
        set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -qopenmp")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -qopenmp")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        message(g++)
        set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
    endif ()
endif ()

include_directories(${CMAKE_SOURCE_DIR}/../dependencies/libpopcnt)
include_directories(${CMAKE_SOURCE_DIR})

if (USE_TCMALLOC)
    # 1st: tcmalloc
    message("USE_TCMALLOC")
    find_package(Tcmalloc REQUIRED)
    if (Tcmalloc_FOUND)
        message("TCMALLOC FOUND: ${Tcmalloc_LIBRARY}")
        link_libraries(${Tcmalloc_LIBRARY})
    else ()
        message("NO TCMALLOC ")
    endif ()
elseif (USE_JEMALLOC)
    # 2nd: jemalloc
    message("USE_JEMALLOC")

    find_package(Jemalloc REQUIRED)
    if (JEMALLOC_FOUND)
        message("Link: ${JEMALLOC_LIBRARY}")
        link_libraries(${JEMALLOC_LIBRARY})
    else ()
        message("NO JEMALLOC ")
    endif ()
else ()
    message("Default Malloc")
    #    link_libraries("/usr/local/lib/libmimalloc.so")
endif ()

set(REORDER_UTILS reordering_utils/reorder_utils.cpp reordering_utils/pkc_reorder.cpp)
set(COMMON_UTILS util/graph/graph.cpp util/log/log.cpp util/md5.cpp util/search/search_util.cpp)
add_library(common-utils ${REORDER_UTILS} ${COMMON_UTILS} opt_pkt/extern_variables.cpp util/graph/graph_preprocessing.cpp)
link_libraries(common-utils)

function(build_truss_algorithm name macros files)
    add_executable(${name} ${files} opt_pkt/main.cpp opt_pkt/iter_helper.cpp opt_pkt/pkt_tri_cnt_intermediate.cpp)

    target_compile_definitions(${name} PRIVATE ${macros})
    target_compile_definitions(${name} PRIVATE "BMP_PROCESSED=1")
    target_compile_definitions(${name} PRIVATE "BMP_QUEUE=1")
endfunction()

############### Parallel Latest Codes ################################
build_truss_algorithm(pkt-inter-shrink "PKT_INTER=1" opt_pkt/pkt_merge.cpp)
################################################################

