// Default to root UID
#define UID 0

#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (seteuid(UID) != 0) {
        printf("seteuid failed\n");
        return 1;
    }

    if (argc <= 1) {
        printf("command not specified\n");
        return 1;
    }

    execvp(argv[1], &argv[1]);

    // execvp never returns unless some error occured
    printf("some error occured\n");
    return 1;
}
