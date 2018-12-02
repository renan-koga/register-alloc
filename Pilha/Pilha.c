#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

typedef struct _nodePilha {
	Item *info;
	struct _nodePilha *next;
  struct _nodePilha *prev;
} nodePilha;

typedef struct _pilha {
	int length;
	struct _nodePilha *inicio;
  struct _nodePilha *fim;
} pilha;

Pilha createPilha() {
	pilha *heap;

	heap = (pilha *) malloc(sizeof(pilha));
	heap->length = 0;
	heap->inicio = NULL;

	return (Pilha) heap;
}

void push(Pilha P, Item info) {
	pilha *heap;
	nodePilha *new, *aux;

	heap = (pilha *) P;

	new = (nodePilha *) malloc(sizeof(nodePilha));
	new->next = NULL;
	new->prev = NULL;
	new->info = info;

	if (heap->length == 0 || heap->inicio == NULL) {
		heap->inicio = new;
	}
	else {
		aux = heap->inicio;

    aux->prev = new;
    new->next = aux;
	}

	heap->inicio = new;
	heap->length++;
}

Item pop(Pilha P) {
  Item info;
  pilha *heap;
  nodePilha *aux1, *aux2;

  info = NULL;
  heap = (pilha *) P;

  if (heap->length > 0) {
    aux1 = heap->inicio;

    if (heap->length == 1) {
      heap->inicio = NULL;
    }
    else {
      aux2 = aux1->next;
      aux2->prev = NULL;

      heap->inicio = aux1->next;
    }

    info = aux1->info;

    heap->length--;

    free(aux1);
    aux1 = NULL;
  }

  return info;
}

int lengthPilha(Pilha P) {
	pilha *heap;
	heap = (pilha *) P;

	return heap->length;
}

void clearPilha(Pilha P) {
  pilha *heap;
  nodePilha *aux1, *aux2;

  heap = (pilha *) P;

  while (heap->length > 0) {
    aux1 = heap->inicio;

    if (heap->length == 1) {
      heap->inicio = NULL;
    }
    else {
      aux2 = aux1->next;
      aux2->prev = NULL;

      heap->inicio = aux2;
    }

    free(aux1);
    aux1 = NULL;

    heap->length--;
  }

	free(P);
}
