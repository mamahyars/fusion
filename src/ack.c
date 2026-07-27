#include <stdio.h>

#include "../include/ack.h"
#include "../include/fusion_protocol.h"
#include "../include/peer.h"

void send_ack(unsigned int packet_id)
{
    unsigned char buffer[sizeof(struct fusion_header)];

    create_ack(
        buffer,
        packet_id
    );

    send_to_peer(
        buffer,
        sizeof(struct fusion_header)
    );

    printf("ACK #%u sent\n", packet_id);
}