/*EXPERIMENT 2a */

//LEX file
%{ 
    int COMMENT=0;
%}

identifier [a-zA-Z][a-zA-Z0-9]*

%%
#.*     {printf("preprocessor directive");} //use %s and yytext
int|
float|
double|
main|
void|
for|
while|
do|
break|
return|
printf|
char    {if(!COMMENT) printf("kwd");} //use double quotes to enclose each string like "int", "do"

\*      {COMMENT=1; printf("comment starts");} //use double quotes like "/*" and wrong slash
*/      {COMMENT=0; printf("comment ends");}    

"+"     {if(!COMMENT) printf("op-plus");}
"-"     {if(!COMMENT) printf("op-minus");}
"*"     {if(!COMMENT) printf("op-mul");}
"/"     {if(!COMMENT) printf("op-div");}

"="     {if(!COMMENT) printf("assign");}
"<"     |
">"     |
"=="    |
"<="    |
">="     {if(!COMMENT) printf("rel-op");}

{identifier}\(              {if(!COMMENT) printf("function");}
"{"                         {if(!COMMENT) printf("blobk begins");}
"}"                         {if(!COMMENT) printf("blobk ends");}
{identifier}(\[[0-9]*\])?   {if(!COMMENT) printf("identifier");}

\".\"   {if(!COMMENT) printf("string");} //correct rule is \".*\"
[0-9]+  {if(!COMMENT) printf("number");}

.       {if(!COMMENT) ECHO;}
%%

int main(int argc, char **argv){
    FILE *fp=fopen("input.c", "r");
    if(!fp){
        printf("error while opening the file\n");
        return 1;   //return 1 for indicating error
    }
    yyin=fp;
    yylex();
    fclose(fp);
    return 0;       //return 0 for successful completion
}

int yywrap(){
    return 1;       //return 1 to indicate the end of 1st processing phase
}