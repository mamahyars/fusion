#ifndef SOCKET_H
#define SOCKET_H

int create_socket();
int send_packet(int sock, unsigned char *buffer, int length);

#endif