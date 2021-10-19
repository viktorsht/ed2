/*
Vitor José Ferreira dos Santos de Santana
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ANOATUAL 2021
#define TAM 30

typedef struct{
	int id;
	char nome[30];
	int nascimento;
	float altura;
}Pessoa;

typedef struct No{
	Pessoa pessoa;
	struct No *proximo;
}No;

typedef struct{
	No *inicio;
	int tam;
}Lista;

void inserir(Lista *lista, Pessoa pessoa){
	No *atual, *novo, *anterior;

	novo = (No *) malloc(sizeof(No));

	atual = lista->inicio;
	anterior = NULL;

	novo->pessoa = pessoa;
	novo->proximo = NULL;

	if(atual == NULL){
		novo->proximo = NULL;
		lista->inicio = novo;
	}
	else{
		while(atual != NULL && atual->pessoa.id < pessoa.id){
			anterior = atual;
			atual = atual->proximo;
		}

		novo->proximo = atual;

		if(anterior == NULL){
			lista->inicio = novo;
		} else{
			anterior->proximo = novo;
		}
	}
}

void imprimir(Lista *lista){
	No *inicio = lista->inicio;
	while(inicio != NULL){
		printf("%d \n", inicio->pessoa.id);
		printf("%s \n", inicio->pessoa.nome);
		printf("%d \n", inicio->pessoa.nascimento);
		printf("%f \n", inicio->pessoa.altura);
		printf("\n");
		inicio = inicio->proximo;
	}
}

void maioridade(Lista *lista, No *inicio,int i, int idad,char str[][TAM]){
	if(inicio != NULL){
		if(inicio->pessoa.nascimento == idad){
			strcpy(str[i],inicio->pessoa.nome);
			i++;
		}
		maioridade(lista,inicio->proximo,i,idad,str);
	}
}

void pessoamaisvelha(Lista *lista,int *maior){
	No *inicio = lista->inicio;
	int count = 0;
	while(inicio != NULL){
		if(inicio->pessoa.nascimento < *maior){
			*maior = inicio->pessoa.nascimento;
		}
		inicio = inicio->proximo;
	}
}

int maioridadeQuantidade(Lista *lista,int maior){
	No *inicio = lista->inicio;
	int count = 0;
	while(inicio != NULL){
		if(inicio->pessoa.nascimento == maior){
			count++;
		}
		inicio = inicio->proximo;
	}
	return count;
}

void maiorEMenorAltura(Lista *lista, int *maior,int *menor,No *inicio){
	if(inicio != NULL){
		if(inicio->pessoa.altura > *maior){
			*maior = inicio->pessoa.altura;
		}
		if(inicio->pessoa.altura < *menor){
			*menor = inicio->pessoa.altura;
		}
		maiorEMenorAltura(lista,maior,menor,inicio->proximo);
	}
}

float calculoAlturaMedia(int maior, int menor){
	return (float)(menor + maior)/2;
}

int pessoaAlturaMediana(Lista *lista, No *inicio,int i,int maior,int menor){
	if(inicio != NULL){
		if((inicio->pessoa.altura) == calculoAlturaMedia(maior,menor)){
			i++;
		}
		pessoaAlturaMediana(lista,inicio->proximo,i,maior,menor);
	}
	return i;
}

void pessoas40(Lista *lista, No *inicio,int *i,int maior,int menor){
	if(inicio != NULL){
		float al = calculoAlturaMedia(maior,menor);
		if((inicio->pessoa.altura) > al && (inicio->pessoa.nascimento > (ANOATUAL - 40))){
			*i += 1;
		}
		pessoas40(lista,inicio->proximo,i,maior,menor);
	}
}

void cadastro(Pessoa *pessoa){

	printf("Id: ");
	scanf("%d",&pessoa->id);
	printf("Nome: ");
	scanf("%s",pessoa->nome);
	printf("Nascimento: ");
	scanf("%d",&pessoa->nascimento);
	printf("Altura: ");
	scanf("%f",&pessoa->altura);

}
void menu(){

	printf("[ 0 ] - Sair\n");
	printf("[ 1 ] - Cadastro\n");
	printf("[ 2 ] - Imprimir\n");
	printf("[ 3 ] - Pessoa mais Velha\n");
	printf("[ 4 ] - Maior e Menor altura\n");
	printf("[ 5 ] - Altura Mediana\n");
	printf("[ 6 ] - Menos de 40 e maior que mediana\n");

}
int main(int argc, char *argv[]){

	Lista lista;
	lista.inicio = NULL;
	lista.tam = 0;

	Pessoa p;
	int op;
	int maior = 0, menor = 300;

	menu();
	do{
		scanf("%d",&op);
		if(op == 0) exit(1);

		else if(op == 1){
			cadastro(&p);
		}

		else if(op == 2){
			imprimir(&lista);
		}
		else if(op == 3){
			int maiorI = 3000;
			pessoamaisvelha(&lista,&maiorI);
			int m = maioridadeQuantidade(&lista,maiorI);
			char maisVelhasVetor[m][TAM];
			maioridade(&lista,lista.inicio,0,maiorI,maisVelhasVetor);
			for(int j = 0; j < m; j++){
				printf("%s\n",maisVelhasVetor[j]);
			}
		}
		else if(op == 4){
			maiorEMenorAltura(&lista,&maior,&menor,lista.inicio);
			printf("Maior altura = %d cm\n",maior);
			printf("Menor altura = %d cm\n",menor);
		}
		else if(op == 5){
			printf("Altura mediana = %.2f\n",calculoAlturaMedia(maior,menor));
			printf("Pessoas com altura igual a mediana = %d\n",pessoaAlturaMediana(&lista,lista.inicio,0,maior,menor));
		}
		else if(op == 6){
			int p40;
			pessoas40(&lista,lista.inicio,&p40,maior,menor);
			printf("Pessoas com menos de 40 anos e maiores que mediana = %d\n",p40);
		}
		else{
			printf("Entrada inválida\n");
		}

	}while(op != 0);

	return 0;
}
