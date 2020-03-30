add_compile_options(-Wall -O3 -g -march=native)
#add_executable(test_tbb test_tbb.cpp)
add_executable(test_reorder test_reorder.cpp ../reordering_utils/pkc_reorder.cpp ../reordering_utils/reorder_utils.cpp
        ../util/log/log.cpp ../util/graph/graph.cpp ../util/md5.cpp)

add_executable(test_bit_op test_bit_op ../util/log/log.cpp)

add_executable(test_inheritence test_inheritence.cpp ../util/log/log.cpp)

add_executable(clear_page_cache clear_page_cache.cpp)

find_package(atomic)

if (ATOMIC_FOUND)
    link_libraries(${ATOMIC_LIBRARY})
    add_executable(test_pre_processing test_pre_processing.cpp ../util/log/log.cpp)
endif ()
