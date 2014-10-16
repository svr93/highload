#ifndef _STRFUNCS_H_
#define _STRFUNCS_H_

#include <stdio.h> // for NULL

int getStrLen(const char* str);

int addSymbs(char* dest, const char* source);

int isEquals(const char* str1, const char* str2);

int decodeUrl(char* decodedUrl, const char* encodedUrl);

#endif
