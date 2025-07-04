#include <stdio.h>          // For printf(), perror()
#include <stdlib.h>         // For exit()
#include <unistd.h>         // For close()
#include <string.h>         // For memset(), strcmp(), strlen()
#include <pthread.h>        // For threads
#include <arpa/inet.h>      // For socket structures

#define PORT 8081           // Port number for the server
#define MAXLINE 1024        // Max buffer size

int sockfd;                         // UDP socket file descriptor
struct sockaddr_in servaddr, cliaddr; // Server and client address structures
socklen_t len = sizeof(cliaddr);    // Length of client address
int running = 1;                    // Global flag to control chat loop

// Thread function to receive messages
void *receive_messages(void *arg) {
    char buffer[MAXLINE];           // Buffer to hold received messages
    int n;

    while (running) {
        // Wait for a message from any client
        n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, 
                     (struct sockaddr *)&cliaddr, &len);

        if (n > 0) {
            buffer[n] = '\0';       // Null-terminate received string
            printf("\nClient: %s\nYou: ", buffer);
            fflush(stdout);         // Ensure "You:" prompt prints immediately

            // If client sends "exit", stop communication
            if (strcmp(buffer, "exit") == 0) {
                running = 0;
                break;
            }
        }
    }
    return NULL;
}

// Thread function to send messages
void *send_messages(void *arg) {
    char message[MAXLINE];          // Buffer for outgoing message

    while (running) {
        printf("You: ");
        fgets(message, MAXLINE, stdin);                        // Read from stdin
        message[strcspn(message, "\n")] = '\0';                // Remove newline

        // Send message to client
        sendto(sockfd, message, strlen(message), MSG_CONFIRM, 
               (struct sockaddr *)&cliaddr, len);

        // If "exit" is typed, stop communication
        if (strcmp(message, "exit") == 0) {
            running = 0;
            break;
        }
    }
    return NULL;
}

int main() {
    pthread_t recv_thread, send_thread; // Thread IDs

    // Step 1: Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Clear server and client address structures
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Step 3: Configure server settings
    servaddr.sin_family = AF_INET;         // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY; // Accept any incoming IP
    servaddr.sin_port = htons(PORT);       // Set port (convert to network byte order)

    // Step 4: Bind the socket to IP/port
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UDP Chat Server running on port %d...\n", PORT);

    // Step 5: Create receiving and sending threads
    pthread_create(&recv_thread, NULL, receive_messages, NULL);
    pthread_create(&send_thread, NULL, send_messages, NULL);

    // Step 6: Wait for threads to finish (i.e., chat ends)
    pthread_join(recv_thread, NULL);
    pthread_join(send_thread, NULL);

    // Step 7: Close socket and clean up
    close(sockfd);
    printf("Chat ended.\n");

    return 0;
}

