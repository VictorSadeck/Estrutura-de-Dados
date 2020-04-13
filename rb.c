#include <stdio.h>
#include <stdlib.h>

enum COR{Vermelho, Preto};

typedef struct No{
	int dado;
	struct No *esq;
	struct No *dir;
	struct No *pai;
	enum COR cor; 
}No;

typedef struct ARN{
	No *raiz;
	No *NIL;
}ARN;

No *novo_no(int dado){
	No* n = malloc(sizeof(No));
 	n->esq = NULL;
	n->dir = NULL;
	n->pai = NULL;
	n->dado = dado;
	n->cor = Vermelho;

	return n;
}

ARN *nova_arvore(){
	ARN *T = malloc(sizeof(ARN));
	No *NIL = malloc(sizeof(No));
	NIL->esq = NULL;
	NIL->dir = NULL;
	NIL->pai = NULL;
	NIL->cor = Preto;
	NIL->dado = 0;
	T->NIL = NIL;
	T->raiz = T->NIL;

	return T;
}

void LL(ARN *t, No *x){
	No *y = x->dir;
	x->dir = y->esq;
	if(y->esq != t->NIL){
		y->esq->pai = x;
	}
	y->pai = x->pai;
	if(x->pai == t->NIL){ // x é raiz
		t->raiz = y;
	}else if(x == x->pai->esq){ // x é o filho esquerdo
		x->pai->esq = y;
	}else{ // x é o filho direito
		x->pai->dir = y;
	}
	y->esq = x;
	x->pai = y;
}

void RR(ARN *t, No *x){
	No * y = x->esq;
	x->esq = y->dir;
	if(y->dir != t->NIL){
		y->dir->pai = x;	
	}
	y->pai = x->pai;
	if(x->pai == t->NIL){ // x é raiz
		t->raiz = y;
	}else if(x == x->pai->dir){ // x é o filho esquerdo
		x->pai->dir = y;
	}else{ // x é o filho direito
		x->pai->esq = y;
	}
	y->dir = x;
	x->pai = y;
}

void RB_Insert_Fixup(ARN *T, No *v){
  // se pai de v é preto não precisamos fazer nada!	
  while(v->pai->cor == Vermelho) {
    if(v->pai == v->pai->pai->esq){
	  // pai na subárvore esquerda
      No *u = v->pai->pai->dir;
	  // pai vermelho e tio vermelho só mudo cores
      if(u->cor == Vermelho){
        v->pai->cor = Preto;
        u->cor = Preto;
        v->pai->pai->cor = Vermelho;
        v = v->pai->pai;
      }
      // pai vermelho e tio preto muda cor e faz rotações
      else{
        if(v == v->pai->dir){ // RL
          v = v->pai;
          LL(T, v);
        }
        v->pai->cor = Preto;
        v->pai->pai->cor = Vermelho;
        RR(T, v->pai->pai);
      }
    }
    else{
      // pai na subárvore direita
      No *u = v->pai->pai->esq;
	  // pai vermelho e tio vermelho só mudo cores
      if(u->cor == Vermelho){
        v->pai->cor = Preto;
        u->cor = Preto;
        v->pai->pai->cor = Vermelho;
        v = v->pai->pai;
      }
      // pai vermelho e tio preto muda cor e faz rotações
      else{
        if(v == v->pai->esq){ // LR
          v = v->pai;
          RR(T, v);
        }
        v->pai->cor = Preto;
        v->pai->pai->cor = Vermelho;
        LL(T, v->pai->pai);
      }
    }
  } // while
  T->raiz->cor = Preto;
}

void RB_Insert(ARN *T, No *v){
	No *y = T->NIL;
	No *x = T->raiz;
	while(x != T->NIL){
		y = x;
		if(v->dado < x->dado){
			x = x->esq;
		}else{
			x = x->dir;		
		}
	}
	v->pai = y;
	if(y == T->NIL){
		T->raiz = v;
	}else if(v->dado < y->dado){
		y->esq = v;
	}else{
		y->dir = v;
	}
	
	v->dir = T->NIL;
	v->esq = T->NIL;
	v->cor = Vermelho;
	RB_Insert_Fixup(T, v);
}

