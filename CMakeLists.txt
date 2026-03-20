cmake_minimum_required(VERSION 3.16)
project(dyNET VERSION 0.1.0 LANGUAGES CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra")

add_library(dynet STATIC
    src/dysyscall.cpp
    src/dysocket.cpp
    src/dyhttp.cpp
    src/dyutils.cpp
    src/dyrouter.cpp
    src/dythread.cpp
)

target_include_directories(dynet PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(examples/hello_server)