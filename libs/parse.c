#include "parse.h"

void getOffsets(short* shifts, const char* key) {
    int keyLen = getStrLen(key);
    
    for (int i = 0; i < SYM_NUM; ++i) {
         *(shifts + i) = keyLen;
    }
    
    int len = keyLen - 1;  
    for (int i = 0; i < len; ++i) {
         *(shifts + key[i]) = len - i;
    }
}

void getValueSubstr(int index, const char* request, char* value) {
    
    index += DELIMITER_SHIFT;
    int i = 0;
    int reqLen = getStrLen(request);
    
    while (index < reqLen && (request[index] != '\r')) {
        value[i++] = request[index++];
    }
}
               
int findValue(const char* request, const char* key, 
char* value) { //Boyer-Moore-Horspool algorithm
    
    if (request == NULL || key == NULL) {
        perror("pointer");
        return -1;
    }
      
    short shifts[SYM_NUM] = {};
    getOffsets(shifts, key);
    
    int reqLen = getStrLen(request);
    int keyLen = getStrLen(key);                  
    int index = keyLen - 1;
    int isFound = 1;
    
    for(;;) {
        for (int i = 0; i < keyLen; ++i) {
            if (request[index - i] != key[keyLen - 1 - i]) {
                isFound = 0;
                break;
            }
        }
        if (isFound == 0 &&
        (index + shifts[request[index]]) < reqLen) {
            index += shifts[request[index]];
            isFound = 1;
        } else {
            break;
        }
    }
                   
    if (isFound == 1 && value != NULL) {
        getValueSubstr(index, request, value);
    }
    
    return isFound;
}

int findUrl(const char* request, char* url) {
    if (request == NULL || url == NULL) {
        perror("pointer");
        return -1;
    }
    
    int reqLen = getStrLen(request);
    int index = 0;
    int i = 0;
    
    for (i = 3; i < reqLen; ++i) {
        if (request[i] == ' ') {
            index = i + 2;
            break;
        }
    }
    
    i = 0;
    
    while (i < URL_LEN && index < reqLen && (request[index] != '\r')) {
        url[i++] = request[index++];
    }
    url[i - 9] = '\0'; //HTTP version excluding
    return 0;
}
