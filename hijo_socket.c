#define _POSIX_C_SOURCE 199506L

/* Cabeceras del sistema */

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
//necesario para el tiempo
#include <time.h>

void m(int s){printf("Entro manej\n");}
void *h(void *p);
int main(void){
	int sock, esc1, esc2;
	struct sockaddr_in dir, g;
	pid_t hijo; pthread_t hilo;
	int res, dato, dato2;
	sigset_t s; struct sigaction sa;
	alarm(3);
	sa.sa_flags=0; sa.sa_handler=m; sigemptyset(&sa.sa_mask);
	sigaction(SIGALRM, &sa, NULL); sigemptyset(&s); sigaddset(&s, SIGALRM);
	sigprocmask(SIG_UNBLOCK, &s, NULL);
	
	memset((char *)&dir,0, sizeof(dir)); 
	dir.sin_family=AF_INET;
	dir.sin_addr.s_addr=INADDR_ANY;
	dir.sin_port=htons(1234);
	esc1=socket(AF_INET, SOCK_STREAM,0); 
	res=bind(esc1, (struct sockaddr *)&dir,sizeof(dir)); if(res==-1) printf("Error en bind\n");
	res=listen(esc1, 10); if(res==-1) printf("Error en listen\n");
	sock=socket(AF_INET, SOCK_STREAM, 0);
/*	res=connect(sock, (struct sockaddr *)&dir, sizeof(dir)); if(res==-1) printf("Error en connect %s\n",strerror(errno));
	pthread_create(&hilo, NULL, h, (void*)sock);
*/
	hijo=fork();
	if(hijo==0){
		printf("Hijo: empiezo\n");
		sock=socket(AF_INET, SOCK_STREAM, 0);
		res=connect(sock, (struct sockaddr *)&dir, sizeof(dir));
		if(res==-1) printf("Error en connect %s\n",strerror(errno));
		if(res!=-1){
			printf("Hijo: Socket conectado con exito\n");
			dato=1;
			send(sock, &dato, sizeof(dato), 0);
			close (sock);
		}
		exit(0);
	}

	sleep(1);
	esc2=accept(esc1, NULL, NULL);
	recv(esc2,&dato2, sizeof(dato2),MSG_WAITALL);
	printf("recibido %d\n",dato2);
	close(esc1);
}

void *h(void *p){
	int a, soc;
	printf("Hilo: empiezo\n");
	soc=(int) p;
	a=1; 
	send(soc, &a, sizeof(a),0);
}