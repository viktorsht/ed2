#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TAM_STR 50
#define TAM_LIST 10
#define MAX_UNI 30



typedef char tdata[TAM_STR];


// LISTA
typedef struct tlist{
    tdata data;
    struct tlist *next; 
} tlist;

typedef struct{
    tlist *s;
    int tam;
} List;
// LISTA
void initList(List *l){
    l->s = NULL;
    l->tam = 0;
}

void insertList(List *l, tdata x){
    
    tlist *s, *new, *prev;
    
	new = (tlist *) malloc(sizeof(tlist));
    s = l->s;
	prev = NULL;

    strcpy(new->data, x);
	new->next = NULL;

	if(s == NULL){
		l->s = new;
        new->next = NULL;
	}else{
		while(s != NULL && strcmp(s->data, x) < 0){
			prev = s;
			s = s->next;
		}
		new->next = s;

		if(prev == NULL) l->s = new;
		else prev->next = new;
	}
    
    l->tam++;
}

void showList(List *l){
    tlist *s = l->s;
    int i=1;

    while(s != NULL){
        printf("%s", s->data);
        printf("%s", i == l->tam ? "\n" : ", ");
        i++;
        s = s->next;
    }

}

// FIM LISTA

// ÁRVORE
typedef struct no{
    tdata data;
    List list;
    struct no *right, *left;
}tno;

tno *createdNodeTree(tdata x){
    tno *new;
    new = (tno *)malloc(sizeof(tno));
    strcpy(new->data, x);
    new->right = new->left = NULL;
    initList(&new->list);
    return new;
}

//---- INSERT
tno *insertTree(tno *root, tno *new, tno *result){
    if(root != NULL){
        result = root;
        if(new->data[0] < root->data[0]) root->left = insertTree(root->left, new, result);
        else root->right = insertTree(root->right, new, result);
                
    }else result = new;

    return result;
} 

// -- INORDER
void showTree(tno *root){
    if(root != NULL){
        showTree(root->left);
        printf("# %s : ", root->data);
        showList(&root->list);
        showTree(root->right);
    }
}
// FIM ÁRVORE

// -- SEARCH
tno *search(tno *root, tdata x, tno *result){   
    
    if(root == NULL) result = NULL;
    else if(strcmp(x,root->data) == 0) result = root;
    else if(strcmp(x,root->data) < 0) result = search(root->left, x, result);
    else result = search(root->right, x, result);

    return result;
}


void openFile2(tno *array[10], double *time_spent){
    FILE *file;
    tno *tnoAux = NULL, *auxSearch = NULL;
    tdata str, aux, ingles, port, arryPort[TAM_STR];
    char *token, *token2, *isComma=NULL, ch = ','; // TOKEN1 = LINHA FULL, TOKEN2 SEEPARAR PORTUGUES
    int flag = 0,i = 1, u = 0, j=0,tam=0;

    file = fopen("ingles.txt", "r");
    
    if(file){
        clock_t begin = clock(); // --- START COUNT TIME
        while(fgets(str, TAM_STR, file) != NULL){
            if(str[0] == '%') u++;
            else{
                token = strtok(str, ":");

                while(token != NULL){
                    if(flag == 1){
                        strcpy(port, strtok(token,"\n"));
                        flag = 0;
                    }else{
                        strcpy(ingles, token);
                        flag = 1;
                    }

                    token = strtok(NULL, ":");
                }

                isComma = strchr(port, ch);
                if(isComma){
                    j=0;

                    token2 = strtok(port, ",");
                    while( token2 != NULL ){
                        tnoAux =  createdNodeTree(token2);
                        auxSearch = search(array[u], token2, array[u]);
                        
                        // if(auxSearch) printf("AUX: %s\n", auxSearch->data);

                        if(auxSearch) insertList(&auxSearch->list , ingles);
                        else{
                            insertList(&tnoAux->list , ingles);
                            array[u] = insertTree(array[u],tnoAux, array[u]); 
                        }              
                        // printf("%s | %s\n", token2, ingles );
                        j++;
                        token2 = strtok(NULL, ",");
                    }

                }else{
                    tnoAux =  createdNodeTree(port); 
                    auxSearch = search(array[u], port, array[u]);
                    
                    if(auxSearch) insertList(&auxSearch->list , ingles);    
                    else{
                        insertList(&tnoAux->list , ingles);
                        array[u] = insertTree(array[u],tnoAux, array[u]);                    
                    }
                    // printf("%s | %s\n", port, ingles );
                } 
                i++; 
            }
        }
        clock_t end = clock(); // --- END COUNT TIME
        *time_spent = (double)(end - begin) / CLOCKS_PER_SEC; // --- CALCULADO TEMPO GASTO
    }else printf("[!] -  Erro ao abrir o arquivo!\n");

    fclose(file);
}

int menu(){
    int op=0;
    printf("[0] - SAIR\n[1] - MOSTRAR UMA UNIDADE\n[2] - PALAVRA EQUIVALENTES\nOPÇÃO: ");
    scanf("%d", &op);
    return op;
}

void initTreeList(tno *array[TAM_LIST]){
    for(int i=0; i<10; i++) array[i] = NULL;
}

int main(){

    tno *root = NULL, *arrayTree[TAM_LIST], *auxSearch = NULL;
    tdata name, xTree, xList;
    List list;
    int i=0, unidade=0, op=0;
    double time_spent_insert = 0.000000, time_spent_search = 0.000000;

    initTreeList(arrayTree);
    openFile2(arrayTree, &time_spent_insert);

    printf("# TEMPO NA INSERÇÃO\n");
    printf("+ Tempo gasto na inserção: %f s | ~ %.3f ms | ~ %.2f µs | ~ %.2fns\n", time_spent_insert, time_spent_insert * 1000, time_spent_insert * 10000,time_spent_insert * 100000);

    do{
        op = menu();

        switch (op){
        case 1:
            printf("# MOSTRAR UNIDADE\n");
            printf("Unidade: ");
            scanf("%d", &unidade);
            if(arrayTree[unidade] != NULL) showTree(arrayTree[unidade]);
            else printf("[!] - UNIDADE VAZIA!\n");
            break;
        case 2:
            printf("# PALAVRAS EQUIVALENTES\n");
            printf("Palavra: ");
            scanf("%s", name);

            for(i=0; i<TAM_LIST;i++){
                clock_t begin = clock(); // --- START COUNT TIME
                auxSearch = search(arrayTree[i], name, arrayTree[i]);
                clock_t end = clock(); // --- END COUNT TIME
                time_spent_search = (double)(end - begin) / CLOCKS_PER_SEC; // --- CALCULADO TEMPO GASTO
                if(auxSearch){
                    printf("Equivalentes: ");
                    showList(&auxSearch->list);
                    printf("# TEMPO NA INSERÇÃO\n");
                    printf("+ Tempo gasto na busca por %s: %f s | ~ %.3f ms | ~ %.2f µs | ~ %.2fns\n", name, time_spent_search, time_spent_search * 1000, time_spent_search * 10000,time_spent_search * 100000);
                }
            }

            break;
        default:
            printf("[!] - OPÇÃO INVÁLIDA!\n");
            break;
        }

    }while(op != 0);

    return 0;
}
