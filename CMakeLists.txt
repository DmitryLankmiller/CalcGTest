cmake_minimum_required(VERSION 3.22)
project(CalcGTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CalcLib
        ICalculator.h
        SimpleCalculator.h SimpleCalculator.cpp
        IHistory.h
        InMemoryHistory.h InMemoryHistory.cpp
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(
        Calculator_test
        CalculatorTest.cpp
)

target_link_libraries(
        Calculator_test
        CalcLib
        GTest::gtest_main
        # GMock::gmock_main
)

gtest_discover_tests(Calculator_test)
