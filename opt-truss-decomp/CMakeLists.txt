cmake_minimum_required(VERSION 3.6)
project(truss_decomp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)
## To allow CMake to locate our Find*.cmake files
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

## Show Compilation Commands
option(DUMP_COMPILATION_TO_FILE "dump compilation to files" OFF)
if (NOT DUMP_COMPILATION_TO_FILE)
    set(CMAKE_VERBOSE_MAKEFILE ON)
else ()
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # dump compilation commands to compile_commands.json
endif ()

#add_compile_options(-Wall -O3 -g -march=native)
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

find_package(TBB REQUIRED)
include_directories(${TBB_INCLUDE_DIRS})
link_libraries(${TBB_LIBRARIES})

include_directories(${CMAKE_SOURCE_DIR}/../dependencies/sparsepp)
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
add_library(common-utils ${REORDER_UTILS} ${COMMON_UTILS} opt_pkt/extern_variables.cpp)
link_libraries(common-utils)

add_library(graph-pre-processing-legacy util/graph/graph_preprocessing.cpp)
target_compile_definitions(graph-pre-processing-legacy PRIVATE NAVIE_SERIAL_CONSTRUCT=1)

add_library(graph-pre-processing util/graph/graph_preprocessing.cpp)

function(build_truss_algorithm_legacy name macros files)
    add_executable(${name} ${files} related_work/main_legacy.cpp)
    target_compile_definitions(${name} PRIVATE ${macros})
    target_link_libraries(${name} PRIVATE graph-pre-processing-legacy)
endfunction()

function(build_eid_ours name macros files)
    add_executable(${name} ${files} opt_pkt/main.cpp opt_pkt/iter_helper.cpp opt_pkt/pkt_tri_cnt_intermediate.cpp util/graph/graph_preprocessing.cpp)
    target_compile_definitions(${name} PRIVATE ${macros})
endfunction()

function(build_eval_tc name macros files)
    add_executable(${name} ${files} exp_varying_parameters/main_eval_tc.cpp opt_pkt/iter_helper.cpp opt_pkt/pkt_tri_cnt_intermediate.cpp)
    target_compile_definitions(${name} PRIVATE ${macros})
    target_link_libraries(${name} PRIVATE graph-pre-processing)
endfunction()

function(build_truss_algorithm name macros files)
    add_executable(${name} ${files} opt_pkt/main.cpp opt_pkt/iter_helper.cpp opt_pkt/pkt_tri_cnt_intermediate.cpp)
    target_link_libraries(${name} PRIVATE graph-pre-processing)

    target_compile_definitions(${name} PRIVATE ${macros})
    target_compile_definitions(${name} PRIVATE "BMP_PROCESSED=1")
    target_compile_definitions(${name} PRIVATE "BMP_QUEUE=1")
    #    target_compile_definitions(${name} PRIVATE "LOCAL_STAT=1") # switch off when do not collect local stat
    #    target_compile_definitions(${name} PRIVATE "SUP_STAT=1") # switch off when do not collect local stat
endfunction()

function(build_varying_parameters name macros files)
    add_executable(${name} ${files} exp_varying_parameters/main_varying_gt_ept_rs.cpp
            opt_pkt/iter_helper.cpp opt_pkt/pkt_tri_cnt_intermediate.cpp opt_pkt/pkt_merge.cpp)
    target_link_libraries(${name} PRIVATE graph-pre-processing)

    target_compile_definitions(${name} PRIVATE ${macros})
    target_compile_definitions(${name} PRIVATE "BMP_PROCESSED=1")
    target_compile_definitions(${name} PRIVATE "BMP_QUEUE=1")
    target_compile_definitions(${name} PRIVATE "PKT_INTER=1")
    #    target_compile_definitions(${name} PRIVATE "LOCAL_STAT=1") # switch off when do not collect local stat
    #    target_compile_definitions(${name} PRIVATE "SUP_STAT=1") # switch off when do not collect local stat
endfunction()

############### Parallel Experimental Executables #################
build_varying_parameters(pkt-varying "" "")

build_truss_algorithm(pkt-disable-psm "PKT_INTER=1" opt_pkt/pkt_merge.cpp) ### (Starts From Skew-Handling and VecOpt)
target_compile_definitions(pkt-disable-psm PRIVATE "DISABLE_BUCKET_OPT=1;NO_SHRINK_GRAPH=1;NO_TC_OPT=1;PEEL_TRI_BASELINE=1;WITHOUT_FIRST_LAST_LEVEL_OPT=1;DISABLE_PSM=1")

