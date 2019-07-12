#define _POSIX_C_SOURCE_199309L

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv)
{
	pid_t pid;
	int estado;
	int codigo=77;
	int i;
	
	printf("padre -> Hola Mundo, soy %d\n", (int)getpid());
	printf("padre -> Soy %d, voy a desdoblarme\n",(int)getpid());
	fflush(stdout);
	
	pid=fork();
	if(pid==0)
	{
		//sleep(1);
		printf("soy el hijo, el proceso %d creado por %d\n",(int)getpid(),(int)getppid());
		printf("para %d codigo vale %d\n",(int)getpid(),codigo);
		
		for(i=0;i<10;i++)
		{
			printf("%d Cuenta: %d\n",(int)getpid(),i);
			//fflush(stdout);
			sleep(2);
		}
		 printf("%d Acaba\n",(int)getpid(),i);
		 exit(3);		 	
	}
	else
	{
		printf("para %d codigo vale %d\n",(int)getpid(),codigo);
		for(i=0;i<10;i++)
		{
			printf("%d Cuenta: %d\n",(int)getpid(),i);
			fflush(stdout);
			sleep(1);
		}
		printf("Voy a esperar al %d \n",(int)pid);
		if(waitpid(pid, &estado,0)>0)
		{
			printf("espera concluida\n");
			if(WIFEXITED(estado))
			{
				printf("%d salio con estado %d\n",(int)pid, WEXITSTATUS(estado));
			}
		}
		else printf("Error en waitpid: %s\n",strerror(errno));
		
		printf("el padre acaba\n");
	}
}