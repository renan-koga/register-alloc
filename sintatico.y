%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#define YYMAXDEPTH 100000000

  extern int yylex();
  extern char* yytext;
	extern int line;
	char *string;
  int num=0;

	void printLine(int line);
	void printErroPointer(int column);
	char *getString(FILE *_stdin);
  int yyerror(char *s);

%}
 
/* declare tokens */
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

start: END_FILE {printf("VAI PORRA!\n"); exit(0);}
	| program start
;

program: graph color bloco
;

graph: GRAPH NUMBER COLON EOL {}
;

color: K ASSIGN NUMBER EOL
;

bloco:
	| NUMBER INFER NUMBER edges
	| NUMBER MOVE NUMBER move
;

edges: NUMBER edges
	| EOL bloco
;

move: 
	| EOL
	| NUMBER MOVE NUMBER move
;

%%

int main(int argc, char **argv){
	// string = getString(stdin);
  // int i;

  // for(i=0; i<size; i++) {
    
    yyparse();
  // }

  return 0;
}

int yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
	fprintf(stderr, "TOKEN: %d", line);

	// if (end_file) {
	// 	if (line_comment) {
	// 		lines--;
	// 		columns = first;
	// 	}
	// 	printf("error:syntax:%d:%d: expected declaration or statement at end of input", lines, columns);
	// }
	// else {
	// 	columns -= strlen(yytext);
	// 	printf("error:syntax:%d:%d: %s", lines, columns, yytext);
	// }
	// printLine(lines);
	// printErroPointer(columns);
	// fflush(stderr);
}

// void printLine(int line) {
// 	int i, j, size, currentLine=1;

// 	size = strlen(string);
// 	for (i=0; i<size; i++) {
// 		if (line == currentLine) {
// 			j = i;
// 			printf("\n");
// 			while (string[j] != '\n' && string[j] != '\0') {
// 				printf("%c", string[j]);
// 				j++;
// 			}

// 			break;
// 		}
// 		else {
// 			if (string[i] == '\n') {
// 				currentLine++;
// 			}
// 		}
// 	}
// 	printf("\n");
// }

// void printErroPointer(int column) {
// 	int i;

// 	for (i=0; i<column-1; i++) {
// 		printf(" ");
// 	}
// 	printf("^");
// }

// char *getString(FILE *_stdin) {
// 	char *cadeia, ch;
// 	int i;

// 	cadeia = (char *) calloc(10000, sizeof(char));
	
// 	i = 0;
// 	while (fscanf(stdin, "%c", &ch) != EOF) {
// 		cadeia[i] = ch;
// 		i++;
// 	}
// 	cadeia[i] = '\0';
// 	rewind(stdin);

// 	return cadeia;
// }