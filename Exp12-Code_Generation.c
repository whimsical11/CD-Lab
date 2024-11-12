#include <stdio.h>
#include <string.h>

struct Code {
    char result[10];
    char arg1[10];
    char arg2[10];
    char op;
};

void generateTargetCode(struct Code *code) {
    switch (code->op) {
        case '+':
            printf("    MOV AX, %s\n", code->arg1);
            printf("    ADD AX, %s\n", code->arg2);
            printf("    MOV %s, AX\n", code->result);
            break;
            
        case '-':
            printf("    MOV AX, %s\n", code->arg1);
            printf("    SUB AX, %s\n", code->arg2);
            printf("    MOV %s, AX\n", code->result);
            break;
            
        case '*':
            printf("    MOV AX, %s\n", code->arg1);
            printf("    MOV BX, %s\n", code->arg2);
            printf("    MUL BX\n");
            printf("    MOV %s, AX\n", code->result);
            break;
            
        case '/':
            printf("    MOV AX, %s\n", code->arg1);
            printf("    MOV BX, %s\n", code->arg2);
            printf("    XOR DX, DX\n");
            printf("    DIV BX\n");
            printf("    MOV %s, AX\n", code->result);
            break;
            
        case '=':
            printf("    MOV %s, %s\n", code->result, code->arg1);
            break;
    }
}

int main() {
    struct Code code;

    printf("Enter TAC instructions in the format (result = arg1 op arg2) or (result = arg1) for assignment, terminated by 'exit':\n");
    
    while (1) {
        char input[50];
        fgets(input, sizeof(input), stdin);

        // Terminate if input is "exit"
        if (strncmp(input, "exit", 4) == 0) {
            break;
        }

        // Parse the input TAC instruction
        if (sscanf(input, "%s = %s %c %s", code.result, code.arg1, &code.op, code.arg2) == 4) {
            // Binary operation
            generateTargetCode(&code);
        } else if (sscanf(input, "%s = %s", code.result, code.arg1) == 2) {
            // Assignment operation
            code.op = '=';
            strcpy(code.arg2, "");  // No second argument
            generateTargetCode(&code);
        } else {
            printf("Invalid instruction format. Try again.\n");
        }
    }

    printf("Assembly code generation complete.\n");

    return 0;
}
