#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

int main (void) {
	char input[80];
	char * current;	
	printf("myshell>");
	char ordered[250];

	fgets(input,80,stdin);
	current = strtok(input,"|");
	strcpy(current,ordered);
	while (current != NULL) {
		//subparser(current);
		//printf("%s\n",current);
		//TODO: make fork here. if current process is parent, skip the call to subparser.
		strcat(current,ordered);
		current = strtok(NULL,"|");
	}
	printf("%s\n",ordered);
}