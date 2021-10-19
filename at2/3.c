#include<stdio.h>
#include<stdlib.h>

typedef struct no{
	int numero;
	struct no *esquerda;
	struct no *direita;
}Arvore;

Arvore* inserir(Arvore *raiz, int valor){
	if(raiz == NULL){
		Arvore *aux = malloc(sizeof(Arvore));
		aux->numero = valor;
		aux->esquerda = NULL;
		aux->direita = NULL;
		raiz = aux;
	}
	else{
		if(valor < raiz->numero){
			raiz->esquerda = inserir(raiz->esquerda,valor);
		}
		else{
			raiz->direita = inserir(raiz->direita,valor);
		}
	}
	return raiz;
}
int mult5menor100(int num){
  int retorno = 1;
  if(num % 5 == 0) retorno = 0;
  return retorno;
}

void buscar(Arvore *raiz,int vetor[],int *i){
	if(raiz){
		if(mult5menor100(raiz->numero) == 0 && raiz->numero < 100){
      vetor[*i] = raiz->numero;
      (*i)++;
    }
		else if(raiz->numero < 100){
			buscar(raiz->esquerda,vetor,i);
		}
		else{
			buscar(raiz->direita,vetor,i);
		}
	}
}

void imprimir1(Arvore *raiz){
	if(raiz){
		printf("%d ",raiz->numero);
		imprimir1(raiz->esquerda);
		imprimir1(raiz->direita);
	}
}

void terceira(Arvore *raiz,int vetor[], int *i){
	if(raiz){
    if(mult5menor100(raiz->numero) == 0 && raiz->numero < 100){
      vetor[*i] = raiz->numero;
      (*i)++;
    }
		terceira(raiz->esquerda,vetor,i);
		terceira(raiz->direita,vetor,i);
	}
}

int main(){
	Arvore *raiz,*busca = NULL;
	int vetor[5] = {50,100,80,23,700};
  int i = 0;
  int v[5];

	for(int i = 0; i < 5; i++){
		raiz = inserir(raiz,vetor[i]);
	}

	//imprimir1(raiz);
	printf("\n");

  terceira(raiz,v,&i);
  printf("%d\n",i);
  for(int j = 0; j < i; j++){
    printf("%d ",v[j]);
  }
  printf("\n");
	return 0;
}
