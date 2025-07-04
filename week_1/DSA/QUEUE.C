#include <stdio.h>          // For printf()

#define SIZE 5              // Define the maximum size of the queue

int queue[SIZE];            // The queue array
int front = -1, rear = -1;  // Front and rear pointers for tracking the queue

// Function to add an element to the queue (Enqueue)
void enqueue(int value) {
    if (rear == SIZE - 1) { // If rear reaches the last index, queue is full
        printf("Queue is full (Overflow)\n");
        return;
    }
    if (front == -1) front = 0; // If this is the first element, initialize front
    rear++;                     // Move rear forward
    queue[rear] = value;        // Add the value at the new rear position
    printf("%d enqueued to queue\n", value);
}

// Function to remove an element from the queue (Dequeue)
void dequeue() {
    if (front == -1 || front > rear) {  // Check if queue is empty
        printf("Queue is empty (Underflow)\n");
        return;
    }
    printf("%d dequeued from queue\n", queue[front]); // Print and remove the front element
    front++; // Move front forward
}

// Function to view the front element without removing it (Peek)
void peek() {
    if (front == -1 || front > rear) {  // Check if queue is empty
        printf("Queue is empty\n");
        return;
    }
    printf("Front element is %d\n", queue[front]); // Show the front element
}

// Function to display all elements of the queue
void display() {
    if (front == -1 || front > rear) {  // Check if queue is empty
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    for (int i = front; i <= rear; i++) { // Loop from front to rear
        printf("%d ", queue[i]);
    }
    printf("\n");
}

// Main function to test queue operations
int main() {
    enqueue(10);   // Add 10 to queue
    enqueue(20);   // Add 20 to queue
    enqueue(30);   // Add 30 to queue
    display();     // Show the queue

    dequeue();     // Remove one element (10)
    display();     // Show queue after dequeue

    peek();        // Show front element (20)

    return 0;      // End program
}

