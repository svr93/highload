#ifndef _PARSE_H_
#define _PARSE_H_

#include <stdio.h> // for NULL
#include "strfuncs.h" // for getStrLen
#include "sending.h"

#define SYM_NUM 128
#define DELIMITER_SHIFT 3

int findValue(const char* request, const char* key, 
char* value); // not enough used

int findUrl(const char* request, char* url);

#endif
