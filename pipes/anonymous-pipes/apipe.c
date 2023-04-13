pipe.c
exels.c
redirect.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
	pid_t pid;
	int fd[2];
	
	if (pipe(fd) == -1) {
		perror("Unable to create pipe.");
		return 0;
	}
	
	if ((pid = fork()) == -1) {
		perror("Unable to create child.");
		return 0;
	}
	
	if (pid == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execl("usr/bin/ls", "ls", NULL);
	}
	
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	execl("usr/bin/grep", "grep", "x", NULL);
	
	return 0;
}
