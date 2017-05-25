#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc ,char *argv[])
{
	int pipefd[2];
	int ret;
	char *write_buffer =malloc(100);
	write_buffer ="transfer data";
	char *read_buffer=malloc(100);
	ret =pipe(pipefd);
	if(ret!=0){
		printf("pipe error!\n");
	}
	else{
		printf("pipe success!\n");
	}
	if(!fork()){
		//child process
		close(pipefd[0]);
		if(write(pipefd[1],write_buffer,100)!=-1){
			printf("child write success!\n");
		}
		exit(0);
	}
	else{
		//father process
		wait(NULL);
		if(read(pipefd[0],read_buffer,100)!=-1){
			printf("parent read success!\n");
		}
		printf("the data from child is :%s\n",read_buffer);
		exit(0);
	}
	return 0;
}
