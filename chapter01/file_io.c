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
    FILE* file = fopen(FILE_NAME, "a+");

    fputs("test\n", file);

    fseek(file, 0, SEEK_SET);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}