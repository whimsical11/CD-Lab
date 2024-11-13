 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>
 #define MAX_EXPR_LEN 100
 #define MAX_TAC_LEN 100
 typedef struct {
    char op;
    // Operator (+,-, *, /)
    char arg1[10]; // First operand
    char arg2[10]; // Second operand
    char result[10]; // Result variable
 } TACInstruction;
 TACInstruction tac[MAX_TAC_LEN]; // Array to store TAC instructions
 int tacIndex = 0;                // Current index in TAC array
 int tempCount = 1;              // Counter for temporary variables
 
 void newTemp(char *temp) {
 sprintf(temp, "t%d", tempCount++); 
 }
 int isOperator(char c) {
 return (c == '+' || c == '-' || c == '*' || c == '/');
 }
 int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-':
                return 1;
        case '*':
        case '/':
                return 2;
        default:
                return 0;
    }
 }
 void generateTAC(char *expr) {
    char operandStack[MAX_EXPR_LEN][10];
    char operatorStack[MAX_EXPR_LEN];
    int operandTop =-1;
    int operatorTop =-1;
    char temp[10];
    int i = 0;
    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        if (isalnum(expr[i])) {
            char operand[10];
            int j = 0;
            while (isalnum(expr[i])) {
                operand[j++] = expr[i++];
            }
            operand[j] = '\0';
            operandTop++;
            strcpy(operandStack[operandTop], operand);
            i--;
        }
        else if (isOperator(expr[i])) {
            while (operatorTop >= 0 &&
            getPrecedence(operatorStack[operatorTop]) >= getPrecedence(expr[i])) {
                newTemp(temp);
                tac[tacIndex].op = operatorStack[operatorTop];
                strcpy(tac[tacIndex].arg2, operandStack[operandTop]);
                strcpy(tac[tacIndex].arg1, operandStack[operandTop- 1]);
                strcpy(tac[tacIndex].result, temp);
                operatorTop--;
                operandTop--;
                strcpy(operandStack[operandTop], temp);
                tacIndex++;
            }
            operatorTop++;
        operatorStack[operatorTop] = expr[i];
        }
        i++;
    }
    while (operatorTop >= 0) {
        newTemp(temp);
        tac[tacIndex].op = operatorStack[operatorTop];
        strcpy(tac[tacIndex].arg2, operandStack[operandTop]);
        strcpy(tac[tacIndex].arg1, operandStack[operandTop- 1]);
        strcpy(tac[tacIndex].result, temp);
        operatorTop--;
        operandTop--;
        strcpy(operandStack[operandTop], temp);
        tacIndex++;
    }
 }
void printTAC() {
    printf("\nGenerated Three Address Code:\n");
    printf("----------------------------\n");
    for (int i = 0; i < tacIndex; i++) {
    printf("%s := %s %c %s\n",
    tac[i].result,
    tac[i].arg1,
    tac[i].op,
    tac[i].arg2);
 }
 }
 int main() {
    char expr[MAX_EXPR_LEN];
    printf("Enter an arithmetic expression: ");
    fgets(expr, MAX_EXPR_LEN, stdin); //use fgets
    expr[strcspn(expr, "\n")] = '\0'; // Remove trailing newline
    tacIndex = 0;
    tempCount = 1;
    generateTAC(expr);
    printTAC();
    return 0;
 }