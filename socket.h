#ifndef SOCKET_SELF
#define SOCKET_SELF

#define check(a,b) if(-1 == a)\
    {\
        perror(b);\
        return a;\
    }

struct sock_space{
	int sockfd;
	char *space;
	int len;
};

int receive(struct sock_space * arg);
int sends(struct sock_space *arg);
#endif
