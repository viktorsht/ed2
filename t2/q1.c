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

struct raiz *rotacionaEsquerda(struct raiz *no);
struct raiz *rotacionaDireita(struct raiz *no);
// Árvore
/*
struct raiz *remove_ArvLLRB(struct raiz *no, char info[]);
struct raiz *remove_NO(struct raiz *no, char info[]);
struct raiz *move2EsqRed(struct raiz *no);
struct raiz *move2DirRED(struct raiz *no);
struct raiz *balancear(struct raiz *no);
struct raiz *removeMenor(struct raiz *no);
struct raiz *procuraMenor(struct raiz *atual);
*/
struct raiz *insereNO(struct raiz *no, Info2 info, int *resp);



int isRed(struct raiz *root);
void swapColorTree(struct raiz *root);

struct raiz *insere_ArvLLRB(struct raiz *no, Info2 info, int *inseriu);
void trocaCor(struct raiz *no);
void consulta_ArvLLRB(struct raiz *no, char info[], int *achou, int *passo);
void imprimir(struct raiz *no);
int cor(struct raiz *no);
void removerLis(struct raiz *no, char info[], int numero, int *achou, int *excluir);
int menu();

struct raiz *toRemoveTree(struct raiz *root, char x[], int line);
struct raiz *toRemoveNodeTree(struct raiz *root, char x[]);
struct raiz *balanceTree(struct raiz *root);
struct raiz *toRemoveSmaller(struct raiz *root);
struct raiz *searchNodeSmaller(struct raiz *root);
struct raiz *move2esq(struct raiz *root);
struct raiz *move2dir(struct raiz *root);
int searchTree(struct raiz *root, char x[TAM], int result, int *countSteps, Info **infoAux);
int qtdOfElementsList(Lista *l);
/*
struct raiz *rotateToLeftTree(struct raiz *root){
    struct raiz *new;

    new = root->right;
    root->right = new->left;
    new->left = root;
    new->color = root->color;
    root->color = 1;

    return new;
}

struct raiz *rotateToRightTree(struct raiz *root){
    struct raiz *new;

    new = root->left;
    root->left = new->right;
    new->right = root;
    new->color = root->color;
    root->color = 1;

    return new;
}
*/
void swapColorTree(struct raiz *root){
    root->cor = !root->cor;

    if (root->esq != NULL) root->esq->cor = !root->esq->cor;
    if (root->dir != NULL) root->dir->cor = !root->dir->cor;
}


int isRed(struct raiz *root){
    return root == NULL ? 0 : root->cor == 1;
}

int searchTree(struct raiz *root, char x[TAM], int result, int *countSteps, Info **infoAux){
    if(root == NULL) result = 0;
    else if(strcmp(root->info.palavra, x) == 0){
        result = 1;
        *infoAux = &root->info;
    }else if(strcmp(x, root->info.palavra) < 0){
        *countSteps += 1;
        result = searchTree(root->esq, x, result, countSteps, infoAux);
    }else{
        *countSteps += 1;
        result = searchTree(root->dir, x, result, countSteps, infoAux);
    }

    return result;
}

struct raiz *toRemoveTree(struct raiz *root, char x[], int line){
    int found = 0, steps= 0 , qtd = 0, result = 0;
    struct Info2 *infoAux;

    infoAux = NULL;

    int achou = 0, excluir = 0;

    found = searchTree(root, x, 0, &steps, &infoAux);

    if(found){
        qtd = qtdOfElementsList(root->info.I) - 1;

        printf("quantidade de elementos = %d\n",qtd);

        if(qtd <= 1){
            struct raiz *new;
            new = root;
            root = toRemoveNodeTree(new, x);
            printf("\n\nAQUI FILHOTE!\n\n");

        }//else result = toRemoveList(&infoAux->l, line);
        else removerLis(root, x, line, &achou, &excluir);


    }else {
        printf("[!] PALAVRA NÃO ENCONTRADA!\n");
    }
    return root;
}

struct raiz *toRemoveNodeTree(struct raiz *root, char x[]){
    if (strcmp(x, root->info.palavra) < 0){
        if (!isRed(root->esq) && !isRed(root->esq->esq))
            root = move2esq(root);
        root->esq = toRemoveNodeTree(root->esq, x);
    }else{
        if (isRed(root->esq)) root = rotacionaDireita(root);
        if (strcmp(x, root->info.palavra) == 0 && root->dir == NULL){
            free(root);
            root =  NULL;
        }
        else{
                if (!isRed(root->dir) && !isRed(root->dir->esq))
                    root = move2dir(root);

                if (strcmp(x, root->info.palavra) == 0){
                    struct raiz *aux;
                    aux = searchNodeSmaller(root->dir);
                    root->info = aux->info;
                    root->dir = toRemoveSmaller(root->dir);
                }else root->dir = toRemoveNodeTree(root->dir, x);
            }

        }
    if(root != NULL)
      root = balanceTree(root);
    return root;
}

struct raiz *balanceTree(struct raiz *root){
    if (isRed(root->dir))
         root = rotacionaEsquerda(root);
    if (root->esq != NULL && isRed(root->esq) && isRed(root->esq->esq))
         root = rotacionaEsquerda(root);
    if (isRed(root->esq) && isRed(root->dir))
         swapColorTree(root);

    return root;
}

struct raiz *toRemoveSmaller(struct raiz *root){
    if (root->esq == NULL){
        free(root);
        root =  NULL;
    }
    else{
        if (!isRed(root->esq) && !isRed(root->esq->esq))
            root = move2esq(root);

        root->esq = toRemoveSmaller(root->esq);

        root = balanceTree(root);
    }
    return root;
}

struct raiz *searchNodeSmaller(struct raiz *root){
    struct raiz *node1, *node2;
    node1 = root;
    node2 = root->esq;

    while (node2 != NULL){
        node1 = node2;
        node2 = node2->esq;
    }

    return node2;
}

struct raiz *move2esq(struct raiz *root){
    swapColorTree(root);
    if (isRed(root->dir->esq)){
        root->dir = rotacionaEsquerda(root->dir);
        root = rotacionaEsquerda(root);
        swapColorTree(root);
    }

    return root;
}

struct raiz *move2dir(struct raiz *root){
    swapColorTree(root);
    if (isRed(root->esq->esq)){
        root = rotacionaEsquerda(root);
        swapColorTree(root);
    }
    return root;
}





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

            //removerLis(no, palavra, numlinha, &achou, &excluir);
            no = toRemoveTree(no, palavra,0);
            /*
            if (excluir == 1){
              printf("%s removida com sucesso!\n",palavra);
            }
            if (achou == 0)
            {
                printf("\nPalavra não encontrada na árvore!\n");
            }
            */

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
/*
*/
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
/*
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
*/
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

int qtdOfElementsList(Lista *l){
//    tlist *s = *l;
    int i = 0;

    while(l != NULL){
        l = l->Prox;
        i++;
    }

    return i;
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

void removerLis(struct raiz *no, char info[], int numero, int *achou, int *excluir)
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
