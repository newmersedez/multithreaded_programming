#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if(fork()) {
        if(fork()) {
            if(fork()) {
                fork();
            }
        }
    }
    printf("Hello!\n");
}
