#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int dado;
	struct no *esq;
	struct no *dir;
	struct no *pai;
}no;

typedef struct arvore_binaria_busca{
	no *raiz;
}arvore_binaria_busca;

no *novo_no(int dado){
	no *n = malloc(sizeof(no));
	n->dado = dado;
	n->esq = NULL;
	n->dir = NULL;
	n->pai = NULL;
	
	return n;
}

arvore_binaria_busca *nova_arvore_binaria_busca(){
	arvore_binaria_busca *t = malloc(sizeof(arvore_binaria_busca));
	t->raiz = NULL;
	
	return t;
}

no *minimo(arvore_binaria_busca *t, no *x){
	while(x->esq != NULL){
		x = x->esq;
	}
	return x;
}

void inserir(arvore_binaria_busca *t, no *n){
	no *y = NULL;
	no *temp = t->raiz;
	while(temp != NULL){
		y = temp;
		if(n->dado < temp->dado){
			temp = temp->esq;
		}else{
			temp = temp->dir;
		}
	}
	n->pai = y;
	
	if(y == NULL){
		t->raiz = n;
	}else if(n->dado < y->dado){
		y->esq = n;
	}else{
		y->dir = n;
	}
}

void transplant(arvore_binaria_busca *t, no *u, no *v){
	if(u->pai == NULL){ // u é raiz
		t->raiz = v;
	}else if(u == u->pai->esq){ // u é filho esquerdo
		u->pai->esq = v;
	}else{ // u é filho direito
		u->pai->dir = v;
	}
	
	if(v != NULL){
		v->pai = u->pai;
	}
}

void deletar(arvore_binaria_busca *t, no *z){
	if(z->esq == NULL){
		transplant(t, z, z->dir);
		free(z);
	}else if(z->dir == NULL){
		transplant(t, z, z->esq);
		free(z);
	}else{
		no *y = minimo(t, z->dir); // menor elemento na subárvore direita
		if(y->pai != z){
			transplant(t, y, y->dir);
			y->dir = z->dir;
			y->dir->pai = y;
		}
		transplant(t, z, y);
		y->esq = z->esq;
		y->esq->pai = y;
		free(z);
	}
}

void in_ordem(arvore_binaria_busca *t, no *n){
	if(n != NULL){
		in_ordem(t, n->esq);
		printf("%d\n", n->dado);
		in_ordem(t, n->dir);
	}
}

int main(int argc, char *argv[]){
	arvore_binaria_busca *t = nova_arvore_binaria_busca();
	
	no *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
	
	a = novo_no(10);
	b = novo_no(20);
	c = novo_no(30);
	d = novo_no(100);
	e = novo_no(90);
	f = novo_no(40);
	g = novo_no(50);
	h = novo_no(60);
	i = novo_no(70);
	j = novo_no(80);
	k = novo_no(150);
	l = novo_no(110);
	m = novo_no(120);
	
	inserir(t, a);
	inserir(t, b);
	inserir(t, c);
	inserir(t, d);
	inserir(t, e);
	inserir(t, f);
	inserir(t, g);
	inserir(t, h);
	inserir(t, i);
	inserir(t, j);
	inserir(t, k);
	inserir(t, l);
	inserir(t, m);
	
	deletar(t, a);
	deletar(t, m);
	
	in_ordem(t, t->raiz);
	
	return 0;
}
