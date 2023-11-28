cmake_minimum_required(VERSION 3.0)
project(lazy-example)

cmake_policy(SET CMP0135 NEW)
set(CMAKE_CXX_STANDARD 17)



if (LAZY_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    include(GoogleTest)

    macro(add_test name)
        add_executable(${name} ${ARGN})
        target_link_libraries(${ARGV0} GTest::gtest_main)
        target_include_directories(${ARGV0} PUBLIC src)
        gtest_discover_tests(${ARGV0})
    endmacro()

    add_test(test_sort test/test_sort.cc)
    add_test(test_heap test/test_heap.cc)
    add_test(test_unroll test/test_unroll.cc)
endif ()

if (LAZY_BUILD_BENCHMARK)
    include(FetchContent)

    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(BENCHMARK_ENABLE_LTO ON CACHE INTERNAL "")
    endif ()
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE INTERNAL "")
    set(BENCHMARK_ENABLE_TESTING OFF CACHE INTERNAL "")
    set(BENCHMARK_ENABLE_INSTALL OFF CACHE INTERNAL "")

    FetchContent_Declare(
            googlebenchmark
            URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
    )
    FetchContent_MakeAvailable(googlebenchmark)

    macro(add_bench name)
        add_executable(${name} ${ARGN})
        target_link_libraries(${name} PRIVATE benchmark::benchmark)
        target_include_directories(${name} PUBLIC src)
    endmacro()

    add_bench(bench_unroll benchmark/bench_unroll.cc)
endif ()
