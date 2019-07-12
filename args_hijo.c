#define _POSIX_C_SOURCE 199309L
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char **argv)
{
	printf("argc vale %d\n",argc);
	printf("Soy el hijo %ld; estos son mis argumentos\n",getpid());
	while (argc--)
	{
		printf("%s ",*argv++);
	}
	printf("\n");
	fflush(stdout);
	printf("padre %ld\n",getppid());
	sleep(5);
	printf("padre sigue siendo el mismo %ld\n",getppid());
	exit(18);
}