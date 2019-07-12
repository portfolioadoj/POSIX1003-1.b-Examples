#include <stdio.h>
#include <stdlib.h>

int a;
void main()
{
	int i=0;
	pid_t hijo;
	int res;int resw;
	int aux;
	
	hijo=fork();
	if(!hijo) {printf("Soy el hijo\n");i=16;a=5; exit(i);}
	fflush(stdout);
	aux=wait(&res);
	//WIFEXITED(res);
	printf("i:%d res:%d WEXITSTATUS(res): %d\n",i,res,WEXITSTATUS(res));
	printf("a vale: %d\n",a);
	printf("hijo no puede cambiar el valor ni de una variable local del main ni de una global\n");
}