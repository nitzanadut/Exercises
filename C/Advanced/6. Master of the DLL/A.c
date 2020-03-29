//gcc -o a A.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PID 15
#define MAX_CMD 35

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s pid\n", argv[0]);
        exit(1);
    }

    // PID to string
    unsigned int pid = atoi(argv[1]);
    char pid_str[MAX_PID];
    sprintf(pid_str, "%d", pid);

    // Command to get CPU usage
    char cmd[MAX_CMD] = "ps -p ";
    strcat(cmd, pid_str);
    strcat(cmd, " -o %cpu | tail -1");

    // System to execute the command
    system(cmd);
}