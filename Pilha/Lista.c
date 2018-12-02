#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

typedef struct _elemento {
	Item *info;
	struct _elemento *next;
	struct _elemento *prev;
} elemento;

typedef struct _lista {
	int length;
	struct _elemento *inicio;
	struct _elemento *fim;
} lista;

Lista *createLista() {
	lista *list;

	list = (lista *) malloc(sizeof(lista));
	list->length = 0;
	list->inicio = NULL;
	list->fim = NULL;

	return (Lista) list;
}

int length(Lista L) {
	lista *list;
	list = (lista *) L;

	return list->length;
}

Posic insert(Lista L, Item info) {
	lista *list;
	elemento *new, *aux;

	list = (lista *) L;

	new = (elemento *) malloc(sizeof(elemento));
	new->next = NULL;
	new->prev = NULL;
	new->info = info;

	if (list->length == 0) {
		list->inicio = new;
	}
	else {
		aux = list->fim;

		aux->next = new;
		new->prev = aux;
		new->next = NULL;
	}

	list->fim = new;
	list->length++;

	return (Posic) new;
}

void remover(Lista L, Posic p) {
	lista *list;

	elemento *aux1, *aux2;

	list = (lista *) L;

	aux1 = (elemento *) p;

	if (aux1->prev == NULL) {
		/*Quando o Posic for o único elemento existente na lista (último e primeiro ao mesmo tempo)*/
		if (aux1->next == NULL) {
			list->inicio = NULL;
			list->fim = NULL;
		}
		/*Quando o Posic aponta para o primeiro elemento*/
		else {
			aux2 = aux1->next;
			aux2->prev = NULL;
			list->inicio = aux2;
		}
	}
	else {
		/*Quando o Posic aponta para o último elemento*/
		if (aux1->next == NULL) {
			aux2 = aux1->prev;
			aux2->next = NULL;
			list->fim = aux2;
		}
		/*Quando o Posic aponta para qualquer elemento no meio da lista*/
		else {
			aux2 = aux1->prev;
			aux2->next = aux1->next;
		 	aux2 = aux2->next;
		 	aux2->prev = aux1->prev;
		}
	}

	free(aux1);
	aux1 = NULL;
	p = NULL;

	list->length--;
}

Item get(Lista L, Posic p) {
	lista *list;
	elemento *aux;

	list = (lista *) L;
	aux = (elemento *) p;

	return (Item) aux->info;
}

Posic insertBefore(Lista L, Posic p, Item info) {
	lista *list;
	elemento *new, *aux1, *aux2;

	list = (lista *) L;

	new = (elemento *) malloc(sizeof(elemento));
	new->next = NULL;
	new->prev = NULL;
	new->info = info;

	aux2 = (elemento *) p;

	if (aux2->prev == NULL) {

		aux2->prev = new;
		new->next = aux2;

		list->inicio = new;
	}
	else {
		aux1 = aux2->prev;

		new->next = aux2;
		new->prev = aux1;
		aux1->next = new;
		aux2->prev = new;
	}

	list->length++;

	return (Posic) new;
}

Posic insertAfter(Lista L, Posic p, Item info) {
	lista *list;
	elemento *new, *aux1, *aux2;

	list = (lista *) L;

	new = (elemento *) malloc(sizeof(elemento));
	new->next = NULL;
	new->next = NULL;
	new->info = info;

	aux2 = (elemento *) p;

	if (aux2->next == NULL) {

		aux2->next = new;
		new->prev = aux2;

		list->fim = new;
	}
	else {
		aux1 = aux2->next;

		new->next = aux1;
		new->prev = aux2;
		aux2->next = new;
		aux1->prev = new;
	}

	list->length++;

	return (Posic) new;
}

Posic getFirst(Lista L) {
	lista *list;
	Posic pos;

	list = (lista *) L;

	if (list->length == 0)
		pos = NULL;
	else pos = (Posic) list->inicio;

	return pos;
}

Posic getNext(Lista L, Posic p) {
	lista *list;
	elemento *aux;
	Posic *pos;

	list = (lista *) L;

	if (list->length == 0) {
		pos = NULL;
	}
	else {
		aux = (elemento *) p;
		aux = aux->next;
		pos = (Posic) aux;
	}

	return pos;
}

Posic getLast(Lista L) {
	lista *list;
	Posic *pos;

	list = (lista *) L;

	if (list->length == 0)
		pos = NULL;
	else pos = (Posic) list->fim;

	return pos;
}

Posic getPrevious(Lista L, Posic p) {
	lista *list;
	elemento *aux;
	Posic *pos;


	list = (lista *) L;

	if (list->length == 0) {
		pos = NULL;
	}

	else {
		aux = (elemento *) p;
		pos = (Posic) p;

		aux = aux->prev;
		pos = (Posic) aux;
	}

	return pos;
}

void clearLista(Lista L) {
	lista *list;
	Posic p;

	list = (lista *) L;

	while (list->length > 0) {
		p = getFirst(list);
		remover(list, p);
	}

	free(L);
}
