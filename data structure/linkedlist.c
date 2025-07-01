#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node *next;
} __attribute__((packed));

struct Node *head = NULL;

// Initialize the list with the first node
int init(int data) {
    if (head != NULL) {
        printf("List already created\n");
        return -1;
    }

    head = malloc(sizeof(struct Node));
    if (head == NULL) {
        printf("Memory not allocated\n");
        return -2;
    }

    head->data = data;
    head->next = NULL;
    return 0;
}

// Add at the beginning
int add(int data) {
    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("Memory not allocated\n");
        return -2;
    }

    new_node->data = data;
    new_node->next = head;
    head = new_node;
    return 0;
}

// Add at the end
int add_at_end(int data) {
    struct Node *n = malloc(sizeof(struct Node));
    if (n == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    n->data = data;
    n->next = NULL;

    if (head == NULL) {
        head = n;
        return 0;
    }

    struct Node *p;
    for (p = head; p->next != NULL; p = p->next) {
        // Move to the last node
    }

    p->next = n;
    return 0;
}

// Traverse and print the list
int traverse() {
    if (!head) {
        printf("List is empty\n");
        return -1;
    }

    for (struct Node *cur = head; cur != NULL; cur = cur->next) {
        printf("%d --> ", cur->data);
    }
    return 0;
}

// Main function to test
int main() {
    init(100);             
    add(1);
    add(2);
    add_at_end(12);
    add_at_end(13);
    traverse();
    return 0;
}

