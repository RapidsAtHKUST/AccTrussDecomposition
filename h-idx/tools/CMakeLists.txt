find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(bfc BFC.cpp)

add_executable(denest denest/densest.cpp denest/hi_pr.c)
target_compile_definitions(denest PRIVATE -DNDEBUG -DCUT_ONLY -DPRINT_CUT -DNO_MAIN)