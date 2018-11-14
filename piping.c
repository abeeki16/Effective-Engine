#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {
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
    	exec("./toexec", (char *) NULL);
    }

    //parent
    else if (cpid > 0) {  
    	wait(NULL);
    	close(pipefd[1]);  
    	dup2(pipefd[0], 0);
    	close(pipefd[0]);
    	//change stdin to pipfd read end
    	exec("./toexec2", (char *) NULL);
    }
}