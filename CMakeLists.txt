cmake_minimum_required(VERSION 3.16)
project(assignment_min_cost LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(hungarian STATIC hungarian.cpp)
target_include_directories(hungarian PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# add_executable(run_assignment run_assignment.cpp)
# target_link_libraries(run_assignment PRIVATE hungarian)

add_executable(test_small test_small.cpp)
target_link_libraries(test_small PRIVATE hungarian)

# add_executable(bench bench.cpp)
# target_link_libraries(bench PRIVATE hungarian)
