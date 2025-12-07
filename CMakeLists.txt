cmake_minimum_required(VERSION 3.16)
project(assignment_min_cost LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(hungarian STATIC hungarian.cpp)
target_include_directories(hungarian PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_small test_small.cpp)
target_link_libraries(test_small PRIVATE hungarian)

add_executable(hungarian_cli main_bench_stdin.cpp)
target_link_libraries(hungarian_cli PRIVATE hungarian)

set_target_properties(hungarian_cli PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
foreach(cfg IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
  string(TOUPPER ${cfg} CFG)
  set_target_properties(hungarian_cli PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_${CFG} "${CMAKE_BINARY_DIR}/${cfg}"
  )
endforeach()
