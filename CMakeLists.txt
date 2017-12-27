cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# CMake on windows doesnt seem to support setting up for C++17 yet.
if(MSVC)
    add_compile_options("/std:c++latest")
endif()


set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string.hpp)

set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string.cpp)

set(TEST_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test/mdl_test.cpp)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/)

add_library(mdl STATIC ${SOURCE})

add_executable(mdl_test ${TEST_SOURCE})
target_link_libraries(mdl_test mdl)
