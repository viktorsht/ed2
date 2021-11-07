#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Arv23 Arv23;

struct Arv23 {
    int chaveEsq, chaveDir; // data1,data2
    int  nChaves; // count
    Arv23 *esq, *centro, *dir;
};

void mostrar(Arv23 *Raiz);

Arv23 *criaNO(int info1, Arv23 *noEsq, Arv23 *noCentro);

Arv23 *adicionaNo(Arv23 *No, int info, Arv23 *Novo);

int folha(Arv23 *No);

Arv23 *quebraNo(Arv23 **Raiz, Arv23 *NovoNo, int info, int *infomeio);

Arv23 *insere23(Arv23 *pai, Arv23 **raiz, int info, int *infoMeio);

void remover(Arv23 **pai, Arv23 **Raiz, int info);

void imprimirOrdem(Arv23 *Raiz) {
    if (Raiz != NULL) {
        printf("%d %d\n", Raiz->chaveEsq, Raiz->chaveDir/*, Raiz->nChaves*/);
        imprimirOrdem(Raiz->esq);
        imprimirOrdem(Raiz->centro);
        imprimirOrdem(Raiz->dir);
    }
}

int search(Arv23 *root, int x, int result){
    if(root != NULL){
        if(x == root->chaveEsq) result = 1;
        else if(x == root->chaveDir) result = 1;
        else if(x < root->chaveEsq) result = search(root->esq, x, result);
        else if (x > root->chaveEsq && x < root->chaveDir) result = search(root->centro, x, result);
        else result = search(root->dir, x, result);
    }
    return result;

}

int main() {
    Arv23 *Raiz = NULL;
    int infoMeio;
    int num[6] = {500, 100, 400, 300, 600, 450};
    for(int i = 0; i < 6; i++){
      insere23(NULL, &Raiz, num[i], &infoMeio);
    }
    //remover(NULL, &Raiz, 1000);

    /* a função remover não consegue remover as raizes!*/
    printf("ÁRVORE INICIO\n");
    mostrar(Raiz);
    printf("\n\n\n");
    //printf("Buscas: %d\n",search(Raiz,350,0));
    //remover(NULL,&Raiz,400);
    remover(NULL,&Raiz,100);
    remover(NULL,&Raiz,500);
    //remover(NULL,&Raiz,300);
    //remover(NULL,&Raiz,600);
    //remover(NULL,&Raiz,450);



    printf("ÁRVORE FINAL\n");
    mostrar(Raiz);


    return 0;
}

int estaContido(Arv23 *Raiz, int info) {
    if (info == Raiz->chaveEsq)
        return 1;
    if (info == Raiz->chaveDir)
        return 2;
    return 0;
}

