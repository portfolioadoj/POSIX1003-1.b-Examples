#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

int manej(int s, siginfo_t *info, void *pa_na){}
int main(int a1, char **a2){
	sigset_t s; struct sigaction sa;
	siginfo_t info;
	int res;
	
	sigemptyset(&s); sigaddset(&s, SIGALRM); sigprocmask(SIG_BLOCK, &s, NULL);
	sa.sa_flags=SA_SIGINFO; sa.sa_sigaction=manej; sigemptyset(&sa.sa_mask); 
	sigaction(SIGALRM, &sa,NULL);
	
	alarm(1);
	res=sigwaitinfo(&s, &info);
	printf("Recibido SIGALRM con %d\n",info.si_value.sival_int);
	return(9);
}