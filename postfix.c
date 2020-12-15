#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack1
{
    int top;
    int size;
    char *a;
};

int stackTop(struct stack1 *s)
{
    return s->a[s->top];
}

int isEmpty(struct stack1 *s)
{
    if (s->top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isFull(struct stack1 *s)
{
    if (s->top == s->size - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(struct stack1 *s, int v)
{
    if (isFull(s))
    {
        printf("stack is overflow!");
    }
    else
    {
        s->top++;
        s->a[s->top] = v;
        // printf("value inserted\n");
    }
}

char pop(struct stack1 *s)
{
    if (isEmpty(s))
    {
        printf("stack is underflow!");
    }
    else
    {
        int gv;
        gv = s->a[s->top];
        s->top--;
        // printf("value deleted was %d", gv);
        return gv;
    }
}

int precedence(char ch)
{
    if (ch == '*' || ch == '/')
    {
        return 3;
    }
    else if (ch == '+' || ch == '-')
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

int isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char *infixtopostfix(char *infix)
{
    struct stack1 *s = (struct stack1 *)malloc(sizeof(struct stack1));
    s->top = -1;
    s->size = 100;
    s->a = (char *)malloc(s->size * sizeof(char));
    char *postfix = (char *)malloc((strlen(infix) + 1) * sizeof(char));
    int i = 0;
    int j = 0;
    while (infix[i] != '\0')
    {
        if (!isOperator(infix[i]))
        {
            postfix[j] = infix[i];
            j++;
            i++;
        }
        else
        {
            if (precedence(infix[i]) > precedence(stackTop(s)))
            {
                push(s, infix[i]);
                i++;
            }
            else
            {
                postfix[j] = pop(s);
                j++;
            }
        }
    }

    while (!isEmpty(s))
    {
        postfix[j] = pop(s);
        j++;
    }
    postfix[j] = '\0';

    return postfix;
}

void main()
{
    char *infix = "a+b"; //put your equation here
    printf("postfix: %s", infixtopostfix(infix));
}