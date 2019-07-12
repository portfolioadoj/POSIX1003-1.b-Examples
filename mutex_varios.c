#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t m1=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2=PTHREAD_MUTEX_INITIALIZER;

void *h(void *p);
int main(void){
	int a, b; pthread_t hilo;
	pthread_mutex_lock(&m1);
	printf("Tengo mutex 1\n");
	pthread_mutex_lock(&m2);
	printf("Tengo mutex 1 y 2 \n");
	pthread_create(&hilo, NULL, h, NULL);
	pthread_mutex_unlock(&m1);
	printf("Libere mutex 1\n");
	sleep(2);
	pthread_mutex_unlock(&m2);
	printf("Libere mutex 2\n");
	pthread_join(hilo, NULL);
}
void *h(void *p){
	pthread_mutex_lock(&m1);
	printf("Hilo: tengo mutex1\n");
	pthread_mutex_unlock(&m1);
	printf("Hilo: libere mutex 1\n");
}