#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 100

void push_value(int val);
int pop_value();
void push_operator(char op);
char pop_operator();
char top_operator();

extern int value_stack[MAX_SIZE];
extern int val_top;
extern char operator_stack[MAX_SIZE];
extern int op_top;

#endif
