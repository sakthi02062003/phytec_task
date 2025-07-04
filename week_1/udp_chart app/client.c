#include <stdio.h>          // For printf(), perror()
#include <stdlib.h>         // For exit(), atoi()
#include <unistd.h>         // For close()
#include <string.h>         // For memset(), strcmp(), strlen()
#include <pthread.h>        // For POSIX threads
#include <arpa/inet.h>      // For sockaddr_in, inet_addr, htons

#define MAXLINE 1024        // Maximum message length

int sockfd;                         // UDP socket file descriptor
struct sockaddr_in servaddr;        // Server address
socklen_t len = sizeof(servaddr);   // Length of server address
int running = 1;                    // Chat loop control flag

// Thread to receive messages from the server
void *receive_messages(void *arg) {
    char buffer[MAXLINE];           // Buffer to store incoming message
    int n;

    while (running) {
        // Receive data from server (blocking)
        n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL,
                     (struct sockaddr *)&servaddr, &len);

        if (n > 0) {
            buffer[n] = '\0';       // Null-terminate received message
            printf("\nServer: %s\nYou: ", buffer);  // Print server response
            fflush(stdout);         // Flush prompt immediately

            // If "exit" received, stop chat
            if (strcmp(buffer, "exit") == 0) {
                running = 0;
                break;
            }
        }
    }
    return NULL;
}

// Thread to send messages to the server
void *send_messages(void *arg) {
    char message[MAXLINE];          // Buffer for user input

    while (running) {
        printf("You: ");
        fgets(message, MAXLINE, stdin);                // Read input from user
        message[strcspn(message, "\n")] = '\0';         // Remove newline

        // Send message to server
        sendto(sockfd, message, strlen(message), MSG_CONFIRM,
               (const struct sockaddr *)&servaddr, len);

        // Exit chat if message is "exit"
        if (strcmp(message, "exit") == 0) {
            running = 0;
            break;
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t recv_thread, send_thread;  // Thread IDs

    // Check if IP and Port are provided
    if (argc != 3) {
        printf("Usage: %s <Server-IP> <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Parse IP and port from command line
    char *server_ip = argv[1];     // e.g., 127.0.0.1
    int port = atoi(argv[2]);      // Convert port to integer

    // Step 1: Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Setup server address struct
    memset(&servaddr, 0, sizeof(servaddr));      // Zero out
    servaddr.sin_family = AF_INET;               // IPv4
    servaddr.sin_port = htons(port);             // Convert to network byte order
    servaddr.sin_addr.s_addr = inet_addr(server_ip);  // Convert IP string to binary

    printf("UDP Chat Client started. Type 'exit' to quit.\n");

    // Step 3: Create send and receive threads
    pthread_create(&recv_thread, NULL, receive_messages, NULL);
    pthread_create(&send_thread, NULL, send_messages, NULL);

    // Step 4: Wait for both threads to complete
    pthread_join(recv_thread, NULL);
    pthread_join(send_thread, NULL);

    // Step 5: Cleanup
    close(sockfd);          // Close socket
    printf("Chat ended.\n");
    return 0;
}

