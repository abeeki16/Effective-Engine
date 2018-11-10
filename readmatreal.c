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
		if (strcmp(buffer,"\n") == 0) {
			state = 1;
			continue;
		}
		//get rid of \n at the end
		buffer[strlen(buffer)-1] = '\0';
		current = strtok(buffer, " ");
		while (current != NULL) {
			//for each line, read each string separated by spaces
			if (state == 0) {
				//if this is the first row then count it
				if (arowcount == 0) {
					acolcount++;
				}
				//need to check if cur row is same as first row?
			}
			else if (state == 1) {
				if (browcount == 0) bcolcount++;
			}
			printf("%s",current);
			current = strtok(NULL, " ");
		}
		printf("\n");
		if (state == 0) arowcount++;
		else if (state == 1) browcount++;
	}
	printf("arow = %d", arowcount);
	printf("acol = %d", acolcount);
	printf("brow = %d", browcount);
	printf("bcol = %d\n", bcolcount);
	if (acol != brow) printf("invalid matrices\n");
}
