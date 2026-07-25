#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../include/socket.h"


int create_socket()
{
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

    if (sock < 0)
    {
        perror("socket");
        return -1;
    }

    return sock;
}


int send_packet(int sock, unsigned char *buffer, int length)
{
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = 0;

    int result = sendto(
        sock,
        buffer,
        length,
        0,
        (struct sockaddr *)&addr,
        sizeof(addr)
    );

    if (result < 0)
    {
        perror("sendto");
        return -1;
    }

    printf("Sent packet: %d bytes\n", length);

    return result;
}