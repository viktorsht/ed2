#include <stdio.h>
#include <stdlib.h>

struct Arv23{
	 int Info1, Info2, NInfos;
	 struct Arv23 *esq, *cen, *dir;
};

int ehFolha(struct Arv23 *Raiz){
	int folha = 0;
	if((*Raiz).esq == NULL && (*Raiz).cen == NULL && (*Raiz).dir == NULL)
		folha =1;

return folha;
}

void inOrdem(struct Arv23 *Raiz)
{
	if (Raiz != NULL)
		{
			inOrdem((*Raiz).esq);
			printf("%d - ",(*Raiz).Info1);
			inOrdem((*Raiz).cen);
			if ((*Raiz).NInfos == 2)
				printf("%d - ",(*Raiz).Info2);
			inOrdem((*Raiz).dir);
		}

}


struct Arv23 *criaNo(int Info, struct Arv23 *FEsq, struct Arv23 *FCen)
{
	struct Arv23 *No;

	No = (struct Arv23 *) malloc(sizeof(struct Arv23));
	(*No).Info1 = Info;
	(*No).Info2 = 0;
	(*No).NInfos = 1;
	(*No).esq = FEsq;
	(*No).cen = FCen;
	(*No).dir = NULL;

return (No);
}

struct Arv23 *adicionaNo(struct Arv23 *No, int Info, struct Arv23 *Filho)
{
	if (Info > (*No).Info1)
	{
		(*No).Info2 = Info;
		(*No).dir = Filho;
	}else{
		(*No).Info2 = (*No).Info1;
		(*No).dir = (*No).cen;
		(*No).Info1 = Info;
		(*No).cen = Filho;
	}
	(*No).NInfos = 2;

return No;
}


void quebraNo(struct Arv23 **No, int Info, struct Arv23 *FilhoMaior, int *Sobe, struct Arv23 **Novo)
{
	if(Info < (**No).Info1)
	{
		*Sobe = (**No).Info1;
		*Novo = criaNo((**No).Info2,(**No).cen,(**No).dir);
		(**No).Info1 = Info;
		(**No).Info2 = 0;
		(**No).cen = FilhoMaior;
		(**No).dir = NULL;
		(**No).NInfos = 1;
	}
	else if (Info < (**No).Info2)
        	{
		       *Sobe = Info;
			   *Novo = criaNo((**No).Info2,FilhoMaior,(**No).dir);
			   (**No).Info2 = 0;
			   (**No).dir = NULL;
			   (**No).NInfos = 1;
	        }
	      else{
				*Sobe = (**No).Info2;
				*Novo = criaNo(Info,(**No).dir,FilhoMaior);
				(**No).Info2 = 0;
				(**No).dir = NULL;
				(**No).NInfos = 1;

			}

}

struct Arv23 *insereArv23(struct Arv23 *Pai,struct Arv23 **Raiz, int Valor, int *Sobe)
{
  struct Arv23 *MaiorNo;
  MaiorNo = NULL;
	if (*Raiz == NULL)
	{
		*Raiz = criaNo(Valor,NULL,NULL);

	}else {
		if(ehFolha(*Raiz))
		{
			if((**Raiz).NInfos == 1)
				*Raiz = adicionaNo(*Raiz,Valor,NULL);
			else { struct Arv23 *NovoNo;
				     NovoNo = NULL;
				    quebraNo(Raiz,Valor, NULL,Sobe, &NovoNo);

					 if(Pai == NULL)
					{
						struct Arv23 *FEsq, *FCen;
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
						struct Arv23 *NovoNo;
						quebraNo(Raiz,*Sobe, MaiorNo,&NovoSobe, &NovoNo);
						if(Pai == NULL)
							{ struct Arv23 *Novo;
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

int estaContido(struct Arv23 *Raiz, int info) {
  int  contido = 0;
    if (info == Raiz->Info2)
        contido = 1;
    else if (info == Raiz->Info1)
            contido =  2;
    return contido;
}

void remover(struct Arv23 **pai, struct Arv23 **Raiz, int info) {
    if (*Raiz != NULL) {
        if (estaContido(*Raiz, info) != 0) { ///NAO PRECISA DESTE TESTE

            if (ehFolha(*Raiz)) { // Verifica se a Raiz da Árvore é um nó Folha.
              if (estaContido(*Raiz, info) == 1 && (**Raiz).NInfos == 2)
                 {(**Raiz).Info2 = 0;
                  (**Raiz).NInfos = 1;}
              else if (estaContido(*Raiz, info) == 2 && (**Raiz).NInfos == 2)
                      {(**Raiz).Info1 = (**Raiz).Info2;
                        (**Raiz).NInfos = 1;}
                    else if (estaContido(*Raiz, info) == 2)
                          {  free(*Raiz);
                             *Raiz = NULL;
                            }


//              if ((**Raiz).NInfos == 2){
//
//                  (**Raiz).NInfos = 1;
//                }
//                else{
//
//                  *Raiz = NULL;
//                }
          }

            else if (*pai == NULL) {
                if ((**Raiz).NInfos == 2) {
                    if (estaContido(*Raiz, info) == 2 && (**Raiz).dir->NInfos == 2) {
                        (**Raiz).Info1 = (**Raiz).dir->Info2;
                        (**Raiz).dir->Info2 = (**Raiz).dir->Info1;
                        (**Raiz).dir->Info1 = 0;
                        (**Raiz).dir->NInfos = 1;
                    }

                    else if (estaContido(*Raiz, info) == 2 && (**Raiz).cen->NInfos == 2) {
                        (**Raiz).Info1 = (**Raiz).cen->Info1;
                        (**Raiz).cen->Info1 = 0;
                        (**Raiz).dir->NInfos = 1;
                    }

                    else if (estaContido(*Raiz, info) == 2 && (**Raiz).esq->NInfos == 2) {
                        (**Raiz).Info1 = 0;
                        (**Raiz).NInfos = 1;
                        (**Raiz).cen->Info1 = (**Raiz).dir->Info2;
                        (**Raiz).cen->NInfos = 2;
                        (**Raiz).dir = NULL;
                    }

                    else if (estaContido(*Raiz, info) == 2 && (**Raiz).esq->NInfos == 1) {
                        (**Raiz).Info1 = 0;
                        (**Raiz).NInfos = 1;
                        (**Raiz).cen->Info1 = (**Raiz).dir->Info2;
                        (**Raiz).cen->NInfos = 2;
                        (**Raiz).dir = NULL;
                    }

                    else if (estaContido(*Raiz, info) == 1 && (**Raiz).cen->NInfos == 2) {
                        (**Raiz).Info2 = (**Raiz).cen->Info2;
                        (**Raiz).cen->Info2 = (**Raiz).cen->Info1;
                        (**Raiz).cen->Info1 = 0;
                        (**Raiz).cen->NInfos = 1;
                    }

                    else if (estaContido(*Raiz, info) == 1 && (**Raiz).esq->NInfos == 2) {
                        (**Raiz).Info2 = (**Raiz).esq->Info1;
                        (**Raiz).esq->Info1 = 0;
                        (**Raiz).esq->NInfos = 1;
                    }

                    else if (estaContido(*Raiz, info) == 1 && (**Raiz).cen->NInfos == 1) {
                        (**Raiz).Info2 = (**Raiz).Info1;
                        (**Raiz).Info1 = 0;
                        (**Raiz).NInfos = 1;
                        (**Raiz).esq->Info1 = (**Raiz).cen->Info2;
                        (**Raiz).esq->NInfos = 2;
                        (**Raiz).cen = NULL;
                    }

                    else if ((**Raiz).NInfos == 1) {
                        if ((**Raiz).cen->NInfos == 2) {
                            (**Raiz).Info2 = (**Raiz).cen->Info2;
                            (**Raiz).cen->Info2 = (**Raiz).cen->Info1;
                            (**Raiz).cen->Info1 = 0;
                            (**Raiz).cen->NInfos = 1;
                        }

                        else if ((**Raiz).esq->NInfos == 2) {
                            (**Raiz).Info2 = (**Raiz).esq->Info1;
                            (**Raiz).esq->Info1 = 0;
                            (**Raiz).esq->NInfos = 1;
                        }

                        else {
                            (**Raiz).esq->Info1 = (**Raiz).cen->Info2;
                            (**Raiz).esq->NInfos = 2;
                            (**Raiz).dir = NULL;
                            *Raiz = (**Raiz).esq;
                        }
                    }
                }
            }

            else if (*pai != NULL && ehFolha(*Raiz)) {

                if ((**Raiz).NInfos == 2) {
                    if (estaContido(*Raiz, info) == 1)
                        (**Raiz).Info2 = (**Raiz).Info1;
                    (**Raiz).Info1 = 0;

                    (**Raiz).NInfos = 1;
                }

                else if ((**pai).NInfos == 2) {
                    if (info > (**pai).Info1 && (**pai).cen->NInfos == 2) {
                        (**Raiz).Info2 = (**pai).Info1;
                        (**pai).Info1 = (**pai).cen->Info1;
                        (**pai).cen->Info1 = 0;
                        (**pai).cen->NInfos = 1;
                    }

                    else if (info > (**pai).Info1 && (**pai).cen->NInfos == 1) {
                        (**pai).cen->Info1 = (**pai).Info1;
                        (**pai).cen->NInfos = 2;
                        (**pai).Info1 = 0;
                        (**pai).NInfos = 1;
                        *Raiz = NULL;
                    }

                    else if (info > (**pai).Info2 && (**pai).dir->NInfos == 2) {
                        (**Raiz).Info2 = (**pai).Info1;
                        (**pai).Info1 = (**pai).dir->Info2;
                        (**pai).dir->Info2 = (**pai).dir->Info1;
                        (**pai).dir->Info1 = 0;
                        (**pai).dir->NInfos = 1;
                    }

                    else if (info > (**pai).Info2 && (**pai).dir->NInfos == 1) {
                        (**Raiz).Info2 = (**pai).Info1;
                        (**Raiz).Info1 = (**pai).dir->Info2;
                        (**Raiz).NInfos = 2;
                        (**pai).Info1 = 0;
                        (**pai).NInfos = 1;
                        (**pai).dir = NULL;
                    }

                    else if (info < (**pai).Info2 && (**pai).cen->NInfos == 2) {
                        (**Raiz).Info2 = (**pai).Info2;
                        (**pai).Info2 = (**pai).cen->Info2;
                        (**pai).cen->Info2 = (**pai).cen->Info1;
                        (**pai).cen->Info1 = 0;
                        (**pai).cen->NInfos = 1;
                    }

                    else if (info < (**pai).Info2 && (**pai).dir->NInfos == 2) {
                        (**Raiz).Info2 = (**pai).Info2;
                        (**pai).Info2 = (**pai).cen->Info2;
                        (**pai).cen->Info2 = (**pai).Info1;
                        (**pai).Info1 = (**pai).dir->Info2;
                        (**pai).dir->Info2 = (**pai).dir->Info1;
                        (**pai).dir->Info1 = 0;
                        (**pai).dir->NInfos = 1;
                    }

                    else {
                        (**Raiz).Info2 = (**pai).Info2;
                        (**pai).Info2 = (**pai).cen->Info2;
                        (**pai).cen->Info2 = (**pai).Info1;
                        (**pai).Info1 = 0;
                        (**pai).NInfos = 1;
                        (**pai).cen->Info1 = (**pai).dir->Info2;
                        (**pai).cen->NInfos = 2;
                        (**pai).dir = NULL;
                    }
                }

                else {
                    if (info > (**pai).Info2 && (**pai).esq->NInfos == 2) {
                        (**Raiz).Info2 = (**pai).Info2;
                        (**pai).Info2 = (**pai).esq->Info1;
                        (**pai).esq->Info1 = 0;
                        (**pai).esq->NInfos = 1;
                    }

                    else if (info < (**pai).Info2 && (**pai).cen->NInfos == 2) {
                        (**Raiz).Info2 = (**pai).Info2;
                        (**pai).Info2 = (**pai).cen->Info2;
                        (**pai).cen->Info2 = (**pai).cen->Info1;
                        (**pai).cen->Info1 = 0;
                        (**pai).cen->NInfos = 1;
                    }

                    else if (info < (**pai).Info2) {
                        (**Raiz).Info2 = (**pai).Info2;
                        (**Raiz).Info1 = (**pai).cen->Info2;
                        (**Raiz).NInfos = 2;
                        *pai = *Raiz;
                    }

                    else {
                        (**pai).esq->Info1 = (**pai).Info2;
                        (**pai).esq->NInfos = 2;
                        *pai = (**pai).esq;
                    }
                }
            }

            else if (*pai != NULL && !ehFolha(*Raiz)) {

                if (estaContido(*Raiz, info) == 2) {
                    if ((**Raiz).dir->NInfos == 2) {
                        (**Raiz).Info1 = (**Raiz).dir->Info2;
                        (**Raiz).dir->Info2 = (**Raiz).dir->Info1;
                        (**Raiz).dir->Info1 = 0;
                        (**Raiz).dir->NInfos = 1;
                    }

                    else if ((**Raiz).cen->NInfos == 2) {
                        (**Raiz).Info1 = (**Raiz).cen->Info1;
                        (**Raiz).cen->Info1 = 0;
                        (**Raiz).cen->NInfos = 1;
                    }

                    else {
                        (**Raiz).cen->Info1 = (**Raiz).dir->Info2;
                        (**Raiz).cen->NInfos = 2;
                        (**Raiz).Info1 = 0;
                        (**Raiz).NInfos = 2;
                        (**Raiz).dir = NULL;
                    }
                }

                else if (estaContido(*Raiz, info) == 1) {
                    if ((**Raiz).cen->NInfos == 2) {
                        (**Raiz).Info2 = (**Raiz).cen->Info2;
                        (**Raiz).cen->Info2 = (**Raiz).cen->Info1;
                        (**Raiz).cen->Info1 = 0;
                        (**Raiz).cen->NInfos = 1;
                    }

                    else if ((**Raiz).esq->NInfos == 2) {
                        (**Raiz).Info2 = (**Raiz).esq->Info1;
                        (**Raiz).esq->Info1 = 0;
                        (**Raiz).esq->NInfos = 1;
                    }

                    else {
                        (**Raiz).Info2 = (**Raiz).cen->Info2;
                        (**Raiz).cen->Info2 = (**Raiz).Info1;
                        (**Raiz).Info1 = (**Raiz).dir->Info2;
                        (**Raiz).dir->Info2 = (**Raiz).dir->Info1;
                        (**Raiz).dir->Info1 = 0;
                        (**Raiz).dir->NInfos = 1;
                    }
                }

            }
        }

        else if (info < (**Raiz).Info2)
          remover(Raiz, &(**Raiz).esq, info);

        else if ((**Raiz).NInfos == 1)
          remover(Raiz, &(**Raiz).cen, info);

        else if (info < (**Raiz).Info1)
          remover(Raiz, &(**Raiz).cen, info);

        else
          remover(Raiz, &(**Raiz).dir, info);

    }
}


int main() {
	struct Arv23 *Raiz, *Pai;
	int valor, aux, i = 0;
	Raiz = NULL;

	printf("Digite -1 para sair\n");
	printf(" {500, 100, 400, 300, 600, 450}\n");
	int num[6] = {500, 100, 400, 300, 600, 450};
	for(int i = 0; i < 6; i++){
		Pai = NULL;
		insereArv23(Pai, &Raiz, num[i], &aux);
		aux = 0;
	}

	printf("Elementos in-ordem \n");
	inOrdem(Raiz);
	remover(&Pai,&Raiz,500);
	//remover(&Pai,&Raiz,600);

	//remover(&Pai,&Raiz,num[0]);
	//remover(&Pai,&Raiz,num[4]);
	printf("\nElementos in-ordem \n");
	inOrdem(Raiz);
	printf("\n");
	return 0;
}
