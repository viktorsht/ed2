#include <stdio.h>
#include <malloc.h>

typedef struct _no23 {
   int  lkey,             // chave esquerda
        rkey,             // chave direita
        nkeys;            // número de chaves
   struct _no23 *left,     // ponteiro ao filho esquerdo 
                *center,   // ponteiro ao filho central
                *right;    // ponteiro ao filho direito
} no23;

no23 *find(no23 *raiz, int key) {
    if (raiz==NULL)
        return NULL;      // não encontrou
    if (key == raiz->lkey)
        return raiz;      // é a chave esquerda
    if ((raiz->nkeys == 2) && (key == raiz->rkey))
        return raiz;      // é a chave direita
    if (key < raiz->lkey)
        return find(raiz->left, key);
    else if (raiz->nkeys == 1)
        return find(raiz->center, key);
    else if (key < raiz->rkey)
        return find(raiz->center, key);
    else
        return find(raiz->right, key);
}
// cria um nó com ch1, ch2 e nchaves, assim como os três ponteiros
no23 *criaNo(int ch1, int ch2, int nchaves, no23 *pl, no23 *pc, no23 *pr){
  no23 *no;
  no = (no23 *) malloc (sizeof(no23));
  no->lkey = ch1;
  no->rkey = ch2;
  no->nkeys = nchaves;
  no->left = pl;
  no->center = pc;
  no->right = pr;
  return no;
}

// verifica se o nó em questão é folha, volta 1 se sim, e 0 caso contrario
int isLeaf(no23 *no){
  if (no->left == NULL)
	return 1;
  return 0;
}

// coloca uma nova chave ch, em um nó com apenas uma chave
void adicionaChave(no23 *no, int ch, no23 *subarvore){
  if (ch >= no->lkey){
	no->rkey = ch;
	no->right = subarvore;
  }
  else {
	no->rkey = no->lkey;
	no->lkey = ch;
	no->right = no->center;
	no->center = subarvore;
  }
  no->nkeys = 2;
}
// Quebra um nó em dois, sendo val e subarvore, os novos dados 
no23 *quebraNo(no23 *no, int val, int *rval, no23 *subarvore){
    no23 *paux;

    if (val > no->rkey) {  // val esta mais a direita
       *rval = no->rkey;   // promove a antiga maior
       paux = no->right;
       no->right = NULL;   // elimina o terceiro filho
       no->nkeys = 1;      // atualiza o número de chaves
       return criaNo(val, 0, 1, paux, subarvore, NULL);
    } else if (val >= no->lkey){ // val esta no meio
       *rval = val;        // continua sendo promovido
       paux = no->right;
       no->right = NULL;
       no->nkeys = 1;
       return criaNo(no->rkey, 0, 1, subarvore, paux, NULL);
    } else {              // val esta a mais a esquerda
       *rval = no->lkey;
       // primeiro cria o nó a direita
       paux = criaNo(no->rkey, 0, 1, no->center, no->right, NULL);
       no->lkey = val;   // em seguida arruma o nó a esquerda
       no->nkeys = 1;
       no->right = NULL;
       no->center = subarvore;
       return paux;
    }
}
void imprimeNo(no23 *r){
  if (r->nkeys == 1)
	printf("<%d , %l, %l>\n", r->lkey, r->left, r->center);
  else
	printf("<%d , %d, %l, %l, %l>\n", r->lkey, r->rkey, r->left, r->center,
		   r->right);
}
// insere val em no (se necessario retorna o novo no e um valor
// rval)
no23 *insere( no23 **no, int val, int *rval){
    no23 *paux, *paux2;
    int   vaux, promov;

    if (*no == NULL) {    // arvore vazia
       *no = criaNo(val, 0, 1, NULL, NULL, NULL); 
             // cria no folha com um valor 
       return NULL;       // nada a fazer depois
    }
    if (isLeaf(*no)){     // chegou a folha
       if ((*no)->nkeys == 1){ // caso fácil
          adicionaChave(*no, val, NULL);
          return NULL;
       } else {
          paux = quebraNo(*no, val, &vaux, NULL);
          *rval = vaux;
          return paux;
       }
    } else {             // continua a procura
       if (val < (*no)->lkey)
          paux = insere( &((*no)->left), val, &vaux);
       else if (((*no)->nkeys == 1) || (val < (*no)->rkey))
          paux = insere( &((*no)->center), val, &vaux);
       else   
          paux = insere( &((*no)->right), val, &vaux);
       if (paux == NULL) // nao promoveu
          return NULL;
       else
          if ((*no)->nkeys == 1){
             adicionaChave(*no, vaux, paux);
             return NULL;
          } else {
             paux2 = quebraNo(*no, vaux, &promov, paux);
             *rval = promov;
             return paux2;
          }
     }
}

void chamaInsere(no23 **raiz, int ch){
  no23 *paux;
  int promovido;

  paux = insere( raiz, ch, &promovido);
  if (paux != NULL) {
	paux = criaNo(promovido, 0, 1, *raiz, paux, NULL);
	*raiz = paux;
  }
}
void imprime(no23 *raiz, int nivel) {
  /* Esta rotina e adequada para imprimir arvores com chaves de */
  /* comprimento maximo igual a 6. */
  int i;
  if (raiz == NULL) return;
  imprime(raiz->left, nivel + 1);
  for(i = 0; i < nivel; i++) printf("  ");
  if (raiz->nkeys == 1){
	printf("[%4d]\n", raiz->lkey);
	imprime(raiz->center, nivel + 1);
  }
  else {
	printf("{%4d,%4d} \n", raiz->lkey, raiz->rkey);
	imprime(raiz->center, nivel + 1);
	for(i = 0; i < nivel; i++) printf("  ");
	printf("{%4d,%4d} \n", raiz->lkey, raiz->rkey);
	imprime(raiz->right, nivel + 1);
  }
}

int main() {
  int num, oper;
  no23 *raiz = NULL;

  oper = 0;
  while (oper != 5) {
    printf("Entre com  um novo numero: ");
    scanf("%d", &num);

	chamaInsere(&raiz, num);
	imprime(raiz, 0);
  }
  return 0;
}
