%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <sintatico.tab.h>
	#include "grafo.h"
	#include "pilha.h"

	#define YYMAXDEPTH 100000000

  extern int yylex();
  extern char* yytext;
	extern int line;
	char *string;
  int num=0;

	grafo graph;
	Pilha stack;
	Pilha vertexes;
	int *vertex, *vertex2;
	int registers;
	int graphNumber;

	void printLine(int line);
	void printErroPointer(int column);
	char *getString(FILE *_stdin);
  int yyerror(char *s);
	void simplify();
	int assign();

%}

%union {
	int integer;
}

%type <integer> NUMBER
 
/* tokens */
%token ASSIGN
%token COLON
%token END_FILE
%token EOL
%token ERROR
%token GRAPH
%token INFER
%token K
%token MOVE
%token NUMBER

%start start 

%%

start: END_FILE {exit(0);}
	| program start
;

program: graph color bloco	{
															printf("Graph %d: ", graphNumber);
															 printGraph(graph);
															//  printf("GRAPH SIZE :%d\n",lenghtLista(graph));
															simplify();
															 printf("SIMPLIFY GO GO GO\n");
															if (assign() == 1) {
																printf("SUCCESS\n");
															}
															else printf("SPILL\n");
															// clearPilha(stack);
															// clearPilha(vertexes);
															// printf("\n\n");
															// printPoint(graph, 32);
														}
;

graph: GRAPH NUMBER COLON EOL { 
																graph =	createGraph();
																stack = createPilha();
																vertexes = createPilha();
																graphNumber = $2;
															}
;

color: K ASSIGN NUMBER EOL { registers = $3; }
;

bloco: {}
	| fork bloco {}
;

fork:	NUMBER INFER edges 	{
														push(vertexes, &$1);
														// vertex = $1;
														// printf("<-- %d\n", vertex);
														vertex = (int *) pop(vertexes);
														insertPoint(graph, *vertex, registers);
														
														while (lengthPilha(vertexes) > 0) {
															vertex2 = (int *) pop(vertexes);
															insertEdge(graph, *vertex, *vertex2, registers);					
														}
													}
	| NUMBER MOVE move {}
;

edges: NUMBER edges {
											push(vertexes, &$1);
											// insertEdge(graph, vertex, $1);
											// printf("%d ", $1);
										}
	| NUMBER EOL 	{
									push(vertexes, &$1);
									// insertEdge(graph, vertex, $1);
									// printf("%d ", $1);
								}
;

move: NUMBER move2
;

move2: NUMBER MOVE NUMBER move2
	| EOL
;

%%

int main(int argc, char **argv){
	yyparse();

  return 0;
}

int yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
	fprintf(stderr, "TOKEN: %d", line);
}

void simplify() {
	point *dot = NULL;
	int count = countVertexes(graph);

  while (count > 0) {
		dot = NULL;
    dot = findLessK(graph, registers);
    if (dot == NULL) {
      dot = findPotencialSpill(graph);
//		printf("TAM: %d\n", countVertexes(graph));
    }
		dot->removido = 1;
    push(stack, dot);
		count--;
    // printf("TAMANHO DA PILHA: %d DO GRAFO: %d -- REG DA VEZ: %d DREGREE: %d\n", lengthPilha(stack), lenghtLista(graph), dot->registrador,  countDegree(graph, dot->registrador));
    // removeVertex(graph, dot->registrador);
    // dot->cor = 0;
  }
}

int assign() {
	point *dot;

  while (lengthPilha(stack) > 0) {
    dot = (point*) pop(stack);
	 // printf("TAMANHO DA PILHA: %d DO GRAFO: %d -- REG DA VEZ: %d DREGREE: %d\n", lengthPilha(stack)+1, countVertexes(graph), dot->registrador,  countDegree(graph, dot->registrador));
    if (assignColor(dot, registers) == 0) {
      return 0;
    }
  }

  return 1;
}

// function simplify() {
//   stack *st;
//   point *dot;
  
//   while (graph.length > 0) {
//     dot = findLessK(graph, registers);

//     if (dot == NULL) {
//       dot = potencialSpill(graph);
//     }
//     push(st, dot);
//     removePoint(graph, dot);
//   }

//   return st;
// }

// function assign(stack) {
//   point *dot;

//   while (stack.length > 0) {
//     dot = pop(stack);
//     if (!assignColor(graph, dot)) {
//       return 0;
//     }
//   }

//   return 1;
// }
