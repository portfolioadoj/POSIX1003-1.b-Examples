#include <time.h>
#include <stdio.h>
#include <math.h>

int main(void){
	struct timespec t1,t2, espera;
	int a; 
	long double hora1, hora2, Ta;
	//float hora1, hora2, Ta;
	espera.tv_sec=0; espera.tv_nsec=1000000;
	
	a=clock_gettime(CLOCK_REALTIME, (struct timespec *)&t1);
	//printf("a: %d\n");
	printf("t1.tv_sec: %d\nt1.tv_nsec: %d\n",t1.tv_sec, t1.tv_nsec);
	nanosleep(&espera, NULL);
	a=clock_gettime(CLOCK_REALTIME, (struct timespec *)&t2);
	printf("t2.tv_sec: %d\nt2.tv_nsec: %d\n",t2.tv_sec, t2.tv_nsec);
	
	printf("Calculando intervalo en ms\n");
	//hora1=t1.tv_sec*1000+t1.tv_nsec*0.000001;
	//hora2=t2.tv_sec*1000+t2.tv_nsec*0.000001;
	hora1=t1.tv_sec+t1.tv_nsec*1000000000;
	hora2=t2.tv_sec+t2.tv_nsec*1000000000;
	Ta=hora2-hora1;
	//printf("Pasaron %f ms\n",Ta);
	printf("Pasaron %d s\n",Ta);
}