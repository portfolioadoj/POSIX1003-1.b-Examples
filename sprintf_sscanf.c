#include <stdio.h>
#include <stdlib.h>

int main(int a1, char **b1)
{
     char msg[50];
     int a=5;
     int b=10;
     char c[50],v[50];
     
     printf("uso sprintf para pasar varios caracteres a una cadena\n");
     sprintf(msg,"a: %d ,b: %d ",a,b);
     printf("[%s] es una cadena completa\n",msg);
     
     printf("modifico a y b para ver si luego funciona sscanf\n");
     a=b=1;
     printf("a:%d, b:%d\n",a,b);
     
     
     printf("uso sscanf para pasar una cadena a varios caracteres\n");
     sscanf(msg,"%s %d %s %d ",c,&a,v,&b);
     printf("%d %d\n",a,b);
     printf("funciona porque cambie a y b, pero copie los enteros de la cadena en a y b\n");
     return(9);
}
