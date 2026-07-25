cmake_minimum_required(VERSION 3.16)

project(Fusion C)

set(CMAKE_C_STANDARD 17)

include_directories(include)

add_executable(fusion
    src/main.c
    src/packet.c
    src/network.c
    src/speed.c
    src/interface.c
    src/speed.c
    src/router.c
    src/forward.c
    src/socket.c
)