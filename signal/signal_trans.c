#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc ,char *argv[])
{
	pid_t pid;
	int status;
	
	if(!(pid =fork())){
		//child process
		printf("this is child!\n");
		sleep(10);
		return;
	}
	else{
		//parent process
		printf("send to child %d\n",pid);
		sleep(1);
		kill(pid ,SIGABRT);
		wait(&status);
		if(WIFSIGNALED(status)){
			printf("child receive signal:%d\n",WTERMSIG(status));
		}	
	}
	return 0;
}
