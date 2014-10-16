#include "sending.h"

int sendAll(int sockfd, const char* buf, int len) {
    int current = 0;
    int total = 0;
    
    while(total < len) {
        current = send(sockfd, buf + total, len - total, 0);
        if (current == -1) {
            perror("send_data");
            break;
        }
        total += current;
    }

    return (current == -1 ? -1 : total);
}

int findGetParams(char* url) {
    int len = getStrLen((const char*)url);
    
    for (int i = 0; i < len; ++i) {
        if (url[i] == '?') {
            url[i] = '\0';
            len = i;
            break;
        }
    }
    return len;
}

void beforeSend(struct requestValues* reqVal, 
struct responseValues* respVal, char* path) {
    
    int isGET = 0;
    int isMethodAllowed = 1;
    char url[URL_LEN + 1] = {};
    
    if (reqVal->request[0] == 'G') {
        isGET = 1;
    } else if (reqVal->request[0] != 'H') {
        isMethodAllowed = 0;
    }
    
    findUrl((const char*)reqVal->request, url);
      
    char decUrl[URL_LEN + 1] = {};
    decodeUrl(decUrl, (const char*)url);
    
    int len = findGetParams(decUrl);
    
    respVal->contType[0] = '\0';
    int isIndex = 0;
    
    if ((isIndex = getContentType((const char*)decUrl, 
    respVal->contType)) == 1) { //4
        
        if (len > 0 && (decUrl[len - 1] != '/')) {
            decUrl[len] = '/';
            decUrl[len + 1] = '\0';
        }
        addSymbs(decUrl, "index.html");
    }
    
    addSymbs(path, DOCUMENT_ROOT);
    addSymbs(path, (const char*)decUrl);
    
    respVal->isFound = 0; //1
    respVal->isAccessDenied = 0; //2
    respVal->contLen = 0; //3
    
    struct stat stat_buf;

    if (stat((const char*)path, &stat_buf) == 0 &&
    findValue((const char*)path, "../", NULL) == 0) {
        
        respVal->isFound = 1;
        if (isMethodAllowed == 1) {
            respVal->contLen = stat_buf.st_size;
        } else {
            respVal->isAccessDenied = 1;
        }
    } else if (isIndex == 1) {
        respVal->isAccessDenied = 1;
    }
    
    if (respVal->isFound == 0 || respVal->isAccessDenied == 1 ||
    isGET == 0) {
        path[0] = '\0';
    }
}

int sendData(struct requestValues* reqValues) {
    if (reqValues == NULL) {
        perror("pointer");
        return -1;
    }
    
    struct responseValues respValues;
    char path[PATH_LEN + 1] = {};
    beforeSend(reqValues, &respValues, path);
    
    char resp[RESP_HEADERS_BUF_SIZE + 1] = {};
    
    setRespHeaders(&respValues, resp);
    addSymbs(resp, "\r\n\r\n");
    sendAll(reqValues->sockfd, resp, getStrLen(resp));
    
    if (path[0] != '\0') {
        int src = open((const char*)path, O_RDONLY);
        off_t offset = 0;
        sendfile(reqValues->sockfd, src, &offset, respValues.contLen);
        close(src);
    }
    return 0;
}
