#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int red = 1;
static int black = 0;

#define TAM 20
#define TAM_STR_ARQ 300

typedef struct lista
{
    int x;
    struct lista *next;
} tlist;

typedef struct{
    tlist *s;
} Lista;

typedef struct info
{
    int i;
    char string[TAM];
    Lista l;
} Info;

struct node
{
    Info info;
    struct node *left;
    struct node *right;
    int color;
};

typedef struct data
{
    char string[TAM];
    int linha;
    Lista l;
}tdata;

// lista novas funções
void init(Lista *l);
void insertList(Lista *l, int x);
void show(Lista *l);
int qtdOfElements(Lista *l);

// Árvore
struct node *remover(struct node *no, char info[],int numberLine);
struct node *rotacionaleftuerda(struct node *no);
struct node *rotacionarighteita(struct node *no);
struct node *insereNO(struct node *no, tdata info, int *resp);
struct node *remove_NO(struct node *no, char info[]);
struct node *move2leftred(struct node *no);
struct node *move2rightred(struct node *no);
struct node *balancear(struct node *no);
struct node *removeMenor(struct node *no);
struct node *procuraMenor(struct node *atual);
struct node *inserirTree(struct node *no, tdata info, int *flagInsert);
void trocaCor(struct node *no);
void consulta_ArvLLRB(struct node *no, char info[], int *achou, int *passo);
void inOrden(struct node *no);
int color(struct node *no);
int removerLis(struct node *no, char info[], int x, int *achou, int *flagDelete);
int menu();
/*
struct node *openFile(struct node *no){
  int flagInsert, i = 1, op, achou, passo;
  char linha[TAM_STR_ARQ];
  tdata info;
  FILE *file;
  no = NULL;

  file = fopen("file.txt", "rt");

  if (file == NULL)
  {
      printf("Erro na abertura do arquivo\n");
  }
  else
  {
      while (!feof(file))
      {
          fgets(linha, TAM_STR_ARQ, file);
          info.string = strtok(linha, " ,.;:\n");
          do
          {
              info.linha = i;
              if (info.string != NULL)
                  no = inserirTree(no, info, &flagInsert);
              info.string = strtok(NULL, " ,.;:\n");
          } while (info.string != NULL);
          i++;
      }
      fclose(file);
    }
    return no;
}
*/

struct node *openFile(struct node *root){
    FILE *file;
    tdata new;
    int i = 1, result = 0;
    char str[1000], *str2, str3;

    file = fopen("file.txt", "r");

    //init(&new.l);

    if(file){
        while(fgets(str, 1000, file) != NULL){

            str2 = strtok(str, "\n");
            str2 = strtok(str, " .,;:!?()-\\/--''\"");

            while(str2){

                strcpy(new.string, str2);

                new.linha = i;

                //insertList(&new.l, i);

                root = inserirTree(root, new, &result);

                
                //init(&new.l);

                str2 = strtok(NULL, " !.,");

            }

            i++;
        }

    }else printf("[!] -  Erro ao abrir o arquivo!\n");

    fclose(file);

    return root;

}
// int search(struct node *root, char x[TAM], int result, int *countSteps/*, Lista *l*/){
//     if(root == NULL) result = 0;
//     else if(strcmp(root->info.string, x) == 0){
//         result = 1;
//         //l->s = root->info.l.s;
//     }else if(strcmp(x, root->info.string) < 0){
//         *countSteps += 1;
//         result = search(root->left, x, result, countSteps);
//     }else{
//         *countSteps += 1;
//         result = search(root->right, x, result, countSteps);
//     }

//     return result;
// }

// BUSCAR NA ÁRVORE VERMLHA E PRETA
int search(struct node *root, char x[TAM], int result, int *countSteps, Lista *l){
    if(root == NULL) result = 0;
    else if(strcmp(root->info.string, x) == 0){
        result = 1;
        l->s = root->info.l.s;
        // l->s = root->data.l.s;
    }else if(strcmp(x, root->info.string) < 0){
        *countSteps += 1;
        result = search(root->left, x, result, countSteps, l);
    }else{
        *countSteps += 1;
        result = search(root->right, x, result, countSteps, l);
    }

    return result;
}
int removerLista(Lista *lista, int x){
  tlist *inicio = lista->s;
	tlist *remover = NULL;
	int result = 1;
	if(inicio != NULL && inicio->x == x){
		remover = lista->s;
		lista->s = inicio->next;
	}
	else{
		while(inicio != NULL && inicio->next != NULL && inicio->next->x != x){
			inicio = inicio->next;
		}
		if(inicio != NULL && inicio->next != NULL){
			remover = inicio->next;
			inicio->next = remover->next;
		}
	}
	if(remover != NULL){
		free(remover);
		result = 0; // REMOVEU!!!!!!!!!
	}
	return result;
}

