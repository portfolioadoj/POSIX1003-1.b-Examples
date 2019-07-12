#define POSIX_C_SOURCE 199309
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv)
{
	pid_t pid_hijo,pid_padre;
	int estado;
	
	pid_padre=getpid();
	printf("El padre es:\n %ld usando pid_padre\n %ld usando getpid()\n",pid_padre,getpid());
	
	pid_hijo=fork();
	if(!pid_hijo)
	{ /*acciones hijo*/
		printf("Soy el hijo, uso getppid() y tengo el pid del padre: %ld\n",getppid());
		printf("Soy el hijo, uso getpid() y tengo el pid del hijo: %ld\n",getpid());
		printf("Soy el hijo, al leer pid_hijo obtengo: %ld\n",pid_hijo);
		exit(1);
	}
	else
	{/*acciones padre*/
		printf("Soy el padre, uso getpid: %ld\n",getpid());
		printf("Soy el padre, pid_hijo es: %ld\n",pid_hijo);
		if(waitpid(pid_hijo,&estado,0)>0)
		{
			printf("espera concluida\n");
			if(WIFEXITED(estado))
			{	
				printf("%d salio con estado %d\n",(int)pid_hijo,WEXITSTATUS(estado));
			}
		}
		else printf("Error en waitpid: %s\n",strerror(errno));
		printf("El padre acaba\n");
	}
}