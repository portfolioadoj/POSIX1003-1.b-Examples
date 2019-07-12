#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PA 1234
#define PB 1235

struct sockaddr_in m1;
void f(int s){}
void g(int c, int j, int k){
	int n; sigset_t v; struct timespec t={0,0L};
	struct timespec t1={0,10000000L};
	int m; struct sigaction a; struct sockaddr_in b;
	a.sa_flags=0; a.sa_handler=f;
	sigemptyset(&a.sa_mask);
	sigaction(SIGALRM, &a, NULL);
	sigprocmask(SIG_UNBLOCK, &v, NULL);
	m=socket(AF_INET, SOCK_DGRAM, 0);
	memset(&b, 0, sizeof(b));
	b.sin_family=AF_INET;
	b.sin_port=htons(c+j);
	b.sin_addr.s_addr=INADDR_ANY;
	bind(m, (struct sockaddr *)&b, sizeof(b));
	t.tv_nsec=k*1000000L;
	t1.tv_nsec=t1.tv_nsec*j;
	nanosleep(&t1, NULL);
	do{
		n=nanosleep(&t, NULL);
		if(n!=-1){
			sendto(m, &j, sizeof(j), MSG_WAITALL, (struct sockaddr *)&m1, sizeof(m1));
			printf("%d: enviado %d\n", j, j);
		}
	} while(n!=-1);
}

int main(int a1, char **a2){
	int i, i1, j, n, ni, k=0, h, h1; pid_t *p; int m;
	memset((char *)&m1, 0, sizeof(m1));
	m1.sin_family=AF_INET;
	m1.sin_port=htons(PA);
	m1.sin_addr.s_addr=INADDR_ANY;
	m=socket(AF_INET, SOCK_DGRAM, 0);
	bind(m, (struct sockaddr *)&m1, sizeof(m1));
	h1=a1-2; p=(pid_t *)malloc(sizeof(pid_t)*h1);
	sscanf(a2[1], "%d", &n); printf("n: %d\n",n);
	for(i=2, i1=0; i<a1; i++, i1++){
		sscanf(a2[i], "%d", &ni);
		p[i1]=fork(); if(p[i1]==0){
			g(PB, i1, ni); exit(0);
		}
	}
	do{
		recv(m, &h, sizeof(j), 0);
		k=k+h; printf("h: %d k: %d\n", h, k);
	} while(k<n);
	for(i=0; i<a1-2; i++) kill(p[i], SIGALRM);
	return 0;
}