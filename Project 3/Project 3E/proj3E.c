#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 10

typedef enum
{
    ADD,
    MULT,
    SUBTRACT,
    UNSUPPORTED
} MathOperation;

typedef struct
{
    double data[STACK_SIZE];
    int top;
} Stack;


void IssueBadNumberError()
{
    printf("The string does not represent a floating point number.\n");
    exit(EXIT_FAILURE);
}

void IssueBadOperationError()
{
    printf("The string does not represent a valid operation.\n");
    exit(EXIT_FAILURE);
}

MathOperation GetOperation(char *op)
{
    if (op[1] != '\0')
        IssueBadOperationError();

    switch (*op)
    {
        case '+':
            return ADD;
        case 'x':
            return MULT;
        case '-':
            return SUBTRACT;
        default:
            return UNSUPPORTED;
    }
}

double StringToDouble(char *str)
{
    double answer = 0.0;
    int i = 0;
    int decimal = 0;
    int is_neg = 0;
    int places = 0;
    int sub_num = 0;
    if (str[0] == '-')
    {
        i++;
        is_neg = 1;
    }

    while (str[i] != '\0')
    {
        if (str[i] == '-')
        {
            IssueBadNumberError();
        }

        if (str[i] == '.')
        {
            decimal++;
            places = 0;
            i++;
        }

        places++;
        sub_num = str[i] - '0';

        if (sub_num > 9)
        {
            IssueBadNumberError();
        }

        i++;
        answer = (answer + sub_num) * 10;
    }

    if (decimal > 1 || is_neg > 1)
    {
        IssueBadNumberError();
    }

    if (decimal == 1)
    {
        for (int j = 0; j < places; j++)
        {
            answer = answer / 10;
        }
    }
    if (is_neg == 1)
    {
        answer = answer * -1;
    }
    return answer / 10;
}

void InitStack(Stack *s)
{
    s->top = -1;
}

int IsFull(Stack *s)
{
    return s->top == STACK_SIZE - 1;
}

int IsEmpty(Stack *s)
{
    return s->top == -1;
}

void Push(Stack *s, double value)
{
    if (IsFull(s))
    {
        printf("Stack overflow.\n");
        exit(EXIT_FAILURE);
    }
    s->data[++(s->top)] = value;
}

double Pop(Stack *s)
{
    if (IsEmpty(s))
    {
        printf("Stack underflow.\n");
        exit(EXIT_FAILURE);
    }
    return s->data[(s->top)--];
}

int main(int argc, char *argv[])
{
    Stack stack;
    InitStack(&stack);

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] >= '0' && argv[i][0] <= '9' || argv[i][0] == '.')
        {
            double num = StringToDouble(argv[i]);
            Push(&stack, num);
        }
        else
        {
            MathOperation op = GetOperation(argv[i]);
            if (op == UNSUPPORTED)
            {
                IssueBadOperationError();
            }
            if (IsEmpty(&stack))
            {
                printf("Insufficient operands.\n");
                exit(EXIT_FAILURE);
            }
            double b = Pop(&stack);
            if (IsEmpty(&stack))
            {
                printf("Insufficient operands.\n");
                exit(EXIT_FAILURE);
            }
            double a = Pop(&stack);
            double result = 0.0;
            switch (op)
            {
                case ADD:
                    result = a + b;
                    break;
                case MULT:
                    result = a * b;
                    break;
                case SUBTRACT:
                    result = a - b;
                    break;
                default:
                    IssueBadOperationError();
            }
            Push(&stack, result);
        }
    }

    if (IsEmpty(&stack))
    {
        printf("No result to display.\n");
        exit(EXIT_FAILURE);
    }

    double final_result = Pop(&stack);
    if (!IsEmpty(&stack))
    {
        printf("Too many operands.\n");
        exit(EXIT_FAILURE);
    }

    printf("The total is %d\n", (int)final_result);

    return 0;
}

