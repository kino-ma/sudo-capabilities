#include <unistd.h>
#include <sys/capability.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    const char *cap_name[CAP_LAST_CAP+1] = {
       "CAP_AUDIT_CONTROL",
       "CAP_AUDIT_READ",
       "CAP_AUDIT_WRITE",
       "CAP_BLOCK_SUSPEND",
       "CAP_CHOWN",
       "CAP_DAC_OVERRIDE",
       "CAP_DAC_READ_SEARCH",
       "CAP_FOWNER",
       "CAP_FSETID",
       "CAP_IPC_LOCK",
       "CAP_IPC_OWNER",
       "CAP_KILL",
       "CAP_LEASE",
       "CAP_LINUX_IMMUTABLE",
       "CAP_MAC_ADMIN",
       "CAP_MAC_OVERRIDE",
       "CAP_MKNOD",
       "CAP_NET_ADMIN",
       "CAP_NET_BIND_SERVICE",
       "CAP_NET_BROADCAST",
       "CAP_NET_RAW",
       "CAP_SETGID",
       "CAP_SETFCAP",
       "CAP_SETPCAP",
       "CAP_SETUID",
       "CAP_SYS_ADMIN",
       "CAP_SYS_BOOT",
       "CAP_SYS_CHROOT",
       "CAP_SYS_MODULE",
       "CAP_SYS_NICE",
       "CAP_SYS_PACCT",
       "CAP_SYS_PTRACE",
       "CAP_SYS_RAWIO",
       "CAP_SYS_RESOURCE",
       "CAP_SYS_TIME",
       "CAP_SYS_TTY_CONFIG",
       "CAP_SYSLOG",
       "CAP_WAKE_ALARM",
    };

    pid_t pid = getpid();
    cap_t cap = cap_get_pid(pid);

    if (cap == NULL) {
        printf("failed to get capabilites\n");
        return 1;
    }

    cap_value_t cap_value;
    cap_flag_value_t cap_flags_value;

    for (int i = 0; i < CAP_LAST_CAP + 1; i += 1) {
        cap_from_name(cap_name[i], &cap_value);

        printf("%-20s %d\t\t", cap_name[i], cap_value);
        printf("flags: \t\t");

        cap_get_flag(cap, cap_value, CAP_EFFECTIVE, &cap_flags_value);
        printf(" EFFECTIVE %-4s ", (cap_flags_value == CAP_SET) ? "YES" : "NO");
        cap_get_flag(cap, cap_value, CAP_PERMITTED, &cap_flags_value);
        printf(" PERMITTED %-4s ", (cap_flags_value == CAP_SET) ? "YES" : "NO");
        cap_get_flag(cap, cap_value, CAP_INHERITABLE, &cap_flags_value);
        printf(" INHERITABLE %-4s ", (cap_flags_value == CAP_SET) ? "YES" : "NO");
        printf("\n");
    }
}
