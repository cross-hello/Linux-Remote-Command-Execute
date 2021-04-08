#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#define pace_size 1024
/*#define check(a,b) if(a==-1)\
	{\
		perror(b);\
		return -1;\
		}
*/
#include"socket.h"
char cc=0;
int sends(struct sock_space * arg)
{
	int i;
	while(0==cc && 0!= strcmp("quit\n", arg->space))
	{
	//	fgets(
			fgets(arg->space, pace_size, stdin);
			i=send(arg->sockfd, arg->space, strlen(arg->space)+1, 0); 
			check(i,"send")
	}
	cc=1;
	close(arg->sockfd);
	printf("send channel close\n");
}

	

// ./clent server_ip server_port
int main(int N, char * COMMAND[])
{
	if(3 !=N)
	{
		printf(" %s server_ip server_port \n",COMMAND[0]);
		return 0;
	}
	int c=socket(AF_INET, SOCK_STREAM, 0);
	check(c,"socket:")
	struct sockaddr_in hi;
	hi.sin_family=AF_INET;
	hi.sin_port=htons(atoi(COMMAND[2]));
	hi.sin_addr.s_addr=inet_addr(COMMAND[1]);
	memset(hi.sin_zero, 0, sizeof hi.sin_zero);
	int i=0;
	i=connect(c,(struct sockaddr *)&hi, sizeof hi);
	check(i,"connect:")
	char recv_space[pace_size], send_space[pace_size];
	struct sock_space sds;
	sds.sockfd=c;
	sds.space=send_space;
	sds.len=sizeof send_space;
	long int tid;
	pthread_create(&tid,NULL,(void *(*)(void *)) sends, &sds);
	//int i=fork();
	//char cc=0;
	//i=fork();
	//if(!i)
	//{
		//while(0 != strcmp("quit", recv_space))
		//printf("I try to accept:\n");
		while(0==cc &&0 != strcmp("quit\n", recv_space))
		{
			i=recv(c, recv_space, pace_size, 0);
			//i=recv(c, recv_space, pace_size, MSG_PEEK);
			//if(0== i)
			//	break;
			check(i,"recv")
			//puts(recv_space);
			//printf("i=%d\n",i);
			//printf("client: %s",recv_space);
			//puts(recv_space);
			printf("%s",recv_space);
		}
		//cc=1;
		//printf("I finished T _ T  \n");
		if (0==c)
		close(c);
		printf("client socket closed\n");
		return 0;
/*	}
	else
	{
		while(0==cc &&0!=strcmp("quit\n", send_space))
		{
			fgets(send_space, pace_size, stdin);
			//int d=strlen(send_space)+1;
			//send(c, send_space, strlen(send_space)+1, 0); 
			//i=send(c, send_space, d, 0); 
			i=send(c, send_space, strlen(send_space)+1, 0); 
			check(i,"send")
			//printf("Send %d bytes\n",d); 
		}
		cc=1;
	}
	
	return 0;
	*/
}
