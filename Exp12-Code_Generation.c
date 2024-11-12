#include <stdio.h>
#include <string.h>

struct Code {
    char result[10];
    char arg1[10];
    char arg2[10];
    char op;
};

void generateTargetCode(struct Code *code, FILE *output) {
    switch (code->op) {
        case '+':
            fprintf(output, "    MOV AX, %s\n", code->arg1);
            fprintf(output, "    ADD AX, %s\n", code->arg2);
            fprintf(output, "    MOV %s, AX\n", code->result);
            break;
            
        case '-':
            fprintf(output, "    MOV AX, %s\n", code->arg1);
            fprintf(output, "    SUB AX, %s\n", code->arg2);
            fprintf(output, "    MOV %s, AX\n", code->result);
            break;
            
        case '*':
            fprintf(output, "    MOV AX, %s\n", code->arg1);
            fprintf(output, "    MOV BX, %s\n", code->arg2);
            fprintf(output, "    MUL BX\n");
            fprintf(output, "    MOV %s, AX\n", code->result);
            break;
            
        case '/':
            fprintf(output, "    MOV AX, %s\n", code->arg1);
            fprintf(output, "    MOV BX, %s\n", code->arg2);
            fprintf(output, "    XOR DX, DX\n");
            fprintf(output, "    DIV BX\n");
            fprintf(output, "    MOV %s, AX\n", code->result);
            break;
            
        case '=':
            fprintf(output, "    MOV %s, %s\n", code->result, code->arg1);
            break;
    }
}

int main() {
    struct Code codes[10];
    int i = 0;
    FILE *output = fopen("target_code.asm", "w");

    if (!output) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Enter the set of intermediate code (terminated by exit):\n");

    while (1) {
        printf("Enter operation: ");
        scanf(" %c", &codes[i].op);
        
        if (codes[i].op == 'e') // Assuming 'e' means exit
            break;

        printf("Enter result: ");
        scanf("%s", codes[i].result);
        printf("Enter arg1: ");
        scanf("%s", codes[i].arg1);

        if (codes[i].op != '=') {
            printf("Enter arg2: ");
            scanf("%s", codes[i].arg2);
        }

        generateTargetCode(&codes[i], output);
        i++;
    }

    fclose(output);
    printf("Target code generated in target_code.asm\n");
    return 0;
}
