/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef LISTA_H
#define LISTA_H

	typedef void *Lista;
	typedef void *Posic;
	typedef void *Item;

	/*
		Tipo Abstrato Lista
			Lista é um conjunto de elementos encadeados, podendo ser acessados através de sua posição (Posic). Uma lista é dita vazia quando não há nenhum elemento (tamanho 0).

			Tipo Posic
				Indica a posição de um elemento dentro da Lista. Quando seu valor é NULL, significa que apresenta um valor inválido.

			Tipo Item
				Conteúdo dentro de um elemento da Lista, podendo ser qualquer coisa.
	*/


	Lista *createLista();
	/*
		Cria uma Lista vazia duplamente encadeada.
	*/

	int length(Lista L);
	/*
		Retorna o tamanho (quantidade de elementos) de uma Lista L.
			-L: Lista
	*/

	Posic insert(Lista L, Item info);
	/*
		Insere um elemento info no final da Lista L, acrescendo em 1 o tamanho da Lista, e retorna a posição do elemento inserido.
			-L: Lista
			-info: Item
	*/

	void remover(Lista L, Posic p);
	/*
		Remove da Lista L o elemento na posição p e diminui o tamanho da Lista em 1. O Posic p que precisa ser um valor válido passa a apontar para um valor inválido.
			-L: Lista
			-p: Posic
	*/

	Item get(Lista L, Posic p);
	/*
		Retorna o Item contido na posição p da Lista L, portanto p deve indicar um valor válido.
	*/

	Posic insertBefore(Lista L, Posic p, Item info);
	/*
		Insere um elemento info na Lista L na posição imediatamente anterior apontado pelo Posic p, logo p deve apontar para um valor dentro da Lista L.
			-L: Lista
			-p: Posic
			-info: Item
	*/

	Posic insertAfter(Lista L, Posic p, Item info);
	/*
		Insere um elemento info na Lista L na posição imediatamente posterior apontado pelo Posic p, logo p deve apontar para um valor dentro da Lista L.
			-L: Lista
			-p: Posic
			-info: Item
	*/

	Posic getFirst(Lista L);
	/*
		Retorna a posição do primeiro elemento de uma Lista, caso a Lista seja vazia, retornará NULL.
			-L: Lista
	*/

	Posic getNext(Lista L, Posic p);
	/*
		Retorna a posição do elemento de uma Lista L seguinte ao elemento apontado pelo Posic p.
			-L: Lista
			-p: Posic
	*/

	Posic getLast(Lista L);
	/*
		Retorna a posição do último elemento da Lista L, caso a lista seka vazia, retornará NULL.
			-L: Lista
	*/

	Posic getPrevious(Lista L, Posic p);
	/*
		Retorna a posição do elemento de uma Lista L anterior ao elemento apontado pelo Posic p.
			-L: Lista
			-p: Posic
	*/

	void clearLista(Lista L);
	/*
		Remove todos os elementos da Lista e libera a memória ocupada ao criar uma Lista.
	*/

#endif
