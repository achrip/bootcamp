#include <stdlib.h>
#include <stdbool.h>

// A node in the linked list
struct Node {
  int data;
  struct Node *next;
};

// The queue data structure
struct Queue {
  struct Node *front;
  struct Node *rear;
};

// Create a new queue
struct Queue *queue_create() {
  struct Queue *queue = malloc(sizeof(struct Queue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

// Enqueue a new element onto the queue
void queue_enqueue(struct Queue *queue, int data) {
  struct Node *node = malloc(sizeof(struct Node));
  node->data = data;
  node->next = NULL;
  if (queue->rear == NULL) {
    // The queue is empty, so the new node is the front and rear
    queue->front = node;
    queue->rear = node;
  } else {
    // Add the new node to the end of the queue
    queue->rear->next = node;
    queue->rear = node;
  }
}

// Dequeue an element from the queue
int queue_dequeue(struct Queue *queue) {
  if (queue->front == NULL) {
    // The queue is empty, so we cannot dequeue any elements
    return -1;
  }

  int data = queue->front->data;
  struct Node *node = queue->front;
  queue->front = queue->front->next;
  if (queue->front == NULL) {
    // The queue is now empty, so the rear should also be NULL
    queue->rear = NULL;
  }
  free(node);
  return data;
}

// Check if the queue is empty
bool queue_is_empty(struct Queue *queue) {
  return queue->front == NULL;
}

// Free the memory used by the queue
void queue_free(struct Queue *queue) {
  while (queue->front != NULL) {
    queue_dequeue(queue);
  }
  free(queue);
}
