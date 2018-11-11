#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

key_t key;
int shmBuf1id;
int (*shmptr)[9];

void createBuf1() {	
	char * argv[2];
	char strid[20];
	pid_t pid;
	key = ftok(".",'b');
	shmBuf1id = shmget(key,sizeof(int[9][9]),IPC_CREAT|0666);
	if(shmBuf1id == -1 ) {  
		perror("shmget error");
		exit(1);
	}
	printf("Don't look! I'm shmatting\n");

	shmptr = shmat(shmBuf1id,0,0);
	if(shmptr == (void*) -1 ){  
		perror("shmat error");
		exit(1);
	}
	shmptr[0][0] = 1;
	printf("%d\n",shmptr[0][0]);
	printf("%p\n",shmptr);
	sprintf(strid, "%d", shmBuf1id);
	pid = fork();
	if (pid == 0) {
		printf("I'm a child. [0][0] is %d\n",shmptr[0][0]);
		//must exec and reconnect to memory
		//must pass shmBuf1id as parameter 
		argv[0] = "./multiply";
		argv[1] = strid;
		execvp("./multiply",argv);
		//printf("I'm supposedly running multiply with exec\n");
	}
	else wait(NULL);
	//for size of arrays, how big should they be initialized?

}

int main(int argc, int *argv[]) {
	createBuf1();
	return 0; 
}
