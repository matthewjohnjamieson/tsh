CC=gcc
CFLAGS=-Wall -Wextra
SOURCE=./headers/bglist.h ./functions/bglist.c ./functions/cd.c ./functions/echo.c ./functions/pwd.c tsh.c

all:
	$(CC) $(CFLAGS) -g $(SOURCE)

clean:
	rm a.out