cmake_minimum_required(VERSION 3.10)
project(CassinoRoyaleTests)

# Collect all source files from different directories
file(GLOB MODULE "../module/*/cpp/*.cpp")

# Combine all source files into a single list
set(SOURCES
    ${MODULE}
    tests.cpp
)

# Include header files
include_directories(../module/graphic-module/hpp ../module/input-module/hpp)

# Create an executable
add_executable(cassino_royale_tests ${SOURCES})