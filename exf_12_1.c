#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int a;
void m(int s, siginfo_t *p, void *p1){
	a+=(s-SIGRTMIN);
}

void f(int i, int n){
	struct timespec t={0,500000000L};
	while(n--){
		kill(getppid(),SIGRTMIN+i);
		nanosleep(&t,NULL);
	}
	exit(0);
}

int main(int b, char **c){
	int i,k,n; pid_t p;
	sigset_t v1; struct sigaction s;
	s.sa_sigaction=m;
	s.sa_flags=SA_SIGINFO;
	sigemptyset(&s.sa_mask);
	for(i=0;i<b;i++){
		sigemptyset(&v1);sigaddset(&v1,SIGRTMIN+i);
		sigaction(SIGRTMIN+i, &s, NULL);
	}
	sigprocmask(SIG_UNBLOCK,&v1, NULL);
	for(i=1;i<b;i++){	
		sscanf(c[i],"%d",&n);
		p=fork(); if(p==0) f(i,n);
	}
	for(i=1;i<b;i++){
		while(wait(&k)==-1);
	}
	printf("valor %d \n",a);
	return 0;
}