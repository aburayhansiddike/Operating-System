#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>

int balance = 100;

void* deposit(void *amount) {
    // balance += *((int*)amount);
    for (int i = 0; i < 100; i++)
    {
        int x = balance;
        usleep(7500);
        x += *((int *)amount);
        usleep(250000);
        balance = x;
        printf("Balance: %d\n", balance);
    }
}

void* withdraw(void *amount) {
    // balance -= *((int*)amount);
    for (int i = 0; i < 100; i++)
    {
        int x = balance;
        usleep(100);
        x -= *((int*)amount);
        usleep(2500);
        balance = x;
        printf("Balance: %d\n", balance);
    }
    
}

int main() {
	pthread_t t1, t2;

    int amount = 50;

    pthread_create(&t1, NULL, deposit, (void*)&amount);
    pthread_create(&t2, NULL, withdraw, (void*)&amount);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final balance: %d\n", balance);

	exit(EXIT_SUCCESS);
}