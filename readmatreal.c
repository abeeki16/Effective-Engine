#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void) {
	char buffer [80];
	int arowcount = 0;
	int acolcount = 0;
	int browcount = 0;
	int bcolcount = 0;
	//state keeps track of whether we are currently at matrix A or matrix B
	int state = 0;
	char * current;
	//read in each line from stdin
	while (fgets (buffer, 79 ,stdin) != NULL) {
		//if it encounters a blank line then state = 1 to signify move to matrix B
		if (strcmp(buffer,"\n") == 0) state = 1;
		printf("%s\n",buffer);
		current = strtok(input, " ");
		while (current != NULL) {
			//for each line, read each string separated by spaces
			if (state == 0) {
				arowcount++;
			}
			current = strtok(NULL, " ");
		}
	}
}