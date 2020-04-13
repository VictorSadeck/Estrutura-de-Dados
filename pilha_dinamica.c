#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int dado;
	struct No * prox;
}No;

typedef struct Pilha{
	struct No *cabeca;
	struct No *topo;
}Pilha;

No * novo_no(int dado){
	No *z;
	z = malloc(sizeof(No));
	z->dado = dado;
	z->prox = NULL;
	return z;
}

Pilha *nova_pilha(){
	Pilha *p = malloc(sizeof(Pilha));
	p->cabeca = NULL;
	p->topo = NULL;
	return p;
}

void traversal(Pilha *p){
	No *temp = p->cabeca;
	while(temp != NULL){
		printf("%d\n", temp->dado);
		temp = temp->prox;
	}
}

int vazia(Pilha *p){
	if(p->topo == NULL){
		return 1;
	}
	return 0;
}

void empilha(Pilha *p, No *n){
	if(vazia(p)){
		p->cabeca = n;
		p->topo = n;
	}else{
		p->topo->prox = n;
		p->topo = n;
	}
}

int desempilha(Pilha *p){
	if(vazia(p)){
		printf("Stack Underflow\n");
		return -1000;
	}else{
		int x = p->topo->dado;
		if(p->topo == p->cabeca){
			free(p->topo);
			p->topo = NULL;
			p->cabeca = NULL;
		}else{
			No *temp = p->cabeca;
			while(temp->prox != p->topo){
				temp = temp->prox;
			}
			temp->prox = NULL;
			free(p->topo);
			p->topo = temp;
		}
		return x;
	}
}

int main(){
	Pilha *p = nova_pilha();
	No *a, *b, *c;
	a = novo_no(10);
	b = novo_no(20);
	c = novo_no(30);
	
	desempilha(p);
	empilha(p, a);
	empilha(p, b);
	empilha(p, c);
	
	traversal(p);
	desempilha(p);
	traversal(p);
	
	return 0;
}
