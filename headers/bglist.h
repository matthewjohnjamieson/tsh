#include "sys/types.h"

int addNode(char * name, pid_t *propid);
struct node *findNodePid(pid_t *targetpid);
struct node *findNodeChar(char *targetname);
void deleteNodePid(pid_t *deletename);
void deleteNodeChar(char *deletename);
void printNode();
void freeList();