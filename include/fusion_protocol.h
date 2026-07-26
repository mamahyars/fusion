#ifndef FUSION_PROTOCOL_H
#define FUSION_PROTOCOL_H
#define FUSION_VERSION 1
#define FUSION_MAGIC 0x46555349
#define FUSION_TYPE_ACK 2


#define FUSION_TYPE_DATA 1

struct fusion_header
{
    unsigned int magic;
    unsigned char version;
    unsigned char type;
    unsigned int packet_id;
};

void add_fusion_header(
    unsigned char *out,
    unsigned char *packet,
    int length
);

int remove_fusion_header(
    unsigned char *packet,
    int length
);
void create_ack(
    unsigned char *buffer,
    unsigned short packet_id
);

#endif