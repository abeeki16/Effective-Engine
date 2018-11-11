#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void) {
	char buffer [80];
	int mata[10][10];
	int matb[10][10];
	int arowcount = 0;
	int acolcount = 0;
	int browcount = 0;
	int bcolcount = 0;
	int temp = 0;
	int toput;
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
				//change cur string to int to put into 
				//temp is the current column number
				sscanf(current, "%d", &toput);
				mata[arowcount][temp] = toput;
				//need to check if cur row is same as first row?
			}
			else if (state == 1) {
				if (browcount == 0) bcolcount++;
				sscanf(current, "%d", &toput);
				matb[browcount][temp] = toput;
			}
			printf("%s",current);
			current = strtok(NULL, " ");
			temp++;
		}
		printf("\n");
		if (state == 0) arowcount++;
		else if (state == 1) browcount++;
		temp = 0;
	}
	printf("arow = %d", arowcount);
	printf("acol = %d", acolcount);
	printf("brow = %d", browcount);
	printf("bcol = %d\n", bcolcount);
	if (acolcount != browcount) printf("invalid matrices\n");

	//print matrix a
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%d ",mata[i][j]);
		}
		printf("\n");
	}
}
