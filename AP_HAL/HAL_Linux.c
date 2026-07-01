#include "AP_HAL.h"

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

static int sockfd;
static struct sockaddr_in tx_addr;

int hal_init(void)
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0)
        return -1;

    struct sockaddr_in local_addr;

    memset(&local_addr,0,sizeof(local_addr));

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(14551);
    local_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd,
         (struct sockaddr*)&local_addr,
         sizeof(local_addr));

    fcntl(sockfd,F_SETFL,O_NONBLOCK);

    memset(&tx_addr,0,sizeof(tx_addr));

    tx_addr.sin_family = AF_INET;
    tx_addr.sin_port = htons(14550);

    inet_pton(AF_INET,
              "172.28.32.1",
		    &tx_addr.sin_addr);

    return 0;
}

void hal_comm_write(uint8_t *data,uint16_t len)
{
    sendto(sockfd,
           data,
           len,
           0,
           (struct sockaddr*)&tx_addr,
           sizeof(tx_addr));
}

int hal_comm_read(uint8_t *data,uint16_t len)
{
    return recv(sockfd,data,len,0);
}

uint32_t hal_millis(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC,&ts);

    return (ts.tv_sec * 1000U) +
           (ts.tv_nsec / 1000000U);
}
