#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "stack.h"

int getOperatorPrecedence(char op);
void apply_op();
void handle_error(const char *msg);
int build_number(const char *input, int *index);
int is_operator(char ch);

int main()
{
    char input[MAX_SIZE];
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        handle_error("Error: Invalid expression.");
    }
    for (int i = 0; i < strlen(input); i++)
    {
        if (isspace((unsigned char)input[i]))
            continue;
        else if (isdigit((unsigned char)input[i]))
        {
            int val = build_number(input, &i);
            push_value(val);
        }
        else if (is_operator(input[i]))
        {
            while (op_top != -1 && getOperatorPrecedence(top_operator()) >= getOperatorPrecedence(input[i]))
            {
                apply_op();
            }
            push_operator(input[i]);
        }
        else
        {
            handle_error("Error: Invalid expression.");
        }
    }
    while (op_top != -1)
    {
        apply_op();
    }
    if (val_top == 0 && op_top == -1)
        printf("%d\n", pop_value());
    else
        handle_error("Error: Invalid expression.");
    return 0;
}

int getOperatorPrecedence(char op)
{
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

void apply_op()
{
    int val2 = pop_value();
    int val1 = pop_value();
    char op = pop_operator();
    switch (op)
    {
    case '+':
        push_value(val1 + val2);
        break;
    case '-':
        push_value(val1 - val2);
        break;
    case '*':
        push_value(val1 * val2);
        break;
    case '/':
        if (val2 == 0)
            handle_error("Error: Division by zero.");
        push_value(val1 / val2);
        break;
    }
}

int build_number(const char *input, int *index)
{
    int val = 0;
    int i = *index;
    while (i < strlen(input) && isdigit((unsigned char)input[i]))
    {
        val = val * 10 + (input[i] - '0');
        i++;
    }
    *index = i - 1;
    return val;
}

int is_operator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
