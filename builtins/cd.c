/*
 * Adam Stomberg
 * File: cd.c
 * changes directories
 * CSCI476 - OSP
 */

#define _POSIX_C_SOURCE 200112L
#define _ISOC99_SOURCE
#define __EXTENSIONS__
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE	1024

int main(int argc, char *argv[]) {

	char cwd1[BUF_SIZE];
	char cwd2[BUF_SIZE];
	char *dir = argv[1];

	if(getcwd(cwd1, sizeof(cwd1)) == NULL){ //saves current working directory
		fprintf(stderr, "Error: getcwd failed.\n");
		return EXIT_FAILURE;
	} 
	
	if(argc == 1){
		fprintf(stderr, "Error: No arugments.\n");
		return EXIT_FAILURE;
	}

	if(chdir(dir) == -1){
		fprintf(stderr, "Error: Could not find directory.\n");
		return EXIT_FAILURE;
	}


	// prints directory it changed to /////////
	if(getcwd(cwd2, sizeof(cwd2)) == NULL){ 
		fprintf(stderr, "Error: getcwd failed.\n");
		return EXIT_FAILURE;
	}
	printf("%s\n", cwd2);
	//////////////////////////////////////////
}
