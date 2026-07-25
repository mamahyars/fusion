#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "packet.h"
#include "../include/network.h"
#include <linux/if.h>
#include <linux/if_tun.h>
#include "../include/speed.h"

int tun_alloc(char *dev)
{
    struct ifreq ifr;
    int fd;

    if ((fd = open("/dev/net/tun", O_RDWR)) < 0) {
        perror("open");
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));

    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;

    if (*dev)
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if (ioctl(fd, TUNSETIFF, (void *)&ifr) < 0) {
        perror("ioctl(TUNSETIFF)");
        close(fd);
        return -1;
    }

    strcpy(dev, ifr.ifr_name);

    return fd;
}

int main()
{
    show_speeds();
    list_interfaces();
    char dev[IFNAMSIZ] = "fusion0";

    int fd = tun_alloc(dev);

    if (fd < 0) {
        printf("Failed to create interface\n");
        return 1;
    }

    printf("Interface created: %s\n", dev);

    unsigned char buffer[2000];

while (1)
{
    int n = read(fd, buffer, sizeof(buffer));

    if (n < 0)
    {
        perror("read");
        break;
    }

    parse_packet(buffer, n);
}

    close(fd);

    return 0;
}