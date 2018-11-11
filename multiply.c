#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char * argv[]) {
	//turn argv[1] back to a pointer again
	int (*shmpointer)[9];
	char buffer[20];
	int shmid;
	
	strcpy(buffer,argv[1]);

	printf("exec: argv0 is %s, argv1 is %s\n",argv[0],argv[1]);
	sscanf(buffer, "%d", &shmid);	
	printf("exec: shmid is %d\n", shmid);
	shmpointer = shmat(shmid, 0, 0);
	
	printf("pointer is %p\n",shmpointer);
	printf("Hi! I'm exec. [0][0] is %d\n",shmpointer[0][0]);
}
