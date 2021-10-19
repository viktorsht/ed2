/*Vitor José Ferreira dos Santos de Santana*/

#include <stdio.h>
#include <stdlib.h>

#define TAM 5

void semPendencia(int vetor[],int divisor,int *mmc){
  int k = 0, i = 0;
  for(int j = 0; j < TAM; j++){
    if(vetor[j] > 1) k = 1;
  }
  if(k){
    for(int j = 0; j < TAM; j++){
      if(vetor[j] % divisor == 0) i = 1;
    }
    if(i){
      for(int j = 0; j < TAM; j++){
        if(vetor[j] % divisor == 0){
          vetor[j] = vetor[j] / divisor;
        }
      }
      *mmc *= divisor;
      semPendencia(vetor,2,mmc);
    }else{
      semPendencia(vetor,divisor + 1,mmc);
    }
  }
}

int pendencia(int vetor[],int divisor, int mmc){
  int k = 0, i = 0;
  for(int j = 0; j < TAM; j++){
    if(vetor[j] > 1) k = 1;
  }
  if(k == 1){
    for(int j = 0; j < TAM; j++){
      if(vetor[j] % divisor == 0) i = 1;
    }
    if(i == 1){
      for(int j = 0; j < TAM; j++){
        if(vetor[j] % divisor == 0){
          vetor[j] = vetor[j] / divisor;
        }
      }
      mmc = pendencia(vetor, 2, mmc * divisor);
    }else{
      mmc = pendencia(vetor,divisor + 1,mmc);
    }
  }
  return mmc;
}

int main(int argc, char *argv[]){

  int vetorSemPendencia[TAM], vetorComPendencia[TAM];
  int numero, mcc = 1;

  for(int i = 0; i < TAM; i++){
    do{
      printf("Número %d: ", i + 1);
      scanf("%d",&numero);
    }while(numero <= 0);

    vetorSemPendencia[i] = vetorComPendencia[i] = numero;
  }

  semPendencia(vetorSemPendencia,2,&mcc);

  printf("Sem pendência: %d\n",mcc);
  printf("Com pendência: %d\n",pendencia(vetorComPendencia,2,1));

  return 0;
}
