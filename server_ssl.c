#include<sys/types.h>
#include<sys/socket.h>
//for the header file of perror
#include<stdio.h>
#include<errno.h>
// for the header files of atoi
#include<stdlib.h>
// for header file of inet_top
#include<arpa/inet.h>
// for header file of memset
#include<string.h>
// for header file of close
#include<unistd.h>
//#include<sys/types.h>
//#include<sys/stat.h>
#include<fcntl.h>
//void set_sockaddr(struct sockaddr_in *modification,int sin_family, const char* local_port, long   )
/*
inline int check(int * record, char * str);
int check(int * record, char *str)
{
	if( -1 == * record)
	{
		perror(str);
		return -1;
	}
}
*/
/*
#define check(a,b) if(-1 == a)\
	{\
		perror(b);\
		return a;\
	}
*/
#include"socket.h"
#include<pthread.h>
char cc=0;
/*struct {
	int sockfd;

};
*/
int receive(struct sock_space * arg)
{	
	int i;
	int back_stdout=dup(fileno(stdout)) ,back_err=dup(fileno(stderr));
	//printf("stdout(%d)-->%d, stderr(%d)-->%d \n",fileno(stdout),back_stdout, fileno(stderr), back_err);
	int f;
	while(0==cc &&0!=strcmp("quit\n",arg->space))
	{
		i=recv(arg->sockfd,arg->space, arg->len, 0);
		check(i,"recv")
		//f=open(".tmp",O_WRONLY|O_CREAT,0600);
		f=open(".tmp",O_WRONLY|O_CREAT|O_TRUNC,0600);

		check(f,"file");
		//printf("server: %s",arg->space);
		//strcpy(arg->space+sizeof(arg->space)," >tmp");
		dup2(f,fileno(stdout));
		dup2(f,fileno(stderr));
		system(arg->space);
		fflush(stderr);
		fflush(stdout);
		dup2(back_stdout,fileno(stdout));
		//dup2(back_stderr,fileno(stderr));
		dup2(back_err,fileno(stderr));
		close(f);
		f=open(".tmp",O_RDONLY);
		//int f=open("tmp",'rb');
		//int f=open("tmp",O_RDONLY);
	//	check(f,"file");
		i=read(f,arg->space,1024);
		//printf("read %d characters\n",i);
//		i=read(1,arg->space,1024);
		check(i,"read");
		close(f);
		arg->space[i]='\0';
//		send(arg->sockfd,arg->space,strlen(arg-,0);
		send(arg->sockfd,arg->space,i+1,0);
	}
	close(arg->sockfd);
	printf("server cocket closed\n");
	cc=1;
	//if(cc)
	//cc=0;
	//else
	//cc=1;
}
// ./server local_port
int main(int N, char *COMMAND[])
{
	if ( 2>N)
	{
		printf("%s local_host_port \n",COMMAND[0]);
		return 0;
	}
	char ipstr[INET_ADDRSTRLEN];
	int s=socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == s)
	{
		//ferror("socket:");
		perror("socket:");
		return s;
	}
	struct sockaddr_in hi;
	hi.sin_family=AF_INET;
	hi.sin_port=htons(atoi(COMMAND[1]));
	hi.sin_addr.s_addr=htonl(INADDR_ANY);
	memset(hi.sin_zero,0, sizeof hi.sin_zero);
	int status=bind(s,(struct sockaddr*)&hi,sizeof hi);
	if (-1 == status)
	{
		perror("bind:");
		return -1;
	}
	status=listen(s, (unsigned int)-1);
	//check(&status, "listen:");
	// test inline function
	//status=-1;
	//check(&status, "listen:");
	check(status, "listen:")
	struct sockaddr_in client;
	int size_client=sizeof client;
	//simplify before 
	//int c[1024];
	//int c_top=0;
	//int c;
	//int i;
	int c,i;
	char recv_space[1024], send_space[1024];
//	*recv_space=*send_space='\0';
	//while(1)
	char r='n';
	//struct sock_space recvs, sends;
	struct sock_space recvs;
	recvs.space=recv_space;
	recvs.len=sizeof(recv_space);
	unsigned long thread_id;
//	while(getchar()!='q')
	while(r!='q')
	{
		cc=0;
		*recv_space=*send_space='\0';
		//c[c_top]=accept(s, &client, &size_client);
		c=accept(s,(struct sockaddr *) &client, &size_client);
		//check(c[c_top],"accept:")
		check(c,"accept:")
		inet_ntop(client.sin_family,&(client.sin_addr), ipstr, sizeof ipstr);
		printf("Connect %s:%d \n",ipstr, ntohs(client.sin_port));
		//i=fork();
		recvs.sockfd=c;
		//pthread_create(NULL,NULL,(void *()(void *))receive,&recvs);
		//pthread_create(NULL,NULL,(void *(*)(void *))receive,&recvs);
		pthread_create(&thread_id,NULL,(void *(*)(void *))receive,&recvs);
		/*
		if(i)
		{
			//while(0 != strcmp("quit",recv_space))
			while(0 != strcmp("quit\n",recv_space))
			{
				i=recv(c, recv_space, sizeof recv_space,0);
				check(i,"recv:")
				//printf("\nReceving %d bytes\n",i);
				//printf("%-80s\n",recv_space);
				printf("server: %s",recv_space);
				//printf("%80s",recv_space);
				//printf("%s",recv_space);
			}
			close(c);
			//return 0;
			break;
		}
		else
		{
		*/
			//printf("I pass here\n");
			//while(0!=strcmp("quit\n", send_space))
			/*
			while(0==cc && 0!=strcmp("quit\n", send_space))
			{
				//puts("I am here");
				//i=fgets(send_space, sizeof send_space, stdio);
				//i=fgets(send_space, sizeof send_space, stdin);
				//fgets(send_space, sizeof send_space, stdin);
			//	printf("stdin=%d\n",stdin);
				fgets(send_space, sizeof send_space, stdin);
				//puts("I am here =  —— =");
				//puts(send_space);
				//send(s,send_space, sizeof send_space, 0);
				//send(s,send_space,i, 0);
				i=send(c,send_space,strlen(send_space)+1, 0);
				//check(i,"send")
			}
			*/
			while(c)
			system("sleep 5");
			printf("send channel close\n");
			//cc=1;
		//	if(cc)
		//	cc=0;
		//	else
		//	cc=1;

		//}
		//close(c);
	/*	r=getchar();
		while(getchar()!='\n')
			continue;
*/
	}

	//inet_ntop(AF_INET, &hi.sin_addr, ipstr, sizeof ipstr);
	//printf("Setting server %s:%d \n", ipstr, ntohs(hi.sin_port));
	cc=close(c);
	//check(cc,"close")
	close(s);
	puts("Socket close");
	return 0;
	
}
