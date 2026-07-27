#include <stdio.h>
#include "../include/forward.h"
#include "../include/peer.h"

#include "../include/cache.h"
#include "../include/fusion_protocol.h"
#include "../include/scheduler.h"


void forward_packet(unsigned char *buffer, int length)
{
    int version = (buffer[0] >> 4);

    if(version != 4)
    {
        printf("Skipping non IPv4 packet\n");
        return;
    }


    printf("Forwarding IPv4 packet: %d bytes\n", length);

    unsigned char fusion_buffer[3000];
    if (length > FUSION_MAX_PAYLOAD)
{
    printf("Large packet detected (%d bytes)\n", length);
}

add_fusion_header(
    fusion_buffer,
    buffer,
    length
);
struct fusion_header *hdr =
    (struct fusion_header *)fusion_buffer;

cache_store(
    hdr->packet_id,
    fusion_buffer,
    length + sizeof(struct fusion_header)
);

int link = select_link();

if(link == 0)
{
    printf("Using LAN\n");
}
else
{
    printf("Using Wi-Fi\n");
}

send_to_peer(
    fusion_buffer,
    length + sizeof(struct fusion_header)
);

    printf("Sent to peer\n");
}