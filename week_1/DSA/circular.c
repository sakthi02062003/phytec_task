#include <stdio.h>          // For printf()
#include <stdbool.h>        // For using bool, true, false

#define SIZE 5              // Define the size of the circular buffer

// Define the circular buffer structure
struct CircularBuffer {
    int buffer[SIZE];       // Array to store buffer data
    int head;               // Write index
    int tail;               // Read index
    int count;              // Number of elements currently in buffer
};

// Initialize the buffer
void initBuffer(struct CircularBuffer *cb) {
    cb->head = 0;           // Start writing from index 0
    cb->tail = 0;           // Start reading from index 0
    cb->count = 0;          // Initially, buffer is empty
}

// Check if buffer is full
bool isFull(struct CircularBuffer *cb) {
    return cb->count == SIZE;   // Full when count equals max size
}

// Check if buffer is empty
bool isEmpty(struct CircularBuffer *cb) {
    return cb->count == 0;      // Empty when count is 0
}

// Add data to the buffer
bool enqueue(struct CircularBuffer *cb, int data) {
    if (isFull(cb)) {   // Can't add if full
        printf("Buffer is full! Cannot enqueue %d\n", data);
        return false;
    }
    cb->buffer[cb->head] = data;             // Insert data at head index
    cb->head = (cb->head + 1) % SIZE;        // Move head forward circularly
    cb->count++;                             // Increment count
    return true;
}

// Remove data from the buffer
bool dequeue(struct CircularBuffer *cb, int *data) {
    if (isEmpty(cb)) {   // Can't remove if empty
        printf("Buffer is empty! Cannot dequeue.\n");
        return false;
    }
    *data = cb->buffer[cb->tail];            // Read from tail index
    cb->tail = (cb->tail + 1) % SIZE;        // Move tail forward circularly
    cb->count--;                             // Decrement count
    return true;
}

// Print contents of the buffer
void printBuffer(struct CircularBuffer *cb) {
    printf("Buffer: ");
    for (int i = 0; i < cb->count; i++) {
        int index = (cb->tail + i) % SIZE;   // Circular index calculation
        printf("%d ", cb->buffer[index]);    // Print each element
    }
    printf("\n");
}

// Main function to test circular buffer
int main() {
    struct CircularBuffer cb;
    initBuffer(&cb);                         // Step 1: Initialize

    enqueue(&cb, 10);                        // Step 2: Enqueue 10
    enqueue(&cb, 20);                        // Enqueue 20
    enqueue(&cb, 30);                        // Enqueue 30
    enqueue(&cb, 40);                        // Enqueue 40
    enqueue(&cb, 50);                        // Enqueue 50 (Buffer full now)
    enqueue(&cb, 60);                        // Will fail (overflow)

    printBuffer(&cb);                        // Output current buffer

    int val;
    dequeue(&cb, &val);                      // Dequeue 10
    printf("Dequeued: %d\n", val);
    dequeue(&cb, &val);                      // Dequeue 20
    printf("Dequeued: %d\n", val);

    printBuffer(&cb);                        // Print after two dequeues

    enqueue(&cb, 60);                        // Should succeed
    enqueue(&cb, 70);                        // Should succeed

    printBuffer(&cb);                        // Final state: 30 40 50 60 70

    return 0;                                // End of program
}

