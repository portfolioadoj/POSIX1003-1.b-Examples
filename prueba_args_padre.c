#define _POSIX_C_SOURCE 199506L
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
	pid_t hijo;
	int res;
	char char1[10];
	
	/*voy a pasarle como argumento un entero, así que tengo que transformarlo a char*/
	sprintf(char1,"%d",48);
	hijo=fork();
	if(hijo==0)
	{
		execl("prueba_args","prueba_args",char1,NULL);
		exit();
	}
}