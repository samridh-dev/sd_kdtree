add_library(pch_lib STATIC pch.hpp pch.cpp)
target_precompile_headers(pch_lib PRIVATE pch.hpp)
target_link_libraries(pch_lib PUBLIC kdtree)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "*.cpp")
list(REMOVE_ITEM TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/pch.cpp")

foreach(TEST_SRC ${TEST_SOURCES})

        if(DEFINED TEST_ONLY AND NOT "${TEST_ONLY}" STREQUAL "")
                get_filename_component(TEST_SRC_NAME ${TEST_SRC} NAME_WE)
                get_filename_component(TEST_ONLY_NAME ${TEST_ONLY} NAME_WE)
                if(NOT TEST_SRC_NAME STREQUAL TEST_ONLY_NAME)
                        continue()
                endif()
        endif()

        get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
        set(TEST_NAME "test__${TEST_NAME}")

        add_executable(${TEST_NAME} ${TEST_SRC})

        target_link_libraries(${TEST_NAME} PRIVATE pch_lib kdtree)

        if (CMAKE_CXX_COMPILER MATCHES "icpx$")
                target_compile_options(${TEST_NAME} PRIVATE -fsycl)
                target_link_options(${TEST_NAME}    PRIVATE -fsycl)
        endif()

        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                target_compile_options(${TEST_NAME} PRIVATE -fopenmp)
                target_link_options(${TEST_NAME}    PRIVATE -fopenmp)
        endif()

        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

endforeach()
