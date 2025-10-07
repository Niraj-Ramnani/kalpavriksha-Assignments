#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int value_stack[MAX_SIZE];
int val_top = -1;
char operator_stack[MAX_SIZE];
int op_top = -1;

void push_value(int val)
{
    if (val_top >= MAX_SIZE - 1)
        handle_error("Error: Stack Overflow.");
    value_stack[++val_top] = val;
}

int pop_value()
{
    if (val_top < 0)
        handle_error("Error: Invalid expression.");
    return value_stack[val_top--];
}

void push_operator(char op)
{
    if (op_top >= MAX_SIZE - 1)
        handle_error("Error: Stack Overflow.");
    operator_stack[++op_top] = op;
}

char pop_operator()
{
    if (op_top < 0)
        handle_error("Error: Invalid expression.");
    return operator_stack[op_top--];
}

char top_operator()
{
    return operator_stack[op_top];
}

void handle_error(const char *msg)
{
    printf("%s\n", msg);
 
}
