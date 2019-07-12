#define _POSIX_C_SOURCE 199306L

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *fp;
	pid_t id;
	
	/*fp=fopen("noexiste.txt","r");
	
	if(fp==NULL)
	{
		printf("algo pasa con fopen\n");
		if (errno==EAGAIN) printf("error EAGAIN %d\n", errno);
		printf("error $d: %s\n",errno,strerror(errno));
	}*/
	 printf("soy %ld\n",getpid());
	 fflush(stdout);
	 id=fork();
	 
	 printf("%ld estoy aqui y fork devuelve %ld\n",getpid(),(long)id);
	 
	 if (id==(pid_t)0)
	 {
	 	printf("soy el hijo\n");
	 	exit(0);
	 }
	 printf("soy el padre \n");
	 return 0;
}