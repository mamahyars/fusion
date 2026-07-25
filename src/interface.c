#include <stdio.h>
#include <string.h>
#include <ifaddrs.h>

#include "../include/interface.h"


int get_interfaces(NetworkInterface *list, int max)
{
    struct ifaddrs *interfaces;
    struct ifaddrs *ifa;

    int count = 0;


    if (getifaddrs(&interfaces) == -1)
    {
        perror("getifaddrs");
        return 0;
    }


    for (ifa = interfaces; ifa != NULL && count < max; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_name)
        {
            int exists = 0;


            for (int i = 0; i < count; i++)
            {
                if (strcmp(list[i].name, ifa->ifa_name) == 0)
                {
                    exists = 1;
                    break;
                }
            }


            if (!exists)
            {
                strncpy(list[count].name,
                        ifa->ifa_name,
                        sizeof(list[count].name)-1);

                list[count].active = 1;
                list[count].speed = 0;

                count++;
            }
        }
    }


    freeifaddrs(interfaces);

    return count;
}



void print_interfaces(NetworkInterface *list, int count)
{
    printf("Detected interfaces:\n");


    for (int i = 0; i < count; i++)
    {
        printf("%s | active: %d | speed: %d Mbps\n",
               list[i].name,
               list[i].active,
               list[i].speed);
    }
}