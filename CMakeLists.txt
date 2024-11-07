project(VectorSimGen)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE true)

add_compile_options(
    "-Wall" "-Wextra" "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)
# cmake . -DCMAKE_BUILD_TYPE=Debug

# Add submodules
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/spdlog)
# add_subdirectory(extern/spdlog)
# add_subdirectory(extern/YCSB-C)

# External sources
include_directories(${PROJECT_SOURCE_DIR}/extern/spdlog/include)
include_directories(${PROJECT_SOURCE_DIR}/extern)
# include_directories(${PROJECT_SOURCE_DIR}/extern/SPTAG)
# include_directories(${PROJECT_SOURCE_DIR}/extern/spdlog)

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
    )

# 
# ------- vsg --------
set(VSGLIB vsg)
add_library(${VSGLIB} SHARED ${HDR_FILES} ${SRC_FILES})
set_target_properties(
    ${VSGLIB} 
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib
)
target_include_directories(${VSGLIB} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
# target_link_libraries(${VSGLIB} PUBLIC pthread)

# 
# ------- Binaries --------
set(VSGBIN_QUERY_TEST vsg-query-test)
add_executable(
    ${VSGBIN_QUERY_TEST}
    ${HDR_FILES} ${SRC_FILES}
    ${PROJECT_SOURCE_DIR}/test/query-load-test.cc
)
set_target_properties(
    ${VSGBIN_QUERY_TEST} 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin
)
target_link_libraries(${VSGBIN_QUERY_TEST} PUBLIC ${VSGLIB})

set(VSGBIN_GT_TEST vsg-gt-test)
add_executable(
    ${VSGBIN_GT_TEST}
    ${HDR_FILES} ${SRC_FILES}
    ${PROJECT_SOURCE_DIR}/test/gt-load-test.cc
)
set_target_properties(
    ${VSGBIN_GT_TEST} 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin
)
target_link_libraries(${VSGBIN_GT_TEST} PUBLIC ${VSGLIB})

set(VSGBIN_YCSB_TEST vsg-ycsb-test)
add_executable(
    ${VSGBIN_YCSB_TEST}
    ${HDR_FILES} ${SRC_FILES}
    ${PROJECT_SOURCE_DIR}/test/ycsb-test.cc
)
set_target_properties(
    ${VSGBIN_YCSB_TEST} 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin
)
target_link_libraries(${VSGBIN_YCSB_TEST} PUBLIC ${VSGLIB})
