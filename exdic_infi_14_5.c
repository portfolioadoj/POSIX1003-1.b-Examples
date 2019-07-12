#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n=0;
pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c1=PTHREAD_COND_INITIALIZER;
int v1=-1; int v2=0; struct w {int a; int b;};

void *f(void *p){
	struct w *p1=(struct w*)p; int i;
	do{
		pthread_mutex_lock(&m);
		while(v1==-1)
			pthread_cond_wait(&c1,&m);
		if(v1==p1->a){
			v1=-1;v2=v2+p1->b; i=1;
		} else i=0;
		pthread_mutex_unlock(&m);
		if(i==1) printf("%d en while\n",p1->a);
	}while(v1!=n);
	return NULL;
}

int main(int a1, char **a2){
	pthread_t *h; int i,j,k; sigset_t s; siginfo_t t; 
	struct w *p;
	sigemptyset(&s); sigaddset(&s,SIGRTMIN);
	pthread_sigmask(SIG_BLOCK,&s,NULL);
	n=a1-1;
	h=(pthread_t *)malloc(sizeof(pthread_t)*n);
	for(i=1;i<a1;i++){
		sscanf(a2[i],"%d",&j);
		p=malloc(sizeof(struct w));
		p->a = i-1; p->b=j;
		pthread_create(&h[i-1],NULL, f, (void *)p);
	}
	do{
		sigwaitinfo(&s,&t); k=t.si_value.sival_int;
		pthread_mutex_lock(&m);
		v1=k; pthread_cond_broadcast(&c1);
		pthread_mutex_unlock(&m);
	}while(k!=n);
	for(i=0;i<n;i++) pthread_join(h[i],NULL);
	printf("v2: %d\n",v2);
	return 0;
}