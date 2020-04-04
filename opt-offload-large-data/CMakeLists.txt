cmake_minimum_required(VERSION 3.6)
project(truss-decomposition-offload-large-data)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH}) # To allow CMake to locate our Find*.cmake files
set(CMAKE_VERBOSE_MAKEFILE ON)

add_compile_options(-Wall -O3 -g -march=native)
#add_compile_options(-O3 -g -march=native)
add_definitions(-DUSE_LOG -DTIME_RESULTS)
option(USE_JEMALLOC "use jemalloc" ON)
option(USE_TCMALLOC "use tcmalloc" OFF)
option(BUILD_CPU "build on cpu" OFF)

find_package(OpenMP)
find_package(TBB REQUIRED)
include_directories(${TBB_INCLUDE_DIRS})
link_libraries(${TBB_LIBRARIES})
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

if (USE_TCMALLOC)
    # 1st: tcmalloc
    find_package(Tcmalloc REQUIRED)
    if (Tcmalloc_FOUND)
        message("TCMALLOC FOUND: ${Tcmalloc_LIBRARY}")
        link_libraries(${Tcmalloc_LIBRARY})
    else ()
        message("NO TCMALLOC ")
    endif ()
elseif (USE_JEMALLOC)
    # 2nd: jemalloc
    find_package(Jemalloc REQUIRED)
    if (JEMALLOC_FOUND)
        message("Link: ${JEMALLOC_LIBRARY}")
        link_libraries(${JEMALLOC_LIBRARY})
    endif ()
else ()
    #    link_libraries("/usr/local/lib/libmimalloc.so")
endif ()

set(CUDA_FAKE_JETBRAINS_IDX_FILES util/cuda/cuda_util.h cuda_fake/fake.h cuda_fake/fake_atomic.h cuda_fake/fake_math.h
        util/cuda/primitives.cuh util/cuda/cuda_config.h cuda_extern_functions.cuh main_helper.h
        cuda_tc_pack_vertex_cpu.h primitives.h)
#### CUDA Related Files
find_package("CUDA")
if (USER_CC_CAP)
    message("User CC (CUDA): ${USER_CC_CAP}")
    set(COMPUTE_CAP ${USER_CC_CAP})
else ()
    message("default: use CC (CUDA): 70")
    set(COMPUTE_CAP "70")
endif ()

if (CUDA_FOUND)
    message("--- CUDA Found, Toolkit Path: ${CUDA_TOOLKIT_ROOT_DIR}/")
    include_directories(${CUDA_TOOLKIT_ROOT_DIR}/include) # locate libraries installed with toolkit, e.g, "thrust"
    include_directories(${CMAKE_SOURCE_DIR}/../dependencies/cub)
    include_directories(${CMAKE_SOURCE_DIR}/../dependencies/moderngpu/src)

    # modify options globally
    macro(cuda_add_compile_options options)
        list(APPEND CUDA_NVCC_FLAGS "${options}")
    endmacro()
    cuda_add_compile_options("-gencode arch=compute_${COMPUTE_CAP},code=sm_${COMPUTE_CAP}")
    cuda_add_compile_options("-std=c++11 -O3 -g -lineinfo")
    cuda_add_compile_options("-Xcompiler ${OpenMP_CXX_FLAGS} -Xcompiler -march=native -DBMP_QUEUE=1 -DBMP_PROCESSED=1")
    cuda_add_compile_options("--expt-extended-lambda -use_fast_math") #for ModernGPU
    #    cuda_add_compile_options("-Xcompiler -DPKT_INTER=1 -Xcompiler -DSUP_STAT=1")
    include_directories(${CMAKE_SOURCE_DIR})

    ######## CUDA Helper Related Build. #################
    cuda_add_library(cuda-tc cuda_tc.cu cuda_pack.cu pkt_inter_based_sup_updates.cu util/cuda/cuda_util.cu
            ${CUDA_FAKE_JETBRAINS_IDX_FILES} OPTIONS " -DCUDA_MEM_STAT=1")
    ######## CUDA Helper Related Build. #################

    ######## CPU Related Build. #################
    add_library(pkt-cpu host/iter_helper.cpp host/extern_variables.cpp
            host/pkt_merge.cpp host/pkt_tri_cnt_intermediate.cpp util/search_util.cpp
            util/graph.cpp util/stat.cpp util/log.cpp util/md5.cpp)
    if (SWITCH_EDGE_NUM)
        target_compile_definitions(pkt-cpu PRIVATE SWITCH_EDGE_NUM=${SWITCH_EDGE_NUM})
        message("SWITCH_EDGE_NUM:${SWITCH_EDGE_NUM}")
    else ()
        set(SWITCH_EDGE_NUM 200000000)
    endif ()
    target_compile_definitions(pkt-cpu PRIVATE BMP_PROCESSED=1 BMP_QUEUE=1 SHRINK_EDGE_LIST=1 COMPACT_CSR=1)
    target_link_libraries(pkt-cpu cuda-tc)
    ######## CPU Related Build. #################

    set(CUDA_SOURCE_FILES main.cu pkt_cuda_experimental.cu)
    function(build_cuda_pkt_offload suffix extra_options)
        cuda_add_executable(cuda-pkt${suffix} ${CUDA_SOURCE_FILES} OPTIONS
                "-DPKT_CUDA -DCUDA_MEM_STAT=1 ${extra_options}")
        target_link_libraries(cuda-pkt${suffix} pkt-cpu)
    endfunction()

    ## Build cuda-pkt-offload
    build_cuda_pkt_offload("-offload" "-DLEGACY_SCAN=1")
    build_cuda_pkt_offload("-offload-opt" "")

    get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
    foreach (dir ${dirs})
        message(STATUS "dir='${dir}'")
    endforeach ()
endif ()


