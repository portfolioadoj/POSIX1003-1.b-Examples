#include <stdlib.h>
#include <signal.h>

void manej(int s, siginfo_t *i, void *pa_na){printf("Entra manej\n");}
void *f (void *p){
	sleep(1);
	kill(getpid(), SIGRTMIN);
}
int main(void){
	sigset_t s1, s2; struct sigaction sa; int i; pthread_t h;
	
	sa.sa_flags=SA_SIGINFO; sa.sa_sigaction=manej;
	sigemptyset(&sa.sa_mask); sigaction(SIGRTMIN, &sa, NULL);
	
	sigemptyset(&s1); sigaddset(&s1, SIGRTMIN); sigprocmask(SIG_UNBLOCK, &s1, NULL);
//	sigemptyset(&s1); sigaddset(&s1, SIGRTMIN); sigprocmask(SIG_BLOCK, &s1, NULL);

	sigemptyset(&s2); sigaddset(&s2, SIGALRM); sigprocmask(SIG_BLOCK, &s2, NULL);
	//alarm(1);
	pthread_create(&h, NULL, f, NULL);
	i=sigwaitinfo(&s2, NULL);
	if(i==-1) printf("Error\n");
	else {
		printf("Llego senal\n");
	}
}