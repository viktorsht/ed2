#include <stdio.h>
#include <stdlib.h>

struct Arv23
{
	int Info1, Info2, NInfos;
	struct Arv23 *esq, *cen, *dir;
};

int ehFolha(struct Arv23 *Raiz)
{
	int folha = 0;
	if ((*Raiz).esq == NULL && (*Raiz).cen == NULL && (*Raiz).dir == NULL)
		folha = 1;

	return folha;
}

void inOrdem(struct Arv23 *Raiz)
{
	if (Raiz != NULL)
	{
		inOrdem((*Raiz).esq);
		printf("%d - ", (*Raiz).Info1);
		inOrdem((*Raiz).cen);
		if ((*Raiz).NInfos == 2)
			printf("%d - ", (*Raiz).Info2);
		inOrdem((*Raiz).dir);
	}
}

struct Arv23 *criaNo(int Info, struct Arv23 *FEsq, struct Arv23 *FCen)
{
	struct Arv23 *No;

	No = (struct Arv23 *)malloc(sizeof(struct Arv23));
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
	}
	else
	{
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
	if (Info < (**No).Info1)
	{
		*Sobe = (**No).Info1;
		*Novo = criaNo((**No).Info2, (**No).cen, (**No).dir);
		(**No).Info1 = Info;
		(**No).Info2 = 0;
		(**No).cen = FilhoMaior;
		(**No).dir = NULL;
		(**No).NInfos = 1;
	}
	else if (Info < (**No).Info2)
	{
		*Sobe = Info;
		*Novo = criaNo((**No).Info2, FilhoMaior, (**No).dir);
		(**No).Info2 = 0;
		(**No).dir = NULL;
		(**No).NInfos = 1;
	}
	else
	{
		*Sobe = (**No).Info2;
		*Novo = criaNo(Info, (**No).dir, FilhoMaior);
		(**No).Info2 = 0;
		(**No).dir = NULL;
		(**No).NInfos = 1;
	}
}

struct Arv23 *insereArv23(struct Arv23 *Pai, struct Arv23 **Raiz, int Valor, int *Sobe)
{
	struct Arv23 *MaiorNo;
	MaiorNo = NULL;
	if (*Raiz == NULL)
	{
		*Raiz = criaNo(Valor, NULL, NULL);
	}
	else
	{
		if (ehFolha(*Raiz))
		{
			if ((**Raiz).NInfos == 1)
				*Raiz = adicionaNo(*Raiz, Valor, NULL);
			else
			{
				struct Arv23 *NovoNo;
				NovoNo = NULL;
				quebraNo(Raiz, Valor, NULL, Sobe, &NovoNo);

				if (Pai == NULL)
				{
					struct Arv23 *FEsq, *FCen;
					FEsq = *Raiz;
					FCen = NovoNo;

					*Raiz = criaNo(*Sobe, FEsq, FCen);

					MaiorNo = NULL;
				}
				else
					MaiorNo = NovoNo;
			}
		}
		else
		{
			if (Valor < (**Raiz).Info1)
				MaiorNo = insereArv23(*Raiz, &((*Raiz)->esq), Valor, Sobe);
			else if ((Valor < (**Raiz).Info2 && (**Raiz).NInfos == 2) || (**Raiz).NInfos == 1)
			{
				MaiorNo = insereArv23(*Raiz, &((*Raiz)->cen), Valor, Sobe);
			}
			else
			{
				MaiorNo = insereArv23(*Raiz, &((*Raiz)->dir), Valor, Sobe);
			}
			if (MaiorNo != NULL)
			{
				if ((**Raiz).NInfos == 1)
				{
					*Raiz = adicionaNo(*Raiz, *Sobe, MaiorNo);
					MaiorNo = NULL;
				}
				else
				{
					int NovoSobe;
					struct Arv23 *NovoNo;
					quebraNo(Raiz, *Sobe, MaiorNo, &NovoSobe, &NovoNo);
					if (Pai == NULL)
					{
						struct Arv23 *Novo;
						Novo = criaNo(NovoSobe, *Raiz, NovoNo);
						*Raiz = Novo;
						MaiorNo = NULL;
					}
					else
					{
						MaiorNo = NovoNo;
						*Sobe = NovoSobe;
					}
				}
			}
		}
	}

	return MaiorNo;
}

int menorEsq(struct Arv23 *Raiz)
{
	int menor;

	if (Raiz != NULL)
	{
		if (ehFolha(Raiz))
			menor = Raiz->Info1;
		else
			menor = menorEsq(Raiz->esq);
	}
	return menor;
}

