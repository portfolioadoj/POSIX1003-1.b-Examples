#include <stdio.h>
#include <pthread.h>

void *f(void *p);

int main(int a1, char **a2){
	int i=0;
	int **result;
	pthread_t h;
	pthread_create(&h, NULL, f, (void *)i);
	
	//sleep(1);
	//pthread_join(h,NULL);
	pthread_join(h,result);
	printf("Hilo envio %d\n",(int)result);
	printf("Main saliendo porque hilo volvio con return, con exit no llego aqui\n");
}

void *f (void *p){
	int  i=(int ) p;
	
	i=2;
	//exit(0);
	return (void *)i;
}