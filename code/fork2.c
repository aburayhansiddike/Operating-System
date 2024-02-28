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


        printf("\n\nI am child process\n ======================\n");
        prinft("PID of current process : %d\n", myPID);
        printf("PID of Parent Process: %d\n", parentPID);
        printf("PID of child Process: %d\n", childPID);
    }
}
