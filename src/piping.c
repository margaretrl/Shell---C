#include "piping.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "path_search.h"

//fill cmd array w path for given token range \
    //@param
        //tokens input tokens 
        //cmd output command array to fill 
        // start Start intedex in tokens in tokens -> process 
        // end End index in tokens -> process

void getCmdArr(char **tokens, char **cmd, int start, int end){
    for (int i = 0; i < end; i++) {
        char *path = findInPATH(tokens[start + i]);
        if (path != NULL){
            cmd[i] = path;
        } 
        else{
            cmd[i] = tokens[start + i];
        }
    }
    cmd[end] = NULL; // makesure command array is null terminated 
}

//Check if tokens contains a pipe
int needsPiping(char ** tokens)
{
    for (int i = 0; tokens[i] != NULL; i++) {
        //return the index of pipe
        if (strcmp(tokens[i], "|") == 0) {
            return i; //return -1 if Index not found 
        }
    }
    return -1;
}

//create pipeline of commands (fork/pipe) 
int fork_pipes(int n, struct command *cmd)
{
    if (cmd == NULL || n <= 0)
    {
        return -1; //if fails return -1
    }

    int i;
    pid_t pid;
    int in = 0;
    int fd[2];

    for (i = 0; i < n; ++i)
    {
        pipe(fd);

        if ((pid = fork()) == 0)
        {
            // Child process
            if (i > 0)
            {
                // input for current command = previous command output
                dup2(in, 0);
                close(in);
            }

            if (i < n - 1)
            {
                // input for current command = next command output
                dup2(fd[1], 1);
                close(fd[1]);
            }

            // command execution 
            execv(cmd[i].argv[0], (char *const *)cmd[i].argv);
            printf("execv\n");
            exit(EXIT_FAILURE);
        }
        else if (pid == -1)
        {
            // Handle fork failure
            printf("fork\n");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe in the parent
        close(fd[1]);

        // Set the read end of the pipe as the input for the next command
        in = fd[0];
    }

    // Wait for the last command to finish
    int status;
    waitpid(pid, &status, 0);

    return 0;
}

void execPipeCmds(tokenlist *tokens, int pipeIndex1){
    char *cmd1[pipeIndex1 + 1];
    getCmdArr(tokens->items, cmd1, 0, pipeIndex1);


    int pipeIndex2 = -1;
    char **cmd2Start = &tokens->items[pipeIndex1 + 1];
    pipeIndex2 = needsPiping(cmd2Start);
        
    if (pipeIndex2 != -1) { // 2 pipes case
        char *cmd2[pipeIndex2 + 1];
        getCmdArr(cmd2Start, cmd2, 0, pipeIndex2);

            char *cmd3[tokens->size - (pipeIndex1 + pipeIndex2 + 2) + 1];
            getCmdArr(cmd2Start, cmd3, pipeIndex2 + 1, tokens->size - (pipeIndex1 + pipeIndex2 + 2));

            struct command cmd[] = {{cmd1}, {cmd2}, {cmd3}};
            fork_pipes(3, cmd); // Call fork_pipes with 3 commands
        } 
        else 
        {
            char *cmd2[tokens->size - pipeIndex1];
            getCmdArr(tokens->items, cmd2, pipeIndex1 + 1, tokens->size - pipeIndex1 - 1);

            struct command cmd[] = {{cmd1}, {cmd2}};
            fork_pipes(2, cmd); // Call fork_pipes with 2 commands.
        }
}
