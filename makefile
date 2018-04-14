CC=gcc
CFLAGS=-Wall -Wextra
SOURCE=./functions/cd.c ./functions/echo.c ./functions/pwd.c tsh.c

all:
	$(CC) $(CFLAGS) -g $(SOURCE)

clean:
	rm a.out