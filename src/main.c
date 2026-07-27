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
#include "../include/fusion_protocol.h"
#include "../include/reorder.h"
#include "../include/ack.h"
#include "../include/cache.h"
#include "../include/scheduler.h"




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
reorder_init();
cache_init();

    while (1)
{
    cache_resend();

    fd_set fds;
        cache_check_timeouts();
        

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
        unsigned char *out_packet;
        int out_length;

        struct fusion_header *hdr =
            (struct fusion_header *)buffer;

        /* اگر ACK است */
        if (is_ack_packet(buffer))
{
    printf("ACK #%u received\n", hdr->packet_id);

    cache_remove(hdr->packet_id);

    continue;
}

        /* اگر DATA است */
        if (hdr->type == FUSION_TYPE_DATA);
        {
            send_ack(hdr->packet_id);
        }

        /* قبل از حذف Header شماره Packet را نگه می‌داریم */
        unsigned int packet_id = hdr->packet_id;

        n = remove_fusion_header(buffer, n);

        if (n > 0)
        {
            if (reorder_packet(
                    packet_id,
                    buffer,
                    n,
                    &out_packet,
                    &out_length))
                        {
                write(fd, out_packet, out_length);
            }
        }
    }
}   // پایان if (FD_ISSET)

}   // پایان while

close(fd);

return 0;
}   // پایان main