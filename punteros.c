#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){

	char nombre[]="Angel";
	char *puntero;
	char *nombre2="Angel";
	
	/*Escoger una de las dos siguientes*/
	puntero=nombre;
	//puntero=nombre2;
	
	printf("nombre: %s\n",nombre);
	printf("nombre2: %s\n",nombre2);
	printf("puntero: %s\n",puntero);
	/*puedo escoger entre estas dos opciones*/
	   /*opcion 1*/
	//printf("Intro nombre\n");
	//scanf("%s",puntero);
	   /*opcion2*/
	sscanf("HOLA","%s",puntero);
	printf("nombre: %s\n",nombre);
	
}