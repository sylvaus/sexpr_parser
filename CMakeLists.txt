cmake_minimum_required(VERSION 3.10)
project(sexpr_parser)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

include_directories(include)

add_library(common src/common.cpp)

add_library(oop_parser src/oop_parser.cpp)
target_link_libraries(oop_parser common)
add_library(func_parser src/func_parser.cpp)
target_link_libraries(func_parser common)
add_library(mvp_parser src/mvp_parser.cpp)
target_link_libraries(mvp_parser common)

add_executable(sexpr_parser src/cli.cpp)
target_link_libraries(sexpr_parser oop_parser)


if (TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    find_package(Threads REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    file(GLOB TESTS_SRC ${PROJECT_SOURCE_DIR}/tests/*.cpp)
    add_executable(tests ${TESTS_SRC})
    target_link_libraries(tests oop_parser func_parser mvp_parser ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
    add_test(all_tests tests)
endif()