/*
 ============================================================================
 Name        : directory_stream.c
 Author      : Nathan Lindzey
 Version     : 1.0
 ============================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>


/***********************************************************
* open_directory:
* preconditon: an absolute directory given by path
* postcondition: a DIR* stream for that directory
* notes: returns NULL if an error occurs
***********************************************************/
DIR* open_directory(char* path){

	DIR* pDir = opendir(path);
	if (pDir == NULL) {
		fprintf(stderr,"Cannot open directory '%s'\n", path);
		return NULL;
	}
	return pDir;
}

/***********************************************************************************
* concatenate:
* preconditon: a relative or absolute directory specified by path and d_name name
* postcondition: returns path/d_name
************************************************************************************/
char* concatenate(char* path, char* name){

	char* path_name = (char*) malloc(strlen(path) + strlen(name) + 4);
	strcpy(path_name, path);
	strcat(path_name,"/");
	strcat(path_name, name);
	return path_name;
}


int main(int argc, char* argv[]) {

	//unsigned char d_type
	printf("the d_type for a directory is %d\n",DT_DIR);
	printf("the d_type for a regular file is %d\n\n\n",DT_REG);
	fflush(stdout);

	sleep(1);

	// open the root directory specified by argv[1]
	DIR* pDir = open_directory(argv[1]);
	struct dirent* dp;

	while ((dp = readdir(pDir)) != NULL){
		// we want to ignore the files . and .. since they are reserved for the current and parent directory
		if (dp->d_name[0] == '.')
			continue;

		// print the relative path name
		char* path = concatenate(argv[1],dp->d_name);
		printf("relative path: %s\n", path);

		// if the d_type of the current filename is a directory, test to see that we can open it
		if (dp->d_type == DT_DIR){
			DIR* foo = open_directory(path);
			if (foo == NULL) fprintf(stderr,"Cannot open directory '%s'\n", path);
			closedir(foo);
		}

		// print dirent information
		printf("d_name: %s (filename)\n", dp->d_name);
		printf("d_type: %u (the type of the file)\n", dp->d_type);
		printf("d_reclen: %d (length of the record)\n", dp->d_reclen);
		printf("d_ino: %ju (length of the record)\n", dp->d_ino);
		printf("\n\n");
	}
	closedir(pDir);

	/*
	 * YOUR TASK:
	 * modify this code so that it prints the relative path names of all the regular files
	 * within the directory specified by argv[1]. you might find it useful to revisit your
	 * data-structure notes, namely, queues and breadth-first search.
	 */

	return EXIT_SUCCESS;
}
