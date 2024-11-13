#include<stdio.h>
#include<string.h>
char states[20][20], result[20][20], copy[3];
void add_state(char a[3], int i)
    strcpy(result[i], a);
void display(int n){ //void
    int k=0;
    printf("\nThe epsilon closure of %s is {", copy); //string type not int
    while(k<n){
        printf("%s",result[k]);
        k++; //its a while loop, so increment k
    }
    printf("} \n"); //closing
}
int main(){
    FILE *file = fopen("input.dat", "r");
    if (!file)
        printf("error");
    char state[20]; //state[3] is enough
    int i=0, end, k, n; //no j is used
    char state1[20], input[20], state2[20]; //size 3
    printf("enter the number of states: ");
    scanf("%d", &n);
    printf("Enter the states\n");
    for(k=0;k<n;k++)
        scanf("%d", &states[k]);
    for(k=0;k<n;k++){
        int flag=0;
        i=0;
        strcpy(state, states[k]);
        strcpy(copy,state);
        add_state(state, i++);
        while(1){            
            end =fscanf(file, "%s%s%s", state1, input, state2);
            if (end == EOF)
                break; //use break not return
            if(strcmp(state, state1)==0){
                if(strcmp(input, "e")==0){
                    add_state(state2, i++); //add state2 to result not copy
                    flag=1;
                    strcpy(state, state2); //main processing is done in state not copy
                }
            }
            if(flag==1)
                strcpy(state copy); //copy only used here
        }
        display(i);
        rewind(file);
    }
    return 0;
}




**********************
 int main(){
    FILE *file = fopen("input.dat", "r");
    char state[20]; //state[3] is enough
    int i=0, end, k, n; //no j is used
    char state1[20], input[20], state2[20]; //size 3
    
    printf("enter the number of states: ");
    scanf("%d", &n);
    printf("Enter the states\n");
    for(k=0;k<n;k++)
        scanf("%d", &states[k]);

    for(k=0;k<n;k++){                                
        int flag=0;
        i=0;
        strcpy(state, states[k]);
        strcpy(copy,state);
        add_state(state, i++);
        while(1){            
            end =fscanf(file, "%s%s%s", state1, input, state2);
            if (end == EOF)
                break; //use break not return
            if(strcmp(state, state1)==0){
                if(strcmp(input, "e")==0){
                    add_state(state2, i++); 
                    strcpy(state, copy); 
                }
            }
        }
        display(i);
        rewind(file);
    }
    return 0;
}
 * 
 * 
 * 
 ************************/ 