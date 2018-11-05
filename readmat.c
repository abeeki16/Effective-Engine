#include <stdio.h>
#include <strings.h>

int multiply(int [] arow, int [] bcol) {
	//get the number of elements in each array
	int n = sizeof(arow)/sizeof(arow[0]);
	int result = 0;
	for (int i = 0; i < n; i++) {
		result += arow[i] * bcol[i];
	}
	return result;
}

int main(int argc, char * argv[]) {
	char temp[50];
	const char s[2] = " ";
	char * token;
	int curnum;
	//if state == 0 then it's still at matrix A
	//else it starts incrementing the counters for B
	int state = 0;
	int arowcount = 0;
	int acolcount = 0;
	int browcount = 0;
	int bcolcount = 0;

	gets(temp);
	//check for separating blank line between A & B
	if (temp == "\n") state = 1;
	token = strtok(temp,s);
	while (token != NULL) {
		sscanf(token, "%d", &curnum);
		printf("%d\n",curnum);
		token = strtok(NULL, s);
		//must store vals in lists
		if (state == 0) {
			arowcount++;
			acolcount++;
		}
		else if (state == 1) {
			browcount++;
			bcolcount++;
		}
	}	
	if (acolcount != browcount) printf("invalid matrices\n");

	/* 
	while (gets(temp) != NULL) {
		token = strtok(temp, s);
		while (token != NULL) {
			sscanf(token, "%d", &curnum);
			printf("%d\n",curnum);
		}		
	}
	*/
}