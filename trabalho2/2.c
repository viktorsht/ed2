#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_STR 100

// LISTA ENCADEADA SIMPLES
typedef struct tlist{
    int x;
    struct tlist *next;
} tlist;

typedef struct{
    tlist *s;
} List;

// TIPO DE DADO
typedef struct{
    List l;
    int i; // número da linha
    char str[TAM_STR]; //palavra

} tdata;

// ÁRVORE 2-3
typedef struct aux{
    int count; //Número das chaves
	tdata data1, data2;
	struct aux *left, *center, *right;
} node;

// ÁRVORE 2-3
node *createNode(tdata data, node *cLeft, node *cCenter);
node *addInNode(node *root, tdata data, node *child);
void toBreakNode(node **root, tdata data, node *cBigger, tdata *dataUp, node **new);
node *insertTree23(node **father, node **root, tdata data, tdata *dataUp);
int isLeaf(node *root);
void inOrder(node *root);

// LISTA ENCADEADA SIMPLES
void initList(List *l);
void insertList(List *l, int x);
void showlist(List *l);
int search(node *root, char x[TAM_STR], int result, int *countSteps, List *l);
void *openFile(node **rootTree, node **nodeAux);


int estaContido(node *Raiz, char *info) {
    if (strcmp(info,Raiz->data1.str) == 0)
        return 1;
    if (strcmp(info,Raiz->data2.str) == 0)
        return 2;
    return 0;
}

