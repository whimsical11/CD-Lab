#include <stdio.h>
 void main()
 {
    char stack[20], ip[20], opt[10][10][1], ter[10];
    int i, j, k, n, top = 0, col, row;
    for (i = 0; i < 10; i++)
    {
        stack[i] = NULL; //set stack 0-10 to NULL
        ip[i] = NULL; //set ip 0-10 to NULL
        for (j = 0; j < 10; j++)
        {
        opt[i][j][1] = NULL;    //set opt[i][j][1] to NULL for all i,j
        }
    }
    printf("Enter the no.of terminals :\n");
    scanf("%d", &n);
    printf("\nEnter the terminals :\n");
    scanf("%s", &ter);
    printf("\nEnter the table values :\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
        printf("Enter the value for %c %c:", ter[i], ter[j]);
        scanf("%s", opt[i][j]); //read opt[i][j] corresponding to ter[i] and ter[j]
        }
    }
    printf("\n**** OPERATOR PRECEDENCE TABLE ****\n");
    for (i = 0; i < n; i++)
    {
        printf("\t%c", ter[i]); //column headings
    }
    printf("\n");
    for (i = 0; i < n; i++)
    {
        printf("\n%c", ter[i]); //row header
        for (j = 0; j < n; j++)
        {
        printf("\t%c", opt[i][j][0]);
        }
    }
    stack[top] = '$'; //initialize stack with $
    printf("\nEnter the input string:");
    scanf("%s", ip);
    i = 0; //while loop runs till i reaches end of ip string
    printf("\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n");
    printf("\n%s\t\t\t%s\t\t\t", stack, ip); //initial step print stack and input string
    while (i <= strlen(ip))
    {
        for (k = 0; k < n; k++)
        {
            if (stack[top] == ter[k]) //calculate col from stack
            col = k;
            if (ip[i] == ter[k]) //calculate row from ip
            row =k;
        }
        if ((stack[top] == '$') && (ip[i] == '$')) //both stack[top] and ip[i] = dollar
        {
            printf("String is accepted\n");
            break;
        }
        else if ((opt[col][row][0] == '<') || (opt[col][row][0] == '='))
        {
            stack[++top] = opt[col][row][0]; //add symbol (< or =)
            stack[++top] = ip[i]; //shift symbol in i
            printf("Shift %c", ip[i]);
            i++;
        }
        else
        {
            if (opt[col][row][0] == '>')
            {
                while (stack[top] != '<')
                {
                }--top; //decrement top until '<' is encountered
                top = top- 1; //decrement top by 1 (to remove '<')
                printf("Reduce");
            }
            else //some sort of error occured, string is not valid
            {
                printf("\nString is not accepted");
                break;
            }
        }
        printf("\n");
        for (k = 0; k <= top; k++)
        {
            printf("%c", stack[k]); //chara by chara print stack from k=0 to top
        }
        printf("\t\t\t");
        for (k = i; k < strlen(ip); k++) //i stores the current index, from i to strlen(ip) print ip
        {
            printf("%c", ip[k]);
        }
        printf("\t\t\t");
    }
 }