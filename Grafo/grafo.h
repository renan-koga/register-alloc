#ifndef GRAFO_H
#define GRAFO_H

	#include "lista.h"

    typedef Lista grafo;
	/*Tipo Abstrato Grafo: Consiste em um conjunto com todos os vértices (Point) de um plano*/
    typedef struct _point{
        int registrador;
        int cor;
        int removido;
        Lista interferencias;
    }point;
	/*Tipo Abstrato Point: Seria o mesmo que os vértices de um grafo, são interligadas por uma aresta (Edge)*/
    typedef struct _edge{
        struct _point* reg1;
        struct _point* reg2;
    }edge;
	/*Tipo Abstrato Edge: Uma aresta representa uma ligação entre dois vértices (Point 'reg1' e Point 'reg2')*/

	grafo createGraph();
	/*Gera uma instância do tipo Point, com um id e sua cor*/
	point* createPoint(int registrador, int cor);
	/*Insere um registrador no grafo*/
	point* insertPoint(grafo anyGrafo, int registrador, int cor);
	void createEdge(point* reg1, point* reg2);
	/*Insere uma aresta entre Point 'reg1' e Point 'reg2'*/
	void insertEdge(grafo anyGrafo, int reg1, int cor1, int reg2, int cor2);
	/*Remove a aresta entre Point 'reg1' e Point 'reg2'*/
	void removeEdge(grafo anyGrafo, int reg1, int reg2);
	/*Remove o registrador*/
	void removePoint(grafo anyGrafo, int registrador);
	/*Printa todas as interferências de um dado registrador*/
	void printPoint(grafo anyGrafo, int registrador);
	/*Encontra o registrador no grafo (retorna 1 para*/
	Node findPoint(grafo anyGrafo, int registrador);
	/*Encontra a aresta entre Point 'reg1' e Point 'reg2', retorna nulo se não existir ligação*/
	Node findEdge(grafo anyGrafo, int reg1, int reg2);
	/*Libera a memória do grafo*/
	void encerraGrafo(grafo anyGrafo);
	/*Libera a memória da lista de interferências*/
	void destroiEdges(int registrador);

#endif
