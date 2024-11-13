#include <stdio.h>
#include <ctype.h>

char s[64]; //store input expression, 
int cnt = 0; //set cnt globally to 0 to use across all functions

int E(), E_(), T(), T_(), F();

int main() {
    printf("Enter Expression to Validate: ");
    scanf("%s", s);
    
    if (E()) {
        printf("Expression is Valid.\n");
    } else {
        printf("Expression is Invalid.\n");
    }

    return 0;
}

// E -> T E'
int E() {
    if (T()) {
        if (E_()) {
            return 1;
        }
    }
    return 0;
}

// E' -> + T E' | ∈
int E_() {
    if (s[cnt] == '+') {
        cnt++; //increment cnt to move to next terminal
        if (T()) {
            if (E_()) {
                return 1; //NOTE: 1 => success
            }
        }
        return 0;
    }
    return 1;  // epsilon (empty production)
}

// T -> F T'
int T() {
    if (F()) {
        if (T_()) {
            return 1;
        }
    }
    return 0;
}

// T' -> * F T' | ∈
int T_() {
    if (s[cnt] == '*') {
        cnt++;
        if (F()) {
            if (T_()) {
                return 1;
            }
        }
        return 0;
    }
    return 1;  // epsilon (empty production)
}

// F -> ( E ) | id
int F() {
    if (s[cnt] == '(') {
        cnt++;
        if (E()) {
            if (s[cnt] == ')') {
                cnt++;
                return 1;
            }
        }
    } else if (isalnum(s[cnt])) {  //to check identifier use isalnum() function
        cnt++;
        return 1;
    }
    return 0;
}
