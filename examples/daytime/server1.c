#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "anet.h"

/* Static server configuration */
#define GENERIC_SERVERPORT 6379 /* TCP port */

/* Global server state structure */
struct genericServer {
    int port;
    char *bindaddr;
    int ipfd;
    char neterr[ANET_ERR_LEN];
};

/* Global vars */
struct genericServer server; /* server global state */

int doIt(int connfd)
{
    char buff[1024];
    time_t ticks;

    ticks = time(NULL);
    snprintf(buff, sizeof(buff), "%s\n", ctime(&ticks)); 
    write(connfd, buff, sizeof(buff));

    return 0;
}

void initServerConfig() 
{
    server.port = GENERIC_SERVERPORT;
    server.bindaddr = NULL;
    server.ipfd = -1;
}

void initServer()
{
    if (server.port != 0) {
        server.ipfd = anetTcpServer(server.neterr,server.port,server.bindaddr);
        if (server.ipfd == ANET_ERR) {
            printf("Opening port %d: %s\n", server.port, server.neterr);
            exit(1);
        }
    }
    
    if (server.ipfd < 0) {
        printf("Configured to not listen anywhere, exiting.\n");
        exit(1);
    }
}

int main(int argc, char **argv)
{
    printf("Hello World!\n");
    initServerConfig();
    initServer();

    for ( ; ;) {
        int cfd;
        cfd = anetTcpAccept(server.neterr, server.ipfd, NULL, NULL);
        if (cfd == ANET_ERR) {
            printf("Accepting client connection: %s\n", server.neterr);
        }
        
        doIt(cfd);

        close(cfd);
    }

    exit(0);

    return 0;
}
