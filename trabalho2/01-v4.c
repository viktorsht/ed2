#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_STR 10000

// STRUCT LISTA
typedef struct tlist{
    int x;
    struct tlist *next;
} tlist;

typedef struct{
    tlist *s;
} List;

// STRUCT TREE
typedef struct{
    List l;
    int i;
    char str[TAM_STR];
} tdata;

struct node{
    struct node *left, *right;
    tdata data;
    int color; // 1 ==> 1, 0 ==> 0
} node;

// ESCOPO FUNÇÕES LISTA
void initList(List *l);
void insertList(List *l, int x);
int toRemoveList(List *l, int x);
void showList(List *l);
int qtdOfElementsList(List *l);


// ESCOPO FUNÇÕES ÁRVORE
struct node *createNodeTree(tdata data);

//int is1(struct node *root);
int color(struct node *no);

void swapColorTree(struct node *root);
void inOrder(struct node *root);
struct node *insertTree(struct node *root, tdata data, int *result);
struct node *insertNodeTree(struct node *root, tdata data, int *result);
struct node *rotateToLeftTree(struct node *root);
struct node *rotateToRightTree(struct node *root);

struct node *openFile(struct node *root);

int searchTree(struct node *root, char x[TAM_STR], int result, int *countSteps, tdata **dataAux);


struct node *toRemoveTree(struct node *root, char x[], int line);
struct node *toRemoveNodeTree(struct node *root, char x[]);
struct node *balanceTree(struct node *root);
struct node *toRemoveSmaller(struct node *root);
struct node *searchNodeSmaller(struct node *root);
struct node *move2Left(struct node *root);
struct node *move2Right(struct node *root);

int menu();


int main(){

    struct node *root = NULL, *nodeAux = NULL;
    tdata *dataAux = NULL, newData;
    int result = 0, count = 0, op = 0, i=0 ;

    root = openFile(root); // CARREGANDO PALAVRAS DO ARQUIVO

    do{
        op = menu();

        switch (op){
        case 0:
            break;
        case 1:
            printf("# MOSTRAR PALAVRAS EM ORDEM\n");
            inOrder(root);
            break;
        case 2:
            printf("# INSERIR NOVA PALAVRA\n");
            printf("Palavra: ");
            scanf("%s", newData.str);

            initList(&newData.l);
            newData.i = i = 0;

            do{
                printf("Informe a linha ou zero (0) para sair\n");
                printf("Linha: ");
                scanf("%d", &newData.i);
                i = newData.i;

                if(i != 0) insertList(&newData.l, i);
                showList(&newData.l);

            }while(i != 0);

            count = qtdOfElementsList(&newData.l);
            printf("QTD %d\n", count);

            if(count){
                root = insertTree(root, newData, &result);
                if(result) printf("# SUCCESS AO INSERIR A PALAVRA!\n");
                else printf("[!] ERRO AO INSERIR A PALAVRA!\n");
            }else printf("[!] NENHUMA LINHA ATRIBUIDA A PALAVRA!\n");
            break;

        case 3:
            printf("# BUSCAR PALAVRA\n");
            printf("Palavra: ");
            scanf("%s", newData.str);

            count = 0;
            result = searchTree(root, newData.str, 0, &count, &dataAux);

            if(result){
                printf("Linhas: ");
                showList(&dataAux->l);
                printf("\n");
                printf("Passos: %d\n", count);
            } else printf("[!] PALAVRA NÃO ENCONTRADA!\n");
            break;

        case 4:
        

            printf("# REMOVER PALAVRA\n");
            printf("Palavra: ");
            scanf("%s", newData.str);
            printf("Linha: ");
            scanf("%d", &newData.i);
            root = toRemoveTree(root, newData.str, newData.i);

            break;


        default:
            printf("[!] OPÇÃO INVÁLIDA!\n");
            break;
        }

    }while ( op != 0 );

    return 0;
}

