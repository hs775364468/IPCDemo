#include <unistd.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#define PATH "a.socket"

int main(int argc ,char *argv[])
{
	int socket_fd;
	int len;
	struct sockaddr_un addr;

	bzero(&addr ,sizeof(struct sockaddr_un));
	addr.sun_family =AF_UNIX;
	strcpy(addr.sun_path,PATH);
	len =strlen(addr.sun_path)+sizeof(addr.sun_family);

	if(!fork()){
		int counter =0;
		char send_buffer[10]={'t','e','s','t'};
		printf("sendbuffer is :%s\n",send_buffer);
		//child process
		socket_fd = socket(AF_UNIX,SOCK_DGRAM,0);
		if(socket_fd<0){
			printf("client socket error!\n");
			return -1;
		}
		while(1)
		{
			//memset(send_buffer,0,10);
			printf("send_buffer message %d time\n",counter);
			counter++;
			//send message
		    sendto(socket_fd, send_buffer, strlen(send_buffer), 0,(struct sockaddr *)&addr,len);
			printf("sendbuffer is :%s\n",send_buffer);
			sleep(1);
		}
		
	
	}
	else{
		//father process
		char recv_buffer[10];
		
		socket_fd = socket(AF_UNIX,SOCK_DGRAM,0);
		if(socket_fd<0){
			printf("server socket error!\n");
			return -1;
		}
		unlink(PATH);
		if(bind(socket_fd,(struct sockaddr *)&addr,len)<0){
			printf("bind error!\n");
			return -1;
		}
		while(1)
		{
			memset(recv_buffer,0,10);

			recvfrom(socket_fd, recv_buffer,10,0,NULL,NULL);
			printf("recvbuffer is :%s\n",recv_buffer);

		}
	}
	return 0;
}
