#include <stdio.h>
#include <pthread.h>
#include <signal.h>

void  m(int sig){}
void *f(void *p);

void main (int a1, char **a2){
	int a=0,b=0,i=0;
	pthread_t h;
	sigset_t s; struct sigaction acc;
	
	//preparo para no tiempo real
	acc.sa_flags=0;
	acc.sa_handler=m;
	sigemptyset(&acc.sa_mask);
	sigaction(SIGRTMIN, &acc, NULL);
	sigaction(SIGRTMIN+1, &acc, NULL);
	
	sigemptyset(&s);
	sigaddset(&s,SIGRTMIN);
	sigaddset(&s,SIGRTMIN+1);
	sigprocmask(SIG_BLOCK, &s, NULL);
	
	//arranco hilo que me enviara senales
	pthread_create(&h,NULL,f,NULL);
	
	printf("SIGRTMIN: %d\n",SIGRTMIN);
	sleep(2);
	a=sigwaitinfo(&s, NULL);
	printf("a: %d\n",a);
	a=sigwaitinfo(&s, NULL);
	printf("a: %d\n",a);
	a=sigwaitinfo(&s, NULL);
	printf("a: %d\n",a);
}


void *f (void *p){
	kill(getpid(),SIGRTMIN);
	kill(getpid(),SIGRTMIN+1);
	kill(getpid(),SIGRTMIN);
	printf("Hilo termino de enviar\n");
	return(NULL);
}