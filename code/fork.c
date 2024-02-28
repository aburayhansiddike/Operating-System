#include<stdio.h>
#include <unistd.h>

int main(){

   fork();
   pid_t p = fork();
   printf("process id %d\n", getpid());
   return 0;
}