int main(){
    struct node *no;
    int flagInsert = 0, numberLine = 1, op, achou, passo;
    int flagDelete = 1;
    char string[TAM];
    tdata new;
    no = openFile(no);
    do
    {
        op = menu();
        switch (op)
        {
        case 0:
        break;
        case 1:

            inOrden(no);

        break;
        case 2:


            printf("PALAVRA: ");
            scanf("%s", string);
            strcpy(new.string,string);
            printf("Linha: ");
            scanf("%d", &new.linha);

            no = inserirTree(no, new, &flagInsert);
            if(flagInsert == 1) printf("\nINSERÇÃO CONCLUIDA:   |%s|\n",string);
            else printf("\nERRO INSERÇÃO:   |%s|\n",string);
            flagInsert = 0;

        break;
        case 3:

            passo = -1;
            achou = 0;
            printf("PALAVRA: ");
            scanf("%s", string);
            // achou = search(no, string, achou, &passo);

            // if (achou == 0) printf("\n NÃO ENCONTRADA:   |%s|\n",string);
            // else{
            //   printf("Palavra Pesquisada: |%s| - Número de passos: |%d|\n",string,passo);
            // }

        break;
        case 4:

            achou = 0;

            printf("PALAVRA: ");
            scanf("%s", string);
            printf("Linha:");
            scanf("%d", &numberLine);

            // funçao de remover na lista ( ... )

            if (flagDelete == 1){
              no = remover(no, string,numberLine);
              achou = 1;
            }
            if (achou == 1) printf("\nREMOÇÃO CONCLUIDA:   |%s|\n",string);
            else  printf("\nREMOÇÃO NÂO CONCLUIDA:   |%s|\n",string);

        break;
        default:
            printf("Entrada inválida\n");
            break;
      }
    } while (op != 0);

    return 0;
}

int menu(){
    int op = 0;
    printf("[0] - Sair\n");
    printf("[1] - Ver Árvore\n");
    printf("[2] - Adcionar Mais\n");
    printf("[3] - Buscar string\n");
    printf("[4] - Remover\n");
    printf("OPÇÃO: ");
    scanf("%d", &op);
    return op;
}

int color(struct node *no)
{
    return no == NULL ? black : no->color;
}

void trocaCor(struct node *no)
{
    no->color = !no->color;
    if (no->left != NULL)
    {
        no->left->color = !no->left->color;
    }
    if (no->right != NULL)
    {
        no->right->color = !no->right->color;
    }
}

struct node *rotacionaleftuerda(struct node *no)
{
    struct node *novo = no->right;
    no->right = novo->left;
    novo->left = no;
    novo->color = no->color;
    no->color = red;
    return novo;
}

struct node *rotacionarighteita(struct node *no)
{
    struct node *novo = no->left;
    no->left = novo->right;
    novo->right = no;
    novo->color = no->color;
    no->color = red;
    return novo;
}

struct node *inserirTree(struct node *no, tdata info, int *flagInsert)
{
    int resp;
    no = insereNO(no, info, flagInsert);
    if (no != NULL)
    {
        no->color = black;
    }
    return no;
}

struct node *insereNO(struct node *no, tdata info, int *resp)
{
    if (no == NULL)
    {
        struct node *novo;
        Lista lista;
        novo = (struct node *)malloc(sizeof(struct node));
        if (novo == NULL)
        {
            *resp = 0;
            return NULL;
        }
        init(&lista);
        insertList(&novo->info.l,info.linha);
        strcpy(novo->info.string, info.string);

        novo->color = red;
        novo->right = NULL;
        novo->left = NULL;
        *resp = 1;
        return novo;
    }
    if (strcmp(info.string, no->info.string) == 0)
    {
        *resp = 0;
        Lista lista;
        init(&lista);
        insertList(&no->info.l,info.linha);
    }
    else
    {
        if (strcmp(info.string, no->info.string) < 0)
        {
            no->left = insereNO(no->left, info, resp);
        }
        else
        {
            no->right = insereNO(no->right, info, resp);
        }
    }
    if (color(no->right) == red && color(no->left) == black)
    {
        no = rotacionaleftuerda(no);
    }
    if (color(no->left) == red && color(no->left->left) == red)
    {
        no = rotacionarighteita(no);
    }
    if (color(no->left) == red && color(no->right) == red)
    {
        trocaCor(no);
    }
    return no;
}

struct node *remover(struct node *no, char info[],int numberLine)
{
    int achou, passos;
    // consulta_ArvLLRB(no, info, &achou, &passo);
    Lista lista;
    init(&lista);

    achou = search(no,info, achou, &passos, &lista);

