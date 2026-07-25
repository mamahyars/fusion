cmake_minimum_required(VERSION 3.16)

project(Fusion C)

set(CMAKE_C_STANDARD 17)

add_executable(fusion
    src/main.c
    src/packet.c
    src/network.c
)