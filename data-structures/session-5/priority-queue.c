#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// The priority queue data structure
typedef struct priority_queue {
  int data[MAX_SIZE];
  int size;
} priority_queue;

// Initialize an empty priority queue
void init(priority_queue *q) {
  q->size = 0;
}

// Check if the priority queue is empty
int is_empty(priority_queue *q) {
  return q->size == 0;
}

// Insert an element into the priority queue
void insert(priority_queue *q, int item) {
  int i;
  if (q->size == MAX_SIZE) {
    printf("Error: priority queue is full!\n");
    return;
  }

  // Find the correct position for the new element
  for (i = q->size; i > 0 && q->data[i-1] > item; i--) {
    q->data[i] = q->data[i-1];
  }

  // Insert the new element
  q->data[i] = item;
  q->size++;
}

// Remove the top element from the priority queue
int remove_top(priority_queue *q) {
  if (is_empty(q)) {
    printf("Error: cannot remove item from empty queue!\n");
    return -1;
  }

  int top = q->data[0];

  // Shift all elements down
  int i;
  for (i = 1; i < q->size; i++) {
    q->data[i-1] = q->data[i];
  }
  q->size--;

  return top;
}

int main() {
  priority_queue q;
  init(&q);

  // Insert some elements into the queue
  insert(&q, 5);
  insert(&q, 3);
  insert(&q, 9);
  insert(&q, 1);

  // Remove the top element from the queue
  printf("%d\n", remove_top(&q));  // should print 1

  return 0;
}
