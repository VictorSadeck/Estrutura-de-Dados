#include <stdio.h>
#include <stdlib.h>

typedef struct Fila {
  int head;
  int tail;
  int tamanho;
  int elementos[];
}Fila;

Fila *nova_fila(int tamanho){
	Fila *f = malloc(sizeof(Fila) + tamanho * sizeof(int));
	
	f->head = 1;
	f->tail = 1;
	f->tamanho = tamanho;
	
	return f;
}

int vazia(Fila *f){
	if(f->tail == f->head){
		return 1;
	}
	return 0;
}

int cheia(Fila *f){
	if(f->head == f->tail+1){
		return 1;
	}
	return 0;
}

void enfila(Fila *f, int elemento){
	if(cheia(f)){
		printf("Overflow\n");
	}else{
		f->elementos[f->tail] = elemento;
		if(f->tail == f->tamanho){
			f->tail = 1;
		}else{
			f->tail = f->tail+1;
		}
	}
}

int desenfila(Fila *f){
	if(vazia(f)){
		printf("Underflow\n");
		return -1000;
	}else{
		int elemento = f->elementos[f->head];
		if(f->head == f->tamanho){
			f->head = 1;
		}else{
			f->head = f->head+1;
		}
		return elemento;
	}
}

void imprimir(Fila *f){
	for(int i = f->head;i < f->tail;i++){
		printf("%d ", f->elementos[i]);
		if(i == f->tamanho){
			i = 0;
		}
	}
}

int main() {
  Fila *f = nova_fila(10);
  enfila(f, 10);
  enfila(f, 20);
  enfila(f, 30);
  enfila(f, 40);
  enfila(f, 50);
  imprimir(f);

  printf("\n");

  desenfila(f);
  desenfila(f);
  imprimir(f);

  printf("\n");

  enfila(f, 60);
  enfila(f, 70);
  imprimir(f);
  
  printf("\n");
  return 0;
}
