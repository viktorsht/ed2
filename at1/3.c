/*Vitor José Ferreira dos Santos de Santana*/

// Concluida com sucesso

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

#define TAM 10

/* letra a - Concluida*/
char maiorString(char s[][TAM],int i, int n, int maior, char str[]){
  if(i <= n){
    if(strlen(s[i]) > maior){
      maior = strlen(s[i]);
      strcpy(str,s[i]) + maiorString(s,i+1,n,maior,str);
    }
    maiorString(s,i+1,n,maior,str);
  }
  return *str;
}

/*letra b - Concluida*/
int vogal(char c){
  int retorno = 0;
  if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') retorno = 1;
  else if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') retorno = 1;
  return retorno;
}

void iniVogal(char s[][TAM], int i, int n, int *count){
  if(i <= n){
    if(vogal(s[i][0]) == 1){
      *count = *count + 1;
    }
    iniVogal(s,i+1,n,count);
  }
}

/*letra c - Concluida*/
void tamanho4(char s[][TAM], int i, int n,char v[][TAM],int *k){
  if(i < n){
    if(strlen(s[i]) >= 4 && isupper(s[i][0])){
      printf("%d\n",*k);
      strcpy(v[*k],s[i]);
      *k = *k + 1;
    }
    tamanho4(s,i+1,n,v,k);
  }
}

int main(int argc, char *argv[]){
  char string[TAM];
  char str[TAM];
  int tamanho,vogais,k = 0;

  printf("Número de palavras para a string: ");
  scanf("%d",&tamanho);

  char vetorString4Maiuscula[tamanho][TAM];
  char vetor[tamanho][TAM];

  for(int i = 0; i < tamanho; i++){
    scanf("%s",string);
    strcpy(vetor[i],string);
  }

  maiorString(vetor,0,tamanho,0,str);
  iniVogal(vetor,0,tamanho,&vogais);
  tamanho4(vetor,0,tamanho,vetorString4Maiuscula,&k);

  printf("\n\n");

  printf("Maior String = %s\n",str);
  printf("Palavras que começam com vogal= %d\n",vogais);
  if(k > 0){
    printf("Palavra tem mais de 4 letras e começa com letra maisuscula\n");
    for(int j = 0; j < k; j++){
      printf("String = %s\n",vetorString4Maiuscula[j]);
    }
  }
  else{
    printf("Nenhuma palavra é maior que 4 e começa com letra maisuscula\n");
  }

  return 0;
}
