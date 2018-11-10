#include <stdio.h>
#include <string.h>
#include <fcntl.h>
void main() {
	char input[80];
	int fd;
	char buffer[80];
	char cmdbuffer[80];
	char * current;
	
	printf("myshell>" );
	fgets(input,80,stdin);
	strtok(input,"\n");
	
	current = strtok(input, " ");
	while (current != NULL) {
		strcpy(buffer, current);
		if (buffer[strlen(buffer)-1] == ';') {
			buffer[strlen(buffer)-1] = '\0';
			//fork and exec
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
			//do something with input and program file
			if (current == NULL) break;
		}
		strcpy(cmdbuffer, current);
		printf("%s\n",buffer);
		current = strtok(NULL, " ");
	}
		
	
}