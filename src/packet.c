#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ip.h>

#include "packet.h"

void parse_packet(unsigned char *buffer, int size)
{
    unsigned char version = buffer[0] >> 4;

if (version != 4)
{
    printf("Not IPv4 packet (version %d)\n", version);
    return;
}
    if (size < sizeof(struct iphdr))
    {
        printf("Packet too small\n");
        return;
    }

    struct iphdr *ip = (struct iphdr *)buffer;

    struct in_addr src;
    struct in_addr dst;

    src.s_addr = ip->saddr;
    dst.s_addr = ip->daddr;

    printf("\n--- IPv4 Packet ---\n");

    printf("Length: %d bytes\n", size);

    printf("Source: %s\n",
           inet_ntoa(src));

    printf("Destination: %s\n",
           inet_ntoa(dst));

    printf("TTL: %d\n", ip->ttl);

    switch(ip->protocol)
{
    case 1:
        printf("Protocol: ICMP\n");
        break;

    case 6:
        printf("Protocol: TCP\n");
        break;

    case 17:
        printf("Protocol: UDP\n");
        break;

    default:
        printf("Protocol: %d\n", ip->protocol);
}
}