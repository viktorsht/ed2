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
    printf("ÁRVORE INICIO\n");
    mostrar(Raiz);
    //printf("Buscas: %d\n",search(Raiz,350,0));
    remover(NULL,&Raiz,450);
    remover(NULL,&Raiz,100);


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
        if (estaContido(*Raiz, info) != 0) {

            if (*pai == NULL && folha(*Raiz)) { // Verifica se a Raiz da Árvore é um nó Folha.
                if (estaContido(*Raiz, info) == 1)
                    (**Raiz).chaveEsq = (**Raiz).chaveDir;
                (**Raiz).chaveDir = 0;

                if ((**Raiz).nChaves == 2)
                    (**Raiz).nChaves = 1;
                else
                    *Raiz = NULL;
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

            else if (*pai != NULL && folha(*Raiz) == 0) {
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
        }

        else if (info < (**Raiz).chaveEsq)
            remover(Raiz, &(**Raiz).esq, info);

        else if ((**Raiz).nChaves == 1)
            remover(Raiz, &(**Raiz).centro, info);

        else if (info < (**Raiz).chaveDir)
            remover(Raiz, &(**Raiz).centro, info);

        else
            remover(Raiz, &(**Raiz).dir, info);
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

Arv23 *insere23(Arv23 *pai, Arv23 **Raiz, int info, int *infoMeio) {
    Arv23 *novo;

    if (*Raiz == NULL)
        *Raiz = criaNO(info, NULL, NULL);
    else {
        if (folha(*Raiz)) {
            if ((**Raiz).nChaves == 1) {
                *Raiz = adicionaNo(*Raiz, info, NULL);
                novo = NULL;
            } else {
                novo = quebraNo(Raiz, NULL, info, infoMeio);

                if (pai == NULL) {
                    *Raiz = criaNO(*infoMeio, *Raiz, novo);
                    novo = NULL;
			    }
            }
        } else {
            if (info < (**Raiz).chaveEsq)
                novo = insere23(*Raiz, &(**Raiz).esq, info, infoMeio);

            else if ((**Raiz).nChaves == 1)
                novo = insere23(*Raiz, &(**Raiz).centro, info, infoMeio);

            else if (info < (**Raiz).chaveDir)
                novo = insere23(*Raiz, &(**Raiz).centro, info, infoMeio);

            else
                novo = insere23(*Raiz, &(**Raiz).dir, info, infoMeio);

            if (novo != NULL) {
                if ((**Raiz).nChaves == 1) {
                    *Raiz = adicionaNo(*Raiz, *infoMeio, novo);
                    novo = NULL;
                } else {
                    novo = quebraNo(Raiz, novo, *infoMeio, infoMeio);

                    if (pai == NULL) {
                        *Raiz = criaNO(*infoMeio, *Raiz, novo);
                        novo = NULL;
                    }
                }
            }

        }
    }

    return novo;
}
