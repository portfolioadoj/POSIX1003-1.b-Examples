#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5
pthread_cond_t c=PTHREAD_COND_INITIALIZER;
pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;
int a,b,d;

void *f1(void *p){
	int res;
	pthread_mutex_lock(&m);
	while(a==b){
		pthread_cond_wait(&c,&m);
	}
	d--; printf("d vale %d\n",d);
	pthread_mutex_unlock(&m);
}

int main( int v1, char **v2){
	int i,k,n; pthread_t h[N];
	struct timespec t={1,0L};
	a=b=0;
	for(i=0,d=0;i<N;i++){
		pthread_create(&h[i],NULL,f1,NULL);
		d++;
	}
	if(v1>=2) sscanf(v2[1],"%d",&k);
	else k=0;
	n=1;
	while(n){
		printf("Mensaje 1\n");
		pthread_mutex_lock(&m);
		a++;
		if(a!=b){
			if(a<k) pthread_cond_signal(&c);
			else pthread_cond_broadcast(&c);
		}
		pthread_mutex_unlock(&m);
		nanosleep(&t,NULL);
		pthread_mutex_lock(&m);
		if(d==0) n=0;
		pthread_mutex_unlock(&m);
	}
	return 0;
}