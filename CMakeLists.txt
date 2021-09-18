cmake_minimum_required(VERSION 3.18.0)
project(benchmark CXX)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-O3)
if(DEFINED OPTION_MARCH)
    add_compile_options(-march=${OPTION_MARCH})
endif()

add_link_options(-static)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
