#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
void subparser () {
	int fd;
	char buffer[80];
	char cmdbuffer[80];
	char input[80];
	char * current;
	int savedStandardOutput;
	int savedStandardInput;
	int savedStandardError;
	int redirectedDescriptors[3] = {0,0,0};
	pid_t pid;
	int readyToExec = 0;
	//signal(SIGINT, SIG_IGN);
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
				strcpy(cmdbuffer,buffer);
			} 
			else if (strcmp(buffer,"<") == 0) {
				current = strtok(NULL, " ");
				strcpy(buffer, current);
				if (buffer[strlen(buffer)-1] == ';') {
					buffer[strlen(buffer)-1] = '\0';
					readyToExec =1;
				} 
				//buffer used to be current
				if ((fd = open(buffer, O_RDONLY)) == -1) {
					perror("something is wrong\n");
					exit(1);
				}
				savedStandardInput = dup(0);
				
				dup2(fd,0);
				close(fd);
				readyToExec = 1;
				redirectedDescriptors[0] = 1;
			}

			//now doing the >, 1>, 2> and &> operators
			else if (strcmp(buffer,">") == 0 || strcmp(buffer,"1>") == 0 || strcmp(buffer,"2>") == 0 || strcmp(buffer,"&>") == 0) {
				current = strtok(NULL, " ");
				strcpy(buffer,current);
				if (buffer[strlen(buffer)-1]==';') {
					buffer[strlen(buffer)-1]='\0';
					readyToExec=1;
				}
				//open file in write mode. Question: Append or overwrite?
				if ((fd = open(buffer, O_WRONLY)) == -1) {
					perror("something is wrong\n");
					exit(1);
				}
				//when in case of &>, does order of output matter?
				if (strcmp(buffer,"2>") == 0 || strcmp(buffer,"&>") == 0) {
					savedStandardError = dup(2);
					dup2(fd,2);
					redirectedDescriptors[2] = 1;
					
				}
				if (strcmp(buffer,"2>") != 0 || strcmp(buffer,"&>") == 0) {
					savedStandardOutput = dup(1);
					dup2(fd,1);
					redirectedDescriptors[1] = 1;
					
				}
				close(fd);
				readyToExec = 1;
				
			} 
			
			else {
				strcpy(cmdbuffer, buffer);
			}
			
			current = strtok(NULL, " ");
			
			if(current==NULL) {
				readyToExec =1 ;
			}
			
			
			if (readyToExec) {
				readyToExec = 0;
				pid = fork();
				if (pid==0) {
					if (execvp(cmdbuffer, (char *) NULL) == -1) {
						perror("execvp went wrong");
					}
				} else {
					wait(NULL);
					if (redirectedDescriptors[0]) {
						//printf("\n%s %d","Standard input:",savedStandardInput);
						dup2(savedStandardInput,0);
						close(savedStandardInput);
					} 
					if (redirectedDescriptors[1]) {
						dup2(savedStandardOutput,1);
						close(savedStandardOutput);
					}
					if (redirectedDescriptors[2]) {
						dup2(savedStandardError,2);
						close(savedStandardError);
					}
				}
			}
			
			//TODO: handle simplest case when it's something like "./a.out"
			//without any operators

			
	}
	
	}
	
	
}

void main() {

	
	subparser();

}

