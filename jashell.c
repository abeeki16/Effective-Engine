#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

void subparser (char * input) {
	int fd;
	char buffer[80];
	char cmdbuffer[80];
	char * current;
	
	printf("myshell>" );
	strtok(input,"\n");
	
	current = strtok(input, " ");
	while (current != NULL) {
		strcpy(buffer, current);
		//the following "if" statement isn't needed anymore if the we go with the recursion method
		if (buffer[strlen(buffer)-1] == ';') {
			buffer[strlen(buffer)-1] = '\0';
		} 
		else if (strcmp(buffer,"<") == 0) {
			current = strtok(NULL, " ");
			if ((fd = open(current, O_RDONLY)) == -1) {
				perror("something is wrong\n");
				exit(1);
			}

			dup2(fd,0);
			close(fd);
			if (execvp(cmdbuffer, (char *) NULL) == -1) {
				perror("execvp went wrong");
			}
			if (current == NULL) break;
		}

		//now doing the > operator
		else if (strcmp(buffer,">") == 0 || strcmp(buffer,"1>") == 0) {
			current = strtok(NULL, " ");
			//open file in write mode. Question: Append or overwrite?
			if ((fd = open(current, O_WRONLY)) == -1) {
				perror("something is wrong\n");
				exit(1);
			}
			dup2(fd,1);
			close(fd);
			if (execvp(cmdbuffer, (char *) NULL) == -1) {
				perror("execvp went wrong");
			}
			if (current == NULL) break;
		}

		strcpy(cmdbuffer, current);
		printf("%s\n",buffer);
		current = strtok(NULL, " ");
	}
}

void main() {

	char input[80];
	char * current;
	
	printf("myshell>");
	fgets(input,80,stdin);
	current = strtok(input,";");
	while (current != NULL) {
		subparser(current);
		//printf("%s\n",current);
		//TODO: make fork here. if current process is parent, skip the call to subparser.
		current = strtok(NULL,";");
	}

}

