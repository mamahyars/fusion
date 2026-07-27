#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <net/if.h>

#include "../include/bind.h"

int bind_socket_to_interface(
    int sock,
    const char *interface_name
)
{
    if (setsockopt(
            sock,
            SOL_SOCKET,
            SO_BINDTODEVICE,
            interface_name,
            strlen(interface_name) + 1) < 0)
    {
        perror("SO_BINDTODEVICE");
        return -1;
    }

    printf(
        "Socket %d bound to %s\n",
        sock,
        interface_name
    );

    return 0;
}