void remover(node **pai, node **Raiz, char *info) {
    if (*Raiz != NULL) {
        if (estaContido(*Raiz, info) != 0) {

            if (*pai == NULL && isLeaf(*Raiz)) { // Verifica se a Raiz da Árvore é um nó Folha.
                if (estaContido(*Raiz, info) == 1)
                    (**Raiz).data1 = (**Raiz).data2;
                (**Raiz).data2.i = 0; // pode haver erro aqui!

                if ((**Raiz).count == 2)
                    (**Raiz).count = 1;
                else
                    *Raiz = NULL;
            }

            else if (*pai == NULL) {
                if ((**Raiz).count == 2) {
                    if (estaContido(*Raiz, info) == 2 && (**Raiz).right->count == 2) {
                        (**Raiz).data2 = (**Raiz).right->data1;
                        (**Raiz).right->data1 = (**Raiz).right->data2;
                        (**Raiz).right->data2.i = 0;
                        (**Raiz).right->count = 1;
                    }

                    else if (estaContido(*Raiz, info) == 2 && (**Raiz).center->count == 2) {
                        (**Raiz).data2 = (**Raiz).center->data2;
                        (**Raiz).center->data2.i = 0;
                        (**Raiz).right->count = 1;
                    }

                    else if (estaContido(*Raiz, info) == 2 && (**Raiz).left->count == 2) {
                        (**Raiz).data2.i = 0;
                        (**Raiz).count = 1;
                        (**Raiz).center->data2 = (**Raiz).right->data1;
                        (**Raiz).center->count = 2;
                        (**Raiz).right = NULL;
                    }

                    else if (estaContido(*Raiz, info) == 2 && (**Raiz).left->count == 1) {
                        (**Raiz).data2.i = 0;
                        (**Raiz).count = 1;
                        (**Raiz).center->data2 = (**Raiz).right->data1;
                        (**Raiz).center->count = 2;
                        (**Raiz).right = NULL;
                    }

                    else if (estaContido(*Raiz, info) == 1 && (**Raiz).center->count == 2) {
                        (**Raiz).data1 = (**Raiz).center->data1;
                        (**Raiz).center->data1 = (**Raiz).center->data2;
                        (**Raiz).center->data2.i = 0;
                        (**Raiz).center->count = 1;
                    }

                    else if (estaContido(*Raiz, info) == 1 && (**Raiz).left->count == 2) {
                        (**Raiz).data1 = (**Raiz).left->data2;
                        (**Raiz).left->data2.i = 0;
                        (**Raiz).left->count = 1;
                    }

                    else if (estaContido(*Raiz, info) == 1 && (**Raiz).center->count == 1) {
                        (**Raiz).data1 = (**Raiz).data2;
                        (**Raiz).data2.i = 0;
                        (**Raiz).count = 1;
                        (**Raiz).left->data2 = (**Raiz).center->data1;
                        (**Raiz).left->count = 2;
                        (**Raiz).center = NULL;
                    }

                    else if ((**Raiz).count == 1) {
                        if ((**Raiz).center->count == 2) {
                            (**Raiz).data1 = (**Raiz).center->data1;
                            (**Raiz).center->data1 = (**Raiz).center->data2;
                            (**Raiz).center->data2.i = 0;
                            (**Raiz).center->count = 1;
                        }

                        else if ((**Raiz).left->count == 2) {
                            (**Raiz).data1 = (**Raiz).left->data2;
                            (**Raiz).left->data2.i = 0;
                            (**Raiz).left->count = 1;
                        }

                        else {
                            (**Raiz).left->data2 = (**Raiz).center->data1;
                            (**Raiz).left->count = 2;
                            (**Raiz).right = NULL;
                            *Raiz = (**Raiz).left;
                        }
                    }
                }
            }

            else if (*pai != NULL && isLeaf(*Raiz)) {

                if ((**Raiz).count == 2) {
                    if (estaContido(*Raiz, info) == 1)
                        (**Raiz).data1 = (**Raiz).data2;
                    (**Raiz).data2.i = 0;

                    (**Raiz).count = 1;
                }

                else if ((**pai).count == 2) {
                    if (strcmp(info,(**pai).data2.str) > 0 && (**pai).center->count == 2) {
                        (**Raiz).data1 = (**pai).data2;
                        (**pai).data2 = (**pai).center->data2;
                        (**pai).center->data2.i = 0;
                        (**pai).center->count = 1;
                    }

                    else if (strcmp(info,(**pai).data2.str) > 0 && (**pai).center->count == 1) {
                        (**pai).center->data2 = (**pai).data2;
                        (**pai).center->count = 2;
                        (**pai).data2.i = 0;
                        (**pai).count = 1;
                        *Raiz = NULL;
                    }

                    else if (strcmp(info,(**pai).data1.str) > 0 && (**pai).right->count == 2) {
                        (**Raiz).data1 = (**pai).data2;
                        (**pai).data2 = (**pai).right->data1;
                        (**pai).right->data1 = (**pai).right->data2;
                        (**pai).right->data2.i = 0;
                        (**pai).right->count = 1;
                    }

                    else if (strcmp(info,(**pai).data1.str) > 0 && (**pai).right->count == 1) {
                        (**Raiz).data1 = (**pai).data2;
                        (**Raiz).data2 = (**pai).right->data1;
                        (**Raiz).count = 2;
                        (**pai).data2.i = 0;
                        (**pai).count = 1;
                        (**pai).right = NULL;
                    }

                    else if (strcmp(info,(**pai).data1.str) < 0 && (**pai).center->count == 2) {
                        (**Raiz).data1 = (**pai).data1;
                        (**pai).data1 = (**pai).center->data1;
                        (**pai).center->data1 = (**pai).center->data2;
                        (**pai).center->data2.i = 0;
                        (**pai).center->count = 1;
                    }

                    else if (strcmp(info,(**pai).data1.str) < 0 && (**pai).right->count == 2) {
                        (**Raiz).data1 = (**pai).data1;
                        (**pai).data1 = (**pai).center->data1;
                        (**pai).center->data1 = (**pai).data2;
                        (**pai).data2 = (**pai).right->data1;
                        (**pai).right->data1 = (**pai).right->data2;
                        (**pai).right->data2.i = 0;
                        (**pai).right->count = 1;
                    }

                    else {
                        (**Raiz).data1 = (**pai).data1;
                        (**pai).data1 = (**pai).center->data1;
                        (**pai).center->data1 = (**pai).data2;
                        (**pai).data2.i = 0;
                        (**pai).count = 1;
                        (**pai).center->data2 = (**pai).right->data1;
                        (**pai).center->count = 2;
                        (**pai).right = NULL;
                    }
                }

                else {
                    if (strcmp(info,(**pai).data1.str) > 0 && (**pai).left->count == 2) {
                        (**Raiz).data1 = (**pai).data1;
                        (**pai).data1 = (**pai).left->data2;
                        (**pai).left->data2.i = 0;
                        (**pai).left->count = 1;
                    }

                    else if (strcmp(info,(**pai).data1.str) < 0 && (**pai).center->count == 2) {
                        (**Raiz).data1 = (**pai).data1;
                        (**pai).data1 = (**pai).center->data1;
                        (**pai).center->data1 = (**pai).center->data2;
                        (**pai).center->data2.i = 0;
                        (**pai).center->count = 1;
                    }

                    else if (strcmp(info,(**pai).data1.str) < 0) {
                        (**Raiz).data1 = (**pai).data1;
                        (**Raiz).data2 = (**pai).center->data1;
                        (**Raiz).count = 2;
                        *pai = *Raiz;
                    }

                    else {
                        (**pai).left->data2 = (**pai).data1;
                        (**pai).left->count = 2;
                        *pai = (**pai).left;
                    }
                }
            }

            else if (*pai != NULL && isLeaf(*Raiz) == 0) {
                if (estaContido(*Raiz, info) == 2) {
                    if ((**Raiz).right->count == 2) {
                        (**Raiz).data2 = (**Raiz).right->data1;
                        (**Raiz).right->data1 = (**Raiz).right->data2;
                        (**Raiz).right->data2.i = 0;
                        (**Raiz).right->count = 1;
                    }

                    else if ((**Raiz).center->count == 2) {
                        (**Raiz).data2 = (**Raiz).center->data2;
                        (**Raiz).center->data2.i = 0;
                        (**Raiz).center->count = 1;
                    }

                    else {
                        (**Raiz).center->data2 = (**Raiz).right->data1;
                        (**Raiz).center->count = 2;
                        (**Raiz).data2.i = 0;
                        (**Raiz).count = 2;
                        (**Raiz).right = NULL;
                    }
                }

                else if (estaContido(*Raiz, info) == 1) {
                    if ((**Raiz).center->count == 2) {
                        (**Raiz).data1 = (**Raiz).center->data1;
                        (**Raiz).center->data1 = (**Raiz).center->data2;
                        (**Raiz).center->data2.i = 0;
                        (**Raiz).center->count = 1;
                    }

                    else if ((**Raiz).left->count == 2) {
                        (**Raiz).data1 = (**Raiz).left->data2;
                        (**Raiz).left->data2.i = 0;
                        (**Raiz).left->count = 1;
                    }

                    else {
                        (**Raiz).data1 = (**Raiz).center->data1;
                        (**Raiz).center->data1 = (**Raiz).data2;
                        (**Raiz).data2 = (**Raiz).right->data1;
                        (**Raiz).right->data1 = (**Raiz).right->data2;
                        (**Raiz).right->data2.i = 0;
                        (**Raiz).right->count = 1;
                    }
                }

            }
        }

        else if (strcmp(info,(**Raiz).data1.str) < 0)
            remover(Raiz, &(**Raiz).left, info);

        else if ((**Raiz).count == 1)
            remover(Raiz, &(**Raiz).center, info);

        else if (strcmp(info,(**Raiz).data2.str) < 0)
            remover(Raiz, &(**Raiz).center, info);

        else
            remover(Raiz, &(**Raiz).right, info);
    }

}


