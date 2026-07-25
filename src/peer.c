#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../include/peer.h"

int peer_sock;
struct sockaddr_in peer_addr;


void set_peer(char *ip, int port)
{
    peer_sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(peer_sock < 0)
    {
        perror("socket");
        return;
    }

    memset(&peer_addr, 0, sizeof(peer_addr));

    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(port);

    inet_pton(AF_INET, ip, &peer_addr.sin_addr);

    printf("Peer set: %s:%d\n", ip, port);
}


void send_to_peer(unsigned char *buffer, int length)
{
    sendto(
        peer_sock,
        buffer,
        length,
        0,
        (struct sockaddr*)&peer_addr,
        sizeof(peer_addr)
    );
}