#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>   

#define msgkey 0x11000001      


int main(int argc ,char *argv[])
{	
	int msgid;
	int ret;
	
	struct msg_buf
	{
		int mytype;
		char data[255];
	}send_buf,recv_buf;
	
	//1.create messagequeue and get messagequeue id
 	msgid = msgget(IPC_PRIVATE,0700);
	if(msgid ==-1){
		printf("create error!\n");
		return -1;
	}
	if(!fork()){
	//child receive data
		sleep(2);
		ret = msgrcv(msgid,&recv_buf,sizeof(recv_buf.data),1,IPC_NOWAIT);
		if(ret ==-1){
			printf("recv message error!\n");
			return -1;
		}
		printf("child recv message sucess! message is : %s\n",recv_buf.data);
		ret =msgctl(msgid,IPC_RMID,NULL);
		if(ret ==-1){
			printf("del messagequeue error!\n");
			return -1;
		}
		exit(0);
	}
	else{
	//father send data
		send_buf.mytype = 1;
		strcpy(send_buf.data,"this is a test , trans data to child!");
		ret = msgsnd(msgid,&send_buf,sizeof(send_buf.data),IPC_NOWAIT);
		if(ret ==-1){
			printf("send message error!\n");
			return -1;
		}
		printf("father send message sucess!\n");
		wait(NULL);
		exit(0);
	}	
	return 0;
}

