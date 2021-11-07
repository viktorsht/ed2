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

//typedef struct{
//    tlist *s;
//} List;

// STRUCT ÁRVORE
typedef struct{
    tlist *l;
    int i;
    char str[TAM_STR];
} tdata;

typedef struct node{
    struct node *left, *right;
    tdata data;
    int color; // red ==> 1, black ==> 0
} node;

// ESCOPO FUNÇÕES LISTA
void initList(tlist **l);
void insertList(tlist **l, int x);
int toRemoveList(tlist **l, int x);
void showList(tlist *l);
int qtdOfElementsList(tlist *l);


// ESCOPO FUNÇÕES ÁRVORE
node *createNodeTree(tdata data);
int isRed(node *root);
void swapColorTree(node *root);
void inOrder(node *root);
node *insertTree(node *root, tdata data, int *result);
node *insertNodeTree(node *root, tdata data, int *result);
node *rotateToLeftTree(node* root);
node *rotateToRightTree(node* root);
node *openFile(node *root);
int searchTree(node *root, char x[TAM_STR], int result, int *countSteps, tdata **dataAux);


// REMOÇÃO LLRB
node *toRemoveTree(node *root, char x[], int line);
node *toRemoveNodeTree(node *root, char x[]);
node *balanceTree(node *root);
node *toRemoveSmaller(node *root);
node *searchNodeSmaller(node *root);
node *move2Left(node *root);
node *move2Right(node *root);

int menu();

int main(){

    node *root, *nodeAux;
    tdata *dataAux = NULL, newData;
    int result = 0, count = 0, op = 0, i=0 ;

    root = NULL;
    nodeAux = NULL;
    //dataAux = NULL;

    root = openFile(root); // CARREGANDO PALAVRAS DO ARQUIVO

    //inOrder(root); // IMPRIMINDO ÁRVORE EM ORDEM

    // STR = vossos | L = 3
    // STR = sejam | L = 1
    // STR = todo | L = 1
    // STR =tudo | L = 1
    // STR = por | L = 1

    // AO TENTAR REMOVER ESSA SEQUÊNCIA DA FALHA DE SEGMENTAÇÃO NA ÚLTIMA REMOÇÃO,
    // OU SEJA, ACHAVAMOS QUE NÓ TINHAMOS CODIFICADO ERRADO, PORÉM
    // IMPLEMENTAMOS A MESMA REMOÇÃO DE EVA/WENDEL E TAMBÉM DEU ERRO

  // root = toRemoveTree(root, "vossos",3); //
//    root = toRemoveTree(root, "Deus",2); //
 //  root = toRemoveTree(root, "sejam",1); //
  // root = toRemoveTree(root, "todo",1); //
//   root = toRemoveTree(root, "tudo",1); //
//    root = toRemoveTree(root, "por",1); //
//
//
    //printf("\n\n Lista depois da remocao!!! \n\n");
    //inOrder(root); // IMPRIMINDO ÁRVORE EM ORDEM APÓS A REMOÇÃO

    // CHAMANDO A FUNÇÃO DE REMOVER
    // PARAMETROS, ENDREÇO DA RAIZ, STRING A SER REMOVIDA E A LINHA
    // root = toRemoveTree(root, "string", linha)





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
            // root = remover(root, newData.str, newData.i);
              root = toRemoveTree(root, newData.str, newData.i);

             break;

         default:
             printf("[!] OPÇÃO INVÁLIDA!\n");
             break;
         }

     }while ( op != 0 );

    return 0;
}

//  REMOÇÃO TREE



// REMOVER



int menu(){
    int op = 0;
    printf("[0] - Sair\n[1] - inOrder\n[2] - Adicionar palavra\n[3] - Buscar\n[4] - Remover\nOPÇÃO: ");
    scanf("%d", &op);
    return op;
}

node *toRemoveTree(node *root, char x[], int line){
    int found = 0, steps= 0 , qtd = 0, result = 0;
    tdata *dataAux;

    dataAux = NULL;

    found = searchTree(root, x, 0, &steps, &dataAux);

    if(found){
        qtd = qtdOfElementsList(dataAux->l);

        if(qtd <= 1){
            node *new;
            new = root;
            root = toRemoveNodeTree(new, dataAux->str);

        }else result = toRemoveList(&dataAux->l, line);

        //return root;

    }else {
        printf("[!] PALAVRA NÃO ENCONTRADA!\n");
        //return root;
    }
    return root;
}

node *toRemoveNodeTree(node *root, char x[]){
    if (strcmp(x, root->data.str) < 0){
        if (!isRed(root->left) && !isRed(root->left->left))
            root = move2Left(root);
        root->left = toRemoveNodeTree(root->left, x);
    }else{
        if (isRed(root->left)) root = rotateToRightTree(root);
        if (strcmp(x, root->data.str) == 0 && root->right == NULL){
            free(root);
            root =  NULL;
        }
        else{
                if (!isRed(root->right) && !isRed(root->right->left))
                    root = move2Right(root);

                if (strcmp(x, root->data.str) == 0){
                    node *aux;
                    aux = searchNodeSmaller(root->right);
                    root->data = aux->data;
                    root->right = toRemoveSmaller(root->right);
                }else root->right = toRemoveNodeTree(root->right, x);
            }

        }
    if(root != NULL)
      root = balanceTree(root);
    return root;
}

node *balanceTree(node *root){
    if (isRed(root->right))
         root = rotateToLeftTree(root);
    if (root->left != NULL && isRed(root->left) && isRed(root->left->left))
         root = rotateToLeftTree(root);
    if (isRed(root->left) && isRed(root->right))
         swapColorTree(root);

    return root;
}

