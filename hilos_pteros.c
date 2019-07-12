#include <stdio.h>
#include <pthread.h>

void *hilo (void *p);

int main(int a1, char **a2){
	int a=0,b=0,c=0;
	pthread_t th;
	
	printf("a: %d\n",a);
	
	pthread_create(&th, NULL, hilo, (void *)a);
	pthread_join(th, NULL);
	
	printf("a: %d\n",a);
	return(0);
}

void *hilo (void *p){
	//int *a= (int *)p;
	int a=(int)p;
	int b;
	printf("hilo a: %d\n",a);
	a+=3;
	printf("hilo a: %d\n",a);

}