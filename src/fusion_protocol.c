#include <stdio.h>
#include <string.h>

#include "../include/fusion_protocol.h"
static unsigned int next_packet_id = 1;
static unsigned short last_packet_id = 0;

void add_fusion_header(
    unsigned char *out,
    unsigned char *packet,
    int length
)
{
    struct fusion_header header;

    header.magic = FUSION_MAGIC;
    header.version = FUSION_VERSION;
    header.type = FUSION_TYPE_DATA;
    header.packet_id = next_packet_id++;

    memcpy(out, &header, sizeof(header));
    memcpy(out + sizeof(header), packet, length);
}

int remove_fusion_header(
    unsigned char *packet,
    int length
)
{
    struct fusion_header *header =
        (struct fusion_header *)packet;

    if (header->magic != FUSION_MAGIC)
    {
        return -1;
    }

    if (header->version != FUSION_VERSION)
    {
        printf("Unsupported Fusion version\n");
        return -1;
    }

    if (last_packet_id != 0 &&
        header->packet_id != last_packet_id + 1)
    {
        printf(
            "Packet loss detected! Expected %u got %u\n",
            last_packet_id + 1,
            header->packet_id
        );
    }

    last_packet_id = header->packet_id;

    memmove(
        packet,
        packet + sizeof(struct fusion_header),
        length - sizeof(struct fusion_header)
    );

    return length - sizeof(struct fusion_header);
}
void create_ack(
    unsigned char *buffer,
    unsigned short packet_id
)
{
    struct fusion_header *header =
        (struct fusion_header *)buffer;

    header->magic = FUSION_MAGIC;
    header->version = FUSION_VERSION;
    header->type = FUSION_TYPE_ACK;
    header->packet_id = packet_id;
}