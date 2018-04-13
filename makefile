CC=gcc
CFLAGS=-Wall -Wextra
SOURCE=./functions/cd.c tsh.c

all:
	$(CC) $(CFLAGS) -g $(SOURCE)

clean:
	rm a.out