#include <stdio.h>                          // Standard I/O functions (printf, etc.)
#include <stdlib.h>                         // For malloc and free
#include <string.h>                         // (Not used in this code, can be removed)

// Define the Node structure
struct Node {
    int data;                               // Data stored in the node
    struct Node *next;                      // Pointer to the next node
} __attribute__((packed));                  // Avoid padding bytes (optional, used for memory optimization)

// Head pointer (global) pointing to the first node in the list
struct Node *head = NULL;                   // Initialize linked list head to NULL

// Initialize the list with a single node
int init(int data) {
    if (head != NULL) {                     // Check if the list already exists
        printf("List already created\n");
        return -1;                          // List already initialized
    }

    head = malloc(sizeof(struct Node));     // Allocate memory for the first node
    if (head == NULL) {                     // Check if allocation failed
        printf("Memory not allocated\n");
        return -2;
    }

    head->data = data;                      // Assign data to the first node
    head->next = NULL;                      // Set next to NULL (end of list)
    return 0;                               // Success
}

// Add a node at the beginning
int add(int data) {
    struct Node *new_node = malloc(sizeof(struct Node)); // Allocate memory
    if (new_node == NULL) {
        printf("Memory not allocated\n");
        return -2;
    }

    new_node->data = data;                  // Assign data
    new_node->next = head;                  // Link new node to current head
    head = new_node;                        // Update head to point to new node
    return 0;
}

// Add a node at the end
int add_at_end(int data) {
    struct Node *n = malloc(sizeof(struct Node));  // Allocate memory
    if (n == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    n->data = data;                          // Assign data
    n->next = NULL;                          // This will be the last node

    if (head == NULL) {                      // If list is empty, assign as head
        head = n;
        return 0;
    }

    struct Node *p;
    for (p = head; p->next != NULL; p = p->next) {
        // Traverse to the last node
    }

    p->next = n;                             // Link last node to new node
    return 0;
}

// Traverse and print the list
int traverse() {
    if (!head) {                             // Check if list is empty
        printf("List is empty\n");
        return -1;
    }

    for (struct Node *cur = head; cur != NULL; cur = cur->next) {
        printf("%d --> ", cur->data);        // Print data of each node
    }
    return 0;
}

// Main function to test the linked list
int main() {
    init(100);             // Initialize list with first node (100)
    add(1);                // Add 1 at the beginning
    add(2);                // Add 2 at the beginning
    add_at_end(12);        // Add 12 at the end
    add_at_end(13);        // Add 13 at the end
    traverse();            // Print the list
    return 0;
}

