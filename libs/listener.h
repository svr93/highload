#ifndef _LISTENER_H_
#define _LISTENER_H_

#include <stdio.h> //for perror
#include <stdlib.h> //for exit
#include <netinet/in.h> //for network funcs

#define QUEUE_SIZE 65536

int makeListeningSock(short port);

#endif
