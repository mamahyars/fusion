#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../include/cache.h"
#include <string.h>
#include <stdio.h>
#include <time.h>


#include "../include/peer.h"
#include "../include/cache.h"
#include "../include/socket.h"
#include "../include/cache.h"

static struct cached_packet cache[CACHE_SIZE];


long long current_time_ms()
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return ts.tv_sec * 1000LL +
           ts.tv_nsec / 1000000LL;
}
void cache_init()
{
    memset(cache, 0, sizeof(cache));
}

void cache_store(
    unsigned int packet_id,
    unsigned char *data,
    int length
)
{
    for(int i = 0; i < CACHE_SIZE; i++)
    {
        if(!cache[i].used)
        {
            cache[i].used = 1;
            cache[i].packet_id = packet_id;
            cache[i].length = length;
            cache[i].send_time = current_time_ms();
            cache[i].retry_count = 0;

            memcpy(
                cache[i].data,
                data,
                length
            );

            return;
        }
    }
}
void cache_check_timeouts()
{
    long long now = current_time_ms();

    for (int i = 0; i < CACHE_SIZE; i++)
    {
        if (!cache[i].used)
            continue;

        if (now - cache[i].send_time > 1000)
        {
            printf(
                "Packet #%u timeout\n",
                cache[i].packet_id
            );
        }
    }
}

struct cached_packet *cache_find(
    unsigned int packet_id
)
{
    for(int i = 0; i < CACHE_SIZE; i++)
    {
        if(cache[i].used &&
           cache[i].packet_id == packet_id)
        {
            return &cache[i];
        }
    }

    return NULL;
}

void cache_remove(
    unsigned int packet_id
    
    
)

{
    for(int i = 0; i < CACHE_SIZE; i++)
    {
        if(cache[i].used &&
           cache[i].packet_id == packet_id)
        {
            cache[i].used = 0;

printf(
    "Removed packet #%u from cache\n",
    packet_id
);

return;
            
        }
    }
}
void cache_resend()
{
    long long now = current_time_ms();

    for (int i = 0; i < CACHE_SIZE; i++)
    {
        if (!cache[i].used)
            continue;

        if (now - cache[i].send_time > 1000)
        {
            printf(
                "Retransmitting packet #%u\n",
                cache[i].packet_id
            );

            send_to_peer(
                cache[i].data,
                cache[i].length
            );

            cache[i].send_time = now;
            cache[i].retry_count++;
        }
    }
}