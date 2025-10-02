#pragma once

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <expected>
#include <fcntl.h>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port number>" << std::endl;
        return 1;
    }

    struct addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;

    struct addrinfo *result = nullptr;
    int rv = getaddrinfo(NULL /* THIS PC */, argv[1] /* port number */, &hint, &result);
    if (rv != 0) {
        std::cerr << "getaddrinfo:" << gai_strerror(rv) << std::endl;
        return 1;
    }
    int fd = -1;
    for (auto* i = result; i != nullptr; i = i->ai_next) {
        fd = socket(i->ai_family, i->ai_socktype, i->ai_protocol);
        if (fd == -1) {
            perror("Error thrown on socket()");
            continue;
        }
        int yes = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)); // enable socket reuse

        if (bind(fd, i->ai_addr, i->ai_addrlen) == -1) {
            perror("Error thrown on bind()");
            close(fd);
            fd = -1;
            continue;
        }

        if (listen(fd, 20) == -1) {
            perror ("Error thrown on listen()");
            close(fd);
            fd = -1;
            continue;
        }

        char host[NI_MAXHOST], serv[NI_MAXSERV];
        if (getnameinfo(i->ai_addr, i->ai_addrlen, host, sizeof(host), serv, sizeof(serv), NI_NUMERICHOST | NI_NUMERICSERV) == 0) {
            std::cout << "Listening on " << host << ":" << serv << "...\n";
        } else {
            std::cout << "Listening on port " << argv[1] << " …\n";
        }

        break;
    }

    freeaddrinfo(result);
    if (fd == -1) {
        std::cerr << "Failed to bind/listen on any address\n";
        return 2;
    }

    while (true) {
        struct sockaddr_storage peer{};
        socklen_t peerlen = sizeof(peer);
        int peer_fd = accept(fd, (struct sockaddr*)&peer, &peerlen);
        if (peer_fd == -1) {
            perror("accept");
            continue;
        }

        int yes = 1;
        setsockopt(peer_fd, SOL_SOCKET, SO_NOSIGPIPE, &yes, sizeof(yes));

        char buffer[1024];
        ssize_t n = recv(peer_fd, buffer, sizeof(buffer), 0);
        if (n > 0) {
            ssize_t sent = 0;
            while (sent < n) {
                ssize_t m = send(peer_fd, buffer + sent, n - sent, 0); // simple echo command
                if (m <= 0) {perror("send"); break;}
                sent += m;
            }
        }

    }

    close(fd);
    return 0;

}
