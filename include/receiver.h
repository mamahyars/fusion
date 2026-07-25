#ifndef RECEIVER_H
#define RECEIVER_H

int create_receiver(int port);
int receive_from_peer(int sock, unsigned char *buffer);
int write_to_tun(int tun_fd, unsigned char *buffer, int length);

#endif