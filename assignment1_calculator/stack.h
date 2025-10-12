#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 100

void handleError(const char *msg);
void pushValue(int val);
int popValue();
void pushOperator(char op);
char popOperator();
char topOperator();

extern int value_stack[MAX_SIZE];
extern int val_top;
extern char operator_stack[MAX_SIZE];
extern int op_top;

#endif
