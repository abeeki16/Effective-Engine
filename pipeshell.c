#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

int main (void) {
	char input[80];
	char * current;	
	printf("myshell> ");
	char * reverser[20];
	int revpointer = 0;

	fgets(input,80,stdin);
	current = strtok(input,"|");
	while (current != NULL) {
		//subparser(current);
		//printf("%s\n",current);
		//TODO: make fork here. if current process is parent, skip the call to subparser.
		reverser[revpointer] = current;
		revpointer++;
		current = strtok(NULL,"|");
	}
	for (int i = revpointer-1; i > 0; i--) {
		printf("%s\n",reverser[i]);
	}
}