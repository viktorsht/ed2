#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define RED 1
#define BLACK 0
#define TAM 200

typedef struct lista
{
    int numero;
    struct lista *Prox;
} Lista;

typedef struct info
{
    char palavra[TAM];
    Lista *I, *F;
} Info;

struct raiz
{
    Info info;
    struct raiz *esq;
    struct raiz *dir;
    int cor;
};

typedef struct info2
{
    char *palavra1;
    char palavra[200];
    int linha;
} Info2;

// lista
Lista *alocaNo(int numero);
int listaVazia(Lista *I);
int buscarLista(Lista *I, int numero);
int inserirLista(Lista **I, Lista **F, Lista *No);
int removerLista(Lista **I, Lista **F, int numero);
void imprimirLista(Lista *I);

// Árvore
struct raiz *remove_ArvLLRB(struct raiz *no, char info[]);
struct raiz *rotacionaEsquerda(struct raiz *no);
struct raiz *rotacionaDireita(struct raiz *no);
struct raiz *insereNO(struct raiz *no, Info2 info, int *resp);
struct raiz *remove_NO(struct raiz *no, char info[]);
struct raiz *move2EsqRed(struct raiz *no);
struct raiz *move2DirRED(struct raiz *no);
struct raiz *balancear(struct raiz *no);
struct raiz *removeMenor(struct raiz *no);
struct raiz *procuraMenor(struct raiz *atual);
struct raiz *insere_ArvLLRB(struct raiz *no, Info2 info, int *inseriu);
void trocaCor(struct raiz *no);
void consulta_ArvLLRB(struct raiz *no, char info[], int *achou, int *passo);
void imprimir(struct raiz *no);
int cor(struct raiz *no);
int removerLis(struct raiz *no, char info[], int numero, int *achou, int *excluir);
int menu();

int main()
{
    struct raiz *no;
    int inseriu, numLinha = 1, opcao, achou, passo, inicio, fim;
    double tempoInserir, tempoBuscar;
    char linha[200];
    Info2 info;
    FILE *arq;
    no = NULL;

    arq = fopen("file.txt", "rt");

    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
    }
    else
    {
        inicio = clock();
        while (!feof(arq))
        {
            fgets(linha, 200, arq);
            info.palavra1 = strtok(linha, " ,.\n");
            do
            {
                info.linha = numLinha;
                if (info.palavra != NULL)
                {
                    strcpy(info.palavra, info.palavra1);
                    no = insere_ArvLLRB(no, info, &inseriu);
                }
                info.palavra1 = strtok(NULL, " ,.\n");
            } while (info.palavra1 != NULL);
            numLinha++;
        }
        fclose(arq);
        fim = clock();
        tempoInserir = (double)(fim - inicio) / CLOCKS_PER_SEC;
    }

    printf("Tempo para inserir: %f\n\n", tempoInserir);

    do
    {
        opcao = menu();
        switch (opcao)
        {
        case 1:
        {
            imprimir(no);
        }
        break;
        case 2:
        {
            int inseriu = 0;
            char p[200];

            printf("Palavra: ");
            scanf("%s", info.palavra);
            printf("Linha: ");
            scanf("%d", &info.linha);

            no = insere_ArvLLRB(no, info, &inseriu);
        }
        break;
        case 3:
        {
            passo = -1;
            achou = 0;
            char palavra[200];

            printf("Palavra: ");
            scanf("%s", palavra);

            inicio = clock();
            consulta_ArvLLRB(no, palavra, &achou, &passo);
            fim = clock();
            tempoBuscar = (double)(fim - inicio) / CLOCKS_PER_SEC;

            if (achou == 0)
            {
                printf("\nPalavra não encontrada na árvore!\n");
            }

            printf("\nTempo para buscar: %f", tempoBuscar);
        }
        break;
        case 4:
        {
            int numlinha, excluir = 0, seila;
            char palavra[100];
            achou = 0;

            printf("Palavra: ");
            scanf("%s", palavra);
            printf("Linha:");
            scanf("%d", &numlinha);

            seila = removerLis(no, palavra, numlinha, &achou, &excluir);
            if (excluir == 1)
                no = remove_ArvLLRB(no, palavra);
            if (achou == 0)
            {
                printf("\nPalavra não encontrada na árvore!\n");
            }
        }
        break;
        default:
            break;
        }
    } while (opcao != 5);

    return 0;
}

int menu()
{
    int opcao;
    do
    {
        printf("\n\n[1] - Imprimir árvore em ordem alfabética\n");
        printf("[2] - Inserir uma palavra\n");
        printf("[3] - Imprimir uma palavra\n");
        printf("[4] - Remover uma palavra de um determinada linha\n");
        printf("[5] - Sair\nOpcão: ");
        scanf("%d", &opcao);
    } while (opcao < 1 || opcao > 5);

    return opcao;
}

