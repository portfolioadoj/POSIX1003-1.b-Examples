#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ms{int i; int j;};
void *h(void *p);

int main(int a1, char **a2){
	struct ms *a;
	pthread_t hilo;
	int *result;
	int aux[]={1,2};
	char aux2[]="PEPE";
	char *aux3="ANGEL";
	char *aux4;
	
	aux4=malloc(5*sizeof(char));
	aux4="LUIS";
	
	printf("aux[0]: %d; aux[1]: %d\n",aux[0], aux[1]);
	printf("aux2[0]: %c\n", aux2[0]);
	printf("aux2: %s\n",aux2);
	printf("aux3[0]: %c\n", aux3[0]);
	printf("aux3: %s\n",aux3);
	printf("aux4[0]: %c\n", aux4[0]);
	printf("aux4: %s\n",aux4);
	
	a=malloc(sizeof(struct ms));
	a->i=1; a->j=2;
	//printf("a.i: %d; a.b: %d\n",a.i, a.j);
	printf("a->i: %d; a->j: %d\n",a->i, a->j);
	
	pthread_create(&hilo, NULL, h, (void*)a);
	//pthread_join(hilo, NULL);
	pthread_join(hilo, &result);
	printf("a->i: %d; a->j: %d\n",a->i, a->j);
	printf("resultado hilo: %d\n",result);
	free(a);
	return(8);
}

void *h(void *p){
	struct ms * b=(struct ms *)p;
	int res=16; 
	b->i=12; b->j=13;
	return(void *)res;
}