#include <stdio.h>
#include <string.h> // For strlen
#include <stdlib.h> // not used?
#include <ctype.h> // For isdigit

#define MAX_PROD 100 
#define MAX_LEN 50 

struct Variable {
    char name;
    int value;
    int is_constant;
};

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/'); //return 1 
}

// Helper function to find variable by name
int getVariableValue(char name, struct Variable* vars, int var_count, int* value) {
    for (int i = 0; i < var_count; i++) {
        if (vars[i].name == name && vars[i].is_constant) { //check if name is same and is constant
            *value = vars[i].value; //assign value to value , * is used to assign value to pointer
            return 1;
        }
    }
    return 0;
}

int main() {
    int n;
    char productions[MAX_PROD][MAX_LEN];
    struct Variable vars[MAX_PROD];
    int var_count = 0;
    
    printf("Enter the number of productions: ");
    scanf("%d", &n);
    getchar(); // Consume newline    
    printf("Enter %d productions:\n", n);
    for (int i = 0; i < n; i++) {
        fgets(productions[i], MAX_LEN, stdin); //use fgets(char array, max_length, stdin)
        productions[i][strcspn(productions[i], "\n")] = 0; // Remove newline, string_complement_span
    }
    
    printf("\nOptimized code:\n");
    
    // Process each production
    for (int i = 0; i < n; i++) {
        char lhs = productions[i][0];
        char *rhs = productions[i] + 2; // Skip '=' character
        
        // Case 1: Direct assignment of constant
        if (strlen(rhs) == 1 && isdigit(rhs[0])) {
            vars[var_count++] = (struct Variable){lhs, rhs[0] - '0', 1}; //name,value,is_constant
            continue;
        }
        
        // Case 2: Assignment of another variable
        if (strlen(rhs) == 1 && isalpha(rhs[0])) {
            int val; 
            if (getVariableValue(rhs[0], vars, var_count, &val)) {
                vars[var_count++] = (struct Variable){lhs, val, 1};
            } else {
                printf("%s\n", productions[i]);
            }
            continue;
        }
        
        // Case 3: Expression
        if (strlen(rhs) == 3 && isOperator(rhs[1])) {
            int val1, val2;
            int can_propagate = 1;

            if (isdigit(rhs[0])) {
                val1 = rhs[0] - '0';
            } else if (!getVariableValue(rhs[0], vars, var_count, &val1)) {
                can_propagate = 0;
            }

            if (isdigit(rhs[2])) {
                val2 = rhs[2] - '0';
            } else if (!getVariableValue(rhs[2], vars, var_count, &val2)) {
                can_propagate = 0;
            }
            
            if (can_propagate) {
                int result;
                switch(rhs[1]) {
                    case '+': result = val1 + val2; break;
                    case '-': result = val1 - val2; break;
                    case '*': result = val1 * val2; break;
                    case '/': result = val1 / val2; break;
                    default: result = 0;
                }
                printf("%c=%d\n", lhs, result);
                vars[var_count++] = (struct Variable){lhs, result, 1};
                continue;
            }
        }
        
        // If no optimization possible, print original production
        printf("%s\n", productions[i]);
    }
    
    return 0;
}
