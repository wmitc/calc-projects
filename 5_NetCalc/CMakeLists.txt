cmake_minimum_required(VERSION 3.16)

set(NAME "netcalc")
project(${NAME} LANGUAGES "C")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include header files
include_directories(include)

# Source files explicitly listed
set(SOURCES
    src/netcalc.c
    src/pollserver.c
    src/process_file.c
    src/evaluate.c
    src/shared_mutex.c
    src/math_utils.c
)

# Add the executable
add_executable(netcalc ${SOURCES})
