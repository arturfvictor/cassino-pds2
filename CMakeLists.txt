cmake_minimum_required(VERSION 3.10)
project(CassinoRoyale)

# Collect all source files from different directories
file(GLOB DAO "dao/*/cpp/*.cpp")
file(GLOB GAME "game/cpp/*.cpp")
file(GLOB MODEL "model/cpp/*.cpp")
file(GLOB MODULE "module/*/cpp/*.cpp")

# Combine all source files into a single list
set(SOURCES
    ${DAO}
    ${GAME}
    ${MODEL}
    ${MODULE}
    main.cpp
)

# Include header files
include_directories(dao/hpp game/hpp model/hpp module/graphic-module/hpp module/random-number-generator/hpp)

# Create an executable
add_executable(cassino_royale ${SOURCES})