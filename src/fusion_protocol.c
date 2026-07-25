#include <string.h>

#include "../include/fusion_protocol.h"


void add_fusion_header(
    unsigned char *out,
    unsigned char *packet,
    int length
)
{
    struct fusion_header header;

    header.magic = FUSION_MAGIC;
    header.type = 1;


    memcpy(out, &header, sizeof(header));
    memcpy(out + sizeof(header), packet, length);
}