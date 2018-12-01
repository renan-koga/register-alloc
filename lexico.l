/* Nao usar a biblioteca do flex*/
%option noyywrap
%x COMMENT

%{
  #include <sintatico.tab.h>
  int line=1;
%}

%%
"Graph"           {return GRAPH; printf("GRAPH ");}
"K"               {return K; printf("K ");}
"="               {return ASSIGN; printf("= ");}
":"               {return COLON; printf(": ");}
" "               {}
"-->"             {return INFER; printf("--> ");}
"<->"             {return MOVE; printf("<-> ");}
[\n]              {line++; return EOL;}
[0-9]+            {yylval.integer = atoi(yytext); return NUMBER; printf("%s ", yytext);}
.                 {return ERROR; printf("ERRO");}
<<EOF>>           {return END_FILE;}
%%
// "Graph"           {printf("GRAPH "); return GRAPH;}
// "K"               {printf("K "); return K;}
// "="               {printf("= "); return ASSIGN;}
// ":"               {printf(": "); return COLON;}
// " "               {}
// "-->"             {printf("--> "); return INFER;}
// "<->"             {printf("<-> "); return MOVE;}
// [\n]              {printf("\n"); return EOL;}
// [0-9]+            {printf("%s ", yytext); return NUMBER;}
// .                 {printf("ERRO"); return ERROR;}
// <<EOF>>           {return END_FILE;}