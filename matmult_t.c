#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <ucontext.h>

int mata[10][10];
int matb[10][10];
int resultant[10][10];
int arowcount = 0;
int acolcount = 0;
int browcount = 0;
int bcolcount = 0;
char * argv[8];
int status = 0;

static ucontext_t *uc;
static ucontext_t uc_main;
char **st;
char st1[8192];


void my_thr_create(void (*func) (int),int thr_id) {
	
	getcontext(&uc[thr_id]);
	if (thr_id==(arowcount*bcolcount)-1) {
		uc[thr_id].uc_link = &uc_main;
	} else {
		uc[thr_id].uc_link = &uc[thr_id+1];

	}
	//uc[thr_id].uc_link = &uc[(thr_id+1)%(arowcount*bcolcount)];
	uc[thr_id].uc_stack.ss_sp = st[thr_id];
	uc[thr_id].uc_stack.ss_size = sizeof st1;
	makecontext (&uc[thr_id],func,1,thr_id);
}

/*

*/
void multiplier(int id) {
	int x = id/bcolcount;
	int y = id%bcolcount;
	printf("%s %d","Thread id",id);
	printf("\n");
	int i;
	int sum = 0;
	for (i = 0; i < acolcount; i++) {
		sum += mata[x][i]*matb[i][y];	
	} 
	resultant[x][y] = sum;
	
	/*if (id<(arowcount*bcolcount)-1){
		setcontext(&uc[id+1]);
	}else {
		setcontext(&uc_main);
	}*/
}

void createBuf1() {	
	//char * argv[7];
	//will need more strids for other matrices
	
	int i;
	st = malloc((arowcount*bcolcount)*sizeof(char));;
	for (i=0;i<arowcount*bcolcount;i++) {
		st[i]  = (char *)malloc(8192 * sizeof(char));
	}
	pid_t pid;
	pid_t wpid;
	char stracol[20];
	char targetrow[20];
	char targetcol[20];
	
	uc = (ucontext_t *)malloc(sizeof(ucontext_t)*(arowcount*bcolcount));
	printf("all shmatting and shmgetting are successful.\n");
	//put matrices into shm areas
	int j;
	void (*funcPointer) (int) = &multiplier;
	for (i = 0; i < (arowcount*bcolcount); i++) {
		my_thr_create((*funcPointer),i);
	}
	
	getcontext(&uc_main);
	//swapcontext(&uc_main,&uc[0]);
	swapcontext(&uc_main,&uc[0]);
	
	for (i = 0; i < arowcount; i++) {
		for (j = 0; j < bcolcount; j++) {
			printf("%d ",resultant[i][j]);
		}
		printf("\n");
	}
	

}

int main (void) {
	char buffer [80];
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
		//	printf("%s",current);
			current = strtok(NULL, " ");
			temp++;
		}
		//printf("\n");
		if (state == 0) arowcount++;
		else if (state == 1) browcount++;
		temp = 0;
	}/*
	printf("arow = %d", arowcount);
	printf("acol = %d", acolcount);
	printf("brow = %d", browcount);
	printf("bcol = %d\n", bcolcount);*/
	if (acolcount != browcount) printf("invalid matrices\n");
	int i;
	int j;
	//print matrix a
	/*for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			printf("%d ",mata[i][j]);
		}
		printf("\n");
	}*/

	createBuf1();
	/*************************/
}
