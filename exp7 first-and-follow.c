 #include<stdio.h> 
 #include<string.h> //strcpy() and strlen() in follow()
 #include<ctype.h> //used in isupper() and islower() in first()
 #include<stdlib.h> //not used
 #include<math.h> //not used
 int n, m = 0, p, i = 0, j = 0;
 char a[10][10], f[10]; //a stores productions, f stores first and follow
 void follow(char c);
 void first(char c);
 
 int main() {
    int i, z; //z is used to check if user wants to continue
    char c, ch;
    printf("Enter the no of productions : \n");
    scanf("%d", & n);
    printf("Enter the productions:\n");
    for (i = 0; i < n; i++)
        scanf("%s%c", a[i], & ch); //ch is used to consume the newline character
    do {
        m=0; //m is used to store the length of f, reset to 0
        printf("Enter a variable whose first & follow is to be found:");
        scanf("%c", & c);
        first(c); 
        printf("First(%c)={", c); //we get m as the length of f
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");
        strcpy(f, " "); //flush f
        m=0;
        follow(c);
        printf("Follow(%c)={", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");
        printf("Want to continue or not(1/0) ? ");
        scanf("%d%c", & z, & ch); //z for option, c for catching newline
    }
    while (z == 1);
    return (0);
 }
 void first(char c) {
    int k; //k is used to iterate over productions
    if (!isupper(c)) //if c is a terminal
        f[m++] = c; //increment m and store c in f
    for (k = 0; k < n; k++) { //n is a global variable
        if (a[k][0] == c) { //if production starts with c
            if (a[k][2] == '$') //if production is of the form A->$
            follow(a[k][0]); 
            else if (islower(a[k][2]))
            f[m++] = a[k][2];
            else
            first(a[k][2]);
        }
    }
 }
 void follow(char c) {
    if (a[0][0] == c)
    f[m++] = '$';
    for (i = 0; i < n; i++) { //i is used because it is a global variable and is updated in first()
        for (j = 2; j < strlen(a[i]); j++) { //starts from 2 because a[i][0] is the variable and a[i][1] is the arrow
            if (a[i][j] == c) {
                if (a[i][j + 1] != '\0')
                first(a[i][j + 1]);
                if (a[i][j + 1] == '\0' && c != a[i][0]) //eg. A->aB, follow(B) = follow(A), not applicable for c==a[i][0] eg A->aA
                follow(a[i][0]);
            }
        }
    }
 }

