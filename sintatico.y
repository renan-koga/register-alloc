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
	int assgin();

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
															printf("GRAPH %d: ", graphNumber);
															// printGraph(graph);
															// printf("GRAPH SIZE :%d\n",lenghtLista(graph));
															simplify();
															if (assgin()) {
																printf("SUCCESS\n");
															}
															else printf("SPILL\n");
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
														insertPoint(graph, *vertex);
														
														while (lengthPilha(vertexes) > 0) {
															vertex2 = (int *) pop(vertexes);
															insertEdge(graph, *vertex, *vertex2);					
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

  while (countVertexes(graph) > 0) {

    dot = findLessK(graph, registers);
    if (dot == NULL) {
      dot = findPotencialSpill(graph);

			printf("TAM: %d\n", countVertexes(graph));
    }
    push(stack, dot);
    removeVertex(graph, dot->registrador);
    
  }
}

int assgin() {
	point *dot;

  while (lengthPilha(stack) > 0) {
    dot = pop(stack);
    if (!assignColor(dot, registers)) {
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
