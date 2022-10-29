#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

char message[] = "Hello World!\n";
char port[] = "9190";

void error_handling(char* msg) {
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
    serv_addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr_in.sin_port = htons(atoi(port));

    if (bind(serv_sock_id, (struct sockaddr*)&serv_addr_in, sizeof(serv_addr_in)) == -1) {
        error_handling("bind() error");
    }

    if (listen(serv_sock_id, 5) == -1) {
        error_handling("listen() error");
    }

    struct sockaddr_in clnt_addr_in;
    socklen_t clnt_addr_size = sizeof(clnt_addr_in);
    int clnt_sock_id = accept(serv_sock_id, (struct sockaddr*)&clnt_addr_in, &clnt_addr_size);
    if (clnt_sock_id == -1) {
        error_handling("accept() error");
    }

    write(clnt_sock_id, message, sizeof(message));
    close(clnt_sock_id);
    close(serv_sock_id);
    return 0;
}