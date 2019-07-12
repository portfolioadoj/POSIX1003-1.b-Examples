#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

sigset_t s;

void f(pid_t a,int d){
	siginfo_t b; union sigval c; int j;
	sigwaitinfo(&s,&b);
	d=d+b.si_value.sival_int;
	c.sival_int=d;
	sigqueue(a,SIGRTMIN,c);
}

void h(int s, siginfo_t *i, void *p) {}

int main(int a1, char **a2)
{
	pid_t *b; int i; int d;
	union sigval v; siginfo_t x;
	struct sigaction sa;
	sa.sa_flags=SA_SIGINFO;
	sa.sa_sigaction=h;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN,&sa,NULL);
	sigemptyset(&s); sigaddset(&s,SIGRTMIN);
	sigprocmask(SIG_BLOCK,&s,NULL);
	b=malloc(a1*sizeof(pid_t));
	b[0]=getpid();
	for(i=1;i<a1;i++){
		b[i]=fork();
		if(!b[i]){
			sscanf(a2[i],"%d",&d);
			f(b[i-1],d);exit(0);
		}
	}
	v.sival_int=0;
	sigqueue(b[a1-1],SIGRTMIN,v);
	sigwaitinfo(&s,&x);
	printf("%d\n",x.si_value.sival_int);
}

