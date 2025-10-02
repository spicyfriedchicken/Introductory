#include <sys/socket.h>   // socket(), connect(), send(), recv()
#include <netinet/in.h>   // sockaddr_in, htons()
#include <arpa/inet.h>    // inet_pton() to convert string IP → binary
#include <unistd.h>       // close()
#include <cstring>        // std::memset
#include <cstdio>         // std::perror

int main() {
    // create a socket: IPv4 + TCP
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) { std::perror("socket"); return 1; }

    // prepare the server address we want to connect to
    sockaddr_in srv;
    std::memset(&srv, 0, sizeof(srv));
    srv.sin_family = AF_INET;          // IPv4
    srv.sin_port   = htons(8080);      // port 8080 → network byte order
    // convert string "127.0.0.1" → binary IP and store into sin_addr
    if (inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr) <= 0) {
        std::perror("inet_pton");
        return 1;
    }

    // connect() to the server at IP:port
    if (connect(fd, (sockaddr*)&srv, sizeof(srv)) == -1) {
        std::perror("connect");
        return 1;
    }

    // send a message to the server
    const char* msg = "Hello from client";
    ssize_t n = send(fd, msg, std::strlen(msg), 0);
    if (n == -1) { std::perror("send"); return 1; }

    // receive response (echo back)
    char buf[1024];
    ssize_t m = recv(fd, buf, sizeof(buf), 0);
    if (m == -1) { std::perror("recv"); return 1; }

    // print what we got
    write(STDOUT_FILENO, buf, m);  // write to stdout directly

    // close the socket
    close(fd);
    return 0;
}