int cor(struct raiz *no)
{
    return no == NULL ? BLACK : no->cor;
}

void trocaCor(struct raiz *no)
{
    no->cor = !no->cor;
    if (no->esq != NULL)
    {
        no->esq->cor = !no->esq->cor;
    }
    if (no->dir != NULL)
    {
        no->dir->cor = !no->dir->cor;
    }
}

struct raiz *rotacionaEsquerda(struct raiz *no)
{
    struct raiz *novo = no->dir;
    no->dir = novo->esq;
    novo->esq = no;
    novo->cor = no->cor;
    no->cor = RED;
    return novo;
}

struct raiz *rotacionaDireita(struct raiz *no)
{
    struct raiz *novo = no->esq;
    no->esq = novo->dir;
    novo->dir = no;
    novo->cor = no->cor;
    no->cor = RED;
    return novo;
}

struct raiz *insere_ArvLLRB(struct raiz *no, Info2 info, int *inseriu)
{
    int resp;
    no = insereNO(no, info, inseriu);
    if (no != NULL)
    {
        no->cor = BLACK;
    }
    return no;
}

struct raiz *insereNO(struct raiz *no, Info2 info, int *resp)
{
    if (no == NULL)
    {
        struct raiz *novo;
        Lista *lista;
        novo = (struct raiz *)malloc(sizeof(struct raiz));
        if (novo == NULL)
        {
            *resp = 0;
            return NULL;
        }
        lista = alocaNo(info.linha);
        inserirLista(&novo->info.I, &novo->info.F, lista);
        strcpy(novo->info.palavra, info.palavra);

        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }
    if (strcmp(info.palavra, no->info.palavra) == 0)
    {
        *resp = 0;
        Lista *lista;
        lista = alocaNo(info.linha);
        inserirLista(&no->info.I, &no->info.F, lista);
    }
    else
    {
        if (strcmp(info.palavra, no->info.palavra) < 0)
        {
            no->esq = insereNO(no->esq, info, resp);
        }
        else
        {
            no->dir = insereNO(no->dir, info, resp);
        }
    }
    if (cor(no->dir) == RED && cor(no->esq) == BLACK)
    {
        no = rotacionaEsquerda(no);
    }
    if (cor(no->esq) == RED && cor(no->esq->esq) == RED)
    {
        no = rotacionaDireita(no);
    }
    if (cor(no->esq) == RED && cor(no->dir) == RED)
    {
        trocaCor(no);
    }
    return no;
}

struct raiz *remove_ArvLLRB(struct raiz *no, char info[])
{
    int achou, passo;
    consulta_ArvLLRB(no, info, &achou, &passo);

    if (achou)
    {
        struct raiz *novo = no;
        no = remove_NO(novo, info);
        if (no != NULL)
        {
            no->cor = BLACK;
        }
        return no;
    }
    else
        return no;
}

struct raiz *remove_NO(struct raiz *no, char info[])
{
    int rem;
    if (strcmp(info, no->info.palavra) < 0)
    {
        if (cor(no->esq) == BLACK && cor(no->esq->esq) == BLACK)
        {
            no = move2EsqRed(no);
        }
        no->esq = remove_NO(no->esq, info);
    }
    else
    {
        if (cor(no->esq) == RED)
        {
            no = rotacionaDireita(no);
        }
        if (strcmp(info, no->info.palavra) == 0 && no->dir == NULL)
        {
            free(no);
            return NULL;
        }
        if (cor(no->dir) == BLACK && cor(no->dir->esq) == BLACK)
        {
            no = move2DirRED(no);
        }
        if (strcmp(info, no->info.palavra) == 0)
        {
            struct raiz *aux = procuraMenor(no->dir);
            no->info = aux->info;
            no->dir = removeMenor(no->dir);
        }
        else
        {
            no->dir = remove_NO(no->dir, info);
        }
    }

    return balancear(no);
}

struct raiz *move2EsqRed(struct raiz *no)
{
    trocaCor(no);
    if (cor(no->dir->esq) == RED)
    {
        no->dir = rotacionaDireita(no->dir);
        no = rotacionaEsquerda(no);
        trocaCor(no);
    }
    return no;
}

struct raiz *move2DirRED(struct raiz *no)
{
    trocaCor(no);
    if (cor(no->esq->esq) == RED)
    {
        no = rotacionaDireita(no);
        trocaCor(no);
    }
    return no;
}

