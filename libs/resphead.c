#include "resphead.h"

int setRespHeaders(struct responseValues* respValues, char* response) {
    if (respValues == NULL || response == NULL) {
        return -1;
    }
    
    addSymbs(response, "HTTP/1.1 ");
    
    if ((respValues->isFound == 1) && 
    (respValues->isAccessDenied == 0)) {
        
        addSymbs(response, "200 OK");
    } else if ((respValues->isFound == 0) && 
    (respValues->isAccessDenied == 0)) {
        
        addSymbs(response, "404 Not Found");
    } else if ((respValues->isFound == 0) &&
    (respValues->isAccessDenied == 1)) {
        
        addSymbs(response, "403 Forbidden");
    } else {
        addSymbs(response, "405 Method Not Allowed");
    }
    
    time_t t = time(NULL);
    struct tm* tmp = gmtime(&t); //GMT instead of UTC
    char timestr[TIME_STR_LEN + 1] = {};
    strftime(timestr, sizeof(timestr), "%a, %d %b %Y %T", tmp); 
    addSymbs(response, "\r\nDate: ");
    addSymbs(response, (const char*)timestr);
    addSymbs(response, " GMT");
    
    addSymbs(response, "\r\nServer: SVR");
    
    addSymbs(response, "\r\nContent-Length: "); 
    char contLen[CONTENTLEN_LEN + 1] = {};
    sprintf(contLen, "%d", respValues->contLen);
    addSymbs(response, (const char*)contLen);
    
    addSymbs(response, "\r\nContent-Type: ");
    addSymbs(response, respValues->contType);
    
    addSymbs(response, "\r\nConnection: keep-alive");
    return 0;
}
