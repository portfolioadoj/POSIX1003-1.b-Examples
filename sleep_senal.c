#include <stdio.h>
#include <signal.h>
#include <time.h>

void manej (int s, siginfo_t *info, void *pa_na){printf("Entro manej\n");}

int main(void){
	sigset_t s; struct sigaction sa; int a; struct timespec t={10,0};
	
	sa.sa_flags=SA_SIGINFO; sa.sa_sigaction=manej;
	sigemptyset(&sa.sa_mask); sigaction(SIGALRM,&sa, NULL);
	sigemptyset(&s); sigaddset(&s, SIGALRM); sigprocmask(SIG_BLOCK, &s, NULL);
	
	alarm(3);
	//sleep(10);
	//nanosleep(&t,NULL);
	sigwaitinfo(&s,NULL);
//	sigwaitinfo(&s, NULL);
	printf("Alarma llego\n");
	printf("Si pongo alarma y sleep, al llegar SIGALRM no rompo (nano)sleep\n");
}