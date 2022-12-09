#include <stdlib.h>
#include <stdbool.h>

// A node in the linked list
struct Node {
  int data;
  struct Node *next;
};

// The stack data structure
struct Stack {
  struct Node *top;
};

// Create a new stack
struct Stack *stack_create() {
  struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
  stack->top = NULL;
  return stack;
}

// Push a new element onto the stack
void stack_push(struct Stack *stack, int data) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->data = data;
  node->next = stack->top;
  stack->top = node;
}

// Pop an element off the stack
int stack_pop(struct Stack *stack) {
  if (stack->top == NULL) {
    // The stack is empty, so we cannot pop any elements
    return -1;
  }

  int data = stack->top->data;
  struct Node *node = stack->top;
  stack->top = stack->top->next;
  free(node);
  return data;
}

// Check if the stack is empty
bool stack_is_empty(struct Stack *stack) {
  return stack->top == NULL;
}

// Free the memory used by the stack
void stack_free(struct Stack *stack) {
  while (stack->top != NULL) {
    stack_pop(stack);
  }
  free(stack);
}
