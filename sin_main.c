#define _POSIX_C_SOURCE 199506L
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>

void *hilo(void *p) /*creo un hilo que va a estar incluso cuando main acabe*/
{
	int cnt;
	printf("El hijo esta aqui\n");
	for(cnt=0;cnt<10;cnt++)
	{
		printf("Hilo: cnt vale %d\n",cnt);
		fflush(stdout);
		sleep(1);
	}
	printf("Hilo acabando...\n");
	fflush(stdout);
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t h;   /*identificador hilo*/
	
	printf("main lanzando el hilo\n");
	fflush(stdout);
	pthread_create(&h, NULL, hilo,NULL); /*&idientificador, config, nombre hilo, args*/
	sleep(1);
	printf("main acabando...\n");
	fflush(stdout);
	pthread_exit(NULL);
	return 0; /*aunque nunca llegara aqui*/
}