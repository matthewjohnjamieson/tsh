
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
#include <unistd.h>


 #if defined (PATH_MAX) && PATH_MAX != -1
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

#define PATH_MAX_GUESS 1024

//This method assumes you're sending it the filename in the form of a char*, prints the current working //directory.
//Returns -1 upon failure, returns 0 on success.

int pwd(char *filename) {
/*  char path[PATH_MAX];
*  memset(path, '\0', sizeof(char) * PATH_MAX);

   if(realpath(filename, path) == NULL) {
      fprintf(stderr, "realpath() failed: %s\n", strerror(errno));
      return -1; //path failed
   }
   printf("%s\n", path);
   return 0; //path successful
}
*/
   char *path, *ptr;
   if(0 == pathmax) {
	errno = 0;
	if( (pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
		if(0 == errno) {
			pathmax = PATH_MAX_GUESS;
		}
		else {
			fprintf(stderr, "Error: maximum path len cannot be determined!\n");
			return -1;
		}
	}
	else
		++pathmax;
   }
   path = (char *)malloc(pathmax * sizeof(char));
   if(NULL == path) {
	fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
	return -1;
   }

   ptr = realpath(filename, path);
   if(NULL == ptr) {
	fprintf(stderr, "%s: %s\n", filename, strerror(errno));
   }
   printf("%s\n", path);
   free(path);
   return 0;

}
