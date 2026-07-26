#include "../include/reorder.h"

void reorder_init()
{
}

int reorder_packet(
    unsigned short packet_id,
    unsigned char *packet,
    int length,
    unsigned char **out_packet,
    int *out_length
)
{
    *out_packet = packet;
    *out_length = length;

    return 1;
}