#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include "path_search.h"
#include <sys/types.h>

// PID is global, not sure if allowed
pid_t child_pid = 0;

void alarmHandler(int signum) {
    if (child_pid != 0) {
        kill(child_pid, SIGTERM); // Send SIGTERM to child process
        printf("Time limit exceeded, process terminated.\n");
    }
}
int main(int argNum, char *args[]) {
    if (argNum < 3) {
        fprintf(stderr, "Usage: %s [snds] [cmd] [cmd-args]...\n", args[0]);
        return EXIT_FAILURE;
    }

    int snds = atoi(args[1]); // Convert to int

    if (snds <= 0) {
        fprintf(stderr, "Number of seconds is invalid.\n");
        return EXIT_FAILURE;
    }

    child_pid = fork();
    if (child_pid == -1) {
        perror("Fork");
        return EXIT_FAILURE;
    }

    else if (child_pid > 0) {
        // Parent process
        signal(SIGALRM, alarmHandler);
        alarm(snds);
        int status;
        waitpid(child_pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Process exited with status %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            printf("Process killed by signal %d\n", WTERMSIG(status));
        }
    }

    else {
        // Child process
        char* fullPath = findInPATH(args[2]);
        if (fullPath) {
            args[2] = fullPath; // Update cmd with full path
        }
        
        // char cmd[1024] = {0};
        // strcat(cmd, args[2]);
        // for (int i = 3; i < argNum; i++) {
        //     strcat(cmd, " ");
        //     strcat(cmd, args[i]);
        // }

        // Execute cmd 
        execv(args[2], &args[2]);
        perror("execv");
        exit(EXIT_FAILURE);
        
        // FILE *fp;
        // char path[1035];
        // fp = popen(cmd, "r"); //IDK IF WE R ALLOWED TO USE THIS AT ALL 
        // if (fp == NULL) {
        //     printf("Failed to run command\n");
        //     exit(1);
        // }
        // while (fgets(path, sizeof(path)-1, fp) != NULL) {
        //     printf("%s", path);
        // }
        // pclose(fp);
    }

    return EXIT_SUCCESS;
}
