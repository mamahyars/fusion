#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../include/receiver.h"


int create_receiver(int port)
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock < 0)
    {
        perror("socket");
        return -1;
    }


    struct sockaddr_in addr;

    memset(&addr,0,sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;


    if(bind(sock,(struct sockaddr*)&addr,sizeof(addr)) < 0)
    {
        perror("bind");
        close(sock);
        return -1;
    }


    printf("Receiver listening on %d\n", port);

    return sock;
}


int receive_from_peer(int sock, unsigned char *buffer)
{
    int size = recv(sock, buffer, 65535, 0);

    if(size > 0)
    {
        printf("Received from peer: %d bytes\n", size);
    }

    return size;
}
int write_to_tun(int tun_fd, unsigned char *buffer, int length)
{
    int written = write(tun_fd, buffer, length);

    if(written < 0)
    {
        perror("tun write");
        return -1;
    }

    printf("Written to TUN: %d bytes\n", written);

    return written;
}