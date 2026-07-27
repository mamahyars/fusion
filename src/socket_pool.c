#include "../include/socket_pool.h"
#include "../include/socket.h"

static int lan_socket;
static int wifi_socket;

int sockets_init()
{
    lan_socket = create_socket();
    wifi_socket = create_socket();

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