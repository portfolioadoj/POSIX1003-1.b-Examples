#include <stdio.h>
#include <time.h>
#include <signal.h>

pid_t *p1; int *a; int n; int c=0;
void f1(int s1, siginfo_t *s2, void *s3){
	int i;
	i=s2->si_value.sival_int;
	while(i!=0){
		c++; i--; if(c==n) c=0;
	}
	if(a[c]!=0) a[c]--;
	if(a[c]==0) kill(p1[c],SIGINT);
}
int f2(int i){
	timer_t t; sigset_t s; siginfo_t v;
	struct timespec x={5,0};
	struct timespec z={0,0};
	struct itimerspec y;
	x.tv_sec+=i;
	y.it_value=x; y.it_interval=z;
	timer_create (CLOCK_REALTIME, NULL, &t);
	sigemptyset(&s); sigaddset(&s,SIGALRM);
	sigaddset(&s,SIGINT);
	sigprocmask(SIG_BLOCK, &s, NULL);
	timer_settime(t,0,&y,NULL);
	exit(i);
}

int main(int a1, char **a2){