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
#include "../include/interface.h"
#include "../include/router.h"
#include "../include/forward.h"
#include "../include/socket.h"

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
   
   NetworkInterface interfaces[MAX_INTERFACES];

int count = get_interfaces(interfaces, MAX_INTERFACES);

print_interfaces(interfaces, count);
NetworkInterface *best;

best = select_best_interface(interfaces, count);

if (best)
{
    printf("Best interface: %s (%d Mbps)\n",
           best->name,
           best->speed);
}
    list_interfaces();
    char dev[IFNAMSIZ] = "fusion0";

    int fd = tun_alloc(dev);
    int sock = create_socket();

if (sock < 0)
{
    printf("Failed to create socket\n");
    return 1;
}

    if (fd < 0) {
        printf("Failed to create interface\n");
        return 1;
    }

    printf("Interface created: %s\n", dev);

    unsigned char buffer[2000];
    

if(sock < 0)
{
    return 1;
}

while (1)
{
    int n = read(fd, buffer, sizeof(buffer));

    if (n < 0)
    {
        perror("read");
        break;
    }

    forward_packet(sock, buffer, n);

    parse_packet(buffer, n);
}

    close(fd);

    return 0;
}