void remover(Arv23 **pai, Arv23 **Raiz, int info) {
    if (*Raiz != NULL) {
        if (estaContido(*Raiz, info) != 0) { // se 0 é pq não é raiz

            if (*pai == NULL && folha(*Raiz)) { // Verifica se a Raiz da Árvore é um nó Folha.
              printf("estou no primeiro if\n");
                if (estaContido(*Raiz, info) == 1)
                    (**Raiz).chaveEsq = (**Raiz).chaveDir;
                (**Raiz).chaveDir = 0;

                if ((**Raiz).nChaves == 2){

                  (**Raiz).nChaves = 1;
                }
                else{

                  *Raiz = NULL;
                }
            }

            else if (*pai == NULL) {
                if ((**Raiz).nChaves == 2) {
                    if (estaContido(*Raiz, info) == 2 && (**Raiz).dir->nChaves == 2) {
                        (**Raiz).chaveDir = (**Raiz).dir->chaveEsq;
                        (**Raiz).dir->chaveEsq = (**Raiz).dir->chaveDir;
                        (**Raiz).dir->chaveDir = 0;
                        (**Raiz).dir->nChaves = 1;
                    }

                    else if (estaContido(*Raiz, info) == 2 && (**Raiz).centro->nChaves == 2) {
                        (**Raiz).chaveDir = (**Raiz).centro->chaveDir;
                        (**Raiz).centro->chaveDir = 0;
                        (**Raiz).dir->nChaves = 1;
                    }

                    else if (estaContido(*Raiz, info) == 2 && (**Raiz).esq->nChaves == 2) {
                        (**Raiz).chaveDir = 0;
                        (**Raiz).nChaves = 1;
                        (**Raiz).centro->chaveDir = (**Raiz).dir->chaveEsq;
                        (**Raiz).centro->nChaves = 2;
                        (**Raiz).dir = NULL;
                    }

                    else if (estaContido(*Raiz, info) == 2 && (**Raiz).esq->nChaves == 1) {
                        (**Raiz).chaveDir = 0;
                        (**Raiz).nChaves = 1;
                        (**Raiz).centro->chaveDir = (**Raiz).dir->chaveEsq;
                        (**Raiz).centro->nChaves = 2;
                        (**Raiz).dir = NULL;
                    }

                    else if (estaContido(*Raiz, info) == 1 && (**Raiz).centro->nChaves == 2) {
                        (**Raiz).chaveEsq = (**Raiz).centro->chaveEsq;
                        (**Raiz).centro->chaveEsq = (**Raiz).centro->chaveDir;
                        (**Raiz).centro->chaveDir = 0;
                        (**Raiz).centro->nChaves = 1;
                    }

                    else if (estaContido(*Raiz, info) == 1 && (**Raiz).esq->nChaves == 2) {
                        (**Raiz).chaveEsq = (**Raiz).esq->chaveDir;
                        (**Raiz).esq->chaveDir = 0;
                        (**Raiz).esq->nChaves = 1;
                    }

                    else if (estaContido(*Raiz, info) == 1 && (**Raiz).centro->nChaves == 1) {
                        (**Raiz).chaveEsq = (**Raiz).chaveDir;
                        (**Raiz).chaveDir = 0;
                        (**Raiz).nChaves = 1;
                        (**Raiz).esq->chaveDir = (**Raiz).centro->chaveEsq;
                        (**Raiz).esq->nChaves = 2;
                        (**Raiz).centro = NULL;
                    }

                    else if ((**Raiz).nChaves == 1) {
                        if ((**Raiz).centro->nChaves == 2) {
                            (**Raiz).chaveEsq = (**Raiz).centro->chaveEsq;
                            (**Raiz).centro->chaveEsq = (**Raiz).centro->chaveDir;
                            (**Raiz).centro->chaveDir = 0;
                            (**Raiz).centro->nChaves = 1;
                        }

                        else if ((**Raiz).esq->nChaves == 2) {
                            (**Raiz).chaveEsq = (**Raiz).esq->chaveDir;
                            (**Raiz).esq->chaveDir = 0;
                            (**Raiz).esq->nChaves = 1;
                        }

                        else {
                            (**Raiz).esq->chaveDir = (**Raiz).centro->chaveEsq;
                            (**Raiz).esq->nChaves = 2;
                            (**Raiz).dir = NULL;
                            *Raiz = (**Raiz).esq;
                        }
                    }
                }
            }

            else if (*pai != NULL && folha(*Raiz)) {

                if ((**Raiz).nChaves == 2) {
                    if (estaContido(*Raiz, info) == 1)
                        (**Raiz).chaveEsq = (**Raiz).chaveDir;
                    (**Raiz).chaveDir = 0;

                    (**Raiz).nChaves = 1;
                }

                else if ((**pai).nChaves == 2) {
                    if (info > (**pai).chaveDir && (**pai).centro->nChaves == 2) {
                        (**Raiz).chaveEsq = (**pai).chaveDir;
                        (**pai).chaveDir = (**pai).centro->chaveDir;
                        (**pai).centro->chaveDir = 0;
                        (**pai).centro->nChaves = 1;
                    }

                    else if (info > (**pai).chaveDir && (**pai).centro->nChaves == 1) {
                        (**pai).centro->chaveDir = (**pai).chaveDir;
                        (**pai).centro->nChaves = 2;
                        (**pai).chaveDir = 0;
                        (**pai).nChaves = 1;
                        *Raiz = NULL;
                    }

                    else if (info > (**pai).chaveEsq && (**pai).dir->nChaves == 2) {
                        (**Raiz).chaveEsq = (**pai).chaveDir;
                        (**pai).chaveDir = (**pai).dir->chaveEsq;
                        (**pai).dir->chaveEsq = (**pai).dir->chaveDir;
                        (**pai).dir->chaveDir = 0;
                        (**pai).dir->nChaves = 1;
                    }

                    else if (info > (**pai).chaveEsq && (**pai).dir->nChaves == 1) {
                        (**Raiz).chaveEsq = (**pai).chaveDir;
                        (**Raiz).chaveDir = (**pai).dir->chaveEsq;
                        (**Raiz).nChaves = 2;
                        (**pai).chaveDir = 0;
                        (**pai).nChaves = 1;
                        (**pai).dir = NULL;
                    }

                    else if (info < (**pai).chaveEsq && (**pai).centro->nChaves == 2) {
                        (**Raiz).chaveEsq = (**pai).chaveEsq;
                        (**pai).chaveEsq = (**pai).centro->chaveEsq;
                        (**pai).centro->chaveEsq = (**pai).centro->chaveDir;
                        (**pai).centro->chaveDir = 0;
                        (**pai).centro->nChaves = 1;
                    }

                    else if (info < (**pai).chaveEsq && (**pai).dir->nChaves == 2) {
                        (**Raiz).chaveEsq = (**pai).chaveEsq;
                        (**pai).chaveEsq = (**pai).centro->chaveEsq;
                        (**pai).centro->chaveEsq = (**pai).chaveDir;
                        (**pai).chaveDir = (**pai).dir->chaveEsq;
                        (**pai).dir->chaveEsq = (**pai).dir->chaveDir;
                        (**pai).dir->chaveDir = 0;
                        (**pai).dir->nChaves = 1;
                    }

                    else {
                        (**Raiz).chaveEsq = (**pai).chaveEsq;
                        (**pai).chaveEsq = (**pai).centro->chaveEsq;
                        (**pai).centro->chaveEsq = (**pai).chaveDir;
                        (**pai).chaveDir = 0;
                        (**pai).nChaves = 1;
                        (**pai).centro->chaveDir = (**pai).dir->chaveEsq;
                        (**pai).centro->nChaves = 2;
                        (**pai).dir = NULL;
                    }
                }

                else {
                    if (info > (**pai).chaveEsq && (**pai).esq->nChaves == 2) {
                        (**Raiz).chaveEsq = (**pai).chaveEsq;
                        (**pai).chaveEsq = (**pai).esq->chaveDir;
                        (**pai).esq->chaveDir = 0;
                        (**pai).esq->nChaves = 1;
                    }

                    else if (info < (**pai).chaveEsq && (**pai).centro->nChaves == 2) {
                        (**Raiz).chaveEsq = (**pai).chaveEsq;
                        (**pai).chaveEsq = (**pai).centro->chaveEsq;
                        (**pai).centro->chaveEsq = (**pai).centro->chaveDir;
                        (**pai).centro->chaveDir = 0;
                        (**pai).centro->nChaves = 1;
                    }

                    else if (info < (**pai).chaveEsq) {
                        (**Raiz).chaveEsq = (**pai).chaveEsq;
                        (**Raiz).chaveDir = (**pai).centro->chaveEsq;
                        (**Raiz).nChaves = 2;
                        *pai = *Raiz;
                    }

                    else {
                        (**pai).esq->chaveDir = (**pai).chaveEsq;
                        (**pai).esq->nChaves = 2;
                        *pai = (**pai).esq;
                    }
                }
            }

            else if (*pai != NULL && !folha(*Raiz)) {

                if (estaContido(*Raiz, info) == 2) {
                    if ((**Raiz).dir->nChaves == 2) {
                        (**Raiz).chaveDir = (**Raiz).dir->chaveEsq;
                        (**Raiz).dir->chaveEsq = (**Raiz).dir->chaveDir;
                        (**Raiz).dir->chaveDir = 0;
                        (**Raiz).dir->nChaves = 1;
                    }

                    else if ((**Raiz).centro->nChaves == 2) {
                        (**Raiz).chaveDir = (**Raiz).centro->chaveDir;
                        (**Raiz).centro->chaveDir = 0;
                        (**Raiz).centro->nChaves = 1;
                    }

                    else {
                        (**Raiz).centro->chaveDir = (**Raiz).dir->chaveEsq;
                        (**Raiz).centro->nChaves = 2;
                        (**Raiz).chaveDir = 0;
                        (**Raiz).nChaves = 2;
                        (**Raiz).dir = NULL;
                    }
                }

                else if (estaContido(*Raiz, info) == 1) {
                    if ((**Raiz).centro->nChaves == 2) {
                        (**Raiz).chaveEsq = (**Raiz).centro->chaveEsq;
                        (**Raiz).centro->chaveEsq = (**Raiz).centro->chaveDir;
                        (**Raiz).centro->chaveDir = 0;
                        (**Raiz).centro->nChaves = 1;
                    }

                    else if ((**Raiz).esq->nChaves == 2) {
                        (**Raiz).chaveEsq = (**Raiz).esq->chaveDir;
                        (**Raiz).esq->chaveDir = 0;
                        (**Raiz).esq->nChaves = 1;
                    }

                    else {
                        (**Raiz).chaveEsq = (**Raiz).centro->chaveEsq;
                        (**Raiz).centro->chaveEsq = (**Raiz).chaveDir;
                        (**Raiz).chaveDir = (**Raiz).dir->chaveEsq;
                        (**Raiz).dir->chaveEsq = (**Raiz).dir->chaveDir;
                        (**Raiz).dir->chaveDir = 0;
                        (**Raiz).dir->nChaves = 1;
                    }
                }

            }
            else{
              printf("não entrei em ninguém\n");
            }
        }

        else if (info < (**Raiz).chaveEsq){
          remover(Raiz, &(**Raiz).esq, info);
        }

        else if ((**Raiz).nChaves == 1){
          remover(Raiz, &(**Raiz).centro, info);
        }

        else if (info < (**Raiz).chaveDir){
          remover(Raiz, &(**Raiz).centro, info);
        }

        else{
          remover(Raiz, &(**Raiz).dir, info);
        }
    }
}

