 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #define MAX_STATES 100
 #define MAX_SYMBOLS 26
 #define MAX_STATE_NAME_LENGTH 20
 typedef struct {
 int states[MAX_STATES];
 int count;
 } StateSet;
 typedef struct {
 StateSet transitions[MAX_STATES][MAX_SYMBOLS];
 int num_states;
 int num_symbols;
 } NFA;
 typedef struct {
 int transitions[MAX_STATES][MAX_SYMBOLS];
 char state_names[MAX_STATES][MAX_STATE_NAME_LENGTH];
 int num_states;
 int num_symbols;
 } DFA;
NFA nfa;
 DFA dfa;
 void read_nfa_from_file(const char* filename) {
 FILE* file = fopen(filename, "r");
 if (!file) {
 printf("Error opening file.\n");
 exit(1);
 }
 int from, to;
 char symbol;
 nfa.num_states = 0;
 nfa.num_symbols = 0;
 while (fscanf(file, "%d %c %d", &from, &symbol, &to) == 3) {
 int sym_index = symbol- 'a';
 nfa.transitions[from][sym_index].states[nfa.transitions[from][sym_index].count++] = to;
 if (from + 1 > nfa.num_states) nfa.num_states = from + 1;
 if (to + 1 > nfa.num_states) nfa.num_states = to + 1;
 if (sym_index + 1 > nfa.num_symbols) nfa.num_symbols = sym_index + 1;
 }
 fclose(file);
 }
 void print_nfa_table() {
 printf("NFA Transition Table:\n");
 printf(" ");
 for (int i = 0; i < nfa.num_symbols; i++) {
printf("%c
 ", 'a' + i);
 }
 printf("\n");
 for (int i = 0; i < nfa.num_states; i++) {
 printf("%d ", i);
 for (int j = 0; j < nfa.num_symbols; j++) {
 if (nfa.transitions[i][j].count == 0) {
 printf("N
 } else {
 ");
 for (int k = 0; k < nfa.transitions[i][j].count; k++) {
 printf("%d", nfa.transitions[i][j].states[k]);
 }
 printf(" ");
 }
 }
 printf("\n");
 }
 }
 void state_set_to_string(StateSet set, char* buffer) {
 buffer[0] = '\0';
 for (int i = 0; i < set.count; i++) {
 char temp[5];
 sprintf(temp, "%d", set.states[i]);
 strcat(buffer, temp);
 }
 }
 void convert_nfa_to_dfa() {
 StateSet dfa_states[MAX_STATES];
int num_dfa_states = 0;
 // Start with initial state
 dfa_states[num_dfa_states++] = (StateSet){{0}, 1};
 state_set_to_string(dfa_states[0], dfa.state_names[0]);
 for (int i = 0; i < num_dfa_states; i++) {
 for (int j = 0; j < nfa.num_symbols; j++) {
 StateSet new_state = {0};
 for (int k = 0; k < dfa_states[i].count; k++) {
 int state = dfa_states[i].states[k];
 for (int l = 0; l < nfa.transitions[state][j].count; l++) {
 int new_state_elem = nfa.transitions[state][j].states[l];
 if (new_state.count == 0 || new_state.states[new_state.count- 1] !=
 new_state_elem) {
 new_state.states[new_state.count++] = new_state_elem;
 }
 }
 }
 // Sort the new_state
 for (int m = 0; m < new_state.count; m++) {
 for (int n = m + 1; n <new_state.count; n++) {
 if (new_state.states[m] > new_state.states[n]) {
 int temp = new_state.states[m];
 new_state.states[m] = new_state.states[n];
 new_state.states[n] = temp;
 }
 }
 }
// Check if new_state already exists in dfa_states
 int exists =-1;
 for (int k = 0; k < num_dfa_states; k++) {
 if (new_state.count == dfa_states[k].count &&
 memcmp(new_state.states, dfa_states[k].states, new_state.count * sizeof(int)) == 0)
 {
 }
 exists = k;
 break;
 }
 }
 if (exists ==-1 && new_state.count > 0) {
 dfa_states[num_dfa_states] = new_state;
 state_set_to_string(new_state, dfa.state_names[num_dfa_states]);
 dfa.transitions[i][j] = num_dfa_states;
 num_dfa_states++;
 } else if (exists !=-1) {
 dfa.transitions[i][j] = exists;
 } else {
 dfa.transitions[i][j] =-1; // Represent NULL state
 }
 }
 }
 dfa.num_states = num_dfa_states;
 dfa.num_symbols = nfa.num_symbols;
 void print_dfa_table() {
 printf("\nDFA Transition Table:\n");
 printf("
 ");
for (int i = 0; i < dfa.num_symbols; i++) {
 printf("%c
 }
 printf("\n");
 ", 'a' + i);
 for (int i = 0; i < dfa.num_states; i++) {
 printf("%-5s ", dfa.state_names[i]);
 for (int j = 0; j < dfa.num_symbols; j++) {
 if (dfa.transitions[i][j] ==-1) {
 printf("N
 } else {
 ");
 printf("%-5s ", dfa.state_names[dfa.transitions[i][j]]);
 }
 }
 printf("\n");
 }
 }
 int main() {
 const char* input_file = "input.txt";
 read_nfa_from_file(input_file);
 print_nfa_table();
 convert_nfa_to_dfa();
 print_dfa_table();
 return 0;
 }