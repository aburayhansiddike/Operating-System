#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
	char *pipePath = "./fifo-chat";
	char *existMsg = "Pipe already exists.\n";
	char *creatErr = "Pipe can't be created.\n";
	char *succsMsg = "Pipe created successfully.\n";

	char msg[100];

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

	int fd = open(pipePath, O_RDWR);

	// while(1) {
		int n = read(fd, msg, strlen(msg));
		// printf("%d\n", n);
		// if (n > 1) {
		// 	printf("Jannat: ");
		// 	write(STDOUT_FILENO, msg, strlen(msg));
		// } else {
			// printf("Write to Jannat: ");
			read(STDIN_FILENO, msg, strlen(msg));
			// write(fd, msg, strlen(msg));
		// }
		// if (strcmp(msg, "bye") == 0) {
		// 	break;
		// }
	// }

	exit(0);
}