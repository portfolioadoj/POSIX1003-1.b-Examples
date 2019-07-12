#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define P 11000
int z=0;
void f(int a) {z=1;}
void f1(int i, struct sockaddr_in a, int k){
	struct timespec t={0,0};
	int c; struct sockaddr_in a1;
	t.tv_nsec=k*300000000;
	a1=a; a1.sin_port=0;
	c=socket(AF_INET, SOCK_DGRAM, 0);
	bind(c, (struct sockaddr *)&a1, sizeof(a1));
	while(z==0){
		nanosleep(&t, NULL);
		sendto(c,&i, sizeof(i),0, (struct sockaddr *)&a, sizeof(a));
	}
	printf("mensaje %d\n",i);
	exit(0);
}

int main(int a, char **b){
	struct sockaddr_in m;
	int i, j, d, s, n, x, k; pid_t *p;
	sigset_t t; struct sigaction sa;
	p=malloc(sizeof(pid_t)*(a-1));
	sigemptyset(&t); sigaddset(&t,SIGALRM);
	sigprocmask(SIG_UNBLOCK, &t, NULL);
	sa.sa_flags=0; sa.sa_handler=f;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGALRM, &sa, NULL);
	s=socket(AF_INET, SOCK_DGRAM,0);
	memset((char *)&m, 0, sizeof(m));
	m.sin_family=AF_INET; m.sin_port=htons(P);
	m.sin_addr.s_addr=INADDR_ANY;
	bind(s, (struct sockaddr *)&m, sizeof(m));
	for(i=1, k=0; i<a; i++){
		sscanf(b[i], "%d",&j);
		p[i-1]=fork();if(p[i-1]==0) f1(i,m,j);
		if(k<j) k=j;
	}
	alarm(k); x=0;
	while(z==0){
		if(recv(s, &d, sizeof(d), 0)!=-1) x=x+d;
	}
	for(i=0;i<a-1;i++) kill(p[i],SIGALRM);
	printf("x: %d\n",x);
	return 0;
}