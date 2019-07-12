#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void *f(void *p);

int main(int a1, char **a2){
	pthread_t h;
	int cancel;
		
	pthread_create(&h, NULL, f, NULL);
	//sleep(2); //para que le de tiempo al hilo
	cancel=pthread_cancel(h);
	printf("Hilo cancelado con resultado %d\n",cancel);
}

void *f (void *p){
	int escucha; struct sockaddr_in dir;
	int res, resp;
	
	dir.sin_addr.s_addr=INADDR_ANY;
	dir.sin_port=htons(0);
	escucha=socket(AF_INET, SOCK_DGRAM,0);
	res=bind(escucha, (struct sockaddr*)&dir, sizeof(dir));
	if(res==-1) {printf("Hilo: Error en bind\n"); return(0);}
	printf("Hilo: Estoy esperando dato\n");
	recv(escucha, &resp, sizeof(resp),MSG_WAITALL);
	printf("Hilo: recibi dato\n");
	while(1){}
	close(escucha);
}