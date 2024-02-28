#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
	char *pipePath = "./fifo-1";
	char *existMsg = "Pipe already exists.\n";
	char *creatErr = "Pipe can't be created.\n";
	char *succsMsg = "Pipe created successfully.\n";

	char writeMsg[100];
	char readMsg[100];

	if (access(pipePath, F_OK) == 0) {
		write(STDOUT_FILENO, existMsg, strlen(existMsg));
	} else {
		int pipeFlag = mkfifo(pipePath, 0666);

		if (pipeFlag < 0) {
			write(STDOUT_FILENO, creatErr, strlen(creatErr));
			exit(1);
		} else {
			write(STDOUT_FILENO, succsMsg, strlen(succsMsg));
		}
	}

	int msgLen = read(STDIN_FILENO, writeMsg, sizeof(writeMsg));
	
	int fd = open(pipePath, O_RDWR);
	write(fd, writeMsg, strlen(writeMsg));

	int n = read(fd, readMsg, strlen(writeMsg));
	readMsg[n] = '\0';
	write(STDOUT_FILENO, readMsg, strlen(readMsg));

	// pid_t pid = fork();

	// if (pid < 0) {
	// 	printf("Fork Error.\n");
	// 	exit(1);
	// }

	// if (pid == 0) {
	// 	printf("Child Process.\n");

	// 	int out_fd = open(pipePath, O_WRONLY);

	// 	write(out_fd, writeMsg, strlen(writeMsg));
	// } else {
	// 	printf("Parent Process.\n");

	// 	int inp_fd = open(pipePath, O_RDONLY);

	// 	read(inp_fd, readMsg, strlen(writeMsg));

	// 	write(STDOUT_FILENO, readMsg, strlen(readMsg));
	// }

	exit(0);
}