int search2(node *root, char str[], int result){
    if (root != NULL){
		if (result != 1){
			if (strcmp(str, root->data1.str) == 0){
				printf("\nPassos: %d\nPalavra: %s ", 0, root->data1.str);
				result = 1;
			}else if (strcmp(str, root->data2.str) < 0){
				result = search2(root->left, str, result);
			}else if (root->count == 2 && strcmp(str, root->data2.str) == 0){
				printf("\nPassos: %d\nPalavra: %s ", 0, root->data2.str);
				result = 1;
			}else if ((root->count == 2 && strcmp(str, root->data2.str) < 0) || root->count == 1){
				result = search2(root->center, str, result);
			}else{
				result = search2(root->right, str, result);
			}
		}
	}

    printf("RESULT = %d\n", result);
    return result;
}

void buscar(node *Raiz, char palavra[], int *achou, int *passo){
	if (Raiz != NULL)
	{
		if (*achou != 1)
		{
			*passo += 1;
			if (strcmp(palavra, Raiz->data1.str) == 0)
			{
				printf("\nPassos: %d\nPalavra: %s ", *passo, Raiz->data1.str);
				// imprimirLista(Raiz->Info1.I);
                // showlist(Raiz->data1.l);
				*achou = 1;
			}
			else if (strcmp(palavra, Raiz->data2.str) < 0)
			{
				buscar(Raiz->left, palavra, achou, passo);
			}
			else if (Raiz->count == 2 && strcmp(palavra, Raiz->data2.str) == 0)
			{
				printf("\nPassos: %d\nPalavra: %s ", *passo, Raiz->data2.str);
				// imprimirLista(Raiz->Info2.I);
                // showlist(Raiz->data1.l);
				*achou = 1;
			}
			else if ((Raiz->count == 2 && strcmp(palavra, Raiz->data2.str) < 0) || Raiz->count == 1)
			{
				buscar(Raiz->center, palavra, achou, passo);
			}
			else
			{
				buscar(Raiz->right, palavra, achou, passo);
			}
		}
	}
}


