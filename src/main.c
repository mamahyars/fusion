#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "packet.h"
#include <sys/select.h>
#include "../include/receiver.h"
#include "../include/network.h"
#include <linux/if.h>
#include <linux/if_tun.h>
#include "../include/speed.h"
#include "../include/interface.h"
#include "../include/router.h"
#include "../include/forward.h"
#include "../include/socket.h"
#include "../include/peer.h"
#include "../include/receiver.h"

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

int main(int argc, char *argv[])
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
    int receiver = create_receiver(9000);
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
if(argc < 3)
{
    printf("Usage: %s <peer_ip> <port>\n", argv[0]);
    return 1;
}

set_peer(argv[1], atoi(argv[2]));

    while (1)
    {
        fd_set fds;

        FD_ZERO(&fds);

        FD_SET(fd, &fds);
        FD_SET(receiver, &fds);

        int maxfd = fd > receiver ? fd : receiver;

        select(maxfd + 1, &fds, NULL, NULL, NULL);


        if (FD_ISSET(fd, &fds))
        {
            int n = read(fd, buffer, sizeof(buffer));

            if (n > 0)
            {
                forward_packet(buffer, n);
                parse_packet(buffer, n);
            }
        }


        if (FD_ISSET(receiver, &fds))
        {
            int n = receive_from_peer(receiver, buffer);

            if (n > 0)
            {
                write(fd, buffer, n);
            }
        }
    }


    close(fd);

    return 0;
}