void RB_Transplant(ARN *T, No *u, No *z){
	if(u->pai == T->NIL){
		T->raiz = z;
	}else if(u == u->pai->esq){
		u->pai->esq = z;
	}else{
		u->pai->dir = z;
	}
	z->pai = u->pai;
}

No *sucessor(ARN *T, No *x){
	while(x->esq != T->NIL){
		x = x->esq;
	}
	return x;
}
void RB_Delete_Fixeup(ARN *T, No *x){
	while(x != T->raiz && x->cor == Preto){
		if(x == x->pai->esq){
			No *w = x->pai->dir;
			if(w->cor == Vermelho){ //Caso 3.1: w vermelho
				w->cor = Preto;
				x->pai->cor = Vermelho;
				LL(T, x->pai);
				w = x->pai->dir;
			}
			if(w->esq->cor == Preto && w->dir->cor == Preto){ //Caso 3.2: w preto e ambos filhos tb
				w->cor = Vermelho;
				x = x->pai;
			}else{
				if(w->dir->cor == Preto){ //Caso 3.3 e 3.4: w preto - w->dir vermelho
					w->esq->cor = Preto;
					w->cor = Vermelho;
					RR(T, w);
					w = x->pai->dir;
				}
				w->cor = x->pai->cor;
				x->pai->cor = Preto;
				w->dir->cor = Preto;
				LL(T, x->pai);
				x = T->raiz;
			}
		}else{
			No *w = x->pai->esq;
			if(w->cor == Vermelho){
				w->cor = Preto;
				x->pai->cor = Vermelho;
				RR(T, x->pai);
				w = x->pai->esq;
			}
			if(w->esq->cor == Preto && w->esq->cor == Preto){
				w->cor = Vermelho;
				x = x->pai;
			}else{
				if(w->esq->cor == Preto){
					w->dir->cor = Preto;
					w->cor = Vermelho;
					LL(T, w);
					w = x->pai->dir;
				}
				w->cor = x->pai->cor;
				x->pai->cor = Preto;
				w->esq->cor = Preto;
				RR(T, x->pai);
				x = T->raiz;
			}
		}
	}
	x->cor = Preto;
}

void RB_Delete(ARN *T, No *v){
	No *y = v;
	No *x;
	enum COR y_cor_original = y->cor;
	if(v->esq == T->NIL){
		x = v->dir;
		RB_Transplant(T, v, x);
	}else if(v->dir == T->NIL){
		x = v->esq;
		RB_Transplant(T, v, x);
	}else{
		y = sucessor(T, v->dir);
		y_cor_original = y->cor;
		x = y->dir;
		if(y->pai == v){
			x->pai = y;
		}else{
			RB_Transplant(T, y, x);
			y->dir = v->dir;
			y->dir->pai = y;
		}
		RB_Transplant(T, v, y);
		y->esq = v->esq;
		y->esq->pai = y;
		y->cor = v->cor;
	}
	if(y_cor_original == Preto){
		RB_Delete_Fixeup(T, x);
	}
}

void in_ordem(ARN *T, No *n){
	if(n != T->NIL){
		in_ordem(T, n->esq);
		printf("%d\n", n->dado);
		in_ordem(T, n->dir);
	}
}
int main(){
	 ARN *T = nova_arvore();
	 No *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
	
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

	 RB_Insert(T, a);
	 RB_Insert(T, b);
	 RB_Insert(T, c);
	 RB_Insert(T, d);
	 RB_Insert(T, e);
	 RB_Insert(T, f);
	 RB_Insert(T, g);
	 RB_Insert(T, h);
	 RB_Insert(T, i);
	 RB_Insert(T, j);
	 RB_Insert(T, k);
	 RB_Insert(T, l);
	 RB_Insert(T, m);

	 RB_Delete(T, a);
	 RB_Delete(T, m);

	 in_ordem(T, T->raiz);

	 return 0;
}
