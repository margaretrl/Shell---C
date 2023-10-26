#include "external_cmd_ex.h"
#include "redirection.h"
#include "piping.h"
#include "background.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void executeExternalCommand(const char *command, char **args) {
    // Will be used to execute external commands including ls, cat, and mv
    pid_t pid, wpid;
    int status;
    if ((pid = fork()) == 0) {  // This block will be run by the child process
        handleIORedirection(args);  // this line is for io redirection
        if (execv(command, args) == -1) {
            perror("Shell Error");
        }
        exit(EXIT_FAILURE);  // If exec fails, we exit
    } else if (pid < 0) {
        // Error forking
        perror("Shell Error");
    } else {
        if ((sizeof(args) > 0) && IsBackground(args))
        {
            args[sizeof(args) - 1] = NULL;
            addJob(pid, joinTokens(args));
        }

        //else {
            do {
                wpid = waitpid(pid, &status, WUNTRACED);  // Parent waits for child
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        //}
    }
}