build_truss_algorithm(pkt-vm "PKT_INTER=1" opt_pkt/pkt_merge.cpp) ### (Starts From Skew-Handling and VecOpt)
target_compile_definitions(pkt-vm PRIVATE "DISABLE_BUCKET_OPT=1;NO_SHRINK_GRAPH=1;NO_TC_OPT=1;PEEL_TRI_BASELINE=1;WITHOUT_FIRST_LAST_LEVEL_OPT=1;")

build_truss_algorithm(pkt-gc "PKT_INTER=1" opt_pkt/pkt_merge.cpp)    ### Add Shrink-OPT
target_compile_definitions(pkt-gc PRIVATE "DISABLE_BUCKET_OPT=1;NO_TC_OPT=1;PEEL_TRI_BASELINE=1;WITHOUT_FIRST_LAST_LEVEL_OPT=1")

build_truss_algorithm(pkt-es "PKT_INTER=1" opt_pkt/pkt_merge.cpp)    ### Add Shrink-OPT
target_compile_definitions(pkt-es PRIVATE "DISABLE_BUCKET_OPT=1;NO_TC_OPT=1;PEEL_TRI_BASELINE=1;")

build_truss_algorithm(pkt-dstcp "PKT_INTER=1" opt_pkt/pkt_merge.cpp)    ### Add INCURR-OPT
target_compile_definitions(pkt-dstcp PRIVATE "DISABLE_BUCKET_OPT=1")

build_truss_algorithm(pkt-bmpf "PKT_INTER=1" opt_pkt/pkt_merge.cpp)    ### Add BUCKET_BMP
target_compile_definitions(pkt-bmpf PRIVATE "DISABLE_BUCKET_OPT=1;BUCKET_BMP=1")
#####################################################################

############### Parallel Latest Codes ################################
build_truss_algorithm(pkt-inter-shrink "PKT_INTER=1" opt_pkt/pkt_merge.cpp)
build_truss_algorithm(demo "PKT_INTER=1" opt_pkt/pkt_merge.cpp)
target_compile_definitions(demo PRIVATE "PAPER_FIGURE=1")
#target_compile_definitions(pkt-inter-shrink PRIVATE "SHRINK_EDGE_LIST=1")
#target_compile_definitions(pkt-inter-shrink PRIVATE "COMPACT_CSR=1")

set(PKT_MARK_SHRINK_FILES opt_pkt/pkt_merge.cpp opt_pkt/pkt_hash_map.cpp)
build_truss_algorithm(pkt-mark-shrink PKT_MARK=1 "${PKT_MARK_SHRINK_FILES}")

set(PKT_RADIX_HASH_SHRINK_FILES opt_pkt/pkt_merge.cpp opt_pkt/pkt_radix_map.cpp)
build_truss_algorithm(pkt-radix-shrink PKT_MARK=1 "${PKT_RADIX_HASH_SHRINK_FILES}")

################################################################

################## Experimental of Pre-Processing and Support Initialization ################################
build_truss_algorithm_legacy(pkt-eid "EID_TEST=1" pkt_parallel_org/pkt_parallel.cpp)
build_eid_ours(pkt-eid-parallel "EID_TEST=1" opt_pkt/pkt_merge.cpp)
build_eid_ours(pkt-eid-parallel-seq-scan "EID_TEST=1;SEQ_SCAN=1" opt_pkt/pkt_merge.cpp)
build_eid_ours(pkt-eid-parallel-rev "EID_TEST=1;REVERSE=1" opt_pkt/pkt_merge.cpp)
add_executable(pkt-varying-wpt exp_varying_parameters/main_eval_tc_varing_wpt.cpp)
target_link_libraries(pkt-varying-wpt PRIVATE graph-pre-processing)

build_eval_tc(pkt-eval-tc-baseline "" "")
build_eval_tc(pkt-eval-tc-dtc "DTC=1" "")
build_eval_tc(pkt-eval-tc-wp "WP=1" "")
################################################################

