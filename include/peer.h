#ifndef PEER_H
#define PEER_H

void set_peer(char *ip, int port);
void send_to_peer(unsigned char *buffer, int length);

#endif