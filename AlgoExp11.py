EXP 11: QUAD

 Algorithm for Generating Quadruples from an Arithmetic Expression

1. Initialize Quadruple Table:
   - Create a `QuadrupleTable` structure to store the generated quadruples.
   - Set initial values for `count` (number of quadruples), `capacity`, and `temp_count` (for temporary variable naming).

2. Define Helper Functions:
   - `isOperator(c)`: Check if a character `c` is an arithmetic operator (`+`, `-`, `*`, `/`, `^`).
   - `getPrecedence(op)`: Determine the precedence of an operator (`^` > `*`, `/` > `+`, `-`).
   - `generateTemp()`: Generate a new temporary variable name in the format `t1`, `t2`, etc.
   - `addQuadruple(op, arg1, arg2, result)`: Add a new quadruple entry with the specified operator, arguments, and result.

3. Input Expression:
   - Prompt the user to enter an arithmetic expression.
   - If the user types "quit", exit the loop.

4. Parse Expression and Generate Quadruples:
   - Initialize stacks: `operandStack` to store operands and `operators` to store operators.
   - For each character in the expression: (expr[i] till ‘\0’) 
     - If it's a whitespace, skip it. (isspace())
     - If it’s a number or letter (an operand), accumulate it in a temporary buffer. (operandStack)
     - When an operator is encountered:
       - Push any accumulated operand onto the operand stack.
       - Pop operators from the operator stack (based on precedence) and generate quadruples until the current operator has higher precedence. (operatorStack prec >=)
       - Push the current operator onto the operator stack.
   - After processing all characters:
     - Push any remaining operand.
     - Pop all remaining operators and generate quadruples until the operator stack is empty.

5. Output Quadruples:
   - Display all generated quadruples in a table format.

6. Loop for Additional Expressions:
   - Repeat steps 3–5 until the user enters "quit".

7. Free Memory:
   - Deallocate memory used by the quadruple table. 

 Summary of Key Operations
- Operator Precedence: Handle operators based on precedence to ensure correct evaluation order.
- Temporary Variables: Use temporary variables for intermediate results in the quadruples.
- Quadruple Table: Store and display all generated quadruples in a structured format.

