#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create child process

    if (pid == 0) {
        // Child executes "date" command
        execlp("date", "date", NULL);
    } else {
        // Parent waits for child
        wait(NULL);
        printf("Child finished\n");
    }

    return 0;
}
