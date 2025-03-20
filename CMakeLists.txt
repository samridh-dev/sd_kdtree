cmake_minimum_required(VERSION 3.16 FATAL_ERROR)  

project(kdtree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(BUILD_TESTS "Build unit tests" ON)

add_library(kdtree INTERFACE)
target_include_directories(kdtree INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:inc>
)

target_compile_features(kdtree INTERFACE cxx_std_20)

if(BUILD_TESTS)
        enable_testing()
        add_subdirectory(tests)
else()
        add_subdirectory(src)
endif()

