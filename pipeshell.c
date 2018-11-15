#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
static char * reverser[20];
void pipeparser(int i, int rightPipe[2]) {
	int leftPipe[2];
	pid_t pid;
	if (i==0) {
		//pipe(rightPipe);
		pid = fork();
		if (pid==0) {
			dup2(rightPipe[1],1);
			close(rightPipe[0]);
			close(rightPipe[1]);
			execvp(reverser[i],NULL);
		} 
	} else if (rightPipe==NULL) {
		pipe(leftPipe);
		pid = fork();
		if (pid ==0) {
			dup2(leftPipe[0],0);
			close(leftPipe[0]);
			close(leftPipe[1]);
			pipeparser(i-1,leftPipe);
			execvp(reverser[i],NULL);
		}
	} else {
		pipe(leftPipe);
		pid = fork();
		if(pid==0) {
			dup2(rightPipe[1],1);
			close(rightPipe[0]);
			close(rightPipe[1]);
			
			dup2(leftPipe[0],0);
			close(leftPipe[0]);
			close(leftPipe[1]);
			pipeparser(i-1,leftPipe);
			execvp(reverser[i], (char *) NULL);
		} 
	} 
	
	
}

int main (void) {
	char input[80];
	char * current;	
	
	printf("myshell> ");
	
	int revpointer = 0;
	char reversed[250];
	pid_t pid;
	fgets(input,80,stdin);
	input[strlen(input)-1] = '\0';
	current = strtok(input,"|");
	
	while (current != NULL) {
		//subparser(current);
		//printf("%s\n",current);
		//TODO: make fork here. if current process is parent, skip the call to subparser.
		reverser[revpointer] = current;
		revpointer++;
		current = strtok(NULL,"|");
	}
	
	pipeparser(revpointer-1,NULL);
	int i;
	for (i = revpointer-1; i >= 0; i--) {
		printf("%s\n",reverser[i]);
	}

}
