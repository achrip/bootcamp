#include <stdio.h>
#include <stdlib.h>

// define a node struct to represent each element in the linked list
typedef struct node {
    int data;
    struct node* next;
} node;

// define a stack struct to keep track of the top of the stack
typedef struct stack {
    node* top;
} stack;

// initialize a new empty stack
stack* stack_new() {
    stack* s = (stack*) malloc(sizeof(stack));
    s->top = NULL;
    return s;
}

// check if the stack is empty
int stack_is_empty(stack* s) {
    return s->top == NULL;
}

// push a new element onto the top of the stack
void push(stack* s, int data) {
    node* n = (node*) malloc(sizeof(node));
    n->data = data;
    n->next = s->top;
    s->top = n;
}

// pop and return the element at the top of the stack
int pop(stack* s) {
    if (stack_is_empty(s)) {
        printf("Error: stack is empty!\n");
        return -1;
    }

    node* n = s->top;
    int data = n->data;
    s->top = s->top->next;
    free(n);
    return data;
}

// print the contents of the stack
void stack_print(stack* s) {
    node* n = s->top;
    while (n != NULL) {
        printf("%d ", n->data);
        n = n->next;
    }
    printf("\n");
}

int main() {
    stack* s = stack_new();
    
    // push some elements onto the stack
    push(s, 1);
    push(s, 2);
    push(s, 3);

    // print the contents of the stack
    stack_print(s);  // 3 2 1

    // pop an element from the top of the stack
    int x = pop(s);
    printf("popped element: %d\n", x);  // popped element: 3

    // push a new element onto the top of the stack
    push(s, 4);

    // print the contents of the stack again
    stack_print(s);  // 4 2 1

    return 0;
}
