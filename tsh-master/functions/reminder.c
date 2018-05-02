/*
 * Adam Stomberg
 * File: reminder.c
 * changes directories
 * CSCI476 - OSP
 */

#define _POSIX_C_SOURCE 200112L
#define _ISOC99_SOURCE
#define __EXTENSIONS__
#define _XOPEN_SOURCE 600


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define BUFFER_SIZE	4096

typedef struct remind{

	int *time; //user input for sleep time will be stored here
	char *msg; //user input message will be stored here
	pthread_mutex_t *mutexR;

}remind;

void *rem(void *remstruct){ //remind function that will remind user given message after a given amount of time
	struct remind *tempArg = (struct remind *)remstruct;
	sleep((int)tempArg->time);
	pthread_mutex_lock(tempArg->mutexR);
	printf("%s\n", tempArg->msg);
	pthread_mutex_unlock(tempArg->mutexR);
	pthread_exit(NULL);
}

int reminder(int remargc, char *remargv[]){
  	
	if(remargc <= 2){ //if there are not enough arguments
		fprintf(stderr, "Error: Usage reminder <seconds> <string(s)>\n");
		return EXIT_FAILURE;
	}
  	
	int ret;
	int start = 0;
	char mess[BUFFER_SIZE];
	memset(mess, '\0', BUFFER_SIZE * sizeof(char));

	int temp = atoi(remargv[1]);
	if(temp < 0){
		fprintf(stderr, "Error: Seconds is not a positive integer!\n");
		return EXIT_FAILURE;
	}

	while(start <= (remargc-1)){
		strcat(mess, remargv[start]);
		strcat(mess, " ");
		start++;
	}
    	
  pthread_mutex_t mutex;
	pthread_t rthread[0];

	remind *r = malloc(sizeof(remind));
	if(!r){ //if malloc fails
		fprintf(stderr, "malloc() failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	ret = pthread_mutex_init(&mutex, NULL);
	if(ret != 0){ //if mutex init fails
		fprintf(stderr, "pthread_mutex_init() failed: %s\n", strerror(errno));
		free(r);
		return EXIT_FAILURE;
	}
	
	r->time = (int *)temp; 	
	if(temp == 0){
		fprintf(stderr, "Error: Usage reminder <seconds> <string(s)>\n");
	}

	r->msg = (char *)malloc(sizeof(strlen(mess)+1));
	strcpy(r->msg, mess);
	r->mutexR = &mutex;

	ret = pthread_create(&rthread[0], NULL, rem, r);
	if(ret != 0){ //if thread create fails
		free(r);
		pthread_mutex_destroy(&mutex);
		fprintf(stderr, "pthread_create() failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	pthread_join(rthread[0], NULL);
	
	free(r);
	pthread_mutex_destroy(&mutex);

	return EXIT_SUCCESS;
}
