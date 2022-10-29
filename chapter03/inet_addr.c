#include <stdio.h>
#include <arpa/inet.h>

void convert_address(const char* addr) {
    unsigned long conv = inet_addr(addr);
    if (conv == INADDR_NONE) {
        printf("Error occured!\n");
    } else {
        printf("Network ordered integer addr: %#lx\n", conv);
    }
}

int main(int argc, char* argv[]) {
    char* addr1 = "1.2.3.4";
    char* addr2 = "1.2.3.256";

    convert_address(addr1);
    convert_address(addr2);
    return 0;
}