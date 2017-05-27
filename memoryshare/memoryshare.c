#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>  

#define PERM S_IRUSR | S_IWUSR 
int main(int argc ,char* argv[])
{	
	int shmid;
	char *p_addr;
	char *c_addr;
	if(argc!=2){
		printf("Usage:%s + string\n",argv[0]);
		return -1;
	}
	//1.create sharememory get fd
	shmid = shmget(IPC_PRIVATE, 1024, PERM);
	if(shmid==-1){
		printf("shmget error!\n");
		return -1;
	}
	if(fork()){
		//2.father process write data 
		p_addr = shmat(shmid,0,0);
		memset(p_addr,0,1024);
		strncpy(p_addr,argv[1],1024);
		wait(NULL);
		exit(0);
	}
	else{
		//3.child process read data
		sleep(2);
		c_addr = shmat(shmid,0,0);
		printf("child get data is :%s\n",c_addr);
		exit(0);
	}
	return 0;
}
