cmake_minimum_required(VERSION 2.8)
project(KT)

option(ENABLE_GPERFTOOLS "enable gperftools for AND" OFF)
if (ENABLE_GPERFTOOLS)
    add_definitions(-DGPERFTOOLS)
endif ()

set(CMAKE_CXX_STANDARD 11)
set(GKLIB_PATH "GKlib" CACHE PATH "path to GKlib")
set(SHARED FALSE CACHE BOOL "build a shared library")
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH}) # To allow CMake to locate our Find*.cmake files
include(SetLibraries)
if (MSVC)
    set(KT_INSTALL FALSE)
else ()
    set(KT_INSTALL TRUE)
endif ()

add_compile_definitions(__OPENMP__ USE_LOG)
add_compile_options(-g)
# Add GKlib's cmake settings
include(${GKLIB_PATH}/GKlibSystem.cmake)

# -restrict with Intel compiler
if (${CMAKE_C_COMPILER_ID} STREQUAL "Intel")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -restrict")
endif ()

# Source files
file(GLOB kt_sources src/*.c)

# Include directories
include_directories(${GKLIB_PATH})

# Build
find_package(PCM)
find_package(Gperftools)
if (Gperftools_FOUND)
    message("-- Gperftools lib/include: ${GPERFTOOLS_LIBRARIES} ${GPERFTOOLS_INCLUDE_DIR}")
endif ()

add_executable(ktruss ${GKlib_sources} ${kt_sources}
        src/yche/yche_helpers.cpp src/yche/log.cpp src/main.cpp
        src/kt.cpp src/and.cpp src/multistage-peeling.cpp)
target_link_libraries(ktruss PRIVATE m)

add_executable(ktruss-improved ${GKlib_sources} ${kt_sources}
        src/yche/yche_helpers.cpp src/yche/log.cpp src/main.cpp
        src/kt.cpp src/and-improved.cpp src/multistage-peeling.cpp)
target_link_libraries(ktruss-improved PRIVATE m)
if (ENABLE_GPERFTOOLS)
    target_link_libraries(ktruss-improved PRIVATE ${GPERFTOOLS_LIBRARIES})
endif ()

# Install
if (KT_INSTALL)
    install(TARGETS ktruss
            RUNTIME DESTINATION bin)
endif ()