int menu(){
    int op = 0;
    printf("[0] - Sair\n[1] - inOrder\n[2] - Adicionar palavra\n[3] - Buscar\n[4] - Remover\nOPÇÃO: ");
    scanf("%d", &op);
    return op;
}

struct node *toRemoveTree(struct node *root, char x[], int line){
    int found = 0, steps= 0 , qtd = 0, result = 0;
    tdata *dataAux = NULL;

    found = searchTree(root, x, 0, &steps, &dataAux);

    if(found){
        qtd = qtdOfElementsList(&dataAux->l);

        if(qtd <= 1){
            struct node *new = root;
            printf("\n\n\nrooT\n\n\n");
            root = toRemoveNodeTree(new, dataAux->str);
            if(root != NULL) root->color = 0;


        }else result = toRemoveList(&dataAux->l, line);

        return root;

    }else {
        printf("[!] PALAVRA NÃO ENCONTRADA!\n");
        return root;
    }

}

struct node *toRemoveNodeTree(struct node *root, char x[]){
    if (strcmp(x, root->data.str) < 0){
        if (color(root->left) == 0 && color(root->left->left) == 0) root = move2Left(root);
        root->left = toRemoveNodeTree(root->left, x);
    }else{
        if (color(root->left) == 1) root = rotateToRightTree(root);
        if (strcmp(x, root->data.str) == 0 && root->right == NULL){
            free(root);
            return NULL;
        }

        if (color(root->right) == 0 && color(root->right->left) == 0) root = move2Right(root);
        if (strcmp(x, root->data.str) == 0){
            struct node *aux = searchNodeSmaller(root->right);
            root->data = aux->data;
            root->right = toRemoveSmaller(root->right);
        }else root->right = toRemoveNodeTree(root->right, x);
    }

    return balanceTree(root);
}

struct node *balanceTree(struct node *root){
    if (color(root->right) == 1) root = rotateToLeftTree(root);
    if (root->left != NULL && color(root->left) == 1 && color(root->left->left) == 1) root = rotateToLeftTree(root);
    if (color(root->left) == 1 && color(root->right) == 1) swapColorTree(root);

    return root;
}

struct node *toRemoveSmaller(struct node *root){
    if (root->left == NULL){
        free(root);
        return NULL;
    }
    if (color(root->left) == 0 && color(root->left->left) == 0) root = move2Left(root);

    root->left = toRemoveSmaller(root->left);

    return balanceTree(root);
}

struct node *searchNodeSmaller(struct node *root){
    struct node *node1 = root;
    struct node *node2 = root->left;

    while (node2 != NULL){
        node1 = node2;
        node2 = node2->left;
    }

    return node2;
}

struct node *move2Left(struct node *root){
    swapColorTree(root);
    if (color(root->right->left) == 1){
        root->right = rotateToRightTree(root->right);
        root = rotateToLeftTree(root);
        swapColorTree(root);
    }

    return root;
}

struct node *move2Right(struct node *root){
    swapColorTree(root);
    if (color(root->left->left) == 1){
        root = rotateToRightTree(root);
        swapColorTree(root);
    }
    return root;
}


struct node *openFile(struct node *root){
    FILE *file;
    tdata new;
    int i = 1, result = 0;
    char str[TAM_STR], *str2, str3;

    file = fopen("file.txt", "r");

    initList(&new.l);

    if(file){
        while(fgets(str, TAM_STR, file) != NULL){

            str2 = strtok(str, "\n");
            str2 = strtok(str, " .,;:!?()-\\/--''\"");

            while(str2){

                strcpy(new.str, str2);
                new.i = i;

                insertList(&new.l, i);

                root = insertTree(root, new, &result);

                initList(&new.l);

                str2 = strtok(NULL, " !.,");

            }


            i++;
        }

    }else printf("[!] -  Erro ao abrir o arquivo!\n");

    fclose(file);

    return root;

}


// FUNÇÕES TREE
struct node *createNode(tdata data){
    struct node *new = (struct node *)malloc(sizeof(node));
    new->left = new->right = NULL;
    // initList(&data.l);
    new->data = data;
    new->color = 1;

