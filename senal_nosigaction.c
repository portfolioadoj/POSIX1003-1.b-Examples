#include <signal.h>
#include <stdio.h>

void manej(int a, siginfo_t *i, void *pa_na){}

int main(void){
	sigset_t s; struct sigaction sa; int d;
	
	sa.sa_flags=SA_SIGINFO;sa.sa_sigaction=manej;
	sigemptyset(&sa.sa_mask); sigaction(SIGRTMIN, &sa, NULL);
	sigemptyset(&s);
	sigaddset(&s, SIGALRM); sigaddset(&s, SIGRTMIN);
	sigprocmask(SIG_BLOCK, &s, NULL);
	
	alarm(1);
	d=sigwaitinfo(&s, NULL);
	if(d!=SIGALRM) printf("Rota espera\n");
	else printf("Llego alarma\n");
}