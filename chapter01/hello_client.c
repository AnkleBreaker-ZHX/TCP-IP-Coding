#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

char buffer[30];

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    int sock_id = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_id == -1) {
        error_handling("socket() error");
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock_id, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }

    int str_len = read(sock_id, buffer, sizeof(buffer) - 1);
    if (str_len == -1) {
        error_handling("read() error");
    }

    printf("Message from server : %s\n", buffer);
    close(sock_id);
    return 0;
}
