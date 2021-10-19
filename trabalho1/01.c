#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NUM 1000
#define NUM_SEARCH 500
#define MAX_LOOP 30

typedef int tdata;
typedef struct no{
    tdata data;
    struct no *right, *left;
}tno;

typedef struct {
    int bigDepth, smallerDepth, diffDepth;
    double time_spent_insert, time_spent_search;
    bool searchNum ;
    
}infoTree;


tno *createdNode(tdata x);
tno *insert(tno *root, tno *new, tno *result);
bool isLeaf(tno *root);
void inOrder(tno *root);
bool search(tno *root, tdata x, bool result);


// --- FUNÕES ESPECIDIFCAS DO PROBLEMA 
// --- ADICIONANDO NÚMEROS RANDOMICOS
tno *numberRandom(tno *root, double *time_spent, int seed){
    tdata x = 0;

    clock_t begin = clock(); // --- START COUNT TIME

    srand(time(NULL) * seed);

    for(int i=0; i<MAX_NUM; i++){
        x = rand() % MAX_NUM;
        root = insert(root,createdNode(x), root);
        // printf("%d ", x);
    }

    clock_t end = clock(); // --- END COUNT TIME
    *time_spent = (double)(end - begin) / CLOCKS_PER_SEC; // --- CALCULADO TEMPO GASTO

    return root;
}

// --- LIMPAR ÁRVORE
tno *toCleanTree(tno *root){
	if(root){
		toCleanTree(root->left);
		toCleanTree(root->right);
		free(root);
	}

    return NULL;
}

// INICIAR STRUCT DE INFORMAÇÕES
void initInfo(infoTree *info){
    info->smallerDepth = 0;
    info->bigDepth = 0;
    info->diffDepth = 0;
    info->time_spent_insert = 0.000000;
    info->time_spent_search = 0.000000;
    info->searchNum = false;
}

//  --- IMPRIMIR INFORMÇÃOES DE UMA ÁRVORE
void showInfoTree(infoTree info){
    printf("### INFO DA ÁRVORE ###\n");
    printf("+ Tempo gasto na inserção: %f s | ~ %.3f ms | ~ %.2f µs\n", info.time_spent_insert, info.time_spent_insert * 1000, info.time_spent_insert * 10000);
    printf("+ Tempo gasto na busca do número %d: %f | ~ %.2f µs | ~ %.2fns\n", NUM_SEARCH, info.time_spent_search, info.time_spent_search * 10000, info.time_spent_search * 100000);
    printf("? Encontrou %d: %s\n", NUM_SEARCH, info.searchNum ? "Sim" : "Não");
    printf("< Menor profundidade: %d\n", info.smallerDepth);
    printf("> Maior profundidade: %d\n", info.bigDepth);
    printf("! Diferença entre menor e maior: %d\n", info.diffDepth);
}

// --- MENOR ENTRE DOIS NÚMEROS
int min(int num1, int num2){
    return num1 > num2 ? num2 : num1;
}

// --- DIFERENÇA ENTRE DOIS NÚMEROS
int diff(int n1, int n2){
    return n1-n2;
}

// --- PROFUNDIDADE DA MAIOR FOLHA
int getBigDepth(tno *root, int result){
  if(root != NULL){
    int dl = getBigDepth(root->left, result);
    int dr = getBigDepth(root->right, result);

    if (dl > dr) result = dl+1;
    else result = dr+1;

  }else result = 0;

  return result;
}

// // --- PROFUNDIDADE DA MENOR FOLHA 2
// int getSmallerDepth2(tno *root, int result){
//   if(root != NULL){
//     int dl = getSmallerDepth2(root->left, result);
//     int dr = getSmallerDepth2(root->right, result);

//     if (dl < dr) result = dl+1;
//     else result = dr+1;

//   }else result = 0;

//   return result;
// }

// --- PROFUNDIDADE DA MENOR FOLHA
int getSmallerDepth(tno *root, int result){
    if(root != NULL){
        int dl, dr;
        if(isLeaf(root)) result = 1;
        dl = getBigDepth(root->left, result);
        dr = getBigDepth(root->right, result);

        result = min(dl,dr) + 1;
    }
    return result;
}

// --- CALCULADO TEMPO DE BUSCA DE UM NUM NA ÁRVORE
bool timeSearch(tno *root, int x, double *time_spent){
  bool result = false;
  clock_t begin = clock();
  result = search(root,x,result);
  clock_t end = clock();
  *time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  return result;
}

// QUANTIDADE REPETIU

void getRepeatedTime(int v[MAX_LOOP], int result[MAX_LOOP]){
    int i, j, k = 0, count;
    int vetor[30];

    for(i = 0; i < 30; i++){
        vetor[i] =  v[i];
    }

    for(i = 0; i < 30; i++){
        count = 0;
        for(j = k++; j < 30; j++){
            if(v[i] == vetor[j]){
                count++;
                vetor[j] = -1;
            }
        }
        result[i] = count;
    }
}

//---- MAIN
int main(){
    tno *root = NULL;
    tdata num=0,x=0;
    infoTree info;
    double time_spent_insert = 0;
    int i=0, k=0,  diffDepth[MAX_LOOP], diffDepthResult[MAX_LOOP];


    for(i=0; i<MAX_LOOP; i++){
        initInfo(&info);

        root = numberRandom(root,&info.time_spent_insert, i); // --- CRIANDO ÁRVORE COM NÚMEROS RANDOMICOS
        
        info.smallerDepth = getSmallerDepth(root,0) - 1;
        info.bigDepth = getBigDepth(root,0) - 1;
        info.diffDepth = diff(info.bigDepth, info.smallerDepth);
        diffDepth[i] = info.diffDepth ;
        info.searchNum = timeSearch(root,NUM_SEARCH, &info.time_spent_search);

        showInfoTree(info); // --- IMPRIMINDO DADOS DA ÁRVORE

        root = toCleanTree(root); // --- LIMPANDO ÁRVORE
    }

    getRepeatedTime(diffDepth,diffDepthResult);

    for(i=0; i<MAX_LOOP;i++) if(diffDepthResult[i] > 0) printf("# %d repetiu %d\n", diffDepth[i], diffDepthResult[i]);

    return 0;
}

// FUNCTIONS

tno *createdNode(tdata x){
    tno *new;
    new = (tno *)malloc(sizeof(tno));
    new->data = x;
    new->right = new->left = NULL;
    return new;
}
//---- INSERT
tno *insert(tno *root, tno *new, tno *result){
    if(root != NULL){
        result = root;
        if(new->data < root->data) root->left = insert(root->left, new, result);
        else root->right = insert(root->right, new, result);
                
    }else result = new;

    return result;
} 

// --- VERIFICNADO SE UM NÓ É FOLHA
bool isLeaf(tno *root){
    return root->left == NULL && root->right == NULL;
}

// -- INORDER
void inOrder(tno *root){
    if(root != NULL){
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// -- SEARCH
bool search(tno *root, tdata x, bool result){
    if(root == NULL) result = false;
    else if(root->data == x) result = true;
    else if(x < root->data) result = search(root->left, x, result);
    else result = search(root->right, x, result);  

    return result;
}





