#include <stdio.h>
#include <stdlib.h>

typedef struct noAVL{
	int dado;
	int altura; // altura do nó
	struct noAVL *esq;
	struct noAVL *dir;
	struct noAVL *pai;
}noAVL;

typedef struct arvoreAVL{
	noAVL *raiz;
}arvoreAVL;

noAVL *novo_no_AVL(int dado){
	noAVL *n = malloc(sizeof(noAVL));
	n->dado = dado;
	n->esq = NULL;
	n->dir = NULL;
	n->pai = NULL;
	n->altura = 0;
	
	return n;
}

arvoreAVL *nova_arvore_AVL(){
	arvoreAVL *t = malloc(sizeof(arvoreAVL));
	t->raiz = NULL;
	
	return t;
}

int max(int a,int b){
	if(a > b){
		return a;
	}
	return b;
}

int altura(noAVL *n){
	if(n == NULL){
		return -1;
	}
	return n->altura;
}

noAVL *minimo(arvoreAVL *t, noAVL *x){
	while(x->esq != NULL){
		x = x->esq;
	}
	return x;
}

void LL(arvoreAVL *t, noAVL *x){
	noAVL *y = x->dir;
	x->dir = y->esq;
	if(y->esq != NULL){
		y->esq->pai = x;
	}
	y->pai = x->pai;
	if(x->pai == NULL){ // x é raiz
		t->raiz = y;
	}else if(x == x->pai->esq){ // x é filho esquerdo
		x->pai->esq = y;
	}else{ // x é filho direito
		x->pai->dir = y;
	}
	y->esq = x;
	x->pai = y;
	
	x->altura = 1 + max(altura(x->esq), altura(x->dir));
	y->altura = 1 + max(altura(y->esq), altura(y->dir));
}

void RR(arvoreAVL *t, noAVL *x){
	noAVL *y = x->esq;
	x->esq = y->dir;
	if(y->dir != NULL){
		y->dir->pai = x;
	}
	y->pai = x->pai;
	if(x->pai == NULL){ // x é raiz
		t->raiz = y;
	}else if(x == x->pai->dir){ // x é filho esquerdo
		x->pai->dir = y;
	}else{ // x é filho direito
		x->pai->esq = y;
	}
	y->dir = x;
	x->pai = y;
	
	x->altura = 1 + max(altura(x->esq), altura(x->dir));
	y->altura = 1 + max(altura(y->esq), altura(y->dir));
}

int balanceamento(noAVL *n){
	if(n == NULL){
		return 0;
	}
	return (altura(n->esq) - altura(n->dir));
}

void inserir(arvoreAVL *t, noAVL *n){
	noAVL *y = NULL;
	noAVL *temp = t->raiz;
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
	
	noAVL *z = n;
	
	while(y != NULL){
		y->altura = 1 + max(altura(y->esq), altura(y->dir));
		noAVL *x = y->pai;
		
		if(balanceamento(x) <= -2  || balanceamento(x) >= 2){
			if(y == x->esq){
				if(z == x->esq->esq){
					RR(t,x);
				}else if(z == x->esq->dir){
					LL(t, y);
					RR(t, x);
				}
			}else if(y == x->dir){
				if(z == x->dir->dir){
					LL(t,x);
				}else if(z == x->dir->esq){
					RR(t, y);
					LL(t, x);
				}
			}
			break;
		}
		y = y->pai;
		z = z->pai;
	}
}

void transplant(arvoreAVL *t, noAVL *u, noAVL *v){
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

void avl_delete_fixup(arvoreAVL *t, noAVL *n){
	noAVL *p = n;
	
	while(p != NULL){
		p->altura = 1 + max(altura(p->esq), altura(p->dir));
		
		if(balanceamento(p) <= -2 || balanceamento(p) >= 2){ // avô desbalanceado
			noAVL *x, *y, *z;
			x = p;
			
			if(x->esq->altura > x->dir->altura){
				y = x->esq;
			}else{
				y = x->dir;
			}
			
			if(y->esq->altura > y->dir->altura){
				z = y->esq;
			}else if(y->esq->altura < y->dir->altura){
				z = y->dir;
			}else{
				if(y == x->esq){
					z = y->esq;
				}else{
					z = y->dir;
				}
			}
			
			if(y == x->esq){
				if(z == x->esq->esq){
					RR(t, x);
				}else if(z == x->esq->dir){
					LL(t, y);
					RR(t, x);
				}
			}else if(y == x->dir){
				if(z == x->dir->dir){
					LL(t, x);
				}else if(z == x->dir->esq){
					RR(t, y);
					LL(t, x);
				}
			}
		}
		p = p->pai;
	}
}

void deletar(arvoreAVL *t, noAVL *z){
	if(z->esq == NULL){
		transplant(t, z, z->dir);
		if(z->dir != NULL){
			avl_delete_fixup(t, z->dir);
		}
		free(z);
	}else if(z->dir == NULL){
		transplant(t, z, z->esq);
		if(z->esq != NULL){
			avl_delete_fixup(t, z->esq);
		}
		free(z);
	}else{
		noAVL *y = minimo(t, z->dir); // menor elemento na subárvore direita
		if(y->pai != z){
			transplant(t, y, y->dir);
			y->dir = z->dir;
			y->dir->pai = y;
		}
		transplant(t, z, y);
		y->esq = z->esq;
		y->esq->pai = y;
		if(y != NULL){
			avl_delete_fixup(t, y);
		}
		free(z);
	}
}

void in_ordem(arvoreAVL *t, noAVL *n){
	if(n != NULL){
		in_ordem(t, n->esq);
		printf("%d\n", n->dado);
		in_ordem(t, n->dir);
	}
}

int main(int argc, char *argv[]){
	arvoreAVL *t = nova_arvore_AVL();
	
	noAVL *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
	
	a = novo_no_AVL(10);
	b = novo_no_AVL(20);
	c = novo_no_AVL(30);
	d = novo_no_AVL(100);
	e = novo_no_AVL(90);
	f = novo_no_AVL(40);
	g = novo_no_AVL(50);
	h = novo_no_AVL(60);
	i = novo_no_AVL(70);
	j = novo_no_AVL(80);
	k = novo_no_AVL(150);
	l = novo_no_AVL(110);
	m = novo_no_AVL(120);
	
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
