/*
CSCI 476
project
part 1
*/

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

#define BUFFERSIZE 256 //tentative user input buffer size
char userinputbuffer[BUFFERSIZE];//user input buffer
char* userinputtokens[256]; //buffer to hold the array of tokens
struct sigaction action, oldaction;
const int signalstoignore[] = {SIGQUIT,SIGINT ,SIGUSR1};
const char* tshbuiltinspath = "./builtins/";
const char* linuxcommandspath = "/bin/";


void getUserInput(){
  memset(&userinputbuffer, '\0', BUFFERSIZE);  //flush the input buffer
  fgets(userinputbuffer, BUFFERSIZE, stdin);  //user input
}

void quittsh(){
  printf("goodbye!\n");
  exit(EXIT_SUCCESS);
}

/*signal masking function
*/
void ignoresignals(int flag){
  if(flag == 1)
    action.sa_handler = SIG_IGN;
  else
    action.sa_handler = SIG_DFL;

  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;

  for(int i = 0; i < (int)(sizeof(signalstoignore) / sizeof(int)); i++ ){
   if(sigaction(signalstoignore[i], &action, NULL) < 0){
    fprintf(stderr, "sigaction failed %s\n",strerror(errno));
    exit(EXIT_FAILURE);
   }
  }
}



/* input handling function
  get user input...
  parse out the input. figure out what to do with it
    the input may be only a function name, or potentially a function with a list
    or arguments. the arguments need to be passed into the new process somehow. 
  dispatch the next function (fork probably)
*/
//basic function to get user input and store it into a buffer
void inputhandler(){
  
  /* quit...  */

  int compare = strcmp(userinputbuffer, "quit\n");
  if(compare == 0)
    quittsh();

  userinputbuffer[strlen(userinputbuffer) - 1] = '\0'; //strip newline from user input

  /*tokenize user input...*/

  const char* delim = " "; //token delimiter
  char* token; //holds the current token
  memset(userinputtokens, '\0', 256); //clear the token buffer

  token = strtok(userinputbuffer, delim); //first do this
  for(int i = 0;(i < (int)(sizeof(userinputbuffer) / sizeof(char))) && token ; i++){
    userinputtokens[i] = token;
    token = strtok(NULL, delim); //subsequent strtok calls are like this (who knows why?)
  }
}

/*fork handling function
*/
void forkchild(){
  int pid = 0;
  ignoresignals(0); // system default signal disposition

  pid = fork();
  if(pid < 0){
    fprintf(stderr, "fork error! %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  else if(pid > 0){
    wait(NULL); //wait for child
    ignoresignals(1); //reset signals
  }
  else{
  /* possible branches of execution:
      ./ or some other path to indicate the user wants to run a program in the specified directory
        or fail
      just the program name:
        try the builtins folder
        try the linux default folder
        or fail
  */

    char* path = (char*)malloc(sizeof(char*)); //<-bad init! char* isn't big enough for long paths.
    strcat(path, linuxcommandspath);
    strcat(path, userinputtokens[0]);
    if(execv(path, userinputtokens) == -1){
      fprintf(stderr, "exec failed: %s\n", strerror(errno));
      exit(-1);//kill child process
    }
    
    //child
    //do some work.
    //or terminate self
  }
}

int main(){
  
  ignoresignals(1);
  //input loop
  while(1){
    printf("tsh > ");
    getUserInput();
    inputhandler();
    forkchild();
  }

  return EXIT_SUCCESS;
}