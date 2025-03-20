add_library(src_pch_lib STATIC pch.hpp pch.cpp)
target_precompile_headers(src_pch_lib PRIVATE pch.hpp)
target_link_libraries(src_pch_lib PUBLIC kdtree)

file(GLOB BENCHMARK_SOURCES CONFIGURE_DEPENDS "*.cpp")
list(REMOVE_ITEM BENCHMARK_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/pch.cpp")

foreach(BENCH_SRC ${BENCHMARK_SOURCES})
        get_filename_component(BENCH_NAME ${BENCH_SRC} NAME_WE)
        add_executable(${BENCH_NAME} ${BENCH_SRC})
        target_link_libraries(${BENCH_NAME} PRIVATE src_pch_lib kdtree)


        if (CMAKE_CXX_COMPILER MATCHES "icpx$")
                target_compile_options(${BENCH_NAME} PRIVATE -fsycl -g -debug inline-debug-info -fprofile -qopt-report=max -O3 -funroll-loops -xHost)
                target_link_options(${BENCH_NAME}    PRIVATE -fsycl)
        else()
                target_compile_options(${BENCH_NAME} PRIVATE 
                        $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
                        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>
                        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2>
                        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/Od /Zi>
                        $<$<AND:$<NOT:$<CXX_COMPILER_ID:MSVC>>,$<CONFIG:Release>>:-O3>
                        $<$<AND:$<NOT:$<CXX_COMPILER_ID:MSVC>>,$<CONFIG:Debug>>:-O0 -g>
                        $<$<CXX_COMPILER_ID:GNU>: -fno-omit-frame-pointer -g3 -Wall -Wextra -Wpedantic -Werror -Warray-bounds -Wcast-align -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdeprecated -Wduplicated-branches -Wduplicated-cond -Wenum-compare -Wextra-semi -Wformat -Wformat=2 -Wformat-security -Wignored-qualifiers -Wimplicit-fallthrough -Winit-self -Winvalid-pch -Wlogical-op -Wmain -Wmaybe-uninitialized -Wmisleading-indentation -Wmissing-declarations -Wmissing-field-initializers -Wmissing-include-dirs -Wmultichar -Wnarrowing -Wnon-virtual-dtor -Wnull-dereference -Wold-style-cast -Woverloaded-virtual -Woverflow -Wparentheses -Wpointer-arith -Wredundant-decls -Wreorder -Wreturn-type -Wsequence-point -Wshadow -Wsign-compare -Wsign-conversion -Wstrict-aliasing -Wstrict-overflow=1  -Wsuggest-override -Wswitch -Wswitch-default -Wswitch-enum -Wtrampolines -Wtrigraphs -Wundef -Wuninitialized -Wunknown-pragmas -Wunused -Wunused-but-set-variable -Wunused-function -Wunused-label -Wunused-local-typedefs -Wunused-parameter -Wunused-result -Wunused-variable -Wvariadic-macros -Wvla -Wvolatile-register-var -Wwrite-strings >

                )
        endif()

        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                target_compile_options(${BENCH_NAME} PRIVATE -fopenmp)
                target_link_options(${BENCH_NAME}    PRIVATE -fopenmp)
        endif()


endforeach()
