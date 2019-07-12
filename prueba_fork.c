#include <stdio.h>
#include <stdlib.h>

void main(){
	int i,j;
	pid_t hijo;
	hijo=fork();
	if(!hijo)
		{
			printf("Hijo: me duermo 5 segundos\n");
			sleep(5);
			printf("Hijo: acabe, tarde 5 segs\n");
			exit(0);
		}
	printf("Padre: me duermo 10 segundos\n");
	sleep(10);
	printf("Padre: acabe, tarde 10 segs\n");
	return;
}