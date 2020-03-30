cmake_minimum_required(VERSION 3.6)
project(bnd_opt)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH}) # To allow CMake to locate our Find*.cmake files

option(BUILD_BND "build-bnd" ON)
option(BUILD_PND "build-pnd" ON)
option(BUILD_ALL "build-all" ON)
option(BUILD_TOOLS "build-tools" ON)
option(ENABLE_GPERFTOOLS "enable gperftools for AND" OFF)
if (ENABLE_GPERFTOOLS)
    add_definitions(-DGPERFTOOLS)
endif ()
add_definitions(-DUSE_LOG)
add_definitions(-DNDEBUG)
add_compile_options("-g;-O3;-march=native;-Wall;-W;-Wextra")

include_directories(bnd/src)
include_directories(nd/src)
include_directories(pnd/src)

### Libraries ##############
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
find_package(TBB)
if (TBB_FOUND)
    add_compile_options(-DTBB=1)
    message("${TBB_VERSION}, ${TBB_INCLUDE_DIRS}, ${TBB_LIBRARIES}")
    include_directories(${TBB_INCLUDE_DIRS})
    link_libraries(${TBB_LIBRARIES})
else ()
    message("TBB NOT FOUND")
endif ()
find_package(Tcmalloc)
if (Tcmalloc_FOUND)
    message("TCMALLOC FOUND")
    link_libraries(${Tcmalloc_LIBRARY})
else ()
    message("NO TCMALLOC ")
    find_package(Jemalloc)
    if (JEMALLOC_FOUND)
        message("Link: ${JEMALLOC_LIBRARY}")
        link_libraries(${JEMALLOC_LIBRARY})
    else ()
        message("NO JEMALLOC ")
    endif ()
endif ()
find_package(Threads REQUIRED)
######################################
set(CMAKE_VERBOSE_MAKEFILE ON)
include_directories(${CMAKE_SOURCE_DIR})

### Our Graph Utilities ###################
include_directories(${CMAKE_SOURCE_DIR}/util/sparsepp)
add_library(graph-utils
        util/log/log.cpp util/graph/graph.cpp util/graph/graph_bin_input_helper.cpp
        util/md5.cpp util/search/search_util.cpp
        reordering_utils/pkc_reorder_refactor.cpp reordering_utils/reorder_utils.cpp)
link_libraries(graph-utils)
find_package(atomic)
if (ATOMIC_FOUND)
    link_libraries(${ATOMIC_LIBRARY})
else ()
    add_compile_definitions(NO_ATOMIC=1)
endif ()
#####################################################3

if (BUILD_BND)
    add_executable(bnd-tip-wing bnd/main.cpp
            bnd/bucket.cpp bnd/graph.cpp bnd/hierarchy.cpp
            bnd/kcore.cpp bnd/ktruss.cpp bnd/tip.cpp bnd/util.cpp bnd/wing.cpp)
    #target_compile_options(bnd PRIVATE -g -O3 -march=native -Wall -W -Wextra)
endif ()

if (BUILD_ALL)
    add_executable(nd nd/main.cpp
            nd/bucket.cpp nd/graph.cpp nd/hierarchy.cpp nd/util.cpp
            nd/k1-3.cpp nd/k1-4.cpp nd/k2-4.cpp nd/k3-4.cpp nd/kcore.cpp nd/ktruss.cpp)

    include_directories()
    add_executable(stream-kcore
            stream-kcore/bucket.cpp
            stream-kcore/edge_generators.cpp
            stream-kcore/kcore.cpp
            stream-kcore/main-kcore.cpp
            stream-kcore/subcore.cpp
            stream-kcore/traversal.cpp
            stream-kcore/ulib.c
            stream-kcore/xcore_insertion.cpp
            stream-kcore/xcore_removal.cpp
            stream-kcore/xtraversal_insertion.cpp)
    target_link_libraries(stream-kcore ${CMAKE_THREAD_LIBS_INIT})
    target_include_directories(stream-kcore PRIVATE ${CMAKE_SOURCE_DIR}/../dependencies/sparsehash-yche/include)
endif ()

include_directories(util)

if (BUILD_PND)
    find_package(PCM)
    find_package(Gperftools)
    if (Gperftools_FOUND)
        message("-- Gperftools lib/include: ${GPERFTOOLS_LIBRARIES} ${GPERFTOOLS_INCLUDE_DIR}")
    endif ()
    add_executable(pnd pnd/main.cpp
            pnd/bucket.cpp pnd/graph.cpp util/set-inter/lemire/intersection.cpp
            pnd/local12.cpp
            #            pnd/local23.cpp
            pnd/local23_yche.cpp pnd/local23_yche_bak.cpp
            #            pnd/local34.cpp
            )
    if (ENABLE_GPERFTOOLS)
        target_link_libraries(pnd PRIVATE ${GPERFTOOLS_LIBRARIES})
    endif ()

    add_executable(hidx-org pnd/main.cpp pnd/bucket.cpp pnd/graph.cpp
            pnd/local12.cpp pnd/local23.cpp
            #            set-inter/lemire/intersection.cpp
            #            pnd/local23_yche.cpp
            #            pnd/local23_yche_bak.cpp
            #            pnd/local34.cpp
            )

endif ()

if (BUILD_TOOLS)
    add_subdirectory(tools)
    add_subdirectory(bnd/tools)
endif ()

add_subdirectory(playground)
