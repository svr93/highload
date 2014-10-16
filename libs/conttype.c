#include "conttype.h"

int isContains(const char* str, int pos, const char* value) {
	int strLen = getStrLen(str);
	int valLen = getStrLen(value);	
	int isFound = 1;
	
	for (int i = pos; i < strLen; ++i) {
		if (str[i] != value[i - pos]) {
			isFound = 0;
			break;
		}
	}
	return isFound;
}
		
int getContentType(const char* url, char* type) {
	if (url == NULL || type == NULL) {
		return -1;
	}
	
	int urlLen = getStrLen(url);
	int pointPos = -1;
	
	for (int i = 0; i < urlLen; ++i) {
		if (url[i] == '.') {
			pointPos = i;
		}
	}
	
	int lastElPos = urlLen - 1;
	if (pointPos == -1 || (lastElPos - pointPos) > 4 || (lastElPos - pointPos) < 2) {
		addSymbs(type, "text/html");
		return 1;
	}
	switch(lastElPos - pointPos) {
		
		case 2:		
		if (isContains(url, pointPos + 1, "js") == 1) {
			addSymbs(type, "text/javascript");
			return 0;
		} 
		if (isContains(url, pointPos + 1, "JS") == 1) {
			addSymbs(type, "text/javascript");
			return 0;
		}
		addSymbs(type, "text/html");
		return 1;
		
		case 3:
		if (isContains(url, pointPos + 1, "jpg") == 1) {
			addSymbs(type, "image/jpeg");
			return 0;
		}
		if (isContains(url, pointPos + 1, "png") == 1) {
			addSymbs(type, "image/png");
			return 0;
		}
		if (isContains(url, pointPos + 1, "gif") == 1) {
			addSymbs(type, "image/gif");
			return 0;
		}
		if (isContains(url, pointPos + 1, "css") == 1) {
			addSymbs(type, "text/css");
			return 0;
		}
		if (isContains(url, pointPos + 1, "swf") == 1) {
			addSymbs(type, "application/x-shockwave-flash");
			return 0;
		}
		if (isContains(url, pointPos + 1, "txt") == 1) {
			addSymbs(type, "text/plain");
			return 0;
		}
		if (isContains(url, pointPos + 1, "JPG") == 1) {
			addSymbs(type, "image/jpeg");
			return 0;
		}
		if (isContains(url, pointPos + 1, "PNG") == 1) {
			addSymbs(type, "image/png");
			return 0;
		}
		if (isContains(url, pointPos + 1, "GIF") == 1) {
			addSymbs(type, "image/gif");
			return 0;
		} 
		if (isContains(url, pointPos + 1, "CSS") == 1) {
			addSymbs(type, "text/css");
			return 0;
		}
		if (isContains(url, pointPos + 1, "SWF") == 1) {
			addSymbs(type, "application/x-shockwave-flash");
			return 0;
		}
		if (isContains(url, pointPos + 1, "txt") == 1) {
			addSymbs(type, "text/plain");
			return 0;
		}
		addSymbs(type, "text/html");
		return 1;
		
		case 4:
		if (isContains(url, pointPos + 1, "jpeg") == 1) {
			addSymbs(type, "image/jpeg");
			return 0;
		}
		if (isContains(url, pointPos + 1, "html") == 1) {
			addSymbs(type, "text/html");
			return 0;
		}
		if (isContains(url, pointPos + 1, "JPEG") == 1) {
			addSymbs(type, "image/jpeg");
			return 0;
		}
		if (isContains(url, pointPos + 1, "HTML") == 1) {
			addSymbs(type, "text/html");
			return 0;
		}
		addSymbs(type, "text/html");
		return 1;
	}
	return -1;
}
