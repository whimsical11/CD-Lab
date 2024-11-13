//LEX file

%{
    #include "y.tab.h"
%}

token num id op

%%
[a-zA-Z][a-zA-Z_0-9]*   return id;
[0-9]+(\.[0-9]*)        return num;
[+/*]                   return op;
.                       return yytext[0];
\n                      return 0;
%%

int yywrap(){
    return 1;
}



//YACC file

%{
    #include<stdio.h>
    #include<stdlib.h>      //not needed
    #include<string.h>      //not needed
    int valid=1;
    int yylex();
    void yyerror(const char *s);
%}

%token num id op

%%
    start: stmt ';'
        | stmt ';' start
        ;

    stmt: id '=' expr //id = expr not stmt = expr
        | expr
        ;

    expr: term op expr
        | term
        ;

    term: num
        | id
        | '-' term
        | '(' expr ')'
        ;
%%

int main(){
    printf("Enter the expression");
    yyparse();     //use yyparse() fn for yacc program, end with semicolon
    if (valid){ //if valid not valid==1
        printf("Expression is valid\n");
    }
    return 0;
}

void yyerror(const char *s){
    valid=0;
    printf("Invalid Expression\n");
}