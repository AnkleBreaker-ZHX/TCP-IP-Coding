#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 35
#define QUE_SIZE 5

char buffer[BUF_SIZE];

const int port = 9190;
const char resp[] = "Accepted!";

void error_handling(const char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    int serv_sock_id = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serv_sock_id == -1) {
        error_handling("socket() error");
    }

    struct sockaddr_in serv_addr_in;
    memset(&serv_addr_in, 0, sizeof(serv_addr_in));
    serv_addr_in.sin_family = AF_INET;
    serv_addr_in.sin_addr.s_addr = INADDR_ANY;
    serv_addr_in.sin_port = htons(port);

    if (bind(serv_sock_id, (struct sockaddr*)&serv_addr_in, sizeof(serv_addr_in)) == -1) {
        error_handling("bind() error");
    }

    if (listen(serv_sock_id, 5) == -1) {
        error_handling("listen() error");
    }

    int clnt_sock_id = 0;
    struct sockaddr_in clnt_addr_in;
    socklen_t clnt_addr_size = sizeof(clnt_addr_in);

    int client_number = 0;
    while (1) {
        int clnt_sock_id = accept(serv_sock_id, (struct sockaddr*)&clnt_addr_in, &clnt_addr_size);
        if (clnt_sock_id == -1) {
            error_handling("accept() error");
        } else {
            printf("Connected client %d\n", ++client_number);
        }

        int str_len = 0;
        while ((str_len = read(clnt_sock_id, buffer, BUF_SIZE)) != 0) {
            buffer[str_len] = 0;
            printf("Accept message from client: %s\n", buffer);
            write(clnt_sock_id, resp, sizeof(resp));
        }

        printf("Client %d disconnected\n", client_number);
        close(clnt_sock_id);
    }

    close(serv_sock_id);
    return 0;
}