void mostrar(Arv23 *raiz) {
    if (raiz != NULL) {
        printf("%d %d\n", raiz->chaveEsq, raiz->chaveDir/*, raiz->nChaves*/);
        mostrar(raiz->esq);
        mostrar(raiz->centro);
        mostrar(raiz->dir);
    }
}


Arv23 *criaNO(int info1, Arv23 *noEsq, Arv23 *noCentro) {
    Arv23 *no = (Arv23*) malloc(sizeof(Arv23));

    (*no).chaveEsq = info1;
    (*no).chaveDir = 0;
    (*no).nChaves = 1;
    (*no).esq = noEsq;
    (*no).centro = noCentro;
    (*no).dir = NULL;

    return no;
}

Arv23 *adicionaNo(Arv23 *Raiz, int info, Arv23 *Novo) {
    if (info > (*Raiz).chaveEsq) {
        (*Raiz).chaveDir = info;
        (*Raiz).dir = Novo;
    } else {
        (*Raiz).chaveDir = (*Raiz).chaveEsq;
        (*Raiz).chaveEsq = info;
        (*Raiz).dir = (*Raiz).centro;
        (*Raiz).centro = Novo;
    }

    (*Raiz).nChaves = 2;
    return Raiz;
}

int folha(Arv23 *Raiz) {
    int folha = 0;

    if ((*Raiz).esq == NULL && (*Raiz).centro == NULL && (*Raiz).dir == NULL)
        folha = 1;

    return folha;
}

