/*Vitor José Ferreira dos Santos de Santana*/

// Concluida com sucesso

#include<stdio.h>

int divisores(int n, int i,int k, int v[],int *count){
	if( n >= i ){
		if(n % i == 0){
			v[k] = i;
			k++;
			*count = *count + 1;
		}
		divisores(n,i+1,k,v,count);
	}
}

int main(int argc, char *argv[]){

	int numero,c = 0;
	int v[1000]; /*Vetor grande o suficiente para caber números com muitos divisores*/
	scanf("%d",&numero);
	divisores(numero,1,0,v,&c);
	for(int i = 0; i < c; i++){
		printf("%d ",v[i]);
	}
	return 0;
}
