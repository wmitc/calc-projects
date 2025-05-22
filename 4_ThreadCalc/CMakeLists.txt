cmake_minimum_required(VERSION 3.16)

set(NAME "threadcalc")
project(${NAME} LANGUAGES "C")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include header files
include_directories(include)

find_package(Threads REQUIRED)

# Add static library for threadpool
add_library(threadpool STATIC
    ${CMAKE_SOURCE_DIR}/src/threadpool.c
    ${CMAKE_SOURCE_DIR}/src/queue.c
    ${CMAKE_SOURCE_DIR}/src/signals.c
)

target_link_libraries(threadpool PRIVATE Threads::Threads)

# Collect all source files from src/
file(GLOB SOURCES "src/*.c")

# Add the executable
add_executable(threadcalc ${SOURCES})

target_link_libraries(threadcalc PRIVATE threadpool Threads::Threads)

# CREATE A LIBRARY OF YOUR THREADPOOL.
# CREATE AN EXECUTABLE FOR YOUR THREADPOOL MAIN FUNCTION.
# BUILD THE EXECUTABLE BINARY IN THE 4_ThreadCalc/bin DIRECTORY.

# THIS INCLUDES THE TESTS FOR ThreadCalc. DO NOT MODIFY!
include(tests_src/thread_tests.cmake)
