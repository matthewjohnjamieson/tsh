#define _POSIX_C_SOURCE 200112L
#define _ISOC99_SOURCE
#define __EXTENSIONS__
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
  printf("I am the test program...\n");

  if(argc > 1)
    printf("and my first argument is: %s\n", argv[1]);
  return EXIT_SUCCESS;
}