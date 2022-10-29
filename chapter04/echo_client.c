#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 35

char buffer[BUF_SIZE];

const char* IP_ADDR = "127.0.0.1";
const int IP_PORT = 9190;

void error_handling(const char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    int sock_id = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_id == -1) {
        error_handling("socket() error");
    }

    struct sockaddr_in addr_in;
    memset(&addr_in, 0, sizeof(addr_in));
    addr_in.sin_family = AF_INET;
    addr_in.sin_addr.s_addr = inet_addr(IP_ADDR);
    addr_in.sin_port = htons(IP_PORT);

    if (connect(sock_id, (struct sockaddr*)&addr_in, sizeof(addr_in)) == -1) {
        error_handling("connect() error");
    } else {
        puts("Connected!");
    }

    while (~scanf("%s", buffer)) {
        write(sock_id, buffer, strlen(buffer));
        int str_len = read(sock_id, buffer, BUF_SIZE);
        buffer[str_len] = 0;
        printf("Message from server: %s\n", buffer);
    }

    close(sock_id);
    return 0;
}