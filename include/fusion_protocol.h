#ifndef FUSION_PROTOCOL_H
#define FUSION_PROTOCOL_H

#define FUSION_MAGIC 0x46555349

struct fusion_header
{
    unsigned int magic;
    unsigned char type;
};

void add_fusion_header(
    unsigned char *out,
    unsigned char *packet,
    int length
);

#endif