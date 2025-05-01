cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(FileCalc VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include header files
include_directories(include)

# Collect all source files from src/
file(GLOB SOURCES "src/*.c")

# Add the executable
add_executable(filecalc ${SOURCES})
