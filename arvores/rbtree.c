#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
    int cor;
}Arvore;

// =================================
// CRIA��O DA ARVORE
// =================================
Arvore* cria_ArvLLRB(){
    Arvore* raiz = (Arvore*) malloc(sizeof(Arvore));
    if(raiz != NULL){
        raiz = NULL;
    }
    return raiz;
}
// =================================
// LIBERAR
// =================================
void libera_NO( Arvore *no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvLLRB(Arvore* raiz){
    if(raiz == NULL)
        return;
    libera_NO(raiz);//libera cada n�
    free(raiz);//libera a raiz
}
// =================================
// CONSULTA �RVORE
// =================================
int consulta_ArvLLRB(Arvore *raiz, int valor){
    if(raiz == NULL)
        return 0;
     Arvore *atual = raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}
// =================================
// ROTA��O
// =================================
 Arvore* rotacionaEsquerda( Arvore *A){
     Arvore *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

 Arvore* rotacionaDireita( Arvore* A){
     Arvore* B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}
// =================================
// PROPRIEDADES
// =================================
int cor( Arvore* H){
    if(H == NULL)
        return BLACK;
    else
        return H->cor;
}

void trocaCor( Arvore* H){
    H->cor = !H->cor;
    if(H->esq != NULL)
        H->esq->cor = !H->esq->cor;
    if(H->dir != NULL)
        H->dir->cor = !H->dir->cor;
}

// =================================
// INSERCAO
// =================================
 Arvore* insereNO( Arvore* H, int valor, int *resp){
    if(H == NULL){
         Arvore *novo;
        novo = ( Arvore*)malloc(sizeof(Arvore));
        if(novo == NULL){
            *resp = 0;
            return NULL;
        }

        novo->info = valor;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }

    if(valor == H->info)
        *resp = 0;// Valor duplicado
    else{
        if(valor < H->info)
            H->esq = insereNO(H->esq,valor,resp);
        else
            H->dir = insereNO(H->dir,valor,resp);
    }

    //n� Vermelho � sempre filho � esquerda
    if(cor(H->dir) == RED && cor(H->esq) == BLACK)
        H = rotacionaEsquerda(H);

    //Filho e Neto s�o vermelhos
    //Filho vira pai de 2 n�s vermelhos
    if(cor(H->esq) == RED && cor(H->esq->esq) == RED)
        H = rotacionaDireita(H);

    //2 filhos Vermelhos: troca cor!
    if(cor(H->esq) == RED && cor(H->dir) == RED)
        trocaCor(H);

    return H;
}

int insere_ArvLLRB(Arvore *raiz, int valor){
    int resp;

    raiz = insereNO(raiz,valor,&resp);
    if((raiz) != NULL)
        (raiz)->cor = BLACK;

    return resp;
}
// =================================
// REMO��O
// =================================
 Arvore* balancear( Arvore* H){
    //n� Vermelho � sempre filho � esquerda
    if(cor(H->dir) == RED)
        H = rotacionaEsquerda(H);

    //Filho da direita e neto da esquerda s�o vermelhos
    //if(H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED)

    //Filho da esquerda e neto da esquerda s�o vermelhos
    if(H->esq != NULL && cor(H->esq) == RED && cor(H->esq->esq) == RED)
        H = rotacionaDireita(H);

    //2 filhos Vermelhos: troca cor!
    if(cor(H->esq) == RED && cor(H->dir) == RED)
        trocaCor(H);

    return H;
}

 Arvore* move2EsqRED( Arvore* H){
    trocaCor(H);
    if(cor(H->dir->esq) == RED){
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
}

 Arvore* move2DirRED( Arvore* H){
    trocaCor(H);
    if(cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
}

 Arvore* removerMenor( Arvore* H){
    if(H->esq == NULL){
        free(H);
        return NULL;
    }
    if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK)
        H = move2EsqRED(H);

    H->esq = removerMenor(H->esq);
    return balancear(H);
}

// tirei a recurs�o, assim fica igual a usada na AVL
 Arvore* procuraMenor( Arvore *atual){
     Arvore *no1 = atual;
     Arvore *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

 Arvore* remove_NO( Arvore *H, int valor){
    if(valor < H->info){
        if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK)
            H = move2EsqRED(H);

        H->esq = remove_NO(H->esq, valor);
    }else{
        if(cor(H->esq) == RED)
            H = rotacionaDireita(H);

        if(valor == H->info && (H->dir == NULL)){
            free(H);
            return NULL;
        }

        if(cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK)
            H = move2DirRED(H);

        if(valor == H->info){
             Arvore* x = procuraMenor(H->dir);
            H->info = x->info;
            H->dir = removerMenor(H->dir);
        }else
            H->dir = remove_NO(H->dir, valor);
    }
    return balancear(H);
}

int remove_ArvLLRB(Arvore *raiz, int valor){
    if(consulta_ArvLLRB(raiz,valor)){
         Arvore *h = raiz;
        raiz = remove_NO(h,valor);
        if(raiz != NULL)
            (raiz)->cor = BLACK;
        return 1;
    }else
        return 0;
}
// =================================
// PROPRIEDADES �RVORE
// =================================
int estaVazia_ArvLLRB(Arvore *raiz){
    if(raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvLLRB(Arvore *raiz){
    if (raiz == NULL)
        return 0;

    int alt_esq = totalNO_ArvLLRB(raiz->esq);
    int alt_dir = totalNO_ArvLLRB(raiz->dir);
    return (alt_esq + alt_dir + 1);
}

int altura_ArvLLRB(Arvore *raiz){
    if (raiz == NULL)
        return 0;
    int alt_esq = altura_ArvLLRB(raiz->esq);
    int alt_dir = altura_ArvLLRB(raiz->dir);
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}
// =================================
// PERCURSO
// =================================
void  posOrdem_ArvLLRB(Arvore *raiz, int H){
    if(raiz != NULL){
        posOrdem_ArvLLRB((raiz->esq),H+1);
        posOrdem_ArvLLRB((raiz->dir),H+1);

        if((raiz)->cor == RED)
            printf("%d  Vermelho: H(%d) \n",(raiz)->info,H);
        else
            printf("%d  Preto: H(%d) \n",(raiz)->info,H);

    }
}

void emOrdem_ArvLLRB(Arvore *raiz, int H){

    if(raiz != NULL){
        emOrdem_ArvLLRB(raiz->esq,H+1);

        if(raiz->cor == RED)
            printf("%d Vermelho: H(%d) \n",raiz->info,H);
        else
            printf("%d Preto: H(%d) \n",raiz->info,H);

        emOrdem_ArvLLRB(raiz->dir,H+1);
    }
}

void preOrdem_ArvLLRB(Arvore *raiz,int H){
    if(raiz != NULL){
        if(raiz->cor == RED)
            printf("%d  Vermelho: H(%d) \n",raiz->info,H);
        else
            printf("%d  Preto: H(%d) \n",raiz->info,H);

        preOrdem_ArvLLRB(raiz->esq,H+1);
        preOrdem_ArvLLRB(raiz->dir,H+1);
    }
}

int main(){
  Arvore *raiz = NULL;
	int vetor[6] = {200,100,300,50,150,120};
  int r = 0;
	for(int i = 0; i < 6; i++){
		raiz = insereNO(raiz,vetor[i],&r);
	}
  preOrdem_ArvLLRB(raiz,0);
  return 0;
}
