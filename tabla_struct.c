#include <stdio.h>

struct ms {
	int a;
	int b;
	int c;
};

int main(int a1, char **a2){
	struct ms *tabla;
	int long_tabla=4; int i;
	char *res;
	
	if(a1>1 && *a2[1]>4) sscanf(a2[1],"%d",&long_tabla);
	tabla=(struct ms *)malloc(sizeof(struct ms)*long_tabla);
	tabla[0].a=5; tabla[0].b=6;
	printf("Intro dato\t"); scanf("%d",&tabla[0].c);//printf("\n");
	printf("long_tabla: %d\n",long_tabla);
	printf("tabla[0].a: %d; tabla[0].b: %d; tabla[0].c: %d\n",tabla[0].a, tabla[0].b, tabla[0].c); 
	free(tabla);
}