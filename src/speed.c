#include <stdio.h>
#include <string.h>
#include <ifaddrs.h>

void show_speeds()
{
    struct ifaddrs *interfaces;
    struct ifaddrs *ifa;

    if (getifaddrs(&interfaces) == -1)
    {
        perror("getifaddrs");
        return;
    }

    printf("Network interfaces:\n");

    for (ifa = interfaces; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_name)
        {
            printf(" - %s\n", ifa->ifa_name);
        }
    }

    freeifaddrs(interfaces);
}