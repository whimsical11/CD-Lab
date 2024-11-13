/***
 * EXPERIMENT NO: 1 - LEXICAL ANALYZER IN C
 * AUTHOR: MERIN JOHNSON
 ***/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int is_keyword(const char* buffer);
//input=constant character string. const=> fn will not modify the string the buffer points to
int is_operator(char ch);

int main(){
    char ch, buffer[15], operators[] = "+-*/%=,;()";
    FILE *fp;
    int i=0, j=0; //j is buffer index, initialize to 0
    //counters
    int keyword_count = 0, identifier_count=0, operator_count=0;

    fp=fopen("input.txt", "r");
    if(fp==NULL){
        printf("error while opening the file\n");
        return 1;
        //exit(0);
    }

    while((ch=fgetc(fp))!=EOF){ //read character from fp to ch
        if (isalnum(ch)) { //if alphanumeric, add to buffer
            buffer[j++]=ch;
        }
        else{
            if(j!=0){ //if buffer has some content
                buffer[j]='\0'; //terminate the string
                j=0; //reset to read next alphanumeric sequence

                if(is_keyword(buffer)){ //check if buffer is a keyword
                    printf("kwd ");
                    keyword_count++;
                }
                else{
                    printf("id "); //else print identifier
                    identifier_count++;
                }
            }

            //after processing the string alread in buffer
            // check the current character
            if(is_operator(ch)){
                operator_count++; 
                switch(ch){
                    case '+': printf("op_plus "); break;
                    case '-': printf("op_minus "); break;
                    case '*': printf("op_mult "); break;
                    case '/': printf("op_div "); break;
                    case '%': printf("op_mod "); break;
                    case '=': printf("op_eq "); break;
                    case ',': printf("op_comma "); break;
                    case ';': printf("op_semicolon "); break;
                    case '(': printf("op_openbr "); break;
                    case ')': printf("op_closebr "); break;
                }
            }
        }
    }

    fclose(fp);

    printf("\nKeywords:\n", keyword_count);
    printf("Identifiers:\n", identifier_count);
    printf("Operators:\n", operator_count);

    return 0;
}

int is_keyword(const char* buffer){
    const char* keywords[] = {"int", "float", "char", "if", "else", "while", "do", "break", "continue", "return"};
    for (int i=0; i<10; ++i){
        if(strcmp(keywords[i], buffer)==0){
            return 1;
        }
    }
    return 0;
}

int is_operator(char ch){
    return strchr("+-*/%=,;()", ch)!=NULL; //return 1 if ch is in the string
}


/******
 * Algorithm for the given C program:
 * 
1. Initialize Variables:
    Declare necessary variables including ch, buffer, operators, file pointer fp, and counters for keywords, identifiers, and operators.
    Open File:

2. Open the file input.txt in read mode.
    If the file cannot be opened, print an error message and exit the program.

3. Read Characters from File:
    Use a while loop to read characters from the file until the end of the file (EOF) is reached.

4. Process Each Character:
    If the character is alphanumeric (isalnum(ch)):
        Add the character to the buffer.
    If the character is not alphanumeric:
        If the buffer is not empty:
            Terminate the string in the buffer with a null character.
            Reset the buffer index j to 0.
            
            Check if the buffer contains a keyword using is_keyword(buffer):
                If true, print "kwd" and increment the keyword counter.
                If false, print "id" and increment the identifier counter.

            Check if the character is an operator using is_operator(ch):
                If true, increment the operator counter and print the corresponding operator token.

5. Close File:
    Close the file after reading all characters.

6. Print Counters:
    Print the counts of keywords, identifiers, and operators.

Helper Functions:
- is_keyword(const char* buffer):
    Check if the buffer matches any of the predefined keywords.
    Return 1 if it is a keyword, otherwise return 0.

-is_operator(char ch):
    Check if the character ch is in the predefined set of operators.
    Return 1 if it is an operator, otherwise return 0.

 * 
 * ******/
