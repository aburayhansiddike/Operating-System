#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main(){
    char *msg;
    char buffer[100];

    int n , c;

    int out_fd = open("./outfile", O_WRONLY | O_CREAT);
    msg = "Insert a number: ";
    write(STDOUT_FILENO, msg, strlen(msg) + 1);

    n = read(STDIN_FILENO, &buffer, sizeof(buffer));
    buffer[n] = '\0';
    write(out_fd, buffer, strlen(buffer));

    

    exit(0);

}