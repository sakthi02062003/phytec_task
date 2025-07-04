#include <stdio.h>                          // Includes standard I/O functions like printf and scanf

// Define states
typedef enum {                              // Start definition of an enum to represent possible states
    STATE_IDLE,                              // Represents IDLE state
    STATE_ON,                                // Represents ON state
    STATE_OFF,                               // Represents OFF state
    STATE_EXIT                               // Represents EXIT state (to stop the program)
} State;                                     // Give the enum type a name: State

// Event: user input
char getEvent() {                            // Function to read and return user input
    char event;                              // Declare a variable to store the input character
    printf("\nEnter event (t=toggle, e=exit, x=force OFF): ");  // Prompt user for input
    scanf(" %c", &event);                    // Read a character from user input (space before %c skips whitespaces)
    return event;                            // Return the user-entered character
}

// Handle each state
State handleState(State currentState, char event) {  // Function to handle state transitions based on input event
    if (event == 'x') {                     // If user enters 'x' (force to OFF)
        if (currentState != STATE_EXIT) {    // As long as we’re not already exiting
            printf("Command 'x' received: Force -> OFF\n");  // Inform user
            return STATE_OFF;               // Force transition to OFF state
        }
    }

    switch (currentState) {                 // Switch based on the current state
        case STATE_IDLE:                    // If in IDLE state
            if (event == 't') {              // If user input is 't' (toggle)
                printf("State: IDLE -> ON\n"); // Log transition
                return STATE_ON;             // Go to ON state
            }
            break;                          // End of IDLE case

        case STATE_ON:                      // If in ON state
            if (event == 't') {              // If user input is 't'
                printf("State: ON -> OFF\n"); // Log transition
                return STATE_OFF;            // Go to OFF state
            }
            break;                          // End of ON case

        case STATE_OFF:                     // If in OFF state
            if (event == 't') {              // If user input is 't'
                printf("State: OFF -> ON\n"); // Log transition
                return STATE_ON;             // Go to ON state
            }
            break;                          // End of OFF case
    }

    if (event == 'e') {                     // If user enters 'e' (exit)
        printf("State: -> EXIT\n");          // Log transition
        return STATE_EXIT;                  // Move to EXIT state
    }

    return currentState;                    // No valid input: stay in the same state
}

int main() {                                // Entry point of the program
    State currentState = STATE_IDLE;        // Initialize current state to IDLE
    char event;                             // Variable to hold user command

    printf("Simple State Machine Started\n");  // Print startup message

    while (currentState != STATE_EXIT) {    // Loop until state becomes EXIT
        event = getEvent();                  // Get user input
        currentState = handleState(currentState, event); // Update current state based on event
    }

    printf("State Machine Exited\n");       // Final message after exiting
    return 0;                               // Return success to OS
}

