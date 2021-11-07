#include <stdio.h>
#include <stdlib.h>

struct raiz
{
    int info;
    struct raiz *esq;
    struct raiz *dir;
    int cor;
};

#define RED 1
#define BLACK 0

int cor(struct raiz *no);
struct raiz *insere_ArvLLRB(struct raiz *no, int valor, int *inseriu);
int remove_ArvLLRB(struct raiz *no, int valor);
struct raiz *rotacionaEsquerda(struct raiz *no);
struct raiz *rotacionaDireita(struct raiz *no);
struct raiz *insereNO(struct raiz *no, int valor, int *resp);
struct raiz *remove_NO(struct raiz *no, int valor);
struct raiz *move2EsqRed(struct raiz *no);
struct raiz *move2DirRED(struct raiz *no);
struct raiz *balancear(struct raiz *no);
struct raiz *removeMenor(struct raiz *no);
struct raiz *procuraMenor(struct raiz *atual);
void trocaCor(struct raiz *no);
void consulta_ArvLLRB(struct raiz *no, int info, int *achou);
void imprimir(struct raiz *no);

int main()
{
    struct raiz *no;
    int inseriu;
    no = NULL;

    no = insere_ArvLLRB(no, 200, &inseriu);
    no = insere_ArvLLRB(no, 300, &inseriu);
    no = insere_ArvLLRB(no, 50, &inseriu);
    // no = insere_ArvLLRB(no, 150, &inseriu);
    // no = insere_ArvLLRB(no, 120, &inseriu);

    imprimir(no);

    return 0;
}

int cor(struct raiz *no)
{
    int aux;
    if (no == NULL)
    {
        aux = BLACK;
    }
    else
    {
        aux = no->cor;
    }
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

struct raiz *insere_ArvLLRB(struct raiz *no, int valor, int *inseriu)
{
    int resp;
    no = insereNO(no, valor, inseriu);
    if (no != NULL)
    {
        no->cor = BLACK;
    }
    return no;
}

struct raiz *insereNO(struct raiz *no, int valor, int *resp)
{
    if (no == NULL)
    {
        struct raiz *novo;
        novo = (struct raiz *)malloc(sizeof(struct raiz));
        if (novo == NULL)
        {
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
    if (valor == no->info)
    {
        *resp = 0;
    }
    else
    {
        if (valor < no->info)
        {
            no->esq = insereNO(no->esq, valor, resp);
        }
        else
        {
            no->dir = insereNO(no->dir, valor, resp);
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

int remove_ArvLLRB(struct raiz *no, int valor)
{
    int achou;
    consulta_ArvLLRB(no, valor, &achou);
    if (achou)
    {
        struct raiz *novo = no;
        no = remove_NO(novo, valor);
        if (no != NULL)
        {
            no->cor = BLACK;
        }
        return 1;
    }
    else
        return 0;
}

struct raiz *remove_NO(struct raiz *no, int valor)
{
    if (valor < no->info)
    {
        if (cor(no->esq) == BLACK && cor(no->esq->esq) == BLACK)
        {
            no = move2EsqRed(no);
        }
        no->esq = remove_NO(no->esq, valor);
    }
    else
    {
        if (cor(no->esq) == RED)
        {
            no = rotacionaDireita(no);
        }
        if (valor == no->info && no->dir == NULL)
        {
            free(no);
            return NULL;
        }
        if (cor(no->dir) == BLACK && cor(no->dir->esq) == BLACK)
        {
            no = move2DirRED(no);
        }
        if (valor == no->info)
        {
            struct raiz *aux = procuraMenor(no->dir);
            no->info = aux->info;
            no->dir = removeMenor(no->dir);
        }
        else
        {
            no->dir = remove_NO(no->dir, valor);
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

void consulta_ArvLLRB(struct raiz *no, int info, int *achou)
{
    if (no != NULL)
    {
        if (*achou != 1)
        {
            if (info < no->info)
                consulta_ArvLLRB(no->esq, info, achou);
            else if (info > no->info)
                consulta_ArvLLRB(no->dir, info, achou);
        }
        if (info == no->info)
            *achou = 1;
    }
}

void imprimir(struct raiz *no)
{
    if (no != NULL)
    {
        imprimir(no->esq);
        printf("%d\n", no->info);
        imprimir(no->dir);
    }
}