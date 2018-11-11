#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>

int main(void) {
	int i, j; // loop counters
	int tostore[10] = {1,2,3,4,5,6,7,8,9,0};
	int * shm_ptr;

	key_t key = ftok("shmfile",65); 
	int shmid = shmget(key,11*sizeof(int),0666|IPC_CREAT);
	if (shm_id < 0) {
		printf("shmget error\n");
		exit(1);
	}
	shm_ptr = (int *) shmat(shm_id, NULL, 0);

	for(i=0;i<2; i++) {
    	for(j=0; j<5; j++) {
            	ptr[i][j] = i+j;
    	}
	}
	printf("%d\n",shm_ptr[0]);

}