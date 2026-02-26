#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[30000] = {0};

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // Listen
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        return 1;
    }

    std::cout << "Backend server running on port 8080..." << std::endl;

    while (true) {
        new_socket = accept(server_fd, (struct sockaddr *)&address,
                            (socklen_t*)&addrlen);

        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        read(new_socket, buffer, 30000);

        // Get container hostname
        char hostname[1024];
        gethostname(hostname, sizeof(hostname));

        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n\r\n"
            "Served by: " + std::string(hostname) + "\n";

        send(new_socket, response.c_str(), response.length(), 0);
        close(new_socket);
    }

    return 0;
}
