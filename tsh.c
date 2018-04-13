/*
CSCI 476
tiny shell
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
int userspecifiedpath = 0;
int builtincalled = 0;

/* function prototypes... */
int cd(int,char**);

void getUserInput(){
  memset(&userinputbuffer, '\0', BUFFERSIZE);  //flush the input buffer
  fgets(userinputbuffer, BUFFERSIZE, stdin);  //user input
}

void quittsh(){
  printf("goodbye!\n");
  exit(EXIT_SUCCESS);
}

/*signal disposition function
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
*/
int inputhandler(){
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
  
  if(!userinputtokens[0])
    return -1;

  if(strcmp(userinputtokens[0], "cd") == 0){
    builtincalled = 1;
    cd((int)(sizeof(userinputtokens)/(sizeof(userinputtokens[0]))), userinputtokens);
  }

  /* handle the case where the user has specified a directory (eg ./) */
  if(userinputtokens[0][0] == '.' || userinputtokens[0][0] == '/')
    userspecifiedpath = 1;

  return 0;
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
  else if(pid > 0){ // Parent branch
    wait(NULL);
    ignoresignals(1); //reset signals
    userspecifiedpath = 0;
  }
  else{ // Child branch

    // user specified path such as /usr/bin or ./
    if(userspecifiedpath == 1){
      if(execv(userinputtokens[0], userinputtokens) == -1){
        exit(-1);//kill child process
      }
    }

    // otherwise try the builtins folder
    char* path = (char*)malloc(sizeof(char*)); //<-bad init! char* isn't big enough for long paths.
    strcat(path, tshbuiltinspath);
    strcat(path, userinputtokens[0]);
    execv(path, userinputtokens);
    
    free(path);
    
    // otherwise try the linux default folder
    path = (char*)calloc(1, sizeof(char*)); //<-bad init! char* isn't big enough for long paths.
    strcat(path, linuxcommandspath);
    strcat(path, userinputtokens[0]);
    execv(path, userinputtokens);
    
    free(path);
    exit(-1);//kill child process

  }
}

int main(){
  
  ignoresignals(1);
  //input loop
  while(1){
    printf("tsh > ");
    getUserInput();
    inputhandler();
    if(builtincalled == 0)
      forkchild();
    builtincalled = 0;
  }

  return EXIT_SUCCESS;
}