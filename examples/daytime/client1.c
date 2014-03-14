#include <stdio.h>
#include <stdlib.h>
#include "anet.h"

#define GENERIC_SERVERPORT 6379 

int doIt(int connfd)
{
    char buff[64];

    read(connfd, buff, 64);
    printf("%s\n", buff);

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: client <Server IP>\n");
        return -1;
    }
    
    int fd;
    fd = anetTcpConnect(NULL, argv[1], GENERIC_SERVERPORT);
    if (fd == ANET_ERR) {
        printf("Connect to server failed!\n");
        exit(1);
    }

    doIt(fd);

    close(fd);

    exit(0);

    return 0;
}