int main(){

    node *rootTree = NULL, *nodeAux = NULL;
    tdata dataAvg, newData;
    int result = 0, count = 0;

    openFile(&rootTree, &nodeAux);

    //inOrder(rootTree);

    strcpy(newData.str, "todo");

    initList(&newData.l);
    result = 0;
    buscar(rootTree, newData.str, &result, &count);
/*
    if(search2(rootTree, newData.str, 0)){
        printf("# SEARCH\n");
        printf("PALAVRA: %s\n", newData.str);
        printf("LINHAS: ");
        // showlist(&newData.l);
        printf("\n");
    }else printf("[!] Não encontrada\n");*/

    // if(search(rootTree, newData.str, 0, &count, &newData.l)){
    //     printf("# SEARCH\n");
    //     printf("PALAVRA: %s\n", newData.str);
    //     printf("PASSO: %d\n", count);
    //     printf("LINHAS: ");
    //     showlist(&newData.l);
    //     printf("\n");

    // }else printf("[!] Não encontrada\n");

// testes na remoção do nó da árvore 23
    printf("ÁRVORE INICIO\n");
    //inOrder(rootTree);
    //remover(NULL,&rootTree,"casas");
    //remover(NULL,&rootTree,"lugar");


    printf("\n\n\nÁRVORE FINAL\n");
    inOrder(rootTree);



    return 0;
}

// ÁRVORE 2-3
node *createNode(tdata data, node *cLeft, node *cCenter){
    node *new;
    new = (node *)malloc(sizeof(node));
    (*new).data1 = data;
    (*new).count = 1;
    (*new).left = cLeft;
    (*new).center = cCenter;
    (*new).right = NULL;

    return new;
}

node *addInNode(node *root, tdata data, node *child){
    if( strcmp(data.str, (*root).data1.str) > 0 ){
        (*root).data2 = data;
        (*root).right = child;
    }else{
        (*root).data2 = (*root).data1;
        (*root).right = (*root).center;
        (*root).data1 = data;
        (*root).center = child;
    }

    (*root).count = 2;

    return root;
}

void toBreakNode(node **root, tdata data, node *cBigger, tdata *dataUp, node **new){

    if( strcmp(data.str, (*root)->data1.str ) < 0 ){
        *dataUp = (*root)->data1;
        *new = createNode((*root)->data2, (*root)->center, (*root)->right);
        (*root)->data1 = data;
        (*root)->center = cBigger;
        (*root)->right = NULL;
        (*root)->count = 1;
    }else if( strcmp(data.str, (*root)->data2.str ) < 0 ){
        *dataUp = data;
        *new = createNode((*root)->data2, (*root)->center, (*root)->right);
        (*root)->center = cBigger;
        (*root)->right = NULL;
        (*root)->count = 1;
    }else{
        *dataUp = (*root)->data2;
        *new = createNode(data, (*root)->right, cBigger);
        (*root)->right =  NULL;
        (*root)->count = 1;
    }

}

