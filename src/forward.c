#include <stdio.h>
#include "../include/forward.h"
#include "../include/peer.h"

void forward_packet(unsigned char *buffer, int length)
{
    int version = (buffer[0] >> 4);

    if(version != 4)
    {
        printf("Skipping non IPv4 packet\n");
        return;
    }


    printf("Forwarding IPv4 packet: %d bytes\n", length);

    send_to_peer(buffer, length);

    printf("Sent to peer\n");
}