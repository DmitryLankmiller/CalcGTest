cmake_minimum_required(VERSION 3.22)
project(CalcGTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CALCULATOR_SOURCES
        src/calculator/SimpleCalculator.cpp
)

set(HISTORY_SOURCES
        src/history/InMemoryHistory.cpp)

set(SOURCES
        ${CALCULATOR_SOURCES}
        ${HISTORY_SOURCES}
)

add_library(CalcLib STATIC ${SOURCES})

target_include_directories(CalcLib PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

set(TEST_INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/fixtures
        ${PROJECT_SOURCE_DIR}/mocks
        ${PROJECT_SOURCE_DIR}/tests
)

set(TEST_SOURCES
        tests/CalculatorAndHistoryTest.cpp
        tests/InMemoryHistoryTest.cpp
        tests/SimpleCalculatorAddTest.cpp
        tests/SimpleCalculatorDivideTest.cpp
        tests/SimpleCalculatorMultiplyTest.cpp
        tests/SimpleCalculatorSubtractTest.cpp
        fixtures/RandomFixture.cpp
)

add_executable(Calculator_test ${TEST_SOURCES})

target_include_directories(Calculator_test PRIVATE ${TEST_INCLUDE_DIRS})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(CalcLib PRIVATE --coverage -fprofile-arcs -ftest-coverage)
        target_link_libraries(Calculator_test PRIVATE --coverage)
endif()

target_link_libraries(Calculator_test PRIVATE
        CalcLib
        gtest_main
        gmock_main
)


gtest_discover_tests(Calculator_test)
