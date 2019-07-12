#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

void manej(int s, siginfo_t *i, void *pa_na){printf("Entro manej\n");}
void *h(void *p);

sigset_t s; struct sigaction sa;

int main(void){
	int a,b,c,i,j;
	pthread_t hilo;
	
	sa.sa_flags=SA_SIGINFO;
	sa.sa_sigaction=manej; sigemptyset(&sa.sa_mask); sigaction(SIGALRM, &sa, NULL);
	sigemptyset(&s); sigaddset(&s, SIGALRM); sigprocmask(SIG_BLOCK,&s,NULL);
	alarm(3);
	pthread_create(&hilo, NULL, h, NULL);
	sigprocmask(SIG_UNBLOCK, &s, NULL);
	sleep(5);
}

void *h (void *p){
	sigwaitinfo(&s,NULL);
	printf("Hilo: llego senal aunque la mascara se desbloqueo tras crearme en main\n");
}