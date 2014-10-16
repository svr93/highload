gcc -std=c99 libs/listener.c libs/strfuncs.c \
libs/parse.c libs/conttype.c libs/resphead.c \
libs/sending.c server.c -o server
