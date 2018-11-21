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

start: program END_FILE {printf("\n\nSUCCESSFUL COMPILATION.\n"); exit(0);}
;

program: GRAPH NUMBER COLON color {printf("\nGRAPH %d", ++num);}
;

program1:
  | program
;

color: K ASSIGN NUMBER vertexes
	| K ASSIGN NUMBER useless1
;



vertexes: NUMBER INFER edges
;

edges: NUMBER edges1
;

edges1: NUMBER edges1
  | edges2
;

edges2: vertexes
  | useless
  | program1
;

useless: NUMBER MOVE NUMBER useless1
;

useless1: useless
  | program1
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