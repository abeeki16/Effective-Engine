#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char * argv[]) {
	//turn argv[1] back to a pointer again
	int (*shmpointera)[10];
	int (*shmpointerb)[10];
	int (*shmpointerc)[10];
	int shmida,shmidb,shmidc;
	int arowind, bcolind, acolnum;
	int sum = 0;
	//acolnum is equal to brownum

	//strcpy(buffer,argv[1]);
	//printf("exec: argv0 is %s, argv1 is %s\n",argv[0],argv[1]);
	
	//turn args into ints for shmatting
	sscanf(argv[1], "%d", &shmida);
	sscanf(argv[2], "%d", &shmidb);
	sscanf(argv[3], "%d", &shmidc);
	printf("exec: shmids are %d %d %d\n", shmida, shmidb, shmidc);

	//initialize pointers
	shmpointera = shmat(shmida, 0, 0);
	shmpointerb = shmat(shmidb, 0, 0);
	shmpointerc = shmat(shmidc, 0, 0,);

	
	
	printf("pointer is %p\n",shmpointera);
	printf("Hi! I'm exec. [0][0] is %d\n",shmpointera[0][0]);
	exit(EXIT_SUCCESS);
}
