#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char * argv[]) {
	//turn argv[1] back to a pointer again
	int (*shmpointer)[9];
	sscanf(argv[1], "%p", shmpointer);
	printf("Hi! I'm exec. [0][0] is %d\n",shmpointer[0][0]);
}