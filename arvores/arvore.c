#include<stdio.h>
#include<stdlib.h>

/*

		ÁRVORE BINÁRIA DE BUSCA - CÓDIGO DE TESTE

*/

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

Arvore *buscar(Arvore *raiz,int valor){
	if(raiz){
		if(valor == raiz->numero) return raiz;
		else if(valor < raiz->numero){
			return buscar(raiz->esquerda,valor);
		}
		else{
			return buscar(raiz->direita,valor);
		}
	}
	return NULL;
}

void imprimir1(Arvore *raiz){
	if(raiz){
		printf("%d ",raiz->numero);
		imprimir1(raiz->esquerda);
		imprimir1(raiz->direita);
	}
}

void imprimir2(Arvore *raiz){
	if(raiz){
		imprimir2(raiz->esquerda);
		printf("%d ",raiz->numero);
		imprimir2(raiz->direita);
	}
}

int altura(Arvore *raiz, int retorno){
	if(raiz == NULL){
		retorno = -1;
	}
	else{
		int esq = altura(raiz->esquerda,retorno);
		int dir = altura(raiz->direita,retorno);
		if(esq > dir){
			retorno = esq + 1;
		}
		else{
			retorno = dir + 1;
		}
	}
	return retorno;
}

int quantidadeNos(Arvore *raiz, int retorno){
	if(raiz == NULL){
		retorno = 0;
	}
	else{
		retorno = 1 + quantidadeNos(raiz->esquerda,retorno) + quantidadeNos(raiz->direita,retorno);
	}
	return retorno;
}

Arvore* remover(Arvore *raiz,Arvore *retorno, int chave){
	if(raiz == NULL){
		retorno = NULL;
	}
	else{
		if(raiz->numero == chave){
			// remove nós folhas(nós sem filhos)
			if(raiz->esquerda ==  NULL && raiz->direita == NULL){
				free(raiz);
				retorno = NULL;
			}
			else{
				// remover nós com 2 filhos
				if(raiz->esquerda !=  NULL && raiz->direita != NULL){
					Arvore *aux = raiz->esquerda;
					while (aux->direita != NULL) {
						aux = raiz->direita;
					}
					raiz->numero = aux->numero;
					aux->numero = chave;
					raiz->esquerda = remover(raiz->esquerda,retorno,chave);
					retorno = raiz;
				}
				else{
					// remover nós com 1 filho apenas
					Arvore *aux;
					if(raiz->esquerda != NULL) aux = raiz->esquerda;
					else aux = raiz->direita;
					free(raiz);
					retorno = aux;
				}
			}
		}
		else{
			if(chave < raiz->numero)
				raiz->esquerda = remover(raiz->esquerda,retorno,chave);
			else
				raiz->direita = remover(raiz->direita,retorno,chave);
			retorno = raiz;
		}
	}
	return retorno;
}

int main(){
	Arvore *raiz,*busca = NULL;
	int vetor[6] = {500,750,250,650,600,700};
	for(int i = 0; i < 6; i++){
		raiz = inserir(raiz,vetor[i]);
	}
	//imprimir1(raiz);
	imprimir1(raiz);
	printf("\n");/*
	busca = buscar(raiz,400);
	if(busca) printf("\nNúmero encontrado: %d\n",busca->numero);
	else printf("\nnão encontrado\n");
	printf("Altura = %d\n",altura(raiz,0));
	printf("Quantidade de nós = %d\n",quantidadeNos(raiz,0));*/
	busca = remover(raiz,busca,650);
	if(busca != NULL){
		printf("%d removido\n",busca->numero);
	}
	imprimir1(raiz);
	printf("\n");
	return 0;
}
