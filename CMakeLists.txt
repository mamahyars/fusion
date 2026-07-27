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
    src/router.c
    src/forward.c
    src/socket.c
    src/peer.c
    src/receiver.c
    src/fusion_protocol.c
    src/reorder.c
    src/ack.c
    src/cache.c
    src/scheduler.c
)