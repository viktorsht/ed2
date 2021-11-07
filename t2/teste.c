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

// STRUCT ÁRVORE
typedef struct{
    List l;
    int i;
    char str[TAM_STR];
} tdata;

typedef struct node{
    struct node *left, *right;
    tdata data;
    int color; // red ==> 1, black ==> 0
} node;

// ESCOPO FUNÇÕES LISTA
void initList(List *l);
void insertList(List *l, int x);
int toRemoveList(List *l, int x);
void showList(List *l);
int qtdOfElementsList(List *l);


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

//  REMOÇÃO EVA/WENDEL LLRB
node *remover( node *no, char info[],int numberLine);
node *rotacionaleftuerda( node *no);
node *rotacionarighteita( node *no);
node *remove_NO( node *no, char info[]);
node *move2leftred( node *no);
node *move2rightred( node *no);
node *balancear( node *no);
node *removeMenor( node *no);
node *procuraMenor( node *atual);
void trocaCor( node *no);
int color( node *no);

int menu();

int main(){

    node *root = NULL, *nodeAux = NULL;
    tdata *dataAux = NULL, newData;
    int result = 0, count = 0, op = 0, i=0 ;

    root = openFile(root); // CARREGANDO PALAVRAS DO ARQUIVO

    //inOrder(root); // IMPRIMINDO ÁRVORE EM ORDEM
    /*
    */
    root = remover(root, "em",1); // REMOVE COM SUCESSO
    root = remover(root, "em",4); // REMOVE COM SUCESSO
    root = remover(root, "sejam",1); //  REMOVE
    root = remover(root, "tudo",1); //  REMOVE
    root = remover(root, "todo",1); //  REMOVE
    root = remover(root,"por",1); // falha
    inOrder(root); // IMPRIMINDO ÁRVORE EM ORDEM APÓS A REMOÇÃO



/*
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
             root = remover(root, newData.str, newData.i);
    //         // root = toRemoveTree(root, newData.str, newData.i);

             break;

         default:
             printf("[!] OPÇÃO INVÁLIDA!\n");
             break;
         }

     }while ( op != 0 );
*/
    return 0;
}

//  REMOÇÃO TREE

node *remover(node *no, char info[],int numberLine){
    int achou, passos;
    tdata *dataAux = NULL;

    achou = searchTree(no,info, achou, &passos, &dataAux);

    if (achou){

        int qtd = qtdOfElementsList(&dataAux->l);
        printf("QTD %d\n", qtd);


        if(qtd <= 1){

            struct node *novo = no;
            no = remove_NO(novo, info);
            if (no != NULL)
            {
                no->color = 0;
            }
        }else{
            int result = toRemoveList(&dataAux->l, numberLine);
        }

        return no;
    }
    else
        return no;
}

node *rotacionaleftuerda( node *no){
    node *novo = no->right;
    no->right = novo->left;
    novo->left = no;
    novo->color = no->color;
    no->color = 1;
    return novo;
}

node *rotacionarighteita(node *no){
    node *novo = no->left;
    no->left = novo->right;
    novo->right = no;
    novo->color = no->color;
    no->color = 1;
    return novo;
}

node *remove_NO( node *no, char info[]){
    if (strcmp(info, no->data.str) < 0){
        if (color(no->left) == 0 && color(no->left->left) == 0){
            no = move2leftred(no);
        }

        no->left = remove_NO(no->left, info);
    }else{
        if (color(no->left) == 1){
            no = rotacionarighteita(no);
        }

        if (strcmp(info, no->data.str) == 0 && no->right == NULL){
            free(no);
            return NULL;
        }

        if (color(no->right) == 0 && color(no->right->left) == 0){
            no = move2rightred(no);
        }

        if (strcmp(info, no->data.str) == 0){
            node *aux = procuraMenor(no->right);
            no->data = aux->data;
            no->right = removeMenor(no->right);
        }else{
            no->right = remove_NO(no->right, info);
        }
    }

    return balancear(no);
}

node *move2leftred(node *no){
    trocaCor(no);

    if (color(no->right->left) == 1){
        no->right = rotacionarighteita(no->right);
        no = rotacionaleftuerda(no);
        trocaCor(no);
    }

    return no;
}

node *move2rightred(node *no){
    trocaCor(no);
    if (color(no->left->left) == 1){
        no = rotacionarighteita(no);
        trocaCor(no);
    }

    return no;
}

node *balancear(node *no){
    if (color(no->right) == 1){
        no = rotacionaleftuerda(no);
    }

    if (no->left != NULL && color(no->left) == 1 && color(no->left->left) == 1){
        no = rotacionaleftuerda(no);
    }

    if (color(no->left) == 1 && color(no->right) == 1){
        trocaCor(no);
    }

    return no;
}

node *removeMenor(node *no){
    if (no->left == NULL){
        free(no);
        return NULL;
    }

    if (color(no->left) == 0 && color(no->left->left) == 0){
        no = move2leftred(no);
    }

    no->left = removeMenor(no->left);
    return balancear(no);
}

node *procuraMenor(node *atual){
    node *no1 = atual;
    node *no2 = atual->left;

    while (no2 != NULL){
        no1 = no2;
        no2 = no2->left;
    }

    return no1;
}

void trocaCor(node *no){
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

int color(node *no){
    return no == NULL ? 0 : no->color;
}


// REMOVER



int menu(){
    int op = 0;
    printf("[0] - Sair\n[1] - inOrder\n[2] - Adicionar palavra\n[3] - Buscar\n[4] - Remover\nOPÇÃO: ");
    scanf("%d", &op);
    return op;
}

node *toRemoveTree(node *root, char x[], int line){
    int found = 0, steps= 0 , qtd = 0, result = 0;
    tdata *dataAux = NULL;

    found = searchTree(root, x, 0, &steps, &dataAux);

    if(found){
        qtd = qtdOfElementsList(&dataAux->l);

        if(qtd <= 1){
            node *new = root;
            root = toRemoveNodeTree(new, dataAux->str);

        }else result = toRemoveList(&dataAux->l, line);

        return root;

    }else {
        printf("[!] PALAVRA NÃO ENCONTRADA!\n");
        return root;
    }

}

node *toRemoveNodeTree(node *root, char x[]){
    if (strcmp(x, root->data.str) < 0){
        if (!isRed(root->left) && !isRed(root->left->left)) root = move2Left(root);
        root->left = toRemoveNodeTree(root->left, x);
    }else{
        if (isRed(root->left)) root = rotateToRightTree(root);
        if (strcmp(x, root->data.str) == 0 && root->right == NULL){
            free(root);
            return NULL;
        }

        if (!isRed(root->right) && !isRed(root->right->left)) root = move2Right(root);
        if (strcmp(x, root->data.str) == 0){
            node *aux = searchNodeSmaller(root->right);
            root->data = aux->data;
            root->right = toRemoveSmaller(root->right);
        }else root->right = toRemoveNodeTree(root->right, x);
    }

    return balanceTree(root);
}

node *balanceTree(node *root){
    if (isRed(root->right)) root = rotateToLeftTree(root);
    if (root->left != NULL && isRed(root->left) && isRed(root->left->left)) root = rotateToLeftTree(root);
    if (isRed(root->left) && isRed(root->right)) swapColorTree(root);

    return root;
}

node *toRemoveSmaller(node *root){
    if (root->left == NULL){
        free(root);
        return NULL;
    }
    if (!isRed(root->left) && !isRed(root->left->left)) root = move2Left(root);

    root->left = toRemoveSmaller(root->left);

    return balanceTree(root);
}

node *searchNodeSmaller(node *root){
    node *node1 = root;
    node *node2 = root->left;

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
node *createNode(tdata data){
    node *new = (node *)malloc(sizeof(node));
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
        showList(&node->data.l);
        printf("\n");
        inOrder(node->right);
    }
}

node *rotateToLeftTree(node *root){
    node *new = root->right;
    root->right = new->left;
    new->left = root;
    new->color = root->color;
    root->color = 1;

    return new;
}

node *rotateToRightTree(node *root){
    node *new = root->left;
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
    if (root == NULL){
        node *new = createNode(data);

        if(new == NULL){
            *result = 0;
            return NULL;
        }


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

    if (isRed(root->right) && !isRed(root->left)) root = rotateToLeftTree(root);
    if (isRed(root->left) && isRed(root->left->left)) root = rotateToRightTree(root);
    if (isRed(root->left) && isRed(root->right)) swapColorTree(root);
    return root;
}

int searchTree(node *root, char x[TAM_STR], int result, int *countSteps, tdata **dataAux){
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
