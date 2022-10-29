#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 35

const char* FILE_NAME = "data.txt";
char buffer[BUF_SIZE];

void error_handling(char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]) {
    int fd = open(FILE_NAME, O_CREAT | O_RDWR | O_APPEND);
    if (fd == -1) {
        error_handling("open() error");
    }

    int pos = 0;
    for (int i = 0; i < 26; i++) {
        buffer[pos++] = 'a' + i;
    }
    buffer[pos] = '\n';
    write(fd, buffer, pos * sizeof(char));

    lseek(fd, 0, SEEK_SET);
    memset(buffer, 0, sizeof(buffer));

    while (read(fd, buffer, sizeof(buffer))) {
        printf("%s", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    close(fd);
    return 0;
}