struct raiz *balancear(struct raiz *no)
{
    if (cor(no->dir) == RED)
    {
        no = rotacionaEsquerda(no);
    }
    if (no->esq != NULL && cor(no->esq) == RED && cor(no->esq->esq) == RED)
    {
        no = rotacionaEsquerda(no);
    }
    if (cor(no->esq) == RED && cor(no->dir) == RED)
    {
        trocaCor(no);
    }
    return no;
}

struct raiz *removeMenor(struct raiz *no)
{
    if (no->esq == NULL)
    {
        free(no);
        return NULL;
    }
    if (cor(no->esq) == BLACK && cor(no->esq->esq) == BLACK)
    {
        no = move2EsqRed(no);
    }

    no->esq = removeMenor(no->esq);
    return balancear(no);
}

struct raiz *procuraMenor(struct raiz *atual)
{
    struct raiz *no1 = atual;
    struct raiz *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

void consulta_ArvLLRB(struct raiz *no, char info[], int *achou, int *passo)
{
    if (no != NULL)
    {
        if (*achou != 1)
        {
            *passo += 1;
            if (strcmp(info, no->info.palavra) < 0)
                consulta_ArvLLRB(no->esq, info, achou, passo);
            else if (strcmp(info, no->info.palavra) > 0)
                consulta_ArvLLRB(no->dir, info, achou, passo);
        }

        if (strcmp(info, no->info.palavra) == 0)
        {
            *achou = 1;
            if (*achou == 1)
            {
                printf("\nPassos: %d\nPalavra: %s", *passo, no->info.palavra);
                imprimirLista(no->info.I);
            }
        }
    }
}

void imprimir(struct raiz *no)
{
    if (no != NULL)
    {
        imprimir(no->esq);
        printf("%s", no->info.palavra);
        imprimirLista(no->info.I);
        printf("\n");
        imprimir(no->dir);
    }
}

// Lista
Lista *alocaNo(int numero)
{
    Lista *No;

    No = NULL;
    No = (Lista *)malloc(sizeof(Lista));
    No->Prox = NULL;
    No->numero = numero;

    return No;
}

int inserirLista(Lista **I, Lista **F, Lista *No)
{
    Lista *Aux, *Ant;
    int inseriu = 1;

    if (!buscarLista(*I, No->numero))
    {
        if (listaVazia(*I))
        {

            (*No).Prox = *I;
            *I = No;
            *F = *I;
        }
        else
        {
            if (No->numero < (**I).numero)
            {
                (*No).Prox = *I;
                (*I) = No;
            }
            else if (No->numero > (**F).numero)
            {
                (**F).Prox = No;
                *F = No;
            }
            else
            {

                Aux = *I;

                while (No->numero > (*Aux).numero)
                {
                    Ant = Aux;
                    Aux = (*Aux).Prox;
                }
                (*Ant).Prox = No;
                No->Prox = Aux;
            }
        }
    }
    else
        inseriu = 0;

    return inseriu;
}

void imprimirLista(Lista *I)
{
    Lista *Aux;
    for (Aux = I; Aux != NULL; Aux = Aux->Prox)
        printf(" %d ", (*Aux).numero);
}

int listaVazia(Lista *I)
{
    return (I == NULL);
}

int removerLista(Lista **I, Lista **F, int numero)
{
    Lista *Ant, *No;
    int removeu = 1;

    if (buscarLista(*I, numero))
    {
        Ant = NULL;
        No = *I;

        while (No != NULL && (*No).numero != numero)
        {
            Ant = No;
            No = (*No).Prox;
        }

        if (Ant == NULL)
        {
            (*I) = (*I)->Prox;
        }
        else
        {
            if ((**F).numero == (*No).numero)
                *F = Ant;
            (*Ant).Prox = (*No).Prox;
        }

        free(No);
    }
    else
        removeu = 0;

    return removeu;
}

int buscarLista(Lista *I, int numero)
{
    Lista *Aux;
    int encontrou;

    encontrou = 0;

    for (Aux = I; Aux != NULL; Aux = (*Aux).Prox)
    {
        if ((*Aux).numero == numero)
            encontrou = 1;
    }

    return encontrou;
}

int removerLis(struct raiz *no, char info[], int numero, int *achou, int *excluir)
{
    if (no != NULL)
    {
        if (*achou != 1)
        {
            if (strcmp(info, no->info.palavra) < 0)
                removerLis(no->esq, info, numero, achou, excluir);
            else if (strcmp(info, no->info.palavra) > 0)
                removerLis(no->dir, info, numero, achou, excluir);
        }
        if (strcmp(info, no->info.palavra) == 0)
        {
            *achou = 1;
            removerLista(&no->info.I, &no->info.F, numero);
            if (listaVazia(no->info.I))
            {
                *excluir = 1;
            }
        }
    }
}
