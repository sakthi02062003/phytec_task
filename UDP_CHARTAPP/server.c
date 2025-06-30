#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8081
#define MAXLINE 1024

int sockfd;
struct sockaddr_in servaddr, cliaddr;
socklen_t len = sizeof(cliaddr);
int running = 1;

void *receive_messages(void *arg) {
    char buffer[MAXLINE];
    int n;

    while (running) {
        n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        if (n > 0) {
            buffer[n] = '\0';
            printf("\nClient: %s\nYou: ", buffer);
            fflush(stdout);
            if (strcmp(buffer, "exit") == 0) {
                running = 0;
                break;
            }
        }
    }
    return NULL;
}

void *send_messages(void *arg) {
    char message[MAXLINE];

    while (running) {
        printf("You: ");
        fgets(message, MAXLINE, stdin);
        message[strcspn(message, "\n")] = '\0'; // remove newline

        sendto(sockfd, message, strlen(message), MSG_CONFIRM, (struct sockaddr *)&cliaddr, len);
        if (strcmp(message, "exit") == 0) {
            running = 0;
            break;
        }
    }
    return NULL;
}

int main() {
    pthread_t recv_thread, send_thread;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UDP Chat Server running on port %d...\n", PORT);

    // Start threads
    pthread_create(&recv_thread, NULL, receive_messages, NULL);
    pthread_create(&send_thread, NULL, send_messages, NULL);

    pthread_join(recv_thread, NULL);
    pthread_join(send_thread, NULL);

    close(sockfd);
    printf("Chat ended.\n");
    return 0;
}