Arv23 *quebraNo(Arv23 **Raiz, Arv23 *NovoNo, int info, int *infoMeio) {
    Arv23 *Novo;

    if (info > (**Raiz).chaveDir) {
        *infoMeio = (**Raiz).chaveDir;
        Novo = criaNO(info, (**Raiz).dir, NovoNo);
    }

    else if (info < (**Raiz).chaveEsq) {
        *infoMeio = (**Raiz).chaveEsq;
        Novo = criaNO((**Raiz).chaveDir, (**Raiz).centro, (**Raiz).dir);

        (**Raiz).chaveEsq = info;
        (**Raiz).centro = NovoNo;
    }

    else {
        *infoMeio = info;
        Novo = criaNO((**Raiz).chaveDir, NovoNo, (**Raiz).dir);
    }

    (**Raiz).chaveDir = 0;
    (**Raiz).nChaves = 1;
    (**Raiz).dir = NULL;

    return Novo;
}


Arv23 *insereArv23(Arv23 *Pai,Arv23 **Raiz, int Valor, int *Sobe)
{
  Arv23 *MaiorNo;
  MaiorNo = NULL;
	if (*Raiz == NULL)
	{
		*Raiz = criaNo(Valor,NULL,NULL);

	}else {
		if(ehFolha(*Raiz))
		{
			if((**Raiz).NInfos == 1)
				*Raiz = adicionaNo(*Raiz,Valor,NULL);
			else { Arv23 *NovoNo;
				     NovoNo = NULL;
				    quebraNo(Raiz,Valor, NULL,Sobe, &NovoNo);

					 if(Pai == NULL)
					{
						Arv23 *FEsq, *FCen;
						FEsq = *Raiz;
						FCen = NovoNo;

						*Raiz = criaNo(*Sobe,FEsq,FCen);

						MaiorNo = NULL;
					}
				    else MaiorNo = NovoNo;
				}
		}
		else
			{
			 if(Valor < (**Raiz).Info1)
			   MaiorNo = insereArv23(*Raiz,&((*Raiz)->esq), Valor,Sobe);
			  else if((Valor < (**Raiz).Info2 && (**Raiz).NInfos == 2) || (**Raiz).NInfos == 1)
					{
						MaiorNo = insereArv23(*Raiz,&((*Raiz)->cen), Valor,Sobe);
					}
			      else {
						MaiorNo = insereArv23(*Raiz,&((*Raiz)->dir), Valor,Sobe);
					}
			  if(MaiorNo != NULL)
			 	{
					if((**Raiz).NInfos == 1)
						{ *Raiz = adicionaNo(*Raiz,*Sobe,MaiorNo);
							MaiorNo = NULL;
						}
					else { int NovoSobe;
						Arv23 *NovoNo;
						quebraNo(Raiz,*Sobe, MaiorNo,&NovoSobe, &NovoNo);
						if(Pai == NULL)
							{ Arv23 *Novo;
								Novo = criaNo(NovoSobe,*Raiz,NovoNo);
								*Raiz = Novo;
								MaiorNo = NULL;
							}
						else MaiorNo = NovoNo;
					}

				}
		}
		}


 return MaiorNo;
}

