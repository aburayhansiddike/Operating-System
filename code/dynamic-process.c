#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

void* get_cpu_info(void *message) {
    for (int i = 0; i < 10; i++) {
        printf("%s: CoreID: %d\n", (char*)message, sched_getcpu());
    }
}

int main() {
    int cores = sysconf(_SC_NPROCESSORS_ONLN);

    for (int i = 1; i <= cores+4; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            cpu_set_t mask;
            CPU_ZERO(&mask);
            CPU_SET(i%cores, &mask);
            if (sched_setaffinity(pid, sizeof(mask), &mask) == -1) {
                perror("sched_setaffinity");
                exit(EXIT_FAILURE);
            }

            char buffer_main[100], buffer_1[100], buffer_2[100];
            sprintf(buffer_main, "Main thread of child process %d with pid %d", i, getpid());
            sprintf(buffer_1, "Thread 1 of child process %d with pid %d", i, getpid());
            sprintf(buffer_2, "Thread 2 of child process %d with pid %d", i, getpid());
            get_cpu_info(buffer_main);

            pthread_t tid1, tid2;
            pthread_create(&tid1, NULL, get_cpu_info, buffer_1);
            pthread_create(&tid2, NULL, get_cpu_info, buffer_2);
            pthread_join(tid1, NULL);
            pthread_join(tid2, NULL);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = -4; i < cores; i++) {
        int status;
        pid_t wpid = waitpid(-1, &status, 0);
        if (wpid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        printf("Child process with PID %d has terminated\n", wpid);
    }

    exit(EXIT_SUCCESS);
}