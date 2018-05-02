#define _POSIX_C_SOURCE 200112L
#define _ISOC99_SOURCE
#define EXTENSIONS
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdlib.h>

/*
*#define PATH_MAX
*not sure if this is how one exactly defines PATH_MAX
*/

//This method assumes you're sending it the filename in the form of a char*, prints the current working //directory.
//Returns -1 upon failure, returns 0 on success.

int pwd(char *filename) {
  char path[PATH_MAX];
  memset(path, '\0', sizeof(char) * PATH_MAX);

   if(realpath(filename, path) == NULL) {
      fprintf(stderr, "realpath() failed: %s\n", strerror(errno));
      return -1; //path failed
   }
   printf("%s\n", path);
   return 0; //path successful
}
