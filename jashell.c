#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

void subparser () {
	int fd;
	char buffer[80];
	char cmdbuffer[80];
	cmdbuffer[0] = '\0';
	char input[80];
	char * current;
	char * argv[8];
	int argIndex = 1;
	int savedStandardOutput;
	int savedStandardInput;
	int savedStandardError;
	int redirectedDescriptors[3] = {0,0,0};
	pid_t pid;
	int readyToExec = 0;
	while (1) {
		printf("myshell> " );
		fgets(input,80,stdin);
		strtok(input,"\n");
		current = strtok(input, " ");
		while (current != NULL) {
			strcpy(buffer, current);
			printf("%s %s\n","Current token",current);
			printf("%s %s\n","Current buffer",buffer);
			//the following "if" statement isn't needed anymore if the we go with the recursion method
			if (buffer[strlen(buffer)-1] == ';') {
				buffer[strlen(buffer)-1] = '\0';
				readyToExec =1;
			} 
			if (strcmp(buffer,"<") == 0) {
				current = strtok(NULL, " ");
				strcpy(buffer, current);
				if (buffer[strlen(buffer)-1] == ';') {
					buffer[strlen(buffer)-1] = '\0';
					readyToExec =1;
				} 
				if ((fd = open(current, O_RDONLY)) == -1) {
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
				//open file in write mode. Question: Append or overwrite?
				if ((fd = open(current, O_WRONLY)) == -1) {
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
				if (cmdbuffer[0]!='\0') {
					argv[argIndex] = malloc(strlen(buffer)+1);
					strcpy(argv[argIndex],buffer);
					argIndex++;
				} else {
					strcpy(cmdbuffer, buffer);
					printf("%s %s\n","Current token",current);
					printf("%s %s\n","Current cmdbuffer",cmdbuffer);
				}
				//printf("%s %s\n","Ready to exec",readyToExec);
			}
			
			current = strtok(NULL, " ");
			
			if(current==NULL) {
				readyToExec =1 ;
			}
			
			printf("%s %d\n","Ready to exec",readyToExec);
			
			
			if (readyToExec) {
				readyToExec = 0;
				pid = fork();
				if (pid==0) {
					printf("%s %s","Current command buffer",cmdbuffer);
					printf("%s %s","Current command buffer",argv);
					argv[argIndex] = NULL;
					argv[0] = cmdbuffer;
					if (execvp(cmdbuffer, argv) == -1) {
						perror("execvp went wrong");
					}
			} else {
					wait(NULL);
					argv[1] =NULL;
					argv[2] = NULL;
					argv[3] =NULL;
					argv[4] =NULL;
					argv[5] =NULL;
					argv[6] =NULL;
					argv[7] =NULL;
					argIndex = 1;
					cmdbuffer[0] = '\0';
					if (redirectedDescriptors[0]) {
						printf("\n%s %d","Standard input:",savedStandardInput);
						dup2(savedStandardInput,0);
						close(savedStandardInput);
						redirectedDescriptors[0] = 0;
					} 
					if (redirectedDescriptors[1]) {
						dup2(savedStandardOutput,1);
						close(savedStandardOutput);
						redirectedDescriptors[1] = 0;
					}
					if (redirectedDescriptors[2]) {
						dup2(savedStandardError,2);
						close(savedStandardError);
						redirectedDescriptors[2] = 0;
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

