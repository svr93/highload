#ifndef _RESPHEAD_H_
#define _RESPHEAD_H_

#include <stdio.h> // for sprintf
#include <time.h> // for date
#include "strfuncs.h" // for addSymbs

#define TIME_STR_LEN 25
#define CONTENTLEN_LEN 10
#define CONTTYPE_LEN 20

struct responseValues { 
    int isFound;
    int isAccessDenied;
    long contLen;
    char contType[CONTTYPE_LEN + 1];
};
    
int setRespHeaders(struct responseValues* respValues, char* response);

#endif
