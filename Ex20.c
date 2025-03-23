#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    int current_nice = getpriority(PRIO_PROCESS, 0);
    if (current_nice == -1) {
        perror("getpriority");
    } else {
        printf("Parent process: current priority (nice) = %d\n", current_nice);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        int new_priority = -10;
        if (setpriority(PRIO_PROCESS, 0, new_priority) == 0) {
            printf("Child process: priority set to %d\n", new_priority);
        } else {
            perror("setpriority");
        }

        execlp("sleep", "sleep", "5", NULL);
        perror("execlp");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent process: child completed\n");
    }

    return 0;
}
