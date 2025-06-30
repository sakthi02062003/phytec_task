#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>

#define MAXLINE 1024

int sockfd;
struct sockaddr_in servaddr;
socklen_t len = sizeof(servaddr);
int running = 1;

void *receive_messages(void *arg) {
    char buffer[MAXLINE];
    int n;

    while (running) {
        n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        if (n > 0) {
            buffer[n] = '\0';
            printf("\nServer: %s\nYou: ", buffer);
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

        sendto(sockfd, message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&servaddr, len);
        if (strcmp(message, "exit") == 0) {
            running = 0;
            break;
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t recv_thread, send_thread;

    if (argc != 3) {
        printf("Usage: %s <Server-IP> <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *server_ip = argv[1];
    int port = atoi(argv[2]);

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(server_ip);

    printf("UDP Chat Client started. Type 'exit' to quit.\n");

    // Start threads
    pthread_create(&recv_thread, NULL, receive_messages, NULL);
    pthread_create(&send_thread, NULL, send_messages, NULL);

    pthread_join(recv_thread, NULL);
    pthread_join(send_thread, NULL);

    close(sockfd);
    printf("Chat ended.\n");
    return 0;
}

