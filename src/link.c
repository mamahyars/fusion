#include "../include/link.h"
#include "../include/peer.h"
#include "../include/socket_pool.h"
#include <stdio.h>

int link_init()
{
    printf("LAN socket : %d\n", get_lan_socket());
printf("WiFi socket: %d\n", get_wifi_socket());
    return 0;
}

int send_lan(
    unsigned char *buffer,
    int length
)
{
    send_to_peer(buffer, length);
    return 0;
}

int send_wifi(
    unsigned char *buffer,
    int length
)
{
    send_to_peer(buffer, length);
    return 0;
}