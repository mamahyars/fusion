#include <stdio.h>
#include <string.h>

#include "../include/speed.h"


int get_interface_speed(char *name)
{
    char path[128];

    snprintf(path, sizeof(path),
             "/sys/class/net/%s/speed",
             name);


    FILE *file = fopen(path, "r");

    if (!file)
    {
        return 0;
    }


    int speed = 0;

    fscanf(file, "%d", &speed);

    fclose(file);


    return speed;
}