node *insertTree23(node **father, node **root, tdata data, tdata *dataUp){
    int result = 1;
    node *aux = NULL;



    if(*root == NULL){
        *root = createNode(data, NULL, NULL);
    }else{

        if( strcmp( (*root)->data1.str, data.str) == 0 ){
            insertList(&(*root)->data1.l, data.i);
        }else if(strcmp( (*root)->data2.str, data.str) == 0){
            insertList(&(*root)->data2.l, data.i);
        }else{
            if(isLeaf(*root)){

                if( (**root).count == 1 ) *root = addInNode(*root, data, NULL);
                else{
                    toBreakNode(root, data, NULL, dataUp, &aux);
                    if(father == NULL){
                        node *new;
                        new = createNode(*dataUp, *root, aux);
                        *root =  new;
                        aux = NULL;
                    }
                }

            }else{

                if( strcmp(data.str, (**root).data1.str )  < 0 ) aux = insertTree23(root, &((*root)->left), data, dataUp);
                else if( ( strcmp(data.str, (**root).data2.str ) < 0 && (**root).count == 2 ) || (**root).count == 1) aux = insertTree23(root,&((*root)->center), data,dataUp);
                else aux = insertTree23(root,&((*root)->right), data, dataUp);

                if(aux != NULL){

                    if((**root).count == 1){
                        *root = addInNode(*root,*dataUp,aux);
                        aux = NULL;
                    }else {

                        tdata newDataUp;
                        node *newNode;
                        toBreakNode(root,*dataUp, aux, &newDataUp, &newNode);

                        if(father == NULL){
                            node *new;
                            new = createNode(newDataUp, *root, newNode);
                            *root = new;
                            aux = NULL;
                        }else aux = newNode;
                    }
                }
            }
        }

    }

    return aux;
}

int isLeaf(node *root){
    return ((*root).left == NULL && (*root).center == NULL && (*root).right == NULL);
}

void inOrder(node *root){
    if(root != NULL){
        inOrder(root->left);
        printf("%s ", root->data1.str);
        printf("L: ");
        showlist(&root->data1.l);
        printf("\n");
        inOrder(root->center);
        if(root->count == 2){
            printf("%s ", root->data2.str);
            printf("L: ");
            showlist(&root->data2.l);
            printf("\n");
        }
        inOrder(root->right);
    }
}

void *openFile(node **rootTree, node **nodeAux){

    FILE *file;
    tdata newData, dataAvg;
    char line[TAM_STR], *str;
    int i = 1;

    file = fopen("file.txt", "r");

    if(file){
        while(fgets(line, 1000, file) != NULL){

            str = strtok(line, "\n");
            str = strtok(line, " .,;:!?()-\\/--''\"");

            while(str){

                // printf("STR = %s | L = %d\n", str, i);

                initList(&newData.l);
                insertList(&newData.l, i);
                newData.i = i;
                strcpy(newData.str, str);

                *nodeAux = insertTree23(NULL, rootTree, newData, &dataAvg);

                str = strtok(NULL, " !.,");
            }

            i++;
        }
        fclose(file);
    }else printf("[!] -  Erro ao abrir o arquivo!\n");
}

// LISTA ENCADEADA SIMPLES
void initList(List *l){
    l->s = NULL;
}

void insertList(List *l, int x){

    // printf("\n### L%d\n", x);
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

		if(prev == NULL) l->s = new;
		else prev->next = new;
	}
}

void showlist(List *l){
    tlist *s = l->s;

    while(s != NULL){
        printf("%d ", s->x);
        s = s->next;
    }

}

int search(node *root, char x[TAM_STR], int result, int *countSteps, List *l){
    if(root == NULL) result = 0;
    else if(strcmp(root->data1.str, x) == 0){
        result = 1;
        l->s = root->data1.l.s;
    }else if(strcmp(x, root->data1.str) < 0){
        *countSteps += 1;
        result = search(root->left, x, result, countSteps, l);
    }else{
        *countSteps += 1;
        result = search(root->right, x, result, countSteps, l);
    }

    return result;
}