    if (achou){

        int qtd = qtdOfElements(&lista);
        printf("QTD %d\n", qtd);


        if(qtd <= 1){

            struct node *novo = no;
            no = remove_NO(novo, info);
            if (no != NULL)
            {
                no->color = black;
            }
        }else{
            show(&lista);
            int result = removerLista(&lista, numberLine);
            printf("\nresult = %d\n", result);
            show(&lista);
        }

        return no;
    }
    else
        return no;
}

struct node *remove_NO(struct node *no, char info[])
{
    if (strcmp(info, no->info.string) < 0)
    {
        if (color(no->left) == black && color(no->left->left) == black)
        {
            no = move2leftred(no);
        }
        no->left = remove_NO(no->left, info);
    }
    else
    {
        if (color(no->left) == red)
        {
            no = rotacionarighteita(no);
        }
        if (strcmp(info, no->info.string) == 0 && no->right == NULL)
        {
            // int qtd = qtdOfElements(&(no->info.l));
            // if(qtd > 1){
            //     printf("QTD %d\n", qtd);
            // }else{}
            free(no);
            return NULL;
        }
        if (color(no->right) == black && color(no->right->left) == black)
        {
            no = move2rightred(no);
        }
        if (strcmp(info, no->info.string) == 0)
        {
            struct node *aux = procuraMenor(no->right);
            no->info = aux->info;
            no->right = removeMenor(no->right);
        }
        else
        {
            no->right = remove_NO(no->right, info);
        }
    }

    return balancear(no);
}

struct node *move2leftred(struct node *no)
{
    trocaCor(no);
    if (color(no->right->left) == red)
    {
        no->right = rotacionarighteita(no->right);
        no = rotacionaleftuerda(no);
        trocaCor(no);
    }
    return no;
}

struct node *move2rightred(struct node *no)
{
    trocaCor(no);
    if (color(no->left->left) == red)
    {
        no = rotacionarighteita(no);
        trocaCor(no);
    }
    return no;
}

struct node *balancear(struct node *no)
{
    if (color(no->right) == red)
    {
        no = rotacionaleftuerda(no);
    }
    if (no->left != NULL && color(no->left) == red && color(no->left->left) == red)
    {
        no = rotacionaleftuerda(no);
    }
    if (color(no->left) == red && color(no->right) == red)
    {
        trocaCor(no);
    }
    return no;
}

struct node *removeMenor(struct node *no)
{
    if (no->left == NULL)
    {
        free(no);
        return NULL;
    }
    if (color(no->left) == black && color(no->left->left) == black)
    {
        no = move2leftred(no);
    }

    no->left = removeMenor(no->left);
    return balancear(no);
}

struct node *procuraMenor(struct node *atual)
{
    struct node *no1 = atual;
    struct node *no2 = atual->left;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->left;
    }
    return no1;
}

void consulta_ArvLLRB(struct node *no, char info[], int *achou, int *passo)
{
    if (no != NULL)
    {
        if (*achou != 1)
        {
            *passo += 1;
            if (strcmp(info, no->info.string) < 0)
                consulta_ArvLLRB(no->left, info, achou, passo);
            else if (strcmp(info, no->info.string) > 0)
                consulta_ArvLLRB(no->right, info, achou, passo);
        }

        if (strcmp(info, no->info.string) == 0)
        {
            *achou = 1;
        }
    }
}

void inOrden(struct node *no)
{
    if (no != NULL)
    {
        inOrden(no->left);
        printf("%s\t", no->info.string);
        //inOrdenLista(no->info.I);
        show(&no->info.l);
        printf("\n");
        inOrden(no->right);
    }
}

// funções lista humberto

void init(Lista *l){
    l->s = NULL;
}
void insertList(Lista *l, int x){
    tlist *s, *new, *prev;

	new = (tlist *) malloc(sizeof(tlist));
    s = l->s;
	prev = NULL;

    new->x = x;
	new->next = NULL;

	if(s == NULL){
		l->s = new;
        new->next = NULL;
	}else{
		while(s != NULL && s->x < x){
			prev = s;
			s = s->next;
		}

        // if(new->x != s->x)
        new->next = s;

		if(prev == NULL) {
            if(x != s->x) l->s = new;
        }else{
            if(prev->next == NULL) prev->next = new;
            if(x != prev->next->x) prev->next = new;
        }
	}
}

int qtdOfElements(Lista *l){
    tlist *s = l->s;
    int i = 0;
    while(s != NULL){
        printf("%d ", s->x);
        s = s->next;
        i++;
    }
    return i;
}

void show(Lista *l){
    tlist *s = l->s;

    while(s != NULL){
        printf("%d ", s->x);
        s = s->next;
    }

}
