#include <stdlib.h>
#include <string.h>

struct tcad
{
	char **pcad;
	int n;
};

int mayor(struct tcad *p){
	int largo=0,i,j;
	int res=0;
	char c; //almaceno la letra actual
	char **a=p->pcad;
	for(i=0;i<(p->n);i++){
		if(p->pcad[i]!=NULL){
			printf("%s\n",p->pcad[i]);
			res=0; //para cada palabra
			j=0;
			do{
				c=p->pcad[i][j]; res++; j++;
			}while(c!='\0');
			if(res>largo) largo=res-1; //para no guardar '\0'
		}
	}
	return(largo);
}
int main(void){
	int res;
	struct tcad *ms;
	char **tabla;
	ms=(struct tcad *)malloc(sizeof(struct tcad));
	tabla=(char **)malloc(sizeof(char));
	tabla[0]=NULL; tabla[1]="hj"; tabla[2]=NULL; tabla[3]="abc"; tabla[4]=NULL;
	ms->n=5;
	ms->pcad=tabla;
	res=mayor(ms);
	printf("%d\n",res);
}

