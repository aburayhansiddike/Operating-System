#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) { // Parent process
        printf("Parent (PID: %d) created a child (PID: %d)\n", getpid(), pid);
        sleep(5); // Sleep for 5 seconds to allow child to terminate
        printf("Parent (PID: %d) exiting\n", getpid());
    } else if (pid == 0) { // Child process
        printf("Child (PID: %d) starting\n", getpid());
        printf("Child (PID: %d) exiting\n", getpid());
    } else { // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}