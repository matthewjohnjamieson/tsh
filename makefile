CC=gcc
CFLAGS=-Wall -Wextra
SOURCE=tsh.c

all:
	$(CC) $(CFLAGS) -g $(SOURCE)

clean:
	rm a.out