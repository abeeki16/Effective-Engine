#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

void subparser () {
	int fd;
	char buffer[80];
	char cmdbuffer[80];
	char input[80];
	char * current;
	pid_t pid;
	int readyToExec = 0;
	while (1) {
		printf("myshell>" );
		fgets(input,80,stdin);
		strtok(input,"\n");
		current = strtok(input, " ");
		while (current != NULL) {
			strcpy(buffer, current);
			//the following "if" statement isn't needed anymore if the we go with the recursion method
			if (buffer[strlen(buffer)-1] == ';') {
				buffer[strlen(buffer)-1] = '\0';
				readyToExec =1;
			} 
			else if (strcmp(buffer,"<") == 0) {
				current = strtok(NULL, " ");
				if ((fd = open(current, O_RDONLY)) == -1) {
					perror("something is wrong\n");
					exit(1);
				}

				dup2(fd,0);
				close(fd);
				readyToExec = 1;
			}

			//now doing the >, 1>, 2> and &> operators
			else if (strcmp(buffer,">") == 0 || strcmp(buffer,"1>") == 0 || strcmp(buffer,"2>") == 0 || strcmp(buffer,"&>") == 0) {
				current = strtok(NULL, " ");
				//open file in write mode. Question: Append or overwrite?
				if ((fd = open(current, O_WRONLY)) == -1) {
					perror("something is wrong\n");
					exit(1);
				}
				//when in case of &>, does order of output matter?
				if (strcmp(buffer,"2>") == 0 || strcmp(buffer,"&>") == 0) dup2(fd,2);
				if (strcmp(buffer,"2>") != 0 || strcmp(buffer,"&>") == 0) dup2(fd,1);
				close(fd);
				readyToExec = 1;
				
			}
			
			strcpy(cmdbuffer, buffer);
			printf(cmdbuffer);
			if (readyToExec) {
				readyToExec = 0;
				printf("Execing");
				pid = fork();
				if (pid==0) {
					if (execvp(cmdbuffer, (char *) NULL) == -1) {
						perror("execvp went wrong");
					}
				} else {
					wait(NULL);
				}
			}
			
			//TODO: handle simplest case when it's something like "./a.out"
			//without any operators

			current = strtok(NULL, " ");
	}
	
	}
	
}

void main() {

	
	subparser();

}

