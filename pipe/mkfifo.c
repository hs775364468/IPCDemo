#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define FIFO "/tmp/myfifo"

int main(int argc ,char *argv[])
{	
	int fd;
	char *write_buffer =malloc(100);
	write_buffer ="transfer data";
	char *read_buffer=malloc(100);
	
	if(mkfifo(FIFO,O_CREAT|O_EXCL)!=0){
		printf("mkfifo create error!\n");
	}
	fd =open(FIFO,O_RDWR|O_NONBLOCK,0);
	if(fd ==-1){
		printf("open error!\n");
	}
	if(!fork()){
		//child process
		if(write(fd,write_buffer,100)!=-1){
			printf("child write success!\n");
		}
		else{
			printf("child write failed!\n");
		}
		exit(0);
	}
	else{
		//father process
		wait(NULL);
		if(read(fd,read_buffer,100)!=-1){
			printf("parent read success!\n");
		}
		printf("the data from child is :%s\n",read_buffer);
		unlink(FIFO);
		exit(0);
	}
	return 0;
}