// ADICIONAR UM PARÂMETRO QUE PEGA O MENOR
// ALTERAR PAI PARA STRUCT NORMAL
// Menor = menor valor de uma subárvore
int removeArv23(struct Arv23 *Pai, struct Arv23 **Raiz, int informacao)
{
	int removeu = 0;
	struct Arv23 *aux;

	if (*Raiz != NULL)
	{
		if (ehFolha(*Raiz))
		{
			if ((*Raiz)->NInfos == 2)
			{
				if (informacao == (*Raiz)->Info2)
				{
					(*Raiz)->NInfos = 1;
					removeu = 2;
				}
				else if (informacao == (*Raiz)->Info1)
				{
					(*Raiz)->Info1 = (*Raiz)->Info2;
					(*Raiz)->NInfos = 1;
					removeu = 2;
				}
			}
			else
			{
				if (informacao == (*Raiz)->Info1)
					removeu = 1;
			}
		}
		else
		{
			if (informacao < (*Raiz)->Info1)
				removeu = removeArv23(*Raiz, &((*Raiz)->esq), informacao);
			else if (informacao == (*Raiz)->Info1)
			{
				/////EM DESENVOLVIMENTO
				if (!ehFolha((*Raiz)->cen))
				{
					int menor;
					menor = menorEsq((*Raiz)->cen);
					removeu = removeArv23((*Raiz), &((*Raiz)->cen), menor);
					if (removeu == 2)
						(*Raiz)->Info1 = menor;
				}
				else
				{
					if ((*Raiz)->cen->NInfos == 2)
					{
						(*Raiz)->Info1 = (*Raiz)->cen->Info1;
						(*Raiz)->cen->Info1 = (*Raiz)->cen->Info2;
						(*Raiz)->cen->NInfos = 1;
						removeu = 2;
					}
					else
					{
						if ((*Raiz)->NInfos == 2)
						{
							if ((*Raiz)->dir->NInfos == 2)
							{
								(*Raiz)->Info1 = (*Raiz)->cen->Info1;
								(*Raiz)->cen->Info1 = (*Raiz)->Info2;
								(*Raiz)->Info2 = (*Raiz)->dir->Info1;
								(*Raiz)->dir->Info1 = (*Raiz)->dir->Info2;
								(*Raiz)->dir->NInfos = 1;
							}
							else
							{
								(*Raiz)->Info1 = (*Raiz)->cen->Info1;
								(*Raiz)->cen->Info1 = (*Raiz)->Info2;
								(*Raiz)->cen->Info2 = (*Raiz)->dir->Info1;
								(*Raiz)->NInfos = 1;
								(*Raiz)->cen->NInfos = 2;
								aux = (*Raiz)->dir;
								(*Raiz)->dir = NULL;
								free(aux);
								removeu = 2;
							}
						}
						else
						{
							if ((*Raiz)->cen->NInfos == 2)
							{
								(*Raiz)->Info1 = (*Raiz)->cen->Info1;
								(*Raiz)->cen->Info1 = (*Raiz)->cen->Info2;
								(*Raiz)->cen->NInfos = 1;
								removeu = 2;
							}
							else
							{
								if ((*Raiz)->esq->NInfos == 2)
								{
									(*Raiz)->Info1 = (*Raiz)->esq->Info2;
									(*Raiz)->esq->NInfos = 1;
									removeu = 2;
								}
								else
								{
									(*Raiz)->Info1 = (*Raiz)->esq->Info1;
									(*Raiz)->Info2 = (*Raiz)->cen->Info1;
									(*Raiz)->NInfos = 2;
									aux = (*Raiz)->esq;
									(*Raiz)->esq = NULL;
									free(aux);
									aux = (*Raiz)->cen;
									(*Raiz)->cen = NULL;
									free(aux);
									removeu = 1;
								}
							}
						}
					}
				}
			}
			else if (((*Raiz)->NInfos == 2 && informacao < (*Raiz)->Info2) || (*Raiz)->NInfos == 1)
			{
				removeu = removeArv23(*Raiz, &((*Raiz)->cen), informacao);
			}
			else if ((*Raiz)->NInfos == 2 && informacao == (*Raiz)->Info2)
			{
				/////EM DESENVOLVIMENTO
				if (!ehFolha((*Raiz)->dir))
				{
					int menor;
					menor = menorEsq((*Raiz)->dir);
					removeu = removeArv23((*Raiz), &((*Raiz)->dir), menor);
					if (removeu == 2)
						(*Raiz)->Info1 = menor;
				}
				else
				{
					if ((*Raiz)->dir->NInfos == 1)
					{
						if ((*Raiz)->cen->NInfos == 1)
						{
							(*Raiz)->cen->Info2 = (*Raiz)->dir->Info1;
							(*Raiz)->cen->NInfos = 2;
							(*Raiz)->NInfos = 1;
							aux = (*Raiz)->dir;
							(*Raiz)->dir = NULL;
							free(aux);
						}
						else
						{
							(*Raiz)->Info2 = (*Raiz)->cen->Info2;
							(*Raiz)->cen->NInfos = 1;
						}
					}
					else
					{
						(*Raiz)->Info2 = (*Raiz)->dir->Info1;
						(*Raiz)->dir->Info1 = (*Raiz)->dir->Info2;
						(*Raiz)->dir->NInfos = 1;
					}
				}
				removeu = 2;
			}
			else
			{
				removeu = removeArv23(*Raiz, &((*Raiz)->dir), informacao);
			}

			if (removeu == 1)
			{
				// FILHO DA ESQUERDA
				if (informacao < (*Raiz)->Info1)
				{
					if ((*(*Raiz)->cen).NInfos == 1)
					{
						if ((*Raiz)->NInfos == 2)
						{
							if ((*Raiz)->dir->NInfos == 2)
							{
								(*Raiz)->esq->Info1 = (*Raiz)->Info1;
								(*Raiz)->Info1 = (*(*Raiz)->cen).Info1;
								(*(*Raiz)->cen).Info1 = (*Raiz)->Info2;
								(*Raiz)->Info2 = (*(*Raiz)->dir).Info1;
								(*(*Raiz)->dir).Info1 = (*(*Raiz)->dir).Info2;
								(*(*Raiz)->dir).NInfos = 1;
								removeu = 2;
							}
							else
							{
								(*Raiz)->esq->Info1 = (*Raiz)->Info1;
								(*Raiz)->Info1 = (*(*Raiz)->cen).Info1;
								(*(*Raiz)->cen).Info1 = (*Raiz)->Info2;
								(*Raiz)->NInfos = 1;
								(*(*Raiz)->cen).Info2 = (*(*Raiz)->dir).Info1;
								(*(*Raiz)->cen).NInfos = 2;
								aux = (*Raiz)->dir;
								(*Raiz)->dir = NULL;
								free(aux);
								removeu = 2;
							}
						}
						else
						{
							(*Raiz)->Info2 = (*(*Raiz)->cen).Info1;
							(*Raiz)->NInfos = 2;
							aux = (*Raiz)->esq;
							(*Raiz)->esq = NULL;
							free(aux);
							aux = (*Raiz)->cen;	 // PENSO QUE AQUI SERIA DO CENTRO
							(*Raiz)->cen = NULL; // PENSO QUE AQUI SERIA DO CENTRO
							free(aux);
							removeu = 2;
						}
					}
					else
					{
						(*Raiz)->esq->Info1 = (*Raiz)->Info1;
						(*Raiz)->Info1 = (*(*Raiz)->cen).Info1;
						(*(*Raiz)->cen).Info1 = (*(*Raiz)->cen).Info2;
						(*(*Raiz)->cen).NInfos = 1;
						removeu = 2;
					}
				}
				else if ((*Raiz)->NInfos == 1)
				{
					if ((*Raiz)->esq->NInfos == 2)
					{
						(*Raiz)->cen->Info1 = (*Raiz)->Info1;
						(*Raiz)->Info1 = (*Raiz)->esq->Info2;
						(*Raiz)->esq->NInfos = 1;
						removeu = 2;
					}
					else
					{
						(*Raiz)->Info2 = (*Raiz)->Info1;
						(*Raiz)->Info1 = (*Raiz)->esq->Info1;
						(*Raiz)->NInfos = 2;
						aux = (*Raiz)->esq;
						(*Raiz)->esq = NULL;
						free(aux);
						aux = (*Raiz)->cen;
						(*Raiz)->cen = NULL;
						free(aux);
						removeu = 2;
					}
				}
				else if ((*Raiz)->NInfos == 2 && informacao > (*Raiz)->Info2)
				{
					// FILHO DA DIREITA - Em desenvolvimento
					if ((*Raiz)->cen->NInfos == 2)
					{
						(*Raiz)->dir->Info1 = (*Raiz)->Info2;
						(*Raiz)->Info2 = (*Raiz)->cen->Info2;
						(*Raiz)->cen->NInfos = 1;
						removeu = 2;
					}
					else
					{
						(*Raiz)->cen->Info2 = (*Raiz)->Info2;
						(*Raiz)->NInfos = 1;
						(*Raiz)->cen->NInfos = 2;
						aux = (*Raiz)->dir;
						(*Raiz)->dir = NULL;
						free(aux);
						removeu = 2;
					}
				}
				else
				{
					// Filho da CENTRO - TEM IRMÃO DA DIREITA
					if ((*Raiz)->dir->NInfos == 2)
					{
						(*Raiz)->cen->Info1 = (*Raiz)->Info2;
						(*Raiz)->Info2 = (*Raiz)->dir->Info1;
						(*Raiz)->dir->Info1 = (*Raiz)->dir->Info2;
						(*Raiz)->dir->NInfos = 1;
						removeu = 2;
					}
					else
					{
						(*Raiz)->cen->Info1 = (*Raiz)->Info2;
						(*Raiz)->NInfos = 1;
						(*Raiz)->cen->Info2 = (*Raiz)->dir->Info1;
						(*Raiz)->cen->NInfos = 2;
						aux = (*Raiz)->dir;
						(*Raiz)->dir = NULL;
						free(aux);
						removeu = 2;
					}
				}
			}
		}
	}

	return removeu;
}

