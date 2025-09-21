#include <sys/socket.h>   // socket(), bind(), listen(), accept(), recv(), send()
#include <netinet/in.h>   // sockaddr_in, htons(), htonl(), INADDR_ANY
// #include <arpa/inet.h> // inet_pton() if you want to bind to a specific IP string
#include <unistd.h>       // close()
#include <cstring>        // std::memset
#include <cstdio>         // std::perror (optional error printing)

int main() {
    // create a new socket: IPv4 (AF_INET), TCP (SOCK_STREAM), protocol 0 = default
    int srv_fd = socket(AF_INET, SOCK_STREAM, 0);

    // setsockopt: configure behavior of the socket
    int yes = 1;
    // SOL_SOCKET → "we are setting an option at the socket API level"
    // SO_REUSEADDR → allows re-binding to same port right after restart
    setsockopt(srv_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    // prepare the sockaddr_in struct for binding
    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr)); // clear all fields to 0
    addr.sin_family = AF_INET;           // IPv4
    addr.sin_port   = htons(8080);       // port number 8080 → network byte order
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // INADDR_ANY = 0.0.0.0 (bind to all local interfaces)

    // bind the socket fd to the address (IP+port)
    if (bind(srv_fd, (sockaddr*)&addr, sizeof(addr)) == -1) {
        std::perror("bind"); // print error reason from errno
        return 1;            // exit failure
    }

    // mark socket as passive (listening) with a connection backlog queue
    if (listen(srv_fd, SOMAXCONN) == -1) {
        std::perror("listen");
        return 1;
    }

    // prepare to accept a client connection
    sockaddr_in client;       // will hold client’s address
    socklen_t clen = sizeof(client); // length of client struct
    // accept() blocks until a client connects → returns new fd for that connection
    int cli_fd = accept(srv_fd, (sockaddr*)&client, &clen);

    // create a buffer and read data from client
    char buf[1024];
    // recv: read up to sizeof(buf) bytes into buf
    ssize_t n = recv(cli_fd, buf, sizeof(buf), 0);

    // send back the same bytes (echo)
    send(cli_fd, buf, n, 0);

    // close both the client socket and the listening socket
    close(cli_fd);
    close(srv_fd);

    return 0; // success
}
