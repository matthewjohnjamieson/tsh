#define _POSIX_C_SOURCE 200112L
#define _ISOC99_SOURCE
#define EXTENSIONS
#define _XOPEN_SOURCE 600

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
*1st idea:
*possibly this can be of use, in the shell we create a char * array
*that holds all the strings that the user passed in on the echo
*call. If there was nothing passed send and empty array.
*Also we would need to pass the length of the array using the
*method shown below.
*ex.
*const char *foo[] = { "abc", "def" };
*const size_t length = sizeof(foo)/sizeof(foo[0]);
*/

/*
*2nd idea:
*An idea I learned in CSCI325; we could do a variable amount of
*parameters as well. I do have code snippets if anyone would like
*to explore this idea.
*/

/*
*This function essentially just prints out the users input
*string by string. It returns 0, to let shell know it was
*successful.
*/
int echo(int length, char* user[]) {
  for(int i = 1; i <= (length - 1) ; i++) {
    if(user[i] == NULL)
      break;
    printf("%s ", user[i]);
  }
  printf("\n");
  
  return 0;
}