#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	char buffer[80];
	int matrix[10][10];
	int resultmatrix[10][10];
	char * current;

	int rowcount = 0;
	int colcount = 0;
	int temp = 0;
	int toput;

	while (fgets (buffer, 79 ,stdin) != NULL) {
		buffer[strlen(buffer)-1] = '\0';
		current = strtok(buffer, " ");
		while (current != NULL) {
			if (rowcount == 0) {
				colcount++;
			}
			sscanf(current, "%d", &toput);
			matrix[rowcount][temp] = toput;
			current = strtok(NULL, " ");
			temp++;
		}
		rowcount++;
		temp = 0;
	}
	int i;
	int j;
	for (i = 0; i < rowcount; i++) {
		for (j = 0; j < colcount; j++) {
			resultmatrix[j][i] = matrix[i][j];
		}
	}

	//print result
	for (i = 0; i < colcount; i++) {
		for (j = 0; j < rowcount; j++) {
			printf("%d ", resultmatrix[i][j]);
		}
		printf("\n");
	}

}
