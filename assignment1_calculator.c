#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SIZE 100

int value_stack[MAX_SIZE];
int val_top = -1;

char operator_stack[MAX_SIZE];
int op_top = -1;

void push_value(int val);
int pop_value();
void push_operator(char op);
char pop_operator();
char top_operator();
int precedence(char op);
void apply_op();
void handle_error(const char *msg);

int main()
{
     char input[MAX_SIZE];
     if (fgets(input, sizeof(input), stdin) == NULL)
     {
          handle_error("Error: Invalid expression.");
     }
     for (int i = 0; i < strlen(input); i++)
     {
          if (isspace(input[i]))
               continue;

          else if (isdigit(input[i]))
          {
               int val = 0;
               while (i < strlen(input) && isdigit(input[i]))
               {
                    val = val * 10 + (input[i] - '0');
                    i++;
               }
               push_value(val);
               i--;
          }

          else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
          {
               while (op_top != -1 && precedence(top_operator()) >= precedence(input[i]))
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

int precedence(char op)
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

void handle_error(const char *msg)
{
     printf("%s\n", msg);
     exit(0);
}