#define _CRT_SECURE_NO_WARNINGS
#define POSTFIX_ERROR (-2)
#define SUCCESS (0)
#define EMPTYSTACK (-3)
#define FILE_DIDNT_OPEN_ERROR (-1)

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct Stack;
typedef struct Stack* Position;
typedef struct Stack {
    double number;
    Position next;
} Stack;


void purple()
{

    printf("\033[0;35m");
}

void cyan()
{
    printf("\033[0;36m");
}


void white()
{
    printf("\033[0;37m");
}

int Postfiks(char*, double*);
int Print(Position);

int main() {
    double result = 0;

    PostfixResult("postfiks.txt", &result);
    purple();
    printf("\n RESULT:%.1lf\n", result);
    white();
    return EXIT_SUCCESS;
}

Position newElement(double number) {
    Position element = NULL;

    element = (Position)malloc(sizeof(Stack));
    if (!element) {
        perror("\nMemory allocation error!");
        return element;
    }

    element->number = number;
    element->next = NULL;

    return element;
}

int readFromFile(char* filename)
{
    FILE* file = NULL;
    int size = 0;
    char* buffer = NULL;

    file = fopen(filename, "r");
    if (!file) {
        printf("\nFile does not exist.");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);

    buffer = (char*)calloc(size + 1, sizeof(char));
    if (!buffer) {
        perror("\nMemory allocation error!");
        return NULL;
    }

    rewind(file);
    fread(buffer, sizeof(char), size, file);
    printf("|%s|\n", buffer);
    fclose(file);

    return buffer;
}

int Postfiks(char* buffer, double* result)
{
    Stack head = { .number = 0, .next = NULL };
    char* currentBuffer = buffer;
    char operation = 0;
    double number = 0.0;
    int status = 0, bytes = 0;
    Position element = NULL;

    while (strlen(currentBuffer) > 0) {
        status = sscanf(currentBuffer, " %lf %n", &number, &bytes);
        if (status != 1) {
            sscanf(currentBuffer, " %c %n", &operation, &bytes);
            status = Operation(&head, operation, result);

            if (status != EXIT_SUCCESS) {
                return POSTFIX_ERROR;
            }

            number = *result;
        }

        element = newElement(number);
        if (!element) {
            return -1;
        }

        currentBuffer += bytes;
        printf("|%s|", currentBuffer);
        purple();
        printf("  =>  ");
        white();
        insertAfter(&head, element);
    }

    return Result(&head, result);
}

int Print(Position first)
{
    Position temp = first;

    while (temp)
    {
        cyan();
        printf("%.0lf,", temp->number);
        white();
        temp = temp->next;
    }
    printf("\n");

    return 0;
}

int insertAfter(Position head, Position element)
{
    element->next = head->next;
    head->next = element;

    Print(head->next);

    return SUCCESS;
}


int Operation(Position head, char operation, double* result) {
    double operand1 = 0;
    double operand2 = 0;
    int status1 = 0;
    int status2 = 0;

    status1 = Pop(head, &operand1);
    if (status1 != 0) {
        return POSTFIX_ERROR;
    }

    status2 = Pop(head, &operand2);
    if (status2 != 0) {
        return POSTFIX_ERROR;
    }

    switch (operation)
    {
    case '+':
        *result = operand2 + operand1;
        break;
    case '-':
        *result = operand2 - operand1;
        break;
    case '*':
        *result = operand2 * operand1;
        break;
    case '/':
        *result = operand2 / operand1;
        break;
    default:
        printf("\nIncorrect postfix operand.", operation);
        return EXIT_FAILURE;
    }

    return SUCCESS;

}


int Pop(Position head, double* result) {
    Position delete = NULL;

    delete = head->next;
    if (!delete) {
        perror("\nThe stack is empty!.");
        return EMPTYSTACK;
    }

    head->next = delete->next;
    *result = delete->number;
    free(delete);

    return SUCCESS;
}


int Result(Position head, double* result)
{
    int status = 0;

    status = Pop(head, result);

    if (status != 0) {
        return status;
    }
    if (head->next) {
        printf("\nIncorrect postfix.");
        return POSTFIX_ERROR;
    }
}


int PostfixResult(char* file, double* result) {
    char* buffer = NULL;
    int status = 0;

    buffer = readFromFile(file);
    if (buffer == NULL) {
        return FILE_DIDNT_OPEN_ERROR;
    }
    status = Postfiks(buffer, result);
    if (status != EXIT_SUCCESS) {
        return POSTFIX_ERROR;
    }

    return SUCCESS;
}