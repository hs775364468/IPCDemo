#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define msgkey 0x11000001      

struct msg_buf
{
	int mytype;
	char data[255];
};

int main(int argc ,char *argv[])
{	
	int msgid;
	int ret;
	
	struct msg_buf msgbuf;
	
	//1.get messagequeue fd
 	msgid = msgget(msgkey, 0666|IPC_CREAT);
	if(msgid ==-1){
		printf("create error!\n");
		return -1;
	}
	msgbuf.mytype = getpid();
	strcpy(msgbuf.data,"this is a test!");
	
	//2.use msgsnd or msgrcv
    ret = msgsnd(msgid,&msgbuf,sizeof(msgbuf.data),IPC_NOWAIT);
	if(ret ==-1){
		printf("send message error!\n");
		return -1;
	}
	memset(&msgbuf,0,sizeof(msgbuf));
	
	ret = msgrcv(msgid,&msgbuf,sizeof(msgbuf.data),getpid(),IPC_NOWAIT);
	if(ret ==-1){
		printf("recv message error!\n");
		return -1;
	}
	printf("recv mesg :%s\n",msgbuf.data);
	//3.use msgctl delete mq
	ret =msgctl(msgid,IPC_RMID,NULL);
	if(ret ==-1){
		printf("del messagequeue error!\n");
		return -1;
	}
	return 0;
}
