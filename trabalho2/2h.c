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
    int i;
    char str[TAM_STR];

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
int qtdOfElementsList(List *l);


void *openFile(node **rootTree, node **nodeAux);


int menu();

int search2(node *root, char str[], int result, int *countSteps, tdata **dataAux){
  if(root != NULL){
    if(result != 1){
      *countSteps += 1;
      if(strcmp(str, root->data1.str) == 0){
        *dataAux = &root->data1;
        result = 1;
  	  }
      else if(strcmp(str, root->data2.str) < 0)
        search2(root->left, str, result, countSteps, (dataAux));
      else if(root->count == 2 && strcmp(str, root->data2.str) == 0){
        *dataAux = &root->data2;
        result = 1;
      }
      else if( (root->count == 2 && strcmp(str, root->data2.str) < 0) || root->count == 1 )
        search2(root->center, str, result, countSteps, (dataAux));
      else
        search2(root->right, str, result, countSteps, (dataAux));
    }
  }
  return result;
}

node *find(node *root, char *str, int *result){
  if(root == NULL) return NULL;
  if(strcmp(str,root->data1.str) == 0) {
    *result = 1;
    return root;
  }
  if((root->count == 2) && (strcmp(str,root->data2.str) == 0)){
    *result = 1;
    return root;
  }
  if(strcmp(str,root->data1.str) < 0) return find(root->left,str,result);
  else if(root->count == 1) return find(root->center,str,result);
  else if(strcmp(str,root->data2.str) < 0) return find(root->center,str,result);
  else return find(root->right,str,result);
}

int main(){

    node *rootTree = NULL, *nodeAux = NULL;
    tdata dataAvg, newData, *dataAux = NULL;
    int result = 0, count = 0, op = 0, i = 0;

    openFile(&rootTree, &nodeAux);

    do{
        op = menu();

        switch (op){
            case 0:
                break;
            case 1:
                printf("# MOSTRAR PALAVRAS EM ORDEM\n");
                inOrder(rootTree);
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
                    // showList(&newData.l);

                }while(i != 0);

                count = qtdOfElementsList(&newData.l);
                printf("QTD %d\n", count);

                if(count){
                    nodeAux = insertTree23(NULL, &rootTree, newData, &dataAvg);
                    // root = insertTree(root, newData, &result);
                    // if(result) printf("# SUCCESS AO INSERIR A PALAVRA!\n");
                    // else printf("[!] ERRO AO INSERIR A PALAVRA!\n");
                }else printf("[!] NENHUMA LINHA ATRIBUIDA A PALAVRA!\n");
                break;
            case 3:
                printf("# BUSCAR PALAVRA\n");
                printf("Palavra: ");
                scanf("%s", newData.str);

                count = 0;
                // result = search(rootTree, newData.str, 0, &count, &dataAux);
                //result = search2(rootTree, newData.str, 0, &count, &dataAux);
                rootTree = find(rootTree,newData.str,&result);
                if(result){
                    printf("# ACHOU!\n");
                    printf("Linhas: ");
                    //showlist(&dataAux->l);
                    printf("\n");
                    printf("Passos: %d\n", count);
                } else printf("[!] PALAVRA NÃO ENCONTRADA!\n");
                break;
            }

    }while(op != 0);

    // inOrder(rootTree);

    // strcpy(newData.str, "vossos");

    // initList(&newData.l);
    // result = 0;

    // if(search(rootTree, newData.str, 0)){
    //     printf("# SEARCH\n");
    //     printf("PALAVRA: %s\n", newData.str);
    //     printf("LINHAS: ");
    //     // showlist(&newData.l);
    //     printf("\n");
    // }else printf("[!] Não encontrada\n");


    return 0;
}

int menu(){
    int op = 0;
    printf("[0] - Sair\n[1] - inOrder\n[2] - Adicionar palavra\n[3] - Buscar\n[4] - Remover\nOPÇÃO: ");
    scanf("%d", &op);
    return op;
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
        printf("%s\n", root->data1.str);
        printf("L: ");
        showlist(&root->data1.l);
        printf("\n");
        inOrder(root->center);
        if(root->count == 2){
            printf("%s\n", root->data2.str);
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

int qtdOfElementsList(List *l){
    tlist *s = l->s;
    int i = 0;

    while(s != NULL){
        s = s->next;
        i++;
    }

    return i;
}
