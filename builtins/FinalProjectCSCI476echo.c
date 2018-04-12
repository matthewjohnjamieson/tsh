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
int echo(char *user[], int length) {
  for(int i = 0; i < length; i++) {
    printf("%s ", user[i]);
  }
  printf("\n");
  return 0;
}

int main() {
  char s1[] = {"hello"};
  char s2[] = {"world"};
  char *foo[] = {};
  char *foo2[] = {s1, s2};
  int length = sizeof(foo)/sizeof(char *);
  int length2 = sizeof(foo2)/sizeof(char *);
  if(length == 0) {
    printf("\n");
    printf("tsh>");
    //return 0; WHEN LEFT UNCOMMENTED, THE FIRST echo() call was
    //ending the program due to this return. Just uncomment to //test an empty char* <array_name>[].
  }
  echo(foo, length);
  echo(foo2, length2);
  printf("\n");
  printf("tsh>");


  return 0;
}
