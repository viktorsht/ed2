#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_STR 10


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
    char str[TAM_STR];
    List l;
} tdata;

// ÁRVORE 2-3
typedef struct aux{
    int count;
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


int main(){

    node *rootTree = NULL, *nodeAux = NULL;
    tdata dataAvg, newData;


    // DATA
    /*
    */
    initList(&newData.l);
    insertList(&newData.l, 1);
    insertList(&newData.l, 5);
    insertList(&newData.l, 3);

    // showlist(&newData.l);
    // DATA


    strcpy(newData.str, "teste");
    nodeAux = insertTree23(NULL, &rootTree, newData, &dataAvg);

    strcpy(newData.str, "teste2");
    nodeAux = insertTree23(NULL, &rootTree, newData, &dataAvg);

    strcpy(newData.str, "teste3");
    nodeAux = insertTree23(NULL, &rootTree, newData, &dataAvg);

    /*
    strcpy(newData.str, "teste4");
    nodeAux = insertTree23(NULL, &rootTree, newData, &dataAvg);

    strcpy(newData.str, "teste5");
    nodeAux = insertTree23(NULL, &rootTree, newData, &dataAvg);

    strcpy(newData.str, "teste6");
    nodeAux = insertTree23(NULL, &rootTree, newData, &dataAvg);

    strcpy(newData.str, "teste7");
    nodeAux = insertTree23(NULL, &rootTree, newData, &dataAvg);

    strcpy(newData.str, "teste8");
    nodeAux = insertTree23(NULL, &rootTree, newData, &dataAvg);

    */

    printf("COUN = %d\n", rootTree->count);

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
    }
    else{
        (*root).data2 = (*root).data1;
        (*root).right = (*root).center;
        (*root).data1 = data;
        (*root).center = child;
    }

    (*root).count = 2;

    return root;
}

void toBreakNode(node **root, tdata data, node *cBigger, tdata *dataUp, node **new){
    if( strcmp(data.str, (*new)->data1.str) < 0 ){
        *dataUp = (*root)->data1;
        *new = createNode((*root)->data2, (*root)->center, (*root)->right);
        (*root)->data1 = data;
        (*root)->center = cBigger;
        (*root)->right = NULL;
        (*root)->count = 1;
    }else if( strcmp(data.str, (*root)->data2.str) < 0 ){
        *dataUp = data;
        *new = createNode((*root)->data2, (*root)->center, (*root)->right);
        (*root)->center = cBigger;
        (*root)->right =  NULL;
        (*root)->count = 1;
    }else{
        *dataUp = (*root)->data2;
        *new = createNode(data, (*root)->right, cBigger);
        (*root)->right = NULL;
        (*root)->count = 1;
    }
}

node *insertTree23(node **father, node **root, tdata data, tdata *dataUp){
    //int result = 1; // não está sendo usado
    node *aux;
    aux = NULL;

    if(*root == NULL) *root = createNode(data, NULL, NULL);
    else{
      if(isLeaf(*root)){
        if((**root).count == 1) *root = addInNode(*root, data, NULL);
        else{
          // aqui o nó tem que ser quabrado
          //toBreakNode(root,data,NULL,dataUp,&aux);
          if(father == NULL){
            node *newNode;
            newNode = createNode(*dataUp, *root, aux);
            *root = newNode;
            aux = NULL;
          }
        }
    }

    else{

            if( strcmp(data.str, (**root).data1.str) < 0 ){
              aux = insertTree23(root, &((*root)->left), data, dataUp);
            }
            else if( (strcmp(data.str, (**root).data2.str) < 0 && (**root).count == 2 ) || (**root).count == 1 ){
              aux = insertTree23(root, &((*root)->center), data, dataUp);
            }
            else{
              aux = insertTree23(root, &((*root)->right), data, dataUp);
              printf("estou aqui\n");
            }


            if(aux != NULL){

                if((**root).count == 1){
                    *root = addInNode(*root, *dataUp, aux);
                    aux = NULL;
                }else{

                    tdata newDataUp;
                    node *newNode;
                    toBreakNode(root, *dataUp, aux, &newDataUp, &newNode);

                    if(father == NULL){
                        node *new;
                        new = createNode(newDataUp, *root,newNode);
                        *root = new;
                        aux = NULL;
                    }
                    else aux = newNode;

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
        printf("%s\n", root->data1.str);
        inOrder(root->center);
        if(root->count == 2) printf("%s\n", root->data2.str);
        inOrder(root->right);
    }
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
    // if(root == NULL) result = 0;
    // else if(strcmp(root->data.str, x) == 0){
    //     result = 1;
    //     l->s = root->data.l.s;
    // }else if(strcmp(x, root->data.str) < 0){
    //     *countSteps += 1;
    //     result = search(root->left, x, result, countSteps, l);
    // }else{
    //     *countSteps += 1;
    //     result = search(root->right, x, result, countSteps, l);
    // }

    // return result;
}
