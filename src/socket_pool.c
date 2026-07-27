#include "../include/socket_pool.h"
#include "../include/socket.h"
#include "../include/bind.h"

static int lan_socket;
static int wifi_socket;

int sockets_init()
{
    lan_socket = create_socket();
    wifi_socket = create_socket();
    bind_socket_to_interface(
    lan_socket,
    "enp0s25"
);

bind_socket_to_interface(
    wifi_socket,
    "wlo1"
);

    return 0;
}

int get_lan_socket()
{
    return lan_socket;
}

int get_wifi_socket()
{
    return wifi_socket;
}