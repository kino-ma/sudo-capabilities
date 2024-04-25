#define UID 0

#include <unistd.h>
#include <sys/capability.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

int check_cap() {
    pid_t pid = getpid();
    cap_t cap = cap_get_pid(pid);

    if (cap == NULL) {
        printf("failed to get capabilites\n");
        return 1;
    }

    cap_value_t cap_value = CAP_SETUID;
    cap_flag_value_t cap_flags_value;

    cap_get_flag(cap, cap_value, CAP_EFFECTIVE, &cap_flags_value);
    printf("EFFECTIVE %s\n", (cap_flags_value == CAP_SET) ? "YES" : "NO");

    cap_get_flag(cap, cap_value, CAP_PERMITTED, &cap_flags_value);
    printf("PERMITTED %s\n", (cap_flags_value == CAP_SET) ? "YES" : "NO");

    cap_get_flag(cap, cap_value, CAP_INHERITABLE, &cap_flags_value);
    printf("INHERITABLE %s\n", (cap_flags_value == CAP_SET) ? "YES" : "NO");

    return 0;
}

int main(int argc, char** argv) {
    if (check_cap() != 0) {
        printf("check_cap failed\n");
        return 1;
    }

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
