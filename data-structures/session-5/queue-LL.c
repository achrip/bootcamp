#include <stdio.h>
#include <stdlib.h>

// define a node struct to represent each element in the linked list
typedef struct node {
    int data;
    struct node* next;
} node;

// define a queue struct to keep track of the front and back of the queue
typedef struct queue {
    node* front;
    node* back;
} queue;

// initialize a new empty queue
queue* queue_new() {
    queue* q = (queue*) malloc(sizeof(queue));
    q->front = NULL;
    q->back = NULL;
    return q;
}

// check if the queue is empty
int queue_is_empty(queue* q) {
    return q->front == NULL;
}

// add a new element to the back of the queue
void enqueue(queue* q, int data) {
    node* n = (node*) malloc(sizeof(node));
    n->data = data;
    n->next = NULL;

    if (queue_is_empty(q)) {
        q->front = n;
        q->back = n;
    } else {
        q->back->next = n;
        q->back = n;
    }
}

// remove and return the element at the front of the queue
int dequeue(queue* q) {
    if (queue_is_empty(q)) {
        printf("Error: queue is empty!\n");
        return -1;
    }

    node* n = q->front;
    int data = n->data;

    if (q->front == q->back) {
        q->front = NULL;
        q->back = NULL;
    } else {
        q->front = q->front->next;
    }

    free(n);
    return data;  
}

// print the contents of the queue
void queue_print(queue* q) {
    node* n = q->front;
    while (n != NULL) {
        printf("%d ", n->data);
        n = n->next;
    }
    printf("\n");
}

int main() {
    queue* q = queue_new();

    // add some elements to the queue
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);

    // print the contents of the queue
    queue_print(q);  // 1 2 3

    // remove an element from the front of the queue
    int x = dequeue(q);
    printf("dequeued element: %d\n", x);  // dequeued element: 1

    // add a new element to the back of the queue
    enqueue(q, 4);

    // print the contents of the queue again
    queue_print(q);  // 2 3 4

    return 0;
}
