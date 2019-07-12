#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

#define N 4
struct s {char e1; int e2;};
//para enviar las señales
void *hilo_senales(void);

void h(int b, char **argv){}

int main(int b, char **argv){
	pthread_t h;
	struct s s1[N]={{'a',2}, {'b',1}, {'c',4}, {'d',5}};
	sigset_t v;
	siginfo_t t; struct sigaction s;
	int c,i; struct timespec m;
	
	//llamo al hilo de las senales
	pthread_create(&h,NULL,hilo_senales,NULL);
	sigemptyset(&v); sigaddset(&v, SIGRTMIN);
	s.sa_flags=SA_SIGINFO;
	s.sa_sigaction=h;
	sigemptyset(&s.sa_mask);
	sigaction(SIGRTMIN, &s,NULL);
	sigprocmask(SIG_BLOCK, &v, NULL);
	do{
		sigwaitinfo(&v,&t);
		for(i=0,c=1;i<N && c==1; i++) //saldra del for cuando no se cumpla alguna de las dos condiciones
		{
			if(s1[i].e2==t.si_value.sival_int){
				c=0;
				printf("%c\n",s1[i].e1);
				m.tv_sec=s1[i].e2; m.tv_nsec=0;
				nanosleep(&m,NULL);
			}
		}
	}while(c==0); //saldra del while cuando acabe el for y no c!=0
	pthread_join(&h,NULL);
}

void *hilo_senales()
{
	struct timespec t;
	union sigval val;
	//cada 500 ms va a enviar una senal con dato
	t.tv_sec=0;
	t.tv_nsec=500000000L;
	
	nanosleep(&t,NULL);
	val.sival_int=1;
	sigqueue(getpid(),SIGRTMIN,val);
	
	nanosleep(&t,NULL);
	val.sival_int=5;
	sigqueue(getpid(),SIGRTMIN,val);
	
	nanosleep(&t,NULL);
	val.sival_int=2;
	sigqueue(getpid(),SIGRTMIN,val);
	
	nanosleep(&t,NULL);
	val.sival_int=0;
	sigqueue(getpid(),SIGRTMIN,val);
	
	return(0);
}	