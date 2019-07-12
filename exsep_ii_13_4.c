#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N 5
pthread_t h[N]; sigset_t b;
void f1(int a, siginfo_t *b, void *c){}
void *f(void *p){
	int k=(int)p;
	struct timespec u={0,500000000L};
	if(k>0) pthread_join(h[k-1],NULL);
	printf("k vale %d\n",k);
	nanosleep(&u,NULL);
	return NULL;
}
void *f2(void *p){
	siginfo_t v; int k;
	while(1){
		k=sigwaitinfo(&b,&v);
		pthread_cancel(h[k-SIGRTMIN]);
	}
}
int main(int p1, char **p2){
	int i; struct sigaction c; pthread_t h1;
	sigemptyset(&b);
	c.sa_sigaction=f1; sigemptyset(&c.sa_mask);
	c.sa_flags=SA_SIGINFO;
	for (i=SIGRTMIN; i<SIGRTMAX;i++) {
		sigaddset(&b,i);
		sigaction(i,&c,NULL);
	}
	sigprocmask(SIG_BLOCK, &b, NULL);
	for (i=0;i<N;i++){
		pthread_create(&h[i],NULL,f,(void *)i);
	}
	pthread_create(&h1,NULL,f2,NULL);
	pthread_join(h[N-1],NULL);
	return 0;
}