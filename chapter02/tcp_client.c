#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 35

const char* IP_ADDR = "127.0.0.1";
const int IP_PORT = 9190;

char buffer[BUF_SIZE];

void error_handling(char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    int sock_id = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_id == -1) {
        error_handling("socket() error");
    }

    struct sockaddr_in sock_addr;
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
    sock_addr.sin_port = htons(IP_PORT);

    if (connect(sock_id, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) == -1) {
        error_handling("connect() error");
    }

    int pos = -1, read_len = 0, str_len = 0;
    while (read_len = read(sock_id, &buffer[++pos], 1)) {
        if (read_len == -1) {
            error_handling("read() error");
        }
        str_len += read_len;
    }

    printf("Message from server: %s", buffer);
    printf("Function read call count: %d\n", str_len);

    close(sock_id);
    return 0;
}