node *toRemoveSmaller(node *root){
    if (root->left == NULL){
        free(root);
        root =  NULL;
    }
    else{
        if (!isRed(root->left) && !isRed(root->left->left))
            root = move2Left(root);

        root->left = toRemoveSmaller(root->left);

        root = balanceTree(root);
    }
    return root;
}

node *searchNodeSmaller(node *root){
    node *node1, *node2;
    node1 = root;
    node2 = root->left;

    while (node2 != NULL){
        node1 = node2;
        node2 = node2->left;
    }

    return node2;
}

node *move2Left(node *root){
    swapColorTree(root);
    if (isRed(root->right->left)){
        root->right = rotateToRightTree(root->right);
        root = rotateToLeftTree(root);
        swapColorTree(root);
    }

    return root;
}

node *move2Right(node *root){
    swapColorTree(root);
    if (isRed(root->left->left)){
        root = rotateToRightTree(root);
        swapColorTree(root);
    }
    return root;
}


node *openFile(node *root){
    FILE *file;
    tdata new;
    int i = 1, result = 0;
    char str[TAM_STR], *str2;
    //, str3;

    file = fopen("file.txt", "r");

    initList(&new.l);

    if(file){
        while(fgets(str, TAM_STR, file) != NULL){

            str2 = strtok(str, "\n");
            str2 = strtok(str, " .,;:!?()-\\/--''\"");

            while(str2){

                strcpy(new.str, str2);
                new.i = i;

                insertList(&(new.l), i);

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
node *createNode(tdata data){
    node *new;

    new = (node *)malloc(sizeof(node));
    new->left = new->right = NULL;
    // initList(&data.l);
    new->data = data;
    new->color = 1;

    return new;
}

int isRed(node *root){
    return root == NULL ? 0 : root->color == 1;
}

void swapColorTree(node *root){
    root->color = !root->color;

    if (root->left != NULL) root->left->color = !root->left->color;
    if (root->right != NULL) root->right->color = !root->right->color;
}

void inOrder(node *node){
    if(node){
        inOrder(node->left);
        printf("STR: %s | COR: %s\n", node->data.str, node->color ? "RED" : "BLACK");

        printf("L: ");
        showList(node->data.l);
        printf("\n");
        inOrder(node->right);
    }
}

node *rotateToLeftTree(node *root){
    node *new;

    new = root->right;
    root->right = new->left;
    new->left = root;
    new->color = root->color;
    root->color = 1;

    return new;
}

node *rotateToRightTree(node *root){
    node *new;

    new = root->left;
    root->left = new->right;
    new->right = root;
    new->color = root->color;
    root->color = 1;

    return new;
}

node *insertTree(node *root, tdata x, int *flag){
    root = insertNodeTree(root, x, flag);
    if (root != NULL) root->color = 0;
    return root;
}

node *insertNodeTree(node *root, tdata data, int *result){
    node *new;
    new = NULL;
    *result = 0;
    if (root == NULL){
        new = createNode(data);
        if(new != NULL)
         *result = 1;
        root =  new;
    }
    else {
        if (strcmp(data.str, root->data.str) == 0){
            *result = 1;
            insertList(&root->data.l,data.i);
        }
        else{
            if (strcmp(data.str, root->data.str) < 0)
                root->left = insertNodeTree(root->left, data, result);
            else root->right = insertNodeTree(root->right, data, result);
        }

        if (isRed(root->right) && !isRed(root->left))
            root = rotateToLeftTree(root);
        if (isRed(root->left) && isRed(root->left->left))
            root = rotateToRightTree(root);
        if (isRed(root->left) && isRed(root->right))
            swapColorTree(root);
    }
    return root;
}

int searchTree(node *root, char x[TAM_STR], int result, int *countSteps, tdata **dataAux){
    if(root == NULL) result = 0;
    else if(strcmp(root->data.str, x) == 0){
        result = 1;
        *dataAux = &root->data;
    }else if(strcmp(x, root->data.str) < 0){
        *countSteps += 1;
        result = searchTree(root->left, x, result, countSteps, dataAux);
    }else{
        *countSteps += 1;
        result = searchTree(root->right, x, result, countSteps, dataAux);
    }

    return result;
}

// FUNÇÕES LISTA
void initList(tlist **l){
    *l = NULL;
}

void insertList(tlist **l, int x){
    tlist *s, *new, *prev;
    //tlist *new, *prev;

	new = (tlist *) malloc(sizeof(tlist));
    s = *l;
	prev = NULL;

    new->x = x;
	new->next = NULL;

	if(*l == NULL){
		*l = new;
        new->next = NULL;
	}else{
		while(s->next != NULL && s->x < x){
			prev = s;
			s = s->next;
		}

    //    new->next = *l;

		if(s->next == NULL) {
            if(x != s->x) s->next = new;
        }else{
            new->next = s;
            prev->next = new;
    //        if(prev->next == NULL) prev->next = new;
    //        if(x != prev->next->x) prev->next = new;
        }
	}

}

int toRemoveList(tlist **l, int x){
    tlist *s, *prev, *remove;
    //tlist  *nodeToRemove;
	int result = 0;

    s = *l;
    prev = NULL;
    if (s != NULL)
	{
		while(s->next != NULL  && s->x != x){
            prev = s;
            s = s->next;
		}

        if(s->x == x){
            remove = s;
            if(prev == NULL)
            { s = s->next;
              *l = s;
            }
            else prev->next = s->next;

            free(remove);
            result = 1;
	   }
    }

	return result;
}

int qtdOfElementsList(tlist *l){
//    tlist *s = *l;
    int i = 0;

    while(l != NULL){
        l = l->next;
        i++;
    }

    return i;
}

void showList(tlist *l){
    //tlist *s = *l;

    while(l != NULL){
        printf("%d ", l->x);
        l = l->next;
    }

}
