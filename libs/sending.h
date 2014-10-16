#ifndef _SENDING_H_
#define _SENDING_H_

#include <stdio.h> // for NULL
#include <sys/stat.h> // for file size
#include <unistd.h> // for open, close
#include <fcntl.h>  // for O_RDONLY
#include <netinet/in.h> // for sending headers
#include <sys/sendfile.h> // for sending files
#include "strfuncs.h" // for getStrLen
#include "parse.h" // for findUrl
#include "conttype.h" // for getting Content-Type
#include "resphead.h" // for making response headers

#define DOCUMENT_ROOT "/home/vladimir/tp_highload_server_sendfile__/"
#define REQ_BUF_SIZE 2048
#define RESP_HEADERS_BUF_SIZE 256
#define URL_LEN 512
#define PATH_LEN 256

struct requestValues {
    char request[REQ_BUF_SIZE];
    int sockfd;
};  

int sendData(struct requestValues* reqValues);

#endif
