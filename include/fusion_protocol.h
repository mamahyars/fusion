#ifndef FUSION_PROTOCOL_H
#define FUSION_PROTOCOL_H
#define FUSION_VERSION 1
#define FUSION_MAGIC 0x46555349
#define FUSION_TYPE_ACK 2

#define FUSION_MAX_PAYLOAD 1300
#define FUSION_TYPE_DATA 1

void send_ack(unsigned int packet_id);
struct fusion_header
{
    unsigned int magic;
    unsigned char version;
    unsigned char type;
    unsigned int packet_id;
    unsigned short fragment_id;
    unsigned short fragment_index;
    unsigned short fragment_count;
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
    unsigned int packet_id
);
int is_ack_packet(
    unsigned char *packet
);

#endif