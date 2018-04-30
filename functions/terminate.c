#define _POSIX_C_SOURCE 200112L
#define _ISOC99_SOURCE
#define EXTENSIONS
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>


void terminate(char *pid){
    int ret;
    ret = kill((atoi(pid)), SIGINT);
    if (ret == 0) {
          deleteNodePid((unsigned long)(atoi(pid)));
    }
     else{
       //kill() has returned -1
       fprintf(stderr,"kill() failed.\n");
     }
}

void main(char *pid){
  terminate(pid);
}
