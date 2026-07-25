#ifndef INTERFACE_H
#define INTERFACE_H

#define MAX_INTERFACES 10

typedef struct
{
    char name[32];
    int active;
    int speed;
} NetworkInterface;


int get_interfaces(NetworkInterface *list, int max);


void print_interfaces(NetworkInterface *list, int count);


#endif