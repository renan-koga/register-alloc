/*
	Autor: Renan Yuji Koga Ferreira
	Estrutura de Dados 2017
*/

#ifndef PILHA_H
#define PILHA_H

  #include "Lista.h"

  typedef void *Pilha;

  Pilha createPilha();
  /*
    Cria uma Pilha e a retorna.
  */

  void push(Pilha P, Item info);
  /*
    Insere um elemento info na Pilha p;
  */

  Item pop(Pilha P);
  /*
    Retorna o primeiro elemento da Pilha p.
  */

  int lengthPilha(Pilha P);
  /*
    Retorna o tamanho da Pilha p.
  */

  void clearPilha(Pilha P);
  /*
    Remove todos os itens da Pilha p.
  */

#endif
