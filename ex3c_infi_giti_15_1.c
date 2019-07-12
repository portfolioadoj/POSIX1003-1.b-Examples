#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

sigset_t s; pid_t p;
void m(int s, siginfo_t *p1, void *p2) {}
void f(int n);

int main( int a, char **b){
	pid_t p1; siginfo_t v; union sigval v1; int i;
	struct sigaction c; int d1=5, d2=2;
	struct timespec t;
	c.sa_sigaction=m;
	c.sa_flags=SA_SIGINFO;
	sigemptyset(&c.sa_mask);
	sigaction(SIGRTMIN, &c, NULL);
	sigemptyset(&s); sigaddset(&s, SIGRTMIN);
	sigprocmask(SIG_BLOCK,&s, NULL);
	if(a>=2) sscanf(b[1], "%d",&d1);
	if(a>=3) sscanf(b[2], "%d",&d2);
	p=getpid();
	p1=fork(); if(p1==0) f(d1);
	t.tv_sec=d2; t.tv_nsec=0;
	nanosleep(&t,NULL);
	sigwaitinfo(&s,&v); v1.sival_int=d2;
	sigqueue((pid_t)(v.si_value.sival_int),SIGRTMIN, v1);
	wait(&i);
	printf("Valor %d\n",WEXITSTATUS(i));
	return(0);
}

void f(int n){
	pid_t p1; int i; union sigval v; siginfo_t v1;
	struct timespec t;
	printf("f con %d\n",n);
	t.tv_sec=0; t.tv_nsec=n*100000000L;
	nanosleep(&t,NULL);
	n=n-1; if(n!=0){
		p1=fork(); if(p1==0) f(n);
		wait(&i); i=WEXITSTATUS(i); i=i*n;
		exit(i);
	} else {
		v.sival_int = (int)getpid();
		sigqueue(p,SIGRTMIN,v);
		sigwaitinfo(&s,&v1);
		exit(v1.si_value.sival_int);
	}
}