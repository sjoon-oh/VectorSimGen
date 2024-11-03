project(VectorSimGen)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE true)

add_compile_options(
    "-Wall" "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)
# cmake . -DCMAKE_BUILD_TYPE=Debug

# Add submodules
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/spdlog)
# add_subdirectory(extern/spdlog)
# add_subdirectory(extern/YCSB-C)

# External sources
include_directories(${PROJECT_SOURCE_DIR}/extern/spdlog/include)
# include_directories(${PROJECT_SOURCE_DIR}/extern/SPTAG)
# include_directories(${PROJECT_SOURCE_DIR}/extern/spdlog)
# include_directories(${PROJECT_SOURCE_DIR}/extern/YCSB-C)

# Internal sources
# include_directories(${PROJECT_SOURCE_DIR}/inc)
file(GLOB_RECURSE HDR_FILES 
    CONFIGURE_DEPENDS
    inc/*.h  
    inc/*.hh
    )
file(GLOB_RECURSE SRC_FILES
    CONFIGURE_DEPENDS
    src/*.c
    src/*.cc
    src/test/*.c
    src/test/*.cc
    )

# 
# ------- vsg --------
set(VSGLIB vsg)
file(GLOB VSGLIB_src 
    CONFIGURE_DEPENDS 
    ${PROJECT_SOURCE_DIR}/src/*.cc 
    ${PROJECT_SOURCE_DIR}/src/test/*.cc
    )

add_library(${VSGLIB} SHARED ${HDR_FILES} ${SRC_FILES})
set_target_properties(
    ${VSGLIB} 
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib
)
target_include_directories(${VSGLIB} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
# target_link_libraries(${VSGLIB} PUBLIC pthread)


# 
# ------- Binaries --------
# Multi-threded test binary
set(VSGBIN vsg-testbin)
add_executable(
    ${VSGBIN}
    ${PROJECT_SOURCE_DIR}/src/test/main.cc
    ${HDR_FILES} ${SRC_FILES}
)
set_target_properties(
    ${VSGBIN} 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin
)
target_link_libraries(${VSGBIN} PUBLIC ${VSGLIB})
