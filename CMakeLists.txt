cmake_minimum_required(VERSION 3.28)
project("Deepcore DPS" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(
    Deepcore
    src/main.cpp
    src/weapons/deepcore_gk2.cpp
    src/weapons/weapon.cpp
)
install(TARGETS Deepcore)
