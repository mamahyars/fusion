#ifndef CACHE_H
#define CACHE_H

#define CACHE_SIZE 1024

struct cached_packet
{
    long long send_time;
    int retry_count;
    unsigned int packet_id;
    unsigned char data[3000];
    int length;
    int used;
};

void cache_init();
void cache_check_timeouts();
void cache_resend();

void cache_store(
    unsigned int packet_id,
    unsigned char *data,
    int length
);

struct cached_packet *cache_find(
    unsigned int packet_id
);

void cache_remove(
    unsigned int packet_id
);

#endif