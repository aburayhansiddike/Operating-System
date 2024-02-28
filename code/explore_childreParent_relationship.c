#include <unistd.h>
#include<stdio.h>

int main(){
    __pid_t myPID, childPID, parentPID;

    int x = 5;
    myPID = getpid();
    parentPID = getpid();

    childPID = fork();

    if(childPID == 0){
        parentPID = getpid();
        //printf("child : \n");
        for(int i = 0; i < 20; i += 1){
            printf("Child: %d ----> %d: x = %d\n",i, myPID, x);
            x = x + i;
            printf("Child: %d -----> %d: x = %d\n", i, myPID, x);
        }
    }else{
        //printf("Parent : \n");
        for(int i = 0; i < 20; i += 1){
            printf("Parent: %d ----> %d: x = %d\n",i, myPID, x);
            x = x + 20 + i;
            printf("Parent: %d ----> %d: x = %d\n", i, myPID, x);
        }
    }

    return 0;
}
