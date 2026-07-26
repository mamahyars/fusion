#include <stdio.h>

#include "../include/ack.h"

void send_ack(unsigned int packet_id)
{
    printf("Sending ACK #%u\n", packet_id);
}