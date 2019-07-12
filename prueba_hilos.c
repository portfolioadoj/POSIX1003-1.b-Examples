#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int i;

void prot2( void *pg){
	while(1){
	i++;
	sleep(1);}
}

void prot1(void *pg){
	while(1>0){
	printf("i vale %d\n",i);
	sleep(2);}
}


void main(void)
{
	int j=0;
	pthread_t h1,h2;
	pthread_create(&h1,NULL,*prot1,(void*)j);
	pthread_create(&h2,NULL,*prot2,(void*)j);
	sleep(15);
	pthread_cancel(h1);
	pthread_cancel(h2);
}
