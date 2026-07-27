#ifndef BIND_H
#define BIND_H

int bind_socket_to_interface(
    int sock,
    const char *interface_name
);

#endif