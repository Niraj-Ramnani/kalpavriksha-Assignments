#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "stack.h"
#define DECIMAL_BASE 10

int getOperatorPrecedence(char op);
void applyOperation();
void handleError(const char *msg);
int buildNumber(const char *input, int *index);
int isOperator(char ch);
void evaluateExpression(const char *input);

int main()
{
    char input[MAX_SIZE];
    printf("Enter the expression \n");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        handleError("Error: Invalid expression.");
    }
    evaluateExpression(input);
    return 0;
}

void evaluateExpression(const char *input)
{
    for (int i = 0; i < strlen(input); i++) {
        if (isspace((unsigned char)input[i])) {
            continue;
        } else if (isdigit((unsigned char)input[i])) {
            int val = buildNumber(input, &i);
            pushValue(val);
        } else if (isOperator(input[i])) {
            while (op_top != -1 && getOperatorPrecedence(topOperator()) >= getOperatorPrecedence(input[i])) {
                applyOperation();
            }
            pushOperator(input[i]);
        } else {
            handleError("Error: Invalid expression.");
        }
    }
    while (op_top != -1) {
        applyOperation();
    }
    if (val_top == 0 && op_top == -1) {
        printf("%d\n", popValue());
    } else {
        handleError("Error: Invalid expression.");
    }
}

int getOperatorPrecedence(char op)
{
    if (op == '*' || op == '/') {
        return 2;
    }
    if (op == '+' || op == '-') {
        return 1;
    }
    return 0;
}

void applyOperation()
{
    int val2 = popValue();
    int val1 = popValue();
    char op = popOperator();
    switch (op) {
    case '+': {
        pushValue(val1 + val2);
        break;
    }
    case '-': {
        pushValue(val1 - val2);
        break;
    }
    case '*': {
        pushValue(val1 * val2);
        break;
    }
    case '/': {
        if (val2 == 0) {
            handleError("Error: Division by zero.");
        }
        pushValue(val1 / val2);
        break;
    }
    }
}

int buildNumber(const char *input, int *index)
{
    int val = 0;
    int i = *index;
    while (i < strlen(input) && isdigit((unsigned char)input[i])) {
        val = val * DECIMAL_BASE + (input[i] - '0');
        i++;
    }
    *index = i - 1;
    return val;
}

int isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
        return 1;
    }
    return 0;
}
