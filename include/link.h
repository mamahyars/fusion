#ifndef LINK_H
#define LINK_H

int link_init();

int send_lan(
    unsigned char *buffer,
    int length
);

int send_wifi(
    unsigned char *buffer,
    int length
);

#endif