    return new;
}



int color(struct node *no)
{
    return no == NULL ? 0 : no->color;
}

void swapColorTree(struct node *root){
    root->color = !root->color;

    if (root->left != NULL) root->left->color = !root->left->color;
    if (root->right != NULL) root->right->color = !root->right->color;
}

void inOrder(struct node *node){
    if(node){
        inOrder(node->left);
        printf("STR: %s | COR: %s\n", node->data.str, node->color ? "1" : "0");

        printf("L: ");
        showList(&node->data.l);
        printf("\n");
        inOrder(node->right);
    }
}

struct node *rotateToLeftTree(struct node *root){
    struct node *new = root->right;
    root->right = new->left;
    new->left = root;
    new->color = root->color;
    root->color = 1;

    return new;
}

struct node *rotateToRightTree(struct node *root){
    struct node *new = root->left;
    root->left = new->right;
    new->right = root;
    new->color = root->color;
    root->color = 1;

    return new;
}

struct node *insertTree(struct node *root, tdata x, int *flag){
    root = insertNodeTree(root, x, flag);
    if (root != NULL) root->color = 0;
    return root;
}

struct node *insertNodeTree(struct node *root, tdata data, int *result){
    if (root == NULL){
        //struct node *new = createNode(data);
        struct node *new;
        new = (struct node *)malloc(sizeof(struct node));


        if(new == NULL){
            *result = 0;
            return NULL;
        }
        new->color = 1;
        new->right = NULL;
        new->left = NULL;

        *result = 1;
        return new;
    }

    if (strcmp(data.str, root->data.str) == 0){
        *result = 1;
        insertList(&root->data.l,data.i);
    }
    else{
        if (strcmp(data.str, root->data.str) < 0) root->left = insertNodeTree(root->left, data, result);
        else root->right = insertNodeTree(root->right, data, result);
    }

    if (color(root->right) == 1 && color(root->left) == 0) root = rotateToLeftTree(root);
    if (color(root->left) == 1 && color(root->left->left) == 1) root = rotateToRightTree(root);
    if (color(root->left) == 1 && color(root->right) == 1) swapColorTree(root);
    return root;
}

int searchTree(struct node *root, char x[TAM_STR], int result, int *countSteps, tdata **dataAux){
    if(root == NULL) result = 0;
    else if(strcmp(root->data.str, x) == 0){
        result = 1;
        *dataAux = &root->data;
    }else if(strcmp(x, root->data.str) < 0){
        *countSteps += 1;
        result = searchTree(root->left, x, result, countSteps, &(*dataAux));
    }else{
        *countSteps += 1;
        result = searchTree(root->right, x, result, countSteps, &(*dataAux));
    }

    return result;
}

// FUNÇÕES LISTA
void initList(List *l){
    l->s = NULL;
}

void insertList(List *l, int x){
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

        new->next = s;

		if(prev == NULL) {
            if(x != s->x) l->s = new;
        }else{
            if(prev->next == NULL) prev->next = new;
            if(x != prev->next->x) prev->next = new;
        }
	}
}

int toRemoveList(List *l, int x){
    tlist *s = l->s;
	tlist *nodeToRemove = NULL;
	int result = 0;


	if(s != NULL && s->x == x){
		nodeToRemove = l->s;
		l->s = s->next;
	}
	else{
		while(s != NULL && s->next != NULL && s->next->x != x){
			s = s->next;
		}
		if(s != NULL && s->next != NULL){
			nodeToRemove = s->next;
			s->next = nodeToRemove->next;
		}
	}
	if(nodeToRemove != NULL){
		free(nodeToRemove);
		result = 1;
    }
	return result;
}

int qtdOfElementsList(List *l){
    tlist *s = l->s;
    int i = 0;

    while(s != NULL){
        s = s->next;
        i++;
    }

    return i;
}

void showList(List *l){
    tlist *s = l->s;

    while(s != NULL){
        printf("%d ", s->x);
        s = s->next;
    }

}
