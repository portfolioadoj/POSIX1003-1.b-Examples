#include <stdlib.h>

int main(void){
	int x=5;
	int y[5]={1,2,3,4,5};
	int *p1=&y[0];
	int **p2=&p1;
	
	printf("%d\n",*p1);
	printf("%d\n",p1[0]);
	printf("%d\n",p1);
	printf("%d\n",*p2);
	printf("%d\n",*p2[0]);
	
}