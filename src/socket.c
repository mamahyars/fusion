#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "../include/socket.h"
#include <netinet/ip.h>


int create_socket()
{
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

    if(sock < 0)
    {
        perror("socket");
        return -1;
    }

    int one = 1;

    setsockopt(
        sock,
        IPPROTO_IP,
        IP_HDRINCL,
        &one,
        sizeof(one)
    );

    return sock;
}


int send_packet(int sock, unsigned char *buffer, int length)
{
    struct iphdr *ip = (struct iphdr *)buffer;


    struct sockaddr_in addr;

    memset(&addr,0,sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ip->daddr;


    int result = sendto(
        sock,
        buffer,
        length,
        0,
        (struct sockaddr *)&addr,
        sizeof(addr)
    );


    if(result < 0)
    {
        perror("sendto");
        return -1;
    }


    printf("Sent packet: %d bytes\n", result);

    return result;
}