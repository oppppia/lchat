#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define PORT      8081

int main(void) {
    int                sock = 0;
    struct sockaddr_in server_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Failed to create socket\n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(PORT);

    // fix: convert IP
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        printf("Invalid address\n");
        return -1;
    }

    // fix: connect client
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) <
        0) {
        printf("Failed to connect socket\n");
        return -1;
    }

    close(sock);

    return 0;
}
