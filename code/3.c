#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(){

    char *pipePath = "./fifo-chat";
    char *existMsg = "Pipe already exists.\n";
	char *creatErr = "Pipe can't be created.\n";
	char *succsMsg = "Pipe created successfully.\n";

    if(access(pipePath, F_OK) == 0){
        write(STDOUT_FILENO, existMsg, strlen(existMsg));
    }else{
        int pipeFlg = mkfifo(pipePath, 0666);
        
        if(pipeFlg < 0){
            write(STDOUT_FILENO, creatErr, strlen(creatErr));
            exit(1);
        }else{
            write(STDOUT_FILENO, succsMsg, strlen(succsMsg));
        }
    }

    pid_t pid = fork();
    if(pid == 0){
        
    }else{

    }
    exit(0);
}