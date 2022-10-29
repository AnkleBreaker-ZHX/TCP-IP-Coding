#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    char* addr = "127.232.124.79";
    struct sockaddr_in inet_addr;

    if (!inet_aton(addr, &inet_addr.sin_addr)) {
        printf("Error occured!\n");
    } else {
        printf("Network ordered integer addr: %#x\n", inet_addr.sin_addr.s_addr);
    }
    return 0;
}