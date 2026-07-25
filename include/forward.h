#ifndef FORWARD_H
#define FORWARD_H

void forward_packet(
    int sock,
    unsigned char *buffer,
    int length
);

#endif