add_executable(balanced_kcore_stat balanced_kcore_stat.cpp ${CMAKE_SOURCE_DIR}/bnd/kcore.cpp
        ${CMAKE_SOURCE_DIR}/bnd/bucket.cpp ${CMAKE_SOURCE_DIR}/bnd/graph.cpp
        ${CMAKE_SOURCE_DIR}/bnd/hierarchy.cpp
        ${CMAKE_SOURCE_DIR}/bnd/util.cpp
        ${CMAKE_SOURCE_DIR}/util/log/log.cpp
        ${CMAKE_SOURCE_DIR}/bnd/tools/bigraph.cpp)

add_executable(dummy ${CMAKE_SOURCE_DIR}/bnd/tools/bigraph_old.cpp)
add_executable(test playground/test_stl.cpp)