/*
int contains(DTNode root, int key)

{
	if (key == root->key_left)
		return 1; // se esta na informação da esquerda
	else if(key == root->key_right)
		return 2; // se esta na informação da direita

	return 0; // em nenhuma das infos
}

int dttDelete(DTNode *parent, DTNode *root, int key)
{

	if (*root != NULL)
	{
		if (contains(*root, key) != 0)
		{
			if (*parent == NULL && isLeaf(*root))
			{
				if (contains(*root, key) == 1)
					(*root)->key_left = (*root)->key_right;

				(*root)->key_right = 0; // deixar vazia

				if((*root)->total_keys == 2)
					(*root)->total_keys = 1;
				else
					*root = NULL;
			}
			else if(*parent == NULL)
			{
				if((*root)->total_keys == 2)
				{
					if(contains(*root, key) == 2 && (*root)->right->total_keys == 2)
					{
						(*root)->key_right = (*root)->right->key_left;
						(*root)->right->key_left = (*root)->right->key_right;
						(*root)->right->key_right = 0;
						(*root)->right->total_keys = 1;
					}
					else if(contains(*root, key) == 2 && (*root)->cen->total_keys ==2)
					{
						(*root)->key_right = (*root)->cen->key_right;
						(*root)->cen->key_right = 0;
						(*root)->right->total_keys = 1;
					}
					else if(contains(*root, key) == 2 && (*root)->left->total_keys == 2)
					{
						(*root)->key_right = 0;
						(*root)->total_keys = 1;
						(*root)->cen->key_right = (*root)->right->key_left;
						(*root)->cen->total_keys = 2;
						(*root)->right = NULL;
					}
					else if(contains(*root, key) == 2 && (*root)->left->total_keys == 1)
					{
						(*root)->key_right = 0;
						(*root)->total_keys = 1;
						(*root)->cen->key_right = (*root)->right->key_left;
						(*root)->cen->total_keys = 2;
						(*root)->right = NULL;
					}
					else if(contains(*root, key) == 1 && (*root)->cen->total_keys == 2)
					{
						(*root)->key_left = (*root)->cen->key_left;
						(*root)->cen->key_left = (*root)->cen->key_right;
						(*root)->cen->key_right = 0;
						(*root)->cen->total_keys = 1;
					}
					else if(contains(*root, key) == 1 && (*root)->left->total_keys == 2)
					{
						(*root)->key_left = (*root)->left->key_right;
						(*root)->left->key_right = 0;
						(*root)->left->total_keys = 1;
					}
					else if (contains(*root, key) == 1 && (*root)->cen->total_keys == 1)
					{
						(*root)->key_left = (*root)->key_right;
						(*root)->key_right = 0;
						(*root)->total_keys = 1;
						(*root)->left->key_right = (*root)->cen->key_left;
						(*root)->left->total_keys = 2;
						(*root)->cen = NULL;
					}
					else if ((*root)->total_keys == 1)
					{
						if((*root)->cen->total_keys == 2)
						{
							(*root)->key_left = (*root)->cen->key_left;
							(*root)->cen->key_left = (*root)->cen->key_right;
							(*root)->cen->key_right = 0;
							(*root)->cen->total_keys = 1;
						}
						else if((*root)->left->total_keys == 2)
						{
							(*root)->key_left = (*root)->left->key_right;
							(*root)->left->key_right = 0;
							(*root)->left->total_keys = 1;
						}
						else
						{
							(*root)->left->key_right = (*root)->cen->key_left;
							(*root)->left->total_keys = 2;
							(*root)->right = NULL;
							*root = (*root)->left;
						}
					}
				}
			}
			else if(*parent != NULL && isLeaf(*root))
			{
				if ((*root)->total_keys == 2)
				{
					if(contains(*root, key) == 1)
						(*root)->key_left = (*root)->key_right;

					(*root)->key_right = 0;
					(*root)->total_keys = 1;
				}
				else if ((*parent)->total_keys == 2)
				{
					if (key > (*parent)->key_right && (*parent)->cen->total_keys == 2)
					{
						(*root)->key_left = (*parent)->key_right;
						(*parent)->key_right = (*parent)->cen->key_right;
						(*parent)->cen->key_right = 0;
						(*parent)->cen->total_keys = 1;
					}
					else if(key > (*parent)->key_right && (*parent)->cen->total_keys == 1)
					{
						(*parent)->cen->key_right = (*parent)->key_right;
						(*parent)->cen->total_keys = 2;
						(*parent)->key_right = 0;
						(*parent)->total_keys = 1;
						*root = NULL;
					}
					else if(key > (*parent)->key_left && (*parent)->right->total_keys == 2)
					{
						(*root)->key_left = (*parent)->key_right;
						(*parent)->key_right = (*parent)->right->key_left;
						(*parent)->right->key_left = (*parent)->right->key_right;
						(*parent)->right->key_right = 0;
						(*parent)->right->total_keys = 1;
					}
					else if(key > (*parent)->key_left && (*parent)->right->total_keys == 1)
					{
						(*root)->key_left = (*parent)->key_right;
						(*root)->key_right = (*parent)->right->key_left;
						(*root)->total_keys = 2;
						(*parent)->key_right = 0;
						(*parent)->total_keys = 1;
						(*parent)->right = NULL;
					}

					else if(key < (*parent)->key_left && (*parent)->cen->total_keys == 2)
					{
						(*root)->key_left = (*parent)->key_left;
						(*parent)->key_left = (*parent)->cen->key_left;
						(*parent)->cen->key_left = (*parent)->cen->key_right;
						(*parent)->cen->key_right = 0;
						(*parent)->cen->total_keys = 1;
					}
					else if (key < (*parent)->key_left && (*parent)->right->total_keys == 2)
					{
						(*root)->key_left = (*parent)->key_left;
						(*parent)->key_left = (*parent)->cen->key_left;
						(*parent)->cen->key_left = (*parent)->key_right;

						(*parent)->key_right = (*parent)->right->key_left;
						(*parent)->right->key_left = (*parent)->right->key_right;
						(*parent)->right->key_right = 0;
						(*parent)->right->total_keys = 1;
					}
					else
					{
						(*root)->key_left = (*parent)->key_left;
						(*parent)->key_left = (*parent)->cen->key_left;
						(*parent)->cen->key_left = (*parent)->key_right;
						(*parent)->key_right = 0;
						(*parent)->total_keys = 1;
						(*parent)->cen->key_right = (*parent)->right->key_left;
						(*parent)->cen->total_keys = 2;
						(*parent)->right = NULL;
					}
				}

				else
				{
					if (key > (*parent)->key_left && (*parent)->left->total_keys == 2)
					{
						(*root)->key_left = (*parent)->key_left;
						(*parent)->key_left = (*parent)->left->key_right;
						(*parent)->left->key_right = 0;
						(*parent)->left->total_keys = 1;
					}
					else if (key < (*parent)->key_left && (*parent)->cen->total_keys == 2)
					{
						(*root)->key_left = (*parent)->key_left;
						(*parent)->key_left = (*parent)->cen->key_left;
						(*parent)->cen->key_left = (*parent)->cen->key_right;
						(*parent)->cen->key_right = 0;
						(*parent)->cen->total_keys = 1;
					}
					else if(key < (*parent)->key_left)
					{
						(*root)->key_left = (*parent)->key_left;
						(*root)->key_right = (*parent)->cen->key_left;
						(*root)->total_keys = 2;
						*parent = *root;
					}
					else
					{
						(*parent)->left->key_right = (*parent)->key_left;
						(*parent)->left->total_keys = 2;
						*parent = (*parent)->left;
					}
				}
			}

			else if(*parent != NULL && !isLeaf(*root))
			{
				if(contains(*root, key) == 2)
				{
					if ((*root)->right->total_keys == 2)
					{
						(*root)->key_right = (*root)->right->key_left;
						(*root)->right->key_left = (*root)->right->key_right;
						(*root)->right->key_right = 0;
						(*root)->right->total_keys = 1;
					}
					else if((*root)->cen->total_keys == 2)
					{
						(*root)->key_right = (*root)->cen->key_right;
						(*root)->cen->key_right = 0;
						(*root)->cen->total_keys = 1;
					}
					else
					{
						(*root)->cen->key_right = (*root)->right->key_left;
						(*root)->cen->total_keys = 2;
						(*root)->key_right = 0;
						(*root)->total_keys = 2;
						(*root)->right = NULL;
					}
				}
				else if (contains(*root, key) == 1)
				{
					if ((*root)->cen->total_keys == 2)
					{
						(*root)->key_left = (*root)->cen->key_left;
						(*root)->cen->key_left = (*root)->cen->key_right;
						(*root)->cen->key_right = 0;
						(*root)->cen->total_keys = 1;
					}
					else if((*root)->left->total_keys == 2)
					{
						(*root)->key_left = (*root)->left->key_right;
						(*root)->left->key_right = 0;
						(*root)->left->total_keys = 1;
					}
					else
					{
						(*root)->key_left = (*root)->cen->key_left;
						(*root)->cen->key_left = (*root)->key_right;
						(*root)->key_right = (*root)->right->key_left;
						(*root)->right->key_left = (*root)->right->key_right;
						(*root)->right->key_right = 0;
						(*root)->right->total_keys = 1;
					}
				}
			}

		}
		else if (key < (*root)->key_left)
			dttDelete(root, &(*root)->left, key);
		else if((*root)->total_keys == 1)
			dttDelete(root, &(*root)->cen, key);
		else if(key < (*root)->key_right)
			dttDelete(root, &(*root)->cen, key);
		else
			dttDelete(root, &(*root)->right, key);

	}


}
*/
