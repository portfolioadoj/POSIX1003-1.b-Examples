#define _POSIX_C_SOURCE 199506L
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>

int comun; /*va a ser mi variable global*/

struct timespec tim= {0, 40000000L}; /*espera 40 ms*/
void *hilo1(void *p);
void *hilo2(void *p);

int main(int argc, char **argv)
{
	pthread_t th;
	int dato = 20;
	int res; 
	int cnt;
	int error;
	void *result;
	
	/*Arranco primer hilo*/
	res=pthread_create(&th, NULL, hilo1, (void *dato));

	/*Ejemplo de comprobacion de errores*/
	if(res) /*if(res!=0)*/
	{
		printf("Error en create: %s\n",strerror(res)); /*notese que no se usa errno, en res se guarda*/
		exit(1);
	}
	
	/*Espera a que termine el primer hilo*/
	pthread_join(th, &result);
	printf("Soy main. Resultado del primer hilo: %s\n", (char*)result); /*result es (void *)*/
	
	/*Generacion y deteccion error*/
	if(res=pthread_join(th, &result))
		printf("Error (previsto porque espero un hilo que termine) en join: %s\n",strerror(res));
	
	/*Arranca segundo hilo*/
	pthread_create(&th, NULL, hilo2, (void *)dato);
	cnt=10;
	while(cnt-)
	{
		nanosleep(&tim, NULL); /*espera 40 ms*/
		printf("Soy main. Var. compartida: %d\n", comun); /*almaceno en la variable compartida la salida*/
	}
	printf("Soy main. Voy a esperar a Hilo2.\n");
	res=pthread_join(th, &result);
	
	printf("Soy main. Hilo2 ha acabado.\n");
	if(res!=0)
		printf("Error en join%s\n",strerror(res));
	else if(result==(void *)PTHREAD_CANCELED)
		printf("Ha sido cancelado.\n"); /*si ha sido cancelado*/
	else printf("Ha generado resultado %d\n", (int) result);
	
	/*Otra vez hilo2; ahora sera cancelado*/
	pthread_create(&th, NULL, hilo2, (void *)dato;
	
	/*Main deja a hilo2 que se ejecute por un tiempo*/
	
	cnt=4;
	while(cnt--) nanosleep(&tim,NULL);
	
	/*Cancelacion hilo2*/
	{
		int a;
		a=pthread_cancel(th);
		if(a) printf("error %s\n",strerror(a));
	}
	
	/*pthread detach(th);*/
	/*la linea anterior hace que el hilo deje de ser esperado, al coste
	de no poder leer su resultado*/
	
	printf("Soy main. Voy a esperar a Hilo2.\n");
	
	res=pthread_join(th, (void *)&result); /*el (void *) es omitible*/
	printf("Soy main. Hilo2 ha acabado.\n");
	
	if (res!=0)
		printf("Error en join %s\n",strerror(res));
	else if(result==(void *)PTHREAD_CANCELED)
		printf("Ha sido cancelado.\n");
	else printf("Ha generado resultado %d\n",(int) result);
	
	/*otra vez hilo2; ahora acabara solo porque main termina y llama a exit*/
	pthread_create(&th, NULL, hilo2, (void *)dato);
	
	/*Main deja a Hilo2 que se ejecute por un tiempo*/
	cnt=6;
	while(cnt--) nanosleep(&tim, NULL);
	printf("Soy main. Voy a acabar.\n");
	
}

/*Rutina del hilo1*/
void *hilo1 (void *p)
{
	char *mensaje="hola";
	char *pc;
	
	printf("Soy hilo2\n");
	pc=(char *)malloc(5);
	strcpy(pc,mensaje);
	/*devuelve un puntero, pero apunta a memoria reservada con malloc, no a la pila*/
	return (void *)pc;
}

/*Rutina del hilo2*/
void *hilo2(void *arg)
{
	int cnt=(int)arg; /*Toma arg como entero*/
	int r=77; 			/*valor que se devuelve*/
	
	printf("Soy hilo2. Argumento: %d\n",(int)arg);
	/*
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	*/
	/*pthread_setcanceltype(PTHREAD_CANCEL_ASYNCRHONOUOS, NULL);*/
	
	while(cnt--)
	{
		/*QNX antiguo daba problemas si paro un hilo tras un printf, por eso se hace esto*/
		pthread_cancelstate(PTHREAD_CANCEL_DISABLE, NULL);
		printf("soy hilo2. Contador: %d\n",cnt);
		pthread_cancelstate(PTHREAD_CANCEL_ENABLE, NULL);
		comun=cnt; */el contador (local) se copia en comun*/
		pthread_testcancel(); /*punto de cancelacion*/
		/*pthread_setcancelstat(PTHREAD_CANCEL_DISABLE, NULL);*/
		nanosleep(&tim, NULL); /*incluye punto de cancelacion*/
		/*pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);*/
	}
	
	return((void *)r);
}