#define _POSIX_C_SOURCE 199506L
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int i=0;
	printf("Numero de args: %d\n",argc);
	for(i=0;i<argc;i++)
		printf("arg n: %d %s\n",i,argv[i]);
}