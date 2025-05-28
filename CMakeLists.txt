cmake_minimum_required(VERSION 3.14)
project(LowPassFilterProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(gtest_force_shared_crt on)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


# ---- Add source files ----
add_library(LowPassFilter src/LowPassFilter.cpp)
target_include_directories(LowPassFilter PUBLIC src)

# ---- Build main executable ----
add_executable(LowPassFilterApp main.cpp)
target_link_libraries(LowPassFilterApp LowPassFilter)

# Test executable
add_executable(LowPassFilterTests tests/test_LowPassFilter.cpp)
target_link_libraries(LowPassFilterTests LowPassFilter GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(LowPassFilterTests)
