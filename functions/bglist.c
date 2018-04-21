#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

struct node {
  char *processName; //stores the name of the process
  pid_t *pid; //stores the pid of the process
  struct node *prev;
  struct node *next;
};

struct node *head = NULL;

/*
*Function: addNode(char *pname, pid_t *propid)
*@parameter:
*  processName:  the name of the process
*  propid: the pid number to be added to the list
*@return value:
*  0: Success
* -1: Error
*/
int addNode(char * name, pid_t *propid) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  if(!temp) {
    fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
    return -1;
  }
  temp->processName = name;
  temp->pid = propid;
  temp->prev = temp->next = NULL;

  if(!head) { /*no node yet*/
    head = temp;
    temp->next = temp;
    temp->prev = temp;
    return 0;
  }
  struct node *lastnode = head->prev;
  lastnode->next = temp;
  temp->prev = lastnode;
  temp->next = head;
  head->prev = temp;
  return 0;
}

/*
* Function: findNode(pid_t *targetpid)
* @parameter:
* targetpid: specific value that will be found
* @return:
* NULL: not found
* if found, a pointer to the node is returned
*/
struct node *findNodePid(pid_t *targetpid){
  if(!head)
    return NULL;
  struct node *temp = head;
  /* reset the last node's next pointer to be NULL
  *  in order to search without caution */
  head->prev->next = NULL;

  while(temp){
    if(temp->pid == targetpid) {
      /* restore it before exit */
      head->prev->next = head;
      return temp;
    }
    temp = temp->next;
  }
  /* restore it before exit */
  head->prev->next = head;
  return NULL;
}

/*
* Function: findNode(char *targetname)
* @parameter:
* targetname: specific name that will be found
* @return:
* NULL: not found
* if found, a pointer to the node is returned
*/
struct node *findNodeChar(char *targetname){
  if(!head)
    return NULL;
  struct node *temp = head;
  /* reset the last node's next pointer to be NULL
  *  in order to search without caution */
  head->prev->next = NULL;

  while(temp){
    if(temp->processName == targetname) {
      /* restore it before exit */
      head->prev->next = head;
      return temp;
    }
    temp = temp->next;
  }
  /* restore it before exit */
  head->prev->next = head;
  return NULL;
}


/*
* Function: deleteNode(pid_t *deletepid)
* @parameter:
* deletepid: the node with pid that is going to be deleted
*/
void deleteNodePid(pid_t *deletepid) {
  struct node *target = findNodePid(deletepid);
  if(!target) {
    return;
  }
  if(target->next == target) { /*if it is a single node */
    target->prev = target->next = NULL;
    head = NULL;
    free(target);
  }
  else if(target == head) { /*if it is the head node going to be deleted */
    head = head->next;
    target->prev->next = head;
    target->next->prev = target->prev;
    target->prev = target->next = NULL;
    free(target);
  }
  else {
    target->prev->next = target->next;
    target->next->prev = target->prev;
    target->prev = target->next = NULL;
    free(target);
  }
}

/*
* Function: deleteNode(char *deletename)
* @parameter:
* deletename: the node with name that is going to be deleted
*/
void deleteNodeChar(char *deletename) {
  struct node *target = findNodeChar(deletename);
  if(!target) {
    return;
  }
  if(target->next == target) { /*if it is a single node */
    target->prev = target->next = NULL;
    head = NULL;
    free(target);
  }
  else if(target == head) { /*if it is the head node going to be deleted */
    head = head->next;
    target->prev->next = head;
    target->next->prev = target->prev;
    target->prev = target->next = NULL;
    free(target);
  }
  else {
    target->prev->next = target->next;
    target->next->prev = target->prev;
    target->prev = target->next = NULL;
    free(target);
  }
}

/*
* Function: printNode()
* prints all nodes in the doubly linked list
*/
void printNode() {
  if(!head)
      return;
  struct node *temp;
  /* reset the last node's next pointer to be NULL
   * in order to print without caution */
  temp = head;
  head->prev->next = NULL;

  while(temp) {
    printf("Process Name: %s\nProcess PID: %d\n->",temp->processName, (int)temp->pid);
    temp = temp->next;
  }
  printf("^\n");
}

/*
 * Function: freeList()
 * free the allocated node memory
*/
void freeList() {
  struct node *temp;

  if(head) {
    /* set the last node's next pointer
     * to NULL to free without caution */
    head->prev->next = NULL;
  }

  while(head) {
    temp = head;
    head = head->next;
    free(temp);
  }
}
