#include <ncurses.h>
#include <stdlib.h>

// define a node struct to represent each element in the linked list
typedef struct Node {
    int value; 
    struct Node* next;
} node; 

// define head object to keep track of the head of the queue
node* head = NULL; 

// initialize a new node 
node* node_new(int value) {
    node* n = (node*) malloc(sizeof(node)); 
    n->value = value; 
    n->next = NULL; 
    return n; 
}

// check if queue is empty
int queue_is_empty() {
    return head == NULL; 
}

// add a new element to the queue
void enqueue(int value) {
    node* new = node_new(value); 

    if (queue_is_empty()) head = new;
    else if (head->value < value) {
        new->next = head; 
        head = new; 
    }
    else {
        node* curr = head;

        // find the correct position for the new node in the queue 
        while (curr->next && curr->next->value > value) {
            curr = curr->next; 
        }

        new->next = curr->next; 
        curr->next = new; 
    }
}

// remove the element at the front of the queue
void dequeue() {
    if (queue_is_empty()) {
        printf("Error: queue is empty!\n"); 
        return; 
    }

    node* n = head; 
    head = head->next; 
    n->next = NULL ; 
    free(n); 
}

// print the contents of the queue
void queue_print() {
    if (queue_is_empty()) {
        printf("Error: queue is empty!\n"); 
        return; 
    }

    node* n = head; 
    printf("Queue:"); 
    while (n) {
        printf(" %d", n->value); 
        n = n->next; 
    }
    puts("");
}

int main() {
    // add some elements to the queue
    enqueue(7);
    enqueue(1);
    enqueue(9);
    enqueue(3);
    enqueue(2);
    enqueue(1);
    enqueue(8);
    enqueue(0);

    // print the contents of the queue
    queue_print(); 

    // dequeue the head of the current queue
    dequeue(1);
    dequeue();
    dequeue();
    dequeue();

    // print the contents of the queue
    queue_print(); 
}