#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int main() {

    int fd[2];
    int pflag = pipe(fd);

    if (pflag < 0) {
        char *error = "Pipe creation failed.\n";
        write(STDOUT_FILENO, error, strlen(error));
    }

    pid_t pid = fork();

    if (pid == 0) {
        // child
        while (1) {
            char msg[100];
            int n = read(STDIN_FILENO, msg, 100);
            msg[n] = '\0';
            write(fd[1], msg, strlen(msg));
        }
    } else {
        // parent

        while (1) {
            char msg[100];
            int n = read(fd[0], msg, 100);
            msg[n] = '\0';

            write(STDOUT_FILENO, msg, strlen(msg));

            n = read(fd[0], msg, sizeof(msg));
            char buffer[100];
            sprintf(buffer, "%d", n);

            write(STDOUT_FILENO, buffer, strlen(buffer));

            write(STDOUT_FILENO, msg, strlen(msg));

            if (strcmp(msg, "Please Terminate.\n") == 0) {
                kill(pid, SIGKILL);
                exit(0);
            }
        }
    }

    exit(0);
}