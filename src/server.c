#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT        8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main(void) {
    int                server_fd;
    int                new_socket;
    struct sockaddr_in address;
    int                opt     = 1;
    int                addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed\n");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Set socket opts\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Failed to bind socket");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Failed to listen socket");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    for (;;) {
        new_socket =
            accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

        printf("New connection from %s:%d\n", inet_ntoa(address.sin_addr),
               ntohs(address.sin_port));

        close(new_socket);
    }

    return 0;
}
