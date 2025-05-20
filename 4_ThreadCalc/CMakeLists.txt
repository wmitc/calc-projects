cmake_minimum_required(VERSION 3.16)
project(ThreadpoolTests C)

# Where executables will go
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add include directories for both your project and test code
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests_include
)

# Create a static library for your threadpool code
add_library(threadpool STATIC
    ${CMAKE_SOURCE_DIR}/src/threadpool.c
    ${CMAKE_SOURCE_DIR}/src/queue.c
)c

# Build the test executable from test sources
add_executable(tests_threads
    ${CMAKE_SOURCE_DIR}/tests_src/thread_tests.c
    ${CMAKE_SOURCE_DIR}/tests_src/thread_tests_main.c
    ${CMAKE_SOURCE_DIR}/tests_src/signal_tests.c
    ${CMAKE_SOURCE_DIR}/src/signals.c
)

# Link the threadpool library and other needed libraries
target_link_libraries(tests_threads
    threadpool
    pthread
    cunit
)

# Optional: Add to CTest for test automation
enable_testing()
add_test(NAME TestThreadLib COMMAND tests_threads)

