
/* EXPERIMENT 2b - COUNT NUMBER OF WORDS AND LINES */
/* This experiment involves writing a program to count the number of words and lines in a given input. */
/* The program will read from the input and provide the total count of words and lines as output. */


%{
    int line_count = 0;
    int word_count = 0;
%}

identifier [a-zA-Z][a-zA-Z0-9]*

%%
\n {line_count++; word_count++;} // newline indicates end of line and word
{identifier} {word_count++;}
[0-9]+ {word_count++;}

[ \t]+ {} // ignore whitespace
. {} // ignore other characters
%%


int main(int argc,  char **argv) {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    yyin = file;
    yylex();
    fclose(file);

    printf("Number of words: %d\n", word_count);
    printf("Number of lines: %d\n", line_count);

    return 0;
}

int yywrap() {
    return 1;
}