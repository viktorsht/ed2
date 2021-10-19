#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_NUMBERS 7

typedef int tdata;
typedef struct no{
    tdata data;
    struct no *right, *left;
}tno;

tno *createdNode(tdata x){
    tno *new;
    new = (tno *)malloc(sizeof(tno));
    new->data = x;
    new->right = new->left = NULL;
    return new;
}


// --- INICIAR ARVORE
void init(tno *root){
  root = NULL;
}

//---- INSERT
tno *insert(tno *root, tno *new, tno *result){
    if(root != NULL){
        if(new->data < root->data) root->left = insert(root->left, new, result);
        else root->right = insert(root->right, new, result);
        result = root;
    }else result = new;

    return result;
}

// -- PREORDER
void preOrder(tno *root){
    if(root != NULL){
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// -- INORDER
void inOrder(tno *root){
    if(root != NULL){
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// -- POSORDER
void posOrder(tno *root){
    if(root != NULL){
        posOrder(root->left);
        posOrder(root->right);
        printf("%d ", root->data);
    }
}

// -- SEARCH
tno *search(tno *root, tdata x, tno *result){
  if(root == NULL) result = NULL;
  else if(x == root->data) result = root;
  else if(x < root->data) result = search(root->left, x, result);
  else result = search(root->right, x, result);

  return result;
}

// --- LOADING NUMBERS OF ONE FILE
tno *openFile(tno *root, tno *result){
    FILE *file;
    tdata x;
    int i, n = TAM_NUMBERS;

    file = fopen("numbers.txt", "r");

    if(file){
        // printf("# QUANTOS NÚMEROS DESEJA LER?\nQTD: ");
        // scanf("%d", &n);

        for(i=0; i<n; i++){
            fscanf(file, "%d", &x);
            printf("%d ", x);
            root = insert(root,createdNode(x), root);
        }
        printf("\n");
        fclose(file);
    }else printf("[!] - ERRO AO ABRIR O ARQUIVO\n");

    return root;
}

// --- FUNÇÃO PARA QUANTIDADE DE NÓS E RAMOS
void getQtdNodesAndTwigs(tno *root, int *result){
    if(root != NULL){
        *result += 1;
        getQtdNodesAndTwigs(root->left, result);
        getQtdNodesAndTwigs(root->right, result);
    }

}

// --- FUNÇÃO PARA CALCULAR ALTURA
void getDepth(tno *root, tdata x, int *result){
    if(root != NULL){
        if(x != root->data){
            *result += 1;

            if(x < root->data) getDepth(root->left, x, result);
            else getDepth(root->right, x, result);
        }
    }
}

int getHeight (tno *root, int result){
	if (root == NULL) result = -1;
	else {
		int hl = getHeight (root->left,result);
		int hr = getHeight (root->right,result);

    result = (hl < hr ? hr : hl) + 1;
	}
	return result;
}

// --- FUNÇÃO PARA CALCULAR NÚMERO DE DESCENDENTES
int getDownward(tno *root, int result, bool flag){
  if(root != NULL){
    if(root->left != NULL) result = getDownward(root->left, result, flag) + 1;
    if(root->right != NULL) result = getDownward(root->right, result, flag) + 1;
  }
  return result;
}

//--- MENU
int menu(){
    int op;
    printf("[0] - Sair\n[1] - Inserir Elementos\n[2] - Quantidade de nós e ramos\n[3] - PROFUNDIDADE\n[4] - Altura\n[5] - Número de descedentes\nOPÇÃO: ");
    scanf("%d", &op);
    return op;
}

//---- MAIN
int main(){

  tno *root = NULL, *aux = NULL;
  tdata num=0;
  int result = 0;

  tno *busca = NULL;
  bool flag = true;
  int op=0, count1=0, count2=0,valor;

  //--- Iniciando árvore
  init(root); 

  // carregando números do arquivo "numbers.txt"
  root = openFile(root, root);


  do{
    printf("# Números IN-ORDER: ");
    inOrder(root);
    printf("\n");
    op = menu();

    switch(op){
      case 1:
        printf("# INSERÇÃO\n");
        printf("DADO: ");
        scanf("%d", &num);
        root = insert(root,createdNode(num), root);
        break;
      case 2:
        printf("# QUANTIDADE DE NÓS E RAMOS\n");
        getQtdNodesAndTwigs(root, &result);
        printf("NÓS: %d\n", result);
        printf("RAMOS: %d\n", result ? result-1 : 0);
        break;
      case 3:
        printf("# PRONFUNDIDADE DE UM NÓ\nX: ");
        scanf("%d", &num);
        result = 0;
        getDepth(root, num, &result);
        printf("PROFUNDIDADE: %d\n", result);
        break;
      case 4:
        printf("# ALTURA DE UM NÓ\nX: ");
        scanf("%d", &num);
        aux = search(root,num, NULL);

        if(aux){
          result = 0 ;
          result = getHeight(aux, 0);
          printf("ALTURA: %d\n", result);
        }
        break;
      case 5:
        printf("# QUANTIDADE DE DESCENDENTES DE UM NÓ\nX: ");
        scanf("%d", &num);
        aux = search(root,num, NULL);

        if(aux){
          result = 0 ;
          result = getDownward(aux,0, flag);
          printf("QTD DE DESCENDENTES: %d\n", result);
        }
        break;
      default:
        printf("[!] - OPÇÃO INVÁLIDA! TENTE NOVAMENTE!\n");
        scanf("%d", &num);
        break;
    }

  }while(op != 0);

  

  return 0;
}
