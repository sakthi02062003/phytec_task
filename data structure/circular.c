#include <stdio.h>
#include <stdbool.h>

#define SIZE 5  // buffer capacity

// Circular buffer structure
struct CircularBuffer {
    int buffer[SIZE];
    int head;     // write position
    int tail;     // read position
    int count;    // number of elements in buffer
};

// Initialize buffer
void initBuffer(struct CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// Check if buffer is full
bool isFull(struct CircularBuffer *cb) {
    return cb->count == SIZE;
}

// Check if buffer is empty
bool isEmpty(struct CircularBuffer *cb) {
    return cb->count == 0;
}

// Add element to buffer
bool enqueue(struct CircularBuffer *cb, int data) {
    if (isFull(cb)) {
        printf("Buffer is full! Cannot enqueue %d\n", data);
        return false;
    }
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % SIZE;
    cb->count++;
    return true;
}

// Remove element from buffer
bool dequeue(struct CircularBuffer *cb, int *data) {
    if (isEmpty(cb)) {
        printf("Buffer is empty! Cannot dequeue.\n");
        return false;
    }
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count--;
    return true;
}

// Display buffer contents
void printBuffer(struct CircularBuffer *cb) {
    printf("Buffer: ");
    for (int i = 0; i < cb->count; i++) {
        int index = (cb->tail + i) % SIZE;
        printf("%d ", cb->buffer[index]);
    }
    printf("\n");
}

// Main function to demonstrate usage
int main() {
    struct CircularBuffer cb;
    initBuffer(&cb);

    enqueue(&cb, 10);
    enqueue(&cb, 20);
    enqueue(&cb, 30);
    enqueue(&cb, 40);
    enqueue(&cb, 50); // buffer full here
    enqueue(&cb, 60); // won't be added

    printBuffer(&cb);

    int val;
    dequeue(&cb, &val);
    printf("Dequeued: %d\n", val);
    dequeue(&cb, &val);
    printf("Dequeued: %d\n", val);

    printBuffer(&cb);

    enqueue(&cb, 60);
    enqueue(&cb, 70);

    printBuffer(&cb);

    return 0;
}

