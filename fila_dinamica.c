#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int dado;
	struct No *prox;
}No;

typedef struct Fila{
	struct No *head;
	struct No *tail;
}Fila;

No *novo_no(int dado){
	No *n = malloc(sizeof(No));
	n->dado = dado;
	n->prox = NULL;
	
	return n;
}

Fila *nova_fila(){
	Fila *f = malloc(sizeof(Fila));
	f->head = NULL;
	f->tail = NULL;
	
	return f;
}

void imprimir(Fila *f){
	No *temp = f->head;
	
	while(temp != NULL){
		printf("%d ", temp->dado);
		temp = temp->prox;
	}
	printf("\n");
}

int vazia(Fila *f){
	if(f->head == NULL){
		return 1;
	}
	return 0;
}

void enfila(Fila *f, No *n){
	if(vazia(f)){
		f->head = n;
		f->tail = n;
	}else{
		f->tail->prox = n;
		f->tail = n;
	}	
}

int desenfila(Fila *f){
	if(vazia(f)){
		printf("Underflow\n");
		return -1000;
	}else{
		int x = f->head->dado;
		No *temp = f->head;
		f->head = f->head->prox;
		free(temp);
		return x;
	}
}

int main(){
	Fila *f = nova_fila();
	
	No *a, *b, *c;
	a = novo_no(10);
	b = novo_no(20);
	c = novo_no(30);
	
	desenfila(f);
	enfila(f, a);
	enfila(f, b);
	enfila(f, c);
	
	imprimir(f);
	desenfila(f);
	imprimir(f);
	
	return 0;
}
