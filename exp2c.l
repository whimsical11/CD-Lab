/**         EXPERIMENT NO:2C COUNT NUMBER OF VOWELS AND CONSONANTS IN A STRING         **/

%{
    int vowel_count=0;
    int consonant_count=0;
%}

vowel [aeiouAEIOU]
consonant [^aeiouAEIOU]

%%
{vowel} {vowel_count++;}
{consonant} {consonant_count++;}
[ \t\n]+ {}
. {}
%%



int main(int argc, char **argv)
{
    FILE *file=fopen("input.txt","r");
    if(!file)
    {
        printf("File not found\n");
        return 1;
    }

    yyin=file;  
    yylex();
    fclose(file);

    printf("Number of vowels: %d\n",vowel_count);
    printf("Number of consonants: %d\n",consonant_count);

    return 0;
}

int yywrap()
{
    return 1;
}






/***
GitHub Copilot
Algorithm for the given Lex program:
Initialize Variables:

Declare and initialize vowel_count to 0.
Declare and initialize consonant_count to 0.
Define Patterns:

Define a pattern vowel to match any vowel (both uppercase and lowercase): [aeiouAEIOU].
Define a pattern consonant to match any consonant (both uppercase and lowercase): [^aeiouAEIOU].
Lexical Rules:

Vowel Pattern:
Pattern: {vowel}
Action: Increment vowel_count.
Consonant Pattern:
Pattern: {consonant}
Action: Increment consonant_count.
Whitespace Pattern:
Pattern: [ \t\n]+
Action: Ignore whitespace characters.
Any Other Character:
Pattern: .
Action: Ignore any other character.
Main Function:

Open the file input.txt for reading.
If the file cannot be opened, print an error message and exit the program.
Set yyin to the file pointer.
Call yylex() to start lexical analysis.
Close the file after analysis.
Print the counts of vowels and consonants.
Helper Functions:
yywrap():
Called when the end of the input file is reached.
Returns 1 to indicate the end of input.
***/