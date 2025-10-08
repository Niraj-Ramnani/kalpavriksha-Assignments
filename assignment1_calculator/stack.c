#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int value_stack[MAX_SIZE];
int val_top = -1;
char operator_stack[MAX_SIZE];
int op_top = -1;

void pushValue(int val)
{
    if (val_top >= MAX_SIZE - 1)
        handleError("Error: Stack Overflow.");
    value_stack[++val_top] = val;
}

int popValue()
{
    if (val_top < 0)
        handleError("Error: Invalid expression.");
    return value_stack[val_top--];
}

void pushOperator(char op)
{
    if (op_top >= MAX_SIZE - 1)
        handleError("Error: Stack Overflow.");
    operator_stack[++op_top] = op;
}

char popOperator()
{
    if (op_top < 0)
        handleError("Error: Invalid expression.");
    return operator_stack[op_top--];
}

char topOperator()
{
    return operator_stack[op_top];
}

void handleError(const char *msg)
{
    printf("%s\n", msg);
   
}
