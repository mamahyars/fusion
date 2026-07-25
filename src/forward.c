#include <stdio.h>
#include <arpa/inet.h>
#include "../include/forward.h"
#include "../include/socket.h"


void forward_packet(int sock, unsigned char *buffer, int length)
{
    // IPv4 check
    int version = (buffer[0] >> 4);

    if (version != 4)
    {
        printf("Skipping non IPv4 packet\n");
        return;
    }


    printf("Forwarding IPv4 packet: %d bytes\n", length);

    send_packet(sock, buffer, length);
}