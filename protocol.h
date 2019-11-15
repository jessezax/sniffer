/* normal header files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>

/* network header files */
#include <arpa/inet.h>
#include <netdb.h>
#include <linux/if_ether.h>
#include <linux/igmp.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
//#include <net/if.h>
#include <net/ethernet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/if_arp.h>


struct PPP_LCP_3001{
        u_short FV;                     /*flag and version*/
        u_short PT;                     /*Protocol Type*/
        u_short PL;                     /*Payload Length*/
        u_short CI;                     /*Call ID*/
        u_int   SN;                     /*Sequence Number*/
};

struct PPP_LCP_3081{
        u_short FV;                     /*flag and version*/
        u_short PT;                     /*Protocol Type*/
        u_short PL;                     /*Payload Length*/
        u_short CI;                     /*Call ID*/
        u_int   SN;                     /*Sequence Number*/
        u_int   ACK;                    /*ACK*/
};
