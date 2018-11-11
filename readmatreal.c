#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

key_t keya;
int shmBuf1id;
int (*shmptra)[10];

key_t keyb;
int shmBuf2id;
int (*shmptrb)[10];

key_t keyc;
int shmBuf3id;
int (*shmptrc)[10];

int mata[10][10];
int matb[10][10];
int arowcount = 0;
int acolcount = 0;
int browcount = 0;
int bcolcount = 0;

void createBuf1() {	
	char * argv[7];
	//will need more strids for other matrices
	char strida[20];
	char stridb[20];
	char stridc[20];
	pid_t pid;
	//making matrix a
	keya = ftok(".",'a');
	shmBuf1id = shmget(keya,sizeof(int[10][10]),IPC_CREAT|0666);
	if(shmBuf1id == -1 ) {  
		perror("shmget error");
		exit(1);
	}
	
	printf("Don't look! I'm shmatting\n");
	shmptra = shmat(shmBuf1id,0,0);
	if(shmptra == (void*) -1 ){  
		perror("shmat error");
		exit(1);
	}
	/*shmptra[0][0] = 1;
	printf("%d\n",shmptra[0][0]);
	printf("%p\n",shmptra); */

	//making space for matrix b
	keyb = ftok(".",5982);
	shmBuf2id = shmget(keyb,sizeof(int[10][10]),IPC_CREAT|0666);
	if(shmBuf2id == -1) {
		perror("shmget b error");
		exit(1);
	}
	shmptrb = shmat(shmBuf2id,0,0);
	if (shmptrb == (void*) -1) {
		perror("shmat b error");
		exit(1);
	}
	
	//making space for matrix c
	keyc = ftok(".",5983);
	shmBuf3id = shmget(keyc,sizeof(int[10][10]),IPC_CREAT|0666);
	if (shmBuf3id == -1) {
		perror("shmget c error");
		exit(1);
	}	
	shmptrc = shmat(shmBuf3id,0,0);
	if (shmptrc == (void*) -1) {
		perror("shmat c error");
		exit(1);
	}
	printf("all shmatting and shmgetting are successful.\n");
	
	//put matrices into shm areas

	//turning id's to strings for argument passing
	sprintf(strida, "%d", shmBuf1id);
	sprintf(stridb, "%d", shmBuf2id);
	sprintf(stridc, "%d", shmBuf3id);	
	
	/*
 * 	argv[0] = "./multiply";
 * 	argv[1] = strida;
 * 	argv[2] = stridb;
 * 	argv[3] = stridc;
 *	argv[6] = acolnum;
 * 	
 
	for (int i = 0; i < arownum; i++) {
		for (int j = 0; j < bcolnum; j++) {
			argv[4] = i;
			argv[5] = j;
		}
	}
	*/

	pid = fork();
	if (pid == 0) {
		printf("I'm a child. [0][0] is %d\n",shmptra[0][0]);
		//must exec and reconnect to memory
		//must pass shmBuf1id as parameter 
		argv[0] = "./multiply";
		argv[1] = strida;
		argv[2] = stridb;
		argv[3] = stridc;
		//argv[4] = i;
		//argv[5] = j;
		//argv[6] = acolnum;
		execvp("./multiply",argv);
		//printf("I'm supposedly running multiply with exec\n");
	}
	else wait(NULL);
	//for size of arrays, how big should they be initialized?
	//then read matrix c and print it out
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

	createBuf1();
	/*************************/
}