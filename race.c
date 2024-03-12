#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <pthread.h>

int balance = 100;

void* deposit(void *amount) {
    balance += *((int*)amount);
    // int x = balance;
    // usleep(250000);
    // x += *((int*)amount);
    // usleep(250000);
    // balance = x;
}

void* withdraw(void *amount) {
    balance -= *((int*)amount);
    // int x = balance;
    // usleep(250000);
    // x -= *((int*)amount);
    // usleep(250000);
    // balance = x;
}

int main() {
	pthread_t t1, t2;

    int amount = 50;

    pthread_create(&t1, NULL, deposit, (void*)&amount);
    pthread_create(&t2, NULL, withdraw, (void*)&amount);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final balance: %d\n", balance);

	exit(0);
}