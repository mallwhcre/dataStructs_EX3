#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// defining the structure for a linkedlist node
typedef struct Node
{
    char data;
    struct Node *next;
} node;

node *st = NULL; // stack to store the phrase
char *phrase;    // phrase to be reversed

// functions for the linked list implementation
node *createNode(char data);
int insertBeforeHead(node **head, char data);
int deleteHead(node **head);

// functions for the stack
int isEmpty(node **stack);
void push(node **stack, char data);
int pop(node **stack);
char peek(node **stack);

// functions for phrase handling
void getPhrase(); //will need to modify  for space handling
void pushToStack(char *phrase, node **stack);
int paliCheck(char *phraseA, char *phraseB);
char *reversePhrase(node **stack);

int main()
{
    st = NULL; // Initialize the stack
    getPhrase();
    pushToStack(phrase, &st);

    char *reversed = reversePhrase(&st);
    if (paliCheck(phrase, reversed) == 0)
    {
        printf("The phrase is a palindrome!\n");
    }
    else
    {
        printf("The phrase is not a palindrome.\n");
    }

    printf("im out");

    // Free allocated memory
    free(reversed);
    free(phrase);
    return 0;
}

node *createNode(char data)
{
    // allocating memory
    node *newNode = (node *)malloc(sizeof(node));

    // if memory allocation is failed
    if (newNode == NULL)
        return NULL;

    // putting data in the node
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int insertBeforeHead(node **head, char data)
{
    node *newNode = createNode(data);
    // check for error
    if (!newNode)
        return -1;

    // if the linked list is empty
    if (*head == NULL)
    {
        *head = newNode;
        return 0;
    }

    newNode->next = *head;
    *head = newNode;

    return 0;
}

int deleteHead(node **head)
{
    node *temp = *head;
    *head = (*head)->next;
    free(temp);

    return 0;
}

// stack
char peek(node **stack)
{
    if (!isEmpty(stack))
        return (*stack)->data;
    else
        exit(1);
}

int isEmpty(node **stack)
{
    return *stack == NULL;
}

void push(node **stack, char data)
{
    insertBeforeHead(stack, data);
}

int pop(node **stack)
{
    if (isEmpty(stack))
    {
        printf("Underflow!");
        return -1;
    }
    deleteHead(stack);
    return 0;
}

// Phrase handling

void getPhrase()
{   
    
    size_t len = 0;
    printf("Input phrase: ");
    getline(&phrase, &len, stdin);

    // Remove the newline character if present
    size_t phraseLen = strlen(phrase);
    if (phrase[phraseLen - 1] == '\n')
    {
        phrase[phraseLen - 1] = '\0';
    }
}

void pushToStack(char *phrase, node **stack)
{
    int i;
    for (i = 0; i < strlen(phrase); i++)
    {
        //    if (phrase[i] == ' ')
        // {
        //    continue; // Skip spaces
        // }
        // else{
        push(stack, phrase[i]);

        //}
    }
}

char *reversePhrase(node **stack)
{
    node *stB = NULL; // Initialize the new stack
    size_t len = strlen(phrase);
    char *phraseB = (char *)malloc((len + 1) * sizeof(phrase)); // Allocate memory for reversed phrase

    if (!phraseB) // iff phraseB is not allocated
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (size_t i = 0; i < len; i++)
    {
        push(&stB, peek(stack));
        phraseB[i] = peek(stack);
        pop(stack);
    }
    phraseB[len] = '\0'; // Null-terminate the string

    return phraseB;
}

int paliCheck(char *phraseA, char *phraseB)
{
    return strcmp(phraseA, phraseB);
}