#include "strfuncs.h"

int getStrLen (const char* str) {
    if (str == NULL) {
        return -1;
    }
    int i = 0;
    while (str[i] != '\0') {
        ++i;
    }
    return i;
}

int addSymbs(char* dest, const char* source) {
    if (dest == NULL || source == NULL) {
        return -1;
    }
    
    int destLen = getStrLen((const char*)dest);
    int sourceLen = getStrLen(source);
    
    int i = 0;
    for (i; i < sourceLen; ++i) {
        dest[destLen + i] = source[i];
    }
    dest[destLen + i] = '\0';
    return 0;
}

int isEquals(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return -1;
    }
    
    int equals = 1;
    for (int i = 0;; ++i) {
        if ((str1[i] == str2[i]) && (str1[i] == '\0')) {
            break;
        } else if (str1[i] != str2[i]) {
            equals = 0;
            break;
        }
    }
    return equals;
}

int decodeUrl(char* decodedUrl, const char* encodedUrl) {
    if (decodedUrl == NULL || encodedUrl == NULL) {
        return -1;
    }
    
    int len = getStrLen(encodedUrl);
    int decIndex = 0;
    
    for (int i = 0; i < len;) {
        if (encodedUrl[i] != '%') {
            decodedUrl[decIndex++] = encodedUrl[i++];
        } else {
            int val1 = (encodedUrl[i + 1] < 58) ? (encodedUrl[i + 1] - '0') : 
            (encodedUrl[i + 1]) % 8 + 57 - '0';
            
            int val2 = (encodedUrl[i + 2] < 58) ? (encodedUrl[i + 2] - '0') : 
            (encodedUrl[i + 2]) % 8 + 57 - '0';
            
            decodedUrl[decIndex++] = val1 * 16 + val2;
            i += 3;
        }
    }
    decodedUrl[decIndex] = '\0';
    return 0;
}