############### Parallel Legacy Codes ################################
build_truss_algorithm_legacy(pkt-legacy "PKT_INTER=1;BASELINE_TC=1" pkt_parallel_org/pkt_parallel.cpp)
build_truss_algorithm_legacy(pkt-inter-legacy PKT_INTER=1 pkt_parallel_org/pkt_parallel.cpp)
set(PKT_INTER_HANDLE_SKEW_TAGS PKT_INTER=1 HANDLE_SKEW=1)
set(PKT_INTER_HANDLE_SKEW_FILES pkt_parallel_org/pkt_parallel.cpp pkt_parallel_org/pkt_parallel_skew_handling.cpp)
set(PKT_INTER_HANDLE_SKEW_VEC_FILES pkt_parallel_org/pkt_parallel.cpp pkt_parallel_org/pkt_parallel_skew_handling_vec.cpp)
build_truss_algorithm_legacy(pkt-inter-handle-skew "${PKT_INTER_HANDLE_SKEW_TAGS}" "${PKT_INTER_HANDLE_SKEW_FILES}")
build_truss_algorithm_legacy(pkt-inter-handle-skew-vec "${PKT_INTER_HANDLE_SKEW_TAGS}" "${PKT_INTER_HANDLE_SKEW_VEC_FILES}")

# to test baseline triangle-counting with skew handling.
if (LEGACY_PKT_ALL)
    build_truss_algorithm_legacy(pkt-inter-handle-skew-vec-baselinetc "${PKT_INTER_HANDLE_SKEW_TAGS}" "${PKT_INTER_HANDLE_SKEW_VEC_FILES}")
    target_compile_definitions(pkt-inter-handle-skew-vec-baselinetc PRIVATE BASELINE_TC=1)
    set(PKT_MARK_FILES pkt_parallel_org/pkt_parallel.cpp pkt_parallel_org/pkt_parallel_marking_improved.cpp)
    set(PKT_MARK_LEGACY_FILES pkt_parallel_org/pkt_parallel.cpp pkt_parallel_org/pkt_parallel_marking.cpp)
    build_truss_algorithm_legacy(pkt-mark-legacy-improved PKT_MARK=1 "${PKT_MARK_FILES}")
    build_truss_algorithm_legacy(pkt-mark-legacy-org PKT_MARK=1 "${PKT_MARK_LEGACY_FILES}")
endif ()
################################################################

############### Serial Codes ################################
if (BUILD_SERIAL)
    build_truss_algorithm_legacy(pkt-inter-serial PKT_SERIAL_INTER=1 pkt_serial/pkt_serial.cpp)
    build_truss_algorithm_legacy(pkt-exp-inter-serial PKT_SERIAL_INTER=1 pkt_serial/pkt_serial_experimental.cpp)
    set(PKT_INTER_EXP_SERIAL_FILES pkt_serial/pkt_serial_experimental.cpp pkt_serial/pkt_serial_marking_improved_experimental.cpp)
    build_truss_algorithm_legacy(pkt-exp-mark-serial PKT_SERIAL_MARK=1 "${PKT_INTER_EXP_SERIAL_FILES}")
    set(PKT_MARK_SERIAL_FILES pkt_serial/pkt_serial.cpp pkt_serial/pkt_serial_marking_improved.cpp)
    build_truss_algorithm_legacy(pkt-mark-serial PKT_SERIAL_MARK=1 "${PKT_MARK_SERIAL_FILES}")

    build_truss_algorithm_legacy(ros ROS=1 related_work/ros_improved.cpp)
    build_truss_algorithm_legacy(wc WC=1 related_work/wc_improved.cpp)
    set(WC_TAGS WC=1 NAIVE_ITER_WITH_PROC=1)
    build_truss_algorithm_legacy(wc-naive "${WC_TAGS}" related_work/wc_improved.cpp)

    set(EAGER_TRUSS_FILES related_work/eager_ktruss.cpp pkt_serial/pkt_serial.cpp)
    build_truss_algorithm_legacy(eager_ktruss "" "${EAGER_TRUSS_FILES}")
endif ()
################################################################

################################### Kcore Codes ################################
add_executable(pkc related_work/pkc.cpp util/log/log.cpp util/graph/graph.cpp)
add_executable(test_pkc_imporved playground/test_pkc.cpp util/log/log.cpp util/graph/graph.cpp
        reordering_utils/pkc_reorder_refactor.cpp)
add_executable(test_pkc_legacy playground/test_pkc.cpp util/log/log.cpp util/graph/graph.cpp
        reordering_utils/pkc_reorder.cpp)
################################################################

find_package(atomic)
add_executable(kron_converter playground/kron_converter.cpp)
if (ATOMIC_FOUND)
    link_libraries(${ATOMIC_LIBRARY})
else ()
    target_compile_definitions(kron_converter PRIVATE NO_ATOMIC=1)
endif ()

######################### Maximum Clique Codes #######################
add_executable(mc_brb clique_utils/main.cpp clique_utils/Graph.cpp)

##### Playground Codes ##############
if (PLAYGROUND)
    add_subdirectory(playground)
endif ()
#############
