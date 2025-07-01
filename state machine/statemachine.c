#include <stdio.h>

// Define states
typedef enum {
    STATE_IDLE,
    STATE_ON,
    STATE_OFF,
    STATE_EXIT
} State;

// Event: user input
char getEvent() {
    char event;
    printf("\nEnter event (t=toggle, e=exit): ");
    scanf(" %c", &event);
    return event;
}

// Handle each state
State handleState(State currentState, char event) {
    switch (currentState) {
        case STATE_IDLE:
            if (event == 't') {
                printf("State: IDLE -> ON\n");
                return STATE_ON;
            }
            break;
        case STATE_ON:
            if (event == 't') {
                printf("State: ON -> OFF\n");
                return STATE_OFF;
            }
            break;
        case STATE_OFF:
            if (event == 't') {
                printf("State: OFF -> ON\n");
                return STATE_ON;
            }
            break;
    }

    if (event == 'e') {
        printf("State: -> EXIT\n");
        return STATE_EXIT;
    }

    return currentState;  // No state change
}

int main() {
    State currentState = STATE_IDLE;
    char event;

    printf("Simple State Machine Started\n");

    while (currentState != STATE_EXIT) {
        event = getEvent();
        currentState = handleState(currentState, event);
    }

    printf("State Machine Exited\n");
    return 0;
}
