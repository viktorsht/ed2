/*Vitor José Ferreira dos Santos de Santana*/

// Concluida com sucesso

#include<stdio.h>
#include<math.h>
#include<string.h>

#define TAM 2

/*
1 - A função misterio1 recebe o enderoço de uma variável do tipo float e modifica,
diretamente, o seu valor durante a execução do código. Sempre que a condição é
válida o valor da variável é incrementada.
*/

void misterio1(char b[TAM],float *dec, int i){
	if( i < strlen(b)){
		if(b[i] == '1'){
			*dec = *dec + pow(2,i);
		}
		misterio1(b,dec,++i);
	}
}


/*
2 - A função misterio2 recebe uma cópia do valor da variável da função main.
Logo, ele faz modificações na variável local, válida somente dentro da função, e
retorna esse valor no final. Onde, na função main, o valor deve ser atribuído a
uma variável do tipo float.
*/

float misterio2(char b[TAM], float dec, int i){
	if(i < strlen(b)){
		dec = misterio2(b,dec,i+1);
    if(b[i] == '1')
      dec = dec + pow(2,i);
		}
	return(dec);
}

int main(int argc, char *argv[]){
	float d = 0;
	float d1 = 0;

	misterio1("11",&d,0);
	misterio2("11",d1,0);

	printf("d = %f\n",d);
	printf("d1 = %f\n",d1);
	return 0;
}
