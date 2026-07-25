#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ifaddrs.h>
#include <net/if.h>

#include "../include/network.h"
void list_interfaces()
{
    struct ifaddrs *ifaddr;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        return;
    }

    char shown[50][64];
    int count = 0;

    for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_name)
            continue;

        int exists = 0;

        for (int i = 0; i < count; i++)
        {
            if (strcmp(shown[i], ifa->ifa_name) == 0)
            {
                exists = 1;
                break;
            }
        }

        if (!exists)
        {
            strcpy(shown[count], ifa->ifa_name);
            count++;

            printf("Interface: %s\n", ifa->ifa_name);
        }
    }

    freeifaddrs(ifaddr);
}