#include "protocol.h"
#include <string.h>
#include <sys/ioctl.h>

int Open_Raw_Socket(void);
int Set_Promisc(char *interface, int sock);
void dump(const unsigned char*data_buffer, const unsigned int length);

#if 0
#define ETH_P_ALL 0x0003
#define ETH_P_IP   0x0800
#define ETH_P_ARP  0x0806
#endif


// 建立一个原始socket句柄
int Open_Raw_Socket(void) {
    int sock;
    //if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0) {
    if ((sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
    //if ((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
        perror("raw socket error\n");
        exit(1);
    }
    return sock;
}

// 设置eth0为混杂模式
int Set_Promisc(char *interface, int sock) {
    struct ifreq ifr;
    
    strncpy(ifr.ifr_name, interface, strnlen(interface, sizeof(interface)) + 1);
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) == -1) {
        perror("set promisc error one if\n");
        exit(2);
    }
    
    printf("The interface is %s\n", interface);
    printf("Retrieved flags from interface is ok\n");
    
    ifr.ifr_flags |= IFF_PROMISC;
    
    if (ioctl(sock, SIOCGIFFLAGS, &ifr) == -1) {
        perror("Can not set PROMISC flag:");
        exit(-1);
    }
    
    printf("Set Promisc ok\n");
    
    return 0;
}

// 输出buffer内容
void dump(const unsigned char*data_buffer, const unsigned int length) {

    unsigned char byte;
    unsigned int i, j;
    
    for (i = 0; i < length; i++) {
        byte = data_buffer[i];
        printf("%02x ", data_buffer[i]);
        if ((i % 16 == 15) || (i == length -1)) {
            for (j = 0; j < 15 -(i % 16); j++) {
                printf("   ");
            }
            printf("|");
            for (j = (i - (i % 16)); j <= i; j++) {
                byte = data_buffer[j];
                if (byte > 31 && byte < 127)
                    printf("%c", byte);
                else
                    printf(".");
            }
            printf("\n");
        }
    }
    
}


int main() {
    int sock;
    sock = Open_Raw_Socket();
    printf("raw socket is %d\n", sock);

    char buffer[65535];
    
    int bytes_recieved;
    size_t fromlen;
    //struct  sockaddr_in from;
    struct  sockaddr_in from;

    struct sockaddr src_addr;
	int addrlen;
    addrlen = sizeof(struct sockaddr);
    
    struct ip *ip1;
    struct tcp *tcp;

    struct PPP_LCP_3001 *PPP_LCP_3001;
    struct PPP_LCP_3081 *PPP_LCP_3081;

    u_short *determine;
    // 设置网卡eth0为混杂模式
    Set_Promisc("ens37", sock);
    // 输出TCP/IP报头的长度
   
    
    while (1) {
        fromlen = sizeof(from);
        //bytes_recieved = recvfrom(sock, buffer, sizeof(buffer),
        //        0, (struct sockaddr*)&from, &fromlen);
        bytes_recieved = recvfrom(sock, buffer, sizeof(buffer), 0, &src_addr, &addrlen);
        
        determine = (u_short*)(buffer + 20);        // IP数据包和TCP数据包有20个字节的距离
           // printf("-------------------------determine:      %x\n",*determine);
        
        ip1 = (struct ip1*)buffer;         
        //if( (strcmp(inet_ntoa(ip1->ip_src),"192.168.0.3")==0)||(strcmp(inet_ntoa(ip1->ip_src),"192.168.0.132")==0)) {
            printf("Source address: %s\n",inet_ntoa(ip1->ip_src));
            printf("Dest address is: %s\n", inet_ntoa(ip1->ip_dst));
          
            //dump((const unsigned char*)buffer, bytes_recieved);   
       // }
    }
    return 0;
}


