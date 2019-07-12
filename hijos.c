#include <stdio.h>
#include <pthread.h>

void f(int i){	
	if(i==0) return;
	printf("Hijo %d: como i!=0, me salte el return\n",i);
}
int main(int a1, char **a2){
	int i=0;
	pid_t p[2];
	
	p[0]=fork(); if(!p[0]) {f(0);printf("Hijo 0 antes de exit\n");exit(0);}
	p[1]=fork(); if(!p[1]) {f(1); printf("Hijo 1 antes de exit\n"); exit(1);}
	return(9);
}