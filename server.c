#include <stdio.h> // for perror
#include <netinet/in.h> // for recv
#include <unistd.h> // for close
#include "libs/listener.h" // for creating listener
#include "libs/sending.h" // for sendData

int main() {
    int listener = makeListeningSock(8000);

    struct requestValues rv;
    for (;;) {
        rv.sockfd = accept(listener, NULL, NULL);
        
        if (rv.sockfd < 0) {
            perror("accept");
            exit(1);
        }
                
        for (int i = 0; i < REQ_BUF_SIZE; ++i) {
            rv.request[i] = '\0';
        }
           
        int n = recv(rv.sockfd, rv.request, REQ_BUF_SIZE, 0);
        if (n <= 0) {
            close(rv.sockfd);
            continue;
        }
                
        sendData(&rv);
        close(rv.sockfd);
    }
    return 0;
}
