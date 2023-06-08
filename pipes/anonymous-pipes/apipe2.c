#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int fd[2];
    int outfd;
    
    if(pipe(fd) == -1) {
        perror("Unable to create pipe. \n");
        return 0;
    }
    
    if ((pid = fork()) == -1) {
        perror("Unable to create child. \n");
        return 0;    
    }
    
    if (pid == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execl("/usr/bin/ls", "ls", NULL);
    }

    // open output file for writing
    if ((outfd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        perror("Unable to open output file. \n");
        return 0;
    }

    // redirect stdout to output file
    dup2(outfd, STDOUT_FILENO);
    close(outfd);
    
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    close(fd[0]);
    execl("/usr/bin/wc", "wc", NULL);
    
    return 0;
}
