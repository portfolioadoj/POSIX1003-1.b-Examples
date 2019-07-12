#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *f( void *p);
int a;
int main(int a1, char ** b ){
	int i=0,j=0;
	pthread_t hilo;
	printf("Main: a: %d\n",a);
	pthread_create(&hilo, NULL,f,(void *) i);
	pthread_join(hilo,NULL);
	printf("Main: i: %d\n",i);
	printf("Main: a: %d\n",a);
	printf("a era variable global, i local, el hilo no reconoce i salvo que se defina dentro pero a si puede cambiarla, y el main ve su cambio\n");
	return(1);
}

void *f(void *p){
	int i=(int )p;
	i++; 
	a++;
	printf("Hilo: i: %d\n",i);
	printf("Hilo: a: %d\n",a);
	return((void *)i);
}

	