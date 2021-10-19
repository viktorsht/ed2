/*
*   Atividade feita em dupla
*
*   Dupla:
*
*   Vitor José Ferreira dos Santos de Santana
*   Humberto José da Silva Júnior
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAM_STR 100

// --- STRUCT PARTICIPANTES
typedef struct {
    char artist[TAM_STR], desc[TAM_STR], personage[TAM_STR];
} Parti;

// --- ÁRVORE DE PARTICIPANTES
typedef struct arvPart{
    Parti tdata;
    struct arvPart *left, *right;
} arvPart;

// -- STRUCT TEMPORADA
typedef struct Seasons{
    int num, qtdEpisodes, year;
    struct arvPar *root;
} Seasons;

// --- LISTA DE TEMPORADAS
typedef struct lSeasons{
    struct Seasons tdata;
    struct lSeasons *next;
} lSeasons;
// --- LISTA
typedef struct{
    lSeasons *s;
    int tam;
} ListSeasons;

// --- STRUCT SERIE
typedef struct Series{
    int id, nSeasons;
    char title[TAM_STR];
    struct lSeasons *start;
} Series;

// --- ARVORE DE SERIES
typedef struct arvSeries{
    struct Series tdata;
    struct arvSeries *left, *right;
} arvSeries;

// -- CRIANDO NÓ DA ARVORE PARTICIPANTES
arvPart *createdNodePart(Parti x){
    arvPart *new;
    new = (arvPart *)malloc(sizeof(arvPart));
    new->tdata = x;
    new->left = new->right = NULL;
    return new;
}
// -- CRIANDO NÓ DA ARVORE SERIES
arvSeries *createdNodeSeries(Series x){
    arvSeries *new;
    new = (arvSeries *)malloc(sizeof(arvSeries));
    new->tdata = x;
    new->left = new->right = NULL;
    return new;
}

// --- INSERINDO NA ÁRVORE PARTICIPANTES
arvPart *insertPart(arvPart *root, arvPart *new){
    if(root == NULL) return new;
    if(new->tdata.artist[0] < root->tdata.artist[0]) root->left = insertPart(root->left, new);
    else root->right = insertPart(root->right, new);
    return root;
}
// --- INSERINDO NA ÁRVORE SERIES
arvSeries *insertSeries(arvSeries *root, arvSeries *new){
    if(root == NULL) return new;
    else if(new->tdata.id < root->tdata.id) root->left = insertSeries(root->left, new);
    else root->right = insertSeries(root->right, new);
    return root;
}

// --- INSERINDO TEMPORADA
void insertSeasons(ListSeasons *l, Seasons x){
    lSeasons *s, *new, *prev;

	new = (lSeasons *) malloc(sizeof(lSeasons));
    s = l->s;
	prev = NULL;

    new->tdata = x;
	new->next = NULL;

	if(s == NULL){
		l->s = new;
        new->next = NULL;
	}else{
		while(s != NULL && s->tdata.num < x.num){
			prev = s;
			s = s->next;
		}
		new->next = s;

		if(prev == NULL) l->s = new;
		else prev->next = new;
	}
  l->tam++;
}

// -- INORDER ARTISTAS
void inOrderArtist(arvPart *root){
    if(root != NULL){
        inOrderArtist(root->left);
        printf("%s\n", root->tdata.artist);
        inOrderArtist(root->right);
    }
}
// -- INORDER PERSONAGENS
void inOrderPersonage(arvPart *root){
    if(root != NULL){
        inOrderPersonage(root->left);
        printf("%s\n", root->tdata.personage);
        inOrderPersonage(root->right);
    }
}

// -- INORDER SERIRES
void inOrderSeries(arvSeries *root){
    if(root != NULL){
        inOrderSeries(root->left);
        printf("%d | %s | %d\n", root->tdata.id, root->tdata.title, root->tdata.nSeasons);
        inOrderSeries(root->right);
    }
}

void showSeasons(ListSeasons *l, int x){
    lSeasons *s = l->s;
    while(s != NULL){
        if(s->tdata.num == x)  printf("%d | %d | %d\n", s->tdata.num, s->tdata.qtdEpisodes, s->tdata.year);
        s = s->next;
    }
}

void initArvParti(arvPart *root){
    root = root->right = root->left = NULL;
}

void initList(ListSeasons *l){
    l->s = NULL;
    l->tam = 0;
}

int menu1(){
    int op = 0;
    printf("[0] - Sair\n[1] - Inserir series\n[2] - Inserir temporada\n[3] - Inserir personagem\n[4] - Executar\nOPÇÃO: ");
    scanf("%d",&op);
    return op;
}

int menu2(){
    int op = 0;
    printf("[0] - Sair\n[1] - Imprimir series\n[2] - Todas as temporadas\n[3]- Imprimir personagens\n[4] - Nomes dos artistas\n[5] - Adicionar\nOPÇÃO: ");
    scanf("%d",&op);
    return op;
}


// --- MAIN
int main(){

    arvPart *rootParti = NULL;
    arvSeries *rootSeries = NULL;
    ListSeasons listSeasons;

    Parti xp;
    Series xs;
    Seasons xss;
    int op = 0;

    initList(&listSeasons);

    if(1){
        strcpy(xp.artist, "Humberto");
        strcpy(xp.desc, "Eu sou eu 1");
        strcpy(xp.personage, "Fulando de tal1");
        rootParti = insertPart(rootParti, createdNodePart(xp));
        strcpy(xp.artist, "Júnior");
        strcpy(xp.desc, "Eu sou eu 2");
        strcpy(xp.personage, "Fulando de tal 2");
        rootParti = insertPart(rootParti, createdNodePart(xp));
        strcpy(xp.artist, "José");
        strcpy(xp.desc, "Eu sou eu 3");
        strcpy(xp.personage, "Fulando de tal 3");
        rootParti = insertPart(rootParti, createdNodePart(xp));

        xs.id = 3;
        xs.nSeasons = 4;
        strcpy(xs.title, "La casa de papel");
        xs.start = NULL;
        rootSeries = insertSeries(rootSeries, createdNodeSeries(xs));
        xs.id = 2;
        xs.nSeasons = 2;
        strcpy(xs.title, "Narcos");
        xs.start = NULL;
        rootSeries = insertSeries(rootSeries, createdNodeSeries(xs));
        xs.id = 1;
        xs.nSeasons = 3;
        strcpy(xs.title, "Riverdale");
        xs.start = NULL;
        rootSeries = insertSeries(rootSeries, createdNodeSeries(xs));

        xss.num = 1;
        xss.qtdEpisodes = 6;
        xss.year = 2020;
        xss.root == NULL;
        insertSeasons(&listSeasons, xss);

        xss.num = 3;
        xss.qtdEpisodes = 4;
        xss.year = 2018;
        xss.root == NULL;
        insertSeasons(&listSeasons, xss);

    }

    printf("##########\n");

    do{
        op = menu1();

        switch(op){
            case 1:
                printf("# SERIE\n");
                printf("ID: ");
                scanf("%d", &xs.id);
                printf("TITULO: ");
                scanf(" %[^\n]", xs.title);
                printf("QUANTIDADE DE TEMPORADAS: ");
                scanf("%d", &xs.nSeasons);
                xs.start = NULL;
                rootSeries = insertSeries(rootSeries, createdNodeSeries(xs));
                break;
            case 2:
                printf("# TEMPORADA\n"); //  int num, qtdEpisodes, year;    struct arvPar *root;
                printf("NUM DA TEMPORADA: ");
                scanf("%d", &xss.num);
                printf("QUANTIDADE DE EPISODIOS: ");
                scanf("%d", &xss.qtdEpisodes);
                printf("ANO: ");
                scanf("%d", &xss.year);
                xs.start =  NULL;
                insertSeasons(&listSeasons, xss);
                break;
            case 3:
                printf("# PERSONAGENS\n");
                printf("Nome artista: ");
                scanf(" %[^\n]", xp.artist);
                printf("Nome personagem: ");
                scanf(" %[^\n]", xp.personage);
                printf("Descrição: ");
                scanf(" %[^\n]", xp.desc);
                break;
            case 4:
                do{
                    op = menu2();
                    switch (op){
                        case 1:
                            printf("# SERIES\n");
                            inOrderSeries(rootSeries);
                            break;
                        case 2:
                            printf("# TEMPORADAS \n");
                            printf("COD da serie: ");
                            scanf("%d", &xs.id);
                            showSeasons(&listSeasons, xs.id);
                            break;
                        case 3:
                            printf("# PERSONAGENS\n");
                            inOrderPersonage(rootParti);
                            break;
                        case 4:
                            printf("# ARTISTAS\n");
                            inOrderArtist(rootParti);
                            break;
                        default:
                            break;
                    }

                }while(op != 0);
                break;
            default:
                break;
        }
    }while(op != 0);

    return 0;
}
