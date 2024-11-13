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