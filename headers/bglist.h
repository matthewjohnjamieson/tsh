#include "sys/types.h"

struct node {
  char *processName; //stores the name of the process
  pid_t pid; //stores the pid of the process
  struct node *prev;
  struct node *next;
};

int addNode(char * name, pid_t propid);
struct node *findNodePid(pid_t targetpid);
struct node *findNodeChar(char *targetname);
void deleteNodePid(pid_t deletename);
void deleteNodeChar(char *deletename);
void printNode();
void freeList();
void terminate(char*);