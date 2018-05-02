CC=gcc
CFLAGS=-Wall -Wextra 
LDFLAGS=-lpthread
SOURCE=./headers/bglist.h ./functions/bglist.c ./functions/cd.c ./functions/echo.c ./functions/pwd.c ./functions/reminder.c tsh.c

all:
	$(CC) $(CFLAGS) -g $(SOURCE) $(LDFLAGS)

clean:
	rm a.out
