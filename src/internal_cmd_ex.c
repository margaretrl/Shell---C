#include "internal_cmd_ex.h"
#include "redirection.h"
#include "background.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>

// Part 9 - Internal Command Execution

bool isInternal(char *command) {
    const char *builtins[] = {"exit", "cd", "jobs", NULL};

    for (int i = 0; builtins[i] != NULL; i++) {
        if (strcmp(command, builtins[i]) == 0) {
            return true;
        }
    }
    return false;
}


void executeInternalCommand(char* input, tokenlist *tokens, char* cmd_history[], int history_count) {

    // exit
    //char ** newitems = tokens->items;

    if (strcmp(tokens->items[0], "exit") == 0) {
        if (tokens->size > 1) { // Args amount check
            fprintf(stderr, "exit: Too many arguments\n");
            return;
        }

        // Implement wait for background processes to finish

        if (history_count == 0) {
            printf("No valid commands executed.\n");
        } 
        else {
            printf("Last %d valid commands:\n", history_count);
            for (int i = 0; i < history_count; i++) {
                printf("[%d]: %s\n", i, cmd_history[i]);
            }
        }
        // Free allocated memory
        if(input != NULL){
            free(input);
        }
		if (tokens != NULL) {
            free_tokens(tokens);
        }
        exit(0);
    } 

    // cd
    else if (strcmp(tokens->items[0], "cd") == 0) {
        bool cdio = false;
        //handleIORedirection(tokens->items);
        //printf("%zu\n", tokens->size);
        if (tokens->size > 2) { // Args amount check
            if (strcmp(tokens->items[1],"<") == 0)
            {
                fprintf(stderr, "cd: Too many arguments\n");
                return;
            }
            else
            {
                cdio = true;
            }
        }

        // cd with no arguments case
        char *dir;
        if (tokens->size == 1) {
            dir = getenv("HOME");
        } 
        else if (cdio == true)
        {
            //dir = tokens->items[2];

            printf("%s\n", tokens->items[1]);
            dir = tokens->items[1];
        }
        else
        {
            dir = tokens->items[1];
        }


        struct stat st;
        if (stat(dir, &st) < 0 || !S_ISDIR(st.st_mode)) {
            fprintf(stderr, "cd: %s: No such file or directory\n", dir);
            return;
        }

        if (chdir(dir) < 0) {
            perror("cd");
            return;
        }
    }
        
    // jobs
    else if (strcmp(tokens->items[0], "jobs") == 0) {
        // WE NEED TO IMPLEMENT BACKGROUN JOB STUFF FOR THIS
        checkJobs();
        //printf("No background jobs.\n");
    }
        // this else if doesnt work but this should be for sleep command specifically
    /*else if (strcmp(tokens->items[0], "sleep") == 0) {
        // Check if the "sleep" command has the correct number of arguments
        if (tokens->size < 2) {
            fprintf(stderr, "Usage: sleep seconds\n");
        } else {
            pid_t pid, wpid;
            int status;

            if ((pid = fork()) == 0) {  // This block will be run by the child process
                if (execv("sleep", tokens->items) == -1) {
                    perror("Shell Error");
                    exit(EXIT_FAILURE);  // If exec fails, we exit
                }
            } else if (pid < 0) {
                // Error forking
                perror("Shell Error");
            } else {
                // Check if the command should run in the background
                if (tokens->size > 1 && strcmp(tokens->items[tokens->size - 1], "&") == 0) {
                    tokens->items[tokens->size - 1] = NULL;
                    addJob(pid, joinTokens(tokens->items));
                } else {
                    do {
                        wpid = waitpid(pid, &status, WUNTRACED);  // Parent process waits here for child to terminate
                    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
                }
            }
        }
    }*/
}
