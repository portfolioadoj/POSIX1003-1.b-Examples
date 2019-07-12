#define _POSIX_C_SOURCE 199506L
#include <pthread.h>
#include <stdlib.h>
#include <sys/wait.h>

#define N 4
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c=PTHREAD_COND_INITIALIZER;
int n=0;

void *f (void *p){
	struct timespec v={0,250000000L};
	int j=0; int i=(int)p;
	pthread_mutex_lock(&m);
//	printf("Hilo %d con mutex\n",i);
//	printf("Hilo %d: n=%d\n",i,n);
	while(n!=i){
//		printf("Hilo %d esperando\n",i);
		pthread_cond_wait(&c, &m);
		j++;
	}
//	printf("Hilo %d cambia n\n",i);
	n++;
	pthread_mutex_unlock(&m);
	nanosleep(&v, NULL);
	pthread_mutex_lock(&m);
	pthread_cond_broadcast(&c);
	pthread_mutex_unlock(&m);
	printf("Para %d j vale %d\n",i,j);
	return NULL;
}
int main(int argc, char **argv){
	int i; pthread_t h[N];
	for(i=0;i<N;i++){
		pthread_create(h+i, NULL, f, (void *)i);
	}
	pthread_mutex_lock(&m);
//	printf("Main con mutex\n");
	n++;
	pthread_cond_broadcast(&c);
	pthread_mutex_unlock(&m);
	for(i=0;i<N; i++){
		pthread_join(h[i], NULL);
		printf("Numero %d\n",i);
	}
	return 0;
}