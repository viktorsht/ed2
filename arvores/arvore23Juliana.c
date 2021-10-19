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

struct Arv23 *criaNo(int Info, struct Arv23 *FEsq, struct Arv23 *FCen){
	struct Arv23 *No;

	No = (struct Arv23 *) malloc(sizeof(struct Arv23 *));
	(*No).Info1 = Info;
	(*No).NInfos = 1;
	(*No).esq = FEsq;
	(*No).cen = FCen;
	(*No).dir = NULL;

return (No);
}

struct Arv23 *adicionaNo(struct Arv23 *No, int Info, struct Arv23 *Filho)
{
	if (Info > (*No).Info1){
		(*No).Info2 = Info;
		(*No).dir = Filho;
	}
	else{
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
	if(Info < (*No)->Info1){
		*Sobe = (*No)->Info1;
		*Novo = criaNo((*No)->Info2,(*No)->cen,(*No)->dir);
		(*No)->Info1 = Info;
		(*No)->cen = FilhoMaior;
		(*No)->dir = NULL;
		(*No)->NInfos = 1;
	}
	else if (Info < (*No)->Info2){
  	*Sobe = Info;
   	*Novo = criaNo((*No)->Info2,(*No)->cen,(*No)->dir);
   	(*No)->cen = FilhoMaior;
   	(*No)->dir = NULL;
   	(*No)->NInfos = 1;
	}
  else{
	*Sobe = (*No)->Info2;
	*Novo = criaNo(Info,(*No)->dir,FilhoMaior);
	(*No)->dir = NULL;
	(*No)->NInfos = 1;
	}
}

struct Arv23 *insereArv23(struct Arv23 **Pai,struct Arv23 **Raiz, int Valor, int *Sobe)
{ int inseriu = 1;
  struct Arv23 *No;
  No = NULL;
	if (*Raiz == NULL) {
		*Raiz = criaNo(Valor,NULL,NULL);
	}
	else{
	if(ehFolha(*Raiz)){
		if((**Raiz).NInfos == 1)
			*Raiz = adicionaNo(*Raiz,Valor,NULL);
		else{
			quebraNo(Raiz,Valor, NULL,Sobe, &No);
			if(Pai == NULL)
				{ struct Arv23 *Novo;
					Novo = criaNo(*Sobe,*Raiz,No);
					*Raiz = Novo;
					No = NULL;
				}
			}
		}
		else {if(Valor < (**Raiz).Info1)
			   No = insereArv23(Raiz,&((*Raiz)->esq), Valor,Sobe);
			  else if((Valor < (**Raiz).Info2 && (**Raiz).NInfos == 2) || (**Raiz).NInfos == 1)
				    No = insereArv23(Raiz,&((*Raiz)->cen), Valor,Sobe);
			      else No = insereArv23(Raiz,&((*Raiz)->dir), Valor,Sobe);
			  if(No != NULL)
			 	{
					if((**Raiz).NInfos == 1)
						{ *Raiz = adicionaNo(*Raiz,*Sobe,No);
							No = NULL;
						}
					else { int NovoSobe;
						struct Arv23 *NovoNo;
						quebraNo(Raiz,*Sobe, No,&NovoSobe, &NovoNo);
						if(Pai == NULL)
							{ struct Arv23 *Novo;
								Novo = criaNo(NovoSobe,*Raiz,NovoNo);
								*Raiz = Novo;
								No = NULL;
							}
						else No = NovoNo;
					}

				}
		}
	}

 return No;
}

int main() {

	return 0;
}
