%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <sintatico.tab.h>
	#include "Grafo/grafo.h"

	#define YYMAXDEPTH 100000000

  extern int yylex();
  extern char* yytext;
	extern int line;
	char *string;
  int num=0;

	grafo graph;
	int vertex;
	int registers;
	int graphNumber;

	void printLine(int line);
	void printErroPointer(int column);
	char *getString(FILE *_stdin);
  int yyerror(char *s);
	void simplify();
	void assgin();

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
															simplify();
															assgin();
															printf("GRAPH %d\n", graphNumber);
														}
;

graph: GRAPH NUMBER COLON EOL { 
	// graph =	createGraph();
	graphNumber = $2;
	 }
;

color: K ASSIGN NUMBER EOL { registers = $3; }
;

bloco:
	| NUMBER INFER NUMBER edges	{
																vertex = $1;
																// insertPoint(graph, vertex);
																// insertEdge(graph, vertex, $3);
																printf("%d <-- %d\n", $3, vertex);
															}
	| NUMBER MOVE NUMBER move {}
;

edges: NUMBER edges {
	//  insertEdge(graph, vertex, $1); 
printf("%d ", $1);}
	| EOL bloco
	| bloco
;

move: 
	| EOL
	| NUMBER MOVE NUMBER move
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
	
}

void assgin() {

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