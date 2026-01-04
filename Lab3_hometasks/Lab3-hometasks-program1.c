#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child runs top
        execlp("top", "top", NULL);
    } else {
        // Parent waits
        wait(NULL);
        printf("Child finished\n");
    }
    return 0;
}
