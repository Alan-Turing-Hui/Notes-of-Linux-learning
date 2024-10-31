#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int _execl() {
    pid_t pid = fork();
    printf("This message both parent and child process will print\n");
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // The child process gets a new process image to execute "ls -l" command
        if (execl("/bin/ls", "ls", "-l", NULL) == -1) {
            perror("Execl failed");
            return 2;
        }
    }
    printf("This message only parent process %d prints\n", getppid());

    return 0;
}