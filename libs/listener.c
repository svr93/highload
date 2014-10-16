#include "listener.h"

void createSock(int* sockfd) {
    if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("create");
        exit(10);
    }
}

void setSockOptions(int sockfd) {
    int state = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &state, 
    sizeof(int)) < 0) {
        
        perror("setsockopt_reuseaddr");
        exit(11);
    }
}

void bindSock(int sockfd, short port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(12);
    }
}

void startListen(int sockfd) {
    if (listen(sockfd, QUEUE_SIZE) < 0) {
        perror("listen");
        exit(13);
    }
}
        
int makeListeningSock(short port) {
    int sockfd = 0;
    createSock(&sockfd);
    setSockOptions(sockfd);
    bindSock(sockfd, port);
    startListen(sockfd);
    return sockfd;
}