int main()
{
	struct Arv23 *Raiz, *Pai;
	int valor, aux, i = 0, menor = 0;
	Raiz = NULL;

	// do
	// {
	// 	printf("Valor[%d]: ", i + 1);
	// 	scanf("%d", &valor);
	// 	// if (valor != -1)
	// 	// {
	// 	// 	Pai = NULL;
	// 	// 	aux = 0;
	// 	// 	insereArv23(Pai, &Raiz, valor, &aux);
	// 	// }
	// 	i++;

	// } while (valor != -1);
	/*
	insereArv23(NULL, &Raiz, 100, &aux);
	insereArv23(NULL, &Raiz, 50, &aux);
	insereArv23(NULL, &Raiz, 25, &aux);
	insereArv23(NULL, &Raiz, 125, &aux);
	insereArv23(NULL, &Raiz, 20, &aux);
	insereArv23(NULL, &Raiz, 150, &aux);
	insereArv23(NULL, &Raiz, 140, &aux);
	insereArv23(NULL, &Raiz, 120, &aux);
	insereArv23(NULL, &Raiz, 10, &aux);
	insereArv23(NULL, &Raiz, 22, &aux);
	insereArv23(NULL, &Raiz, 5, &aux);
	insereArv23(NULL, &Raiz, 24, &aux);
	insereArv23(NULL, &Raiz, 23, &aux);
	insereArv23(NULL, &Raiz, 27, &aux);
	insereArv23(NULL, &Raiz, 26, &aux);
	insereArv23(NULL, &Raiz, 21, &aux);
	insereArv23(NULL, &Raiz, 29, &aux);
	insereArv23(NULL, &Raiz, 30, &aux);
	insereArv23(NULL, &Raiz, 105, &aux);
	insereArv23(NULL, &Raiz, 103, &aux);
	insereArv23(NULL, &Raiz, 122, &aux);*/

	int num[6] = {500, 100, 400, 300, 600, 450};
	for(int i = 0; i < 6; i++){
		Pai = NULL;
		insereArv23(Pai, &Raiz, num[i], &aux);
	//	aux = 0;
	}

	// 100, 50, 25, 125, 20, 150, 140, 120, 10, 22, 5, 24, 23,27,26,21,29,30,105,103, 122

	printf("Elementos in-ordem: \n");
	inOrdem(Raiz);

	printf("\n\n");

	removeArv23(NULL, &Raiz, 500);
	removeArv23(NULL, &Raiz, 100);
	removeArv23(NULL, &Raiz, 400);

	//removeArv23(NULL, &Raiz, 20);
	//removeArv23(NULL, &Raiz, 21);

	inOrdem(Raiz);
	printf("\n\n");

	// removeArv23(NULL, &Raiz, &menor, 20);
	// inOrdem(Raiz);
	// printf("\n\n");

	// removeArv23(NULL, &Raiz, &menor, 120);
	// inOrdem(Raiz);
	// printf("\n\n");

	// removeArv23(NULL, &Raiz, &menor, 25);

	// inOrdem(Raiz);
	// printf("\n\n");

	// removeArv23(NULL, &Raiz, &menor, 150);

	// inOrdem(Raiz);
	// printf("\n\n");

	// if (removeArv23(NULL, &Raiz, &menor, 120))
	// {
	// 	printf("\n\n");
	// }
	// 100, 50, 25, 125, 20, 150, 140, 120
	return 0;
}
