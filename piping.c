#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {
	char input[80];
	char * current;	
	printf("myshell> ");
	char * reverser[20];
	int revpointer = 0;
	//char * reversed[20];
	//int tempcounter = 0;

	fgets(input,80,stdin);
	input[strlen(input)-1] = '\0';
	current = strtok(input,"|");
	
	while (current != NULL) {
		//subparser(current);
		//printf("%s\n",current);
		//TODO: make fork here. if current process is parent, skip the call to subparser.
		reverser[revpointer] = current;
		revpointer++;
		current = strtok(NULL,"|");
	}
	for (int i = revpointer-1; i >= 0; i--) {
		printf("%s\n",reverser[i]);
		//reversed[tempcounter] = reverser[i];
		//tempcounter++;
	}

	/************************** pipeshell ends here *************************************************/

	int pipefd[2]; // pipefd[0]: read endpoint, pipefd[1]: write endpoint
    pid_t cpid;
    char buf;

    if (pipe(pipefd) == -1) {
       printf("An error occured creating the pipe\n");
       return 0;
    }

    cpid = fork();
    //child
    if (cpid == 0) {
    	dup2(pipefd[1], 1);
    	//change stdout to pipefd write end
    	exec("reverser[revpointer-1]", (char *) NULL);
    }

    //parent
    else if (cpid > 0) {  
    	wait(NULL);
    	close(pipefd[1]);  
    	dup2(pipefd[0], 0);
    	close(pipefd[0]);
    	//change stdin to pipfd read end
    	exec("reverser[revpointer]", (char *) NULL);
    }
}