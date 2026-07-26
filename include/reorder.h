#ifndef REORDER_H
#define REORDER_H

void reorder_init();

int reorder_packet(
    unsigned short packet_id,
    unsigned char *packet,
    int length,
    unsigned char **out_packet,
    int *out_length
);

#endif