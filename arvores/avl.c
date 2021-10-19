#include<stdio.h>
#include<stdlib.h>

/*

		ÁRVORE AVL - CÓDIGO DE TESTE
    continuar de https://www.youtube.com/watch?v=lQsVUxa3Auk
*/

typedef struct no{
	int valor;
  int altura;
	struct no *esquerda;
	struct no *direita;
}Arvore;

int alturaNo(Arvore *raiz){
  int retorno;
  if(raiz == NULL) retorno = -1;
  else retorno = raiz->altura;
  return retorno;
}

int fatorBalanciamento(Arvore *raiz){
  return labs(alturaNo(raiz->esquerda) - alturaNo(raiz->direita));
  // The C library function long int labs(long int x) returns the absolute value of x.
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}


// rotações
void rotacaoLL(Arvore *raiz){
  Arvore *no;
  no = raiz->esquerda;
  raiz->esquerda = no->direita;
  no->direita = raiz;
  raiz->altura = maior(alturaNo(raiz->esquerda),alturaNo(raiz->direita)) + 1;
  no->altura = maior(alturaNo(no->esquerda),raiz->altura) + 1;
  raiz = no;
}

void rotacaoRR(Arvore *raiz){
  Arvore *no;
  no = raiz->direita;
  raiz->direita = no->esquerda;
  no->esquerda = raiz;
  raiz->altura = maior(alturaNo(raiz->esquerda),alturaNo(raiz->direita)) + 1;
  no->altura = maior(alturaNo(no->direita),raiz->altura) + 1;
  raiz = no;
}

void rotacaoLR(Arvore *raiz){
  rotacaoRR(raiz->esquerda);
  rotacaoLL(raiz);
}

void rotacaoRL(Arvore *raiz){
    rotacaoLL(raiz->direita);
    rotacaoRR(raiz);
}
/*
int inserir(Arvore *raiz, int chave){
	int res;
	if(raiz == NULL){
		Arvore *novo;
		//novo = (Arvore *)malloc(sizeof(Arvore));
		if(novo == NULL)
			return 0;
		novo->valor = chave;
		novo->altura = 0;
		novo->esquerda = NULL;
		novo->direita = NULL;
		raiz = novo;
		return 1;
	}
	Arvore *atual = raiz;
  if(chave < atual->valor){

        if(res = inserir(raiz->esquerda,chave) == 1){

            if(fatorBalanciamento(atual) >= 2){

                if(chave < raiz->esquerda->valor){

                    rotacaoLL(raiz);
                }
                else{

                    rotacaoLR(raiz);
                }
            }
        }
    }
    else{

        if(chave > atual->valor){

            if(res = inserir(raiz->direita,chave) == 1){

                if(fatorBalanciamento(atual) >= 2){

                    if(raiz->direita->valor < chave){

                        rotacaoRR(raiz);
                    }
                    else{

                        rotacaoRL(raiz);
                    }
                }
            }

        }
        else{

            printf("valor duplicado\n");
            return 0;
        }
    }
    atual->altura = maior(alturaNo(atual->esquerda),alturaNo(atual->direita)) + 1;
    return res;
}

Arvore *inserir(Arvore *raiz, int valor){
    Arvore *res;
    if(raiz == NULL){//�rvore vazia ou n� folha
        Arvore *novo;
        novo = (Arvore *)malloc(sizeof(Arvore));
         if(novo == NULL)
            return NULL; //falha

        novo->valor = valor;
        novo->altura = 0;
        novo->esquerda = NULL;
        novo->direita = NULL;
        raiz = novo;
				//printf("raiz->valor: %d\n", raiz->valor);

        return raiz; // sucesso
    }

		Arvore *atual = raiz;

    if(valor < atual->valor){
			//printf("atual->valor: %d\n", atual->valor);
        if((raiz = inserir(atual->esquerda, valor)) != NULL){
            if(fatorBalanciamento(atual) >= 2){
                if(valor < raiz->esquerda->valor ){
                    rotacaoLL(raiz);
                }else{
                    rotacaoLR(raiz);
                }
            }
        }
    }
		else{
        if(valor > atual->valor){
					//printf("atual->valor: %d\n", atual->valor);

            if((raiz = inserir(atual->direita, valor)) != NULL){
                if(fatorBalanciamento(atual) >= 2){
                    if(raiz->direita->valor < valor){
                        rotacaoRR(raiz);
                    }else{
                        rotacaoRL(raiz);
                    }
                }
            }
        }
				else{
            printf("Valor duplicado!!\n");
            return NULL;
        }
    }

    atual->altura = maior(alturaNo(atual->esquerda),alturaNo(atual->direita)) + 1;

    return raiz;
}
*/


Arvore* novoNo(int elem)//aloca um novo no com a chave dada e com ponteiros esquerdo e direito nulos
{
    Arvore* no = (Arvore*)
                        malloc(sizeof(Arvore));
    no->valor = elem; //no->info   = elem;
    no->esquerda    = NULL;
    no->direita    = NULL;
    no->altura = 0;  //novo no inicialmente eh uma folha

    return(no);
}


Arvore* inserir(Arvore* no, int chave) //funcao recursiva para inserir uma chave na subarvore de raiz no e retorna a nova raiz da subarvore
{
    //Passo 1: Insercao normal de arvore binaria de busca
    if (no == NULL)
        return(novoNo(chave));

    if (chave < no->valor)      //(chave < no->valor)
        no->esquerda = inserir(no->esquerda, chave);
    else if (chave > no->valor) //(chave > no->valor)
        no->direita = inserir(no->direita, chave);
    else //chaves iguais: nao permitido
        return no;

    //Passo 2: Atualizar a altura do no pai
    no->altura = maior(alturaNo(no->esquerda),
                           alturaNo(no->direita));

    ///Passo 3: Obter o fator de balanceamento do no pai e confirmar se esse no esta desbalanceado
    int balanco = fatorBalanciamento(no);

    //esquerda esquerda
    if (balanco > 1 && (chave < no->esquerda->valor))  //(balanco > 1 && chave < no->esquerda->valor)
        rotacaoRR(no);

    //direita direita
    if (balanco < -1 && (chave > no->direita->valor)) //(balanco < -1 && chave > no->direita->valor)
        rotacaoLL(no);

    //esquerda direita
    if (balanco > 1 && (chave > no->esquerda->valor))  //(balanco > 1 && chave > no->esquerda->valor)
    {/*
        no->esquerda =  rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);*/
				rotacaoLR(no);
    }

     //direita esquerda
    if (balanco < -1 && (chave < no->direita->valor)) //(balanco < -1 && chave < no->direita->valor)
    {	/*
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);*/
				rotacaoRL(no);
    }

    //retorna o ponteiro do no (nao modificado)
    return no;
}

void imprimir1(Arvore *raiz){
	if(raiz){
		printf("%d ",raiz->valor);
		imprimir1(raiz->esquerda);
		imprimir1(raiz->direita);
	}
}

int main(int argc, char *argv[]){
	Arvore *raiz = NULL;
	//int vetor[6] = {500,750,250,650,600,700};
	for(int i = 0; i < 1000; i++){
		raiz = inserir(raiz,rand() % 1000);
	}
	imprimir1(raiz);
	return 0;
}
