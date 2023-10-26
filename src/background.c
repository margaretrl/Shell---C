#include "background.h"
#include <stdbool.h>
#include <stdlib.h>

#define MAX_JOBS 10
typedef struct {
    int jobNumber;
    pid_t pid;
    char *commandLine;
    bool active;
} Job;

bool IsBackground(char ** tokens)
{
    for (int i = 0; tokens[i] != NULL;i++)
    {
        if (strcmp(tokens[i], "&") == 0)
        {
            return true;
        }
    }
    return false;
}


char *joinTokens(char **tokens) {
    char *result = NULL;
    int totalLength = 0;

    for (int i = 0; tokens[i] != NULL; i++) {
        totalLength += strlen(tokens[i]) + 1; // +1 for space between tokens
    }

    result = (char *)malloc(totalLength);
    if (result == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(result, "");
    for (int i = 0; tokens[i] != NULL; i++) {
        strcat(result, tokens[i]);
        if (tokens[i + 1] != NULL) {
            strcat(result, " ");
        }
    }

    return result;
}

void addJob(pid_t pid, char *commandLine) {
    Job jobs[MAX_JOBS];
    int nextJobNumber = 1;
    for (int i = 0; i < MAX_JOBS; i++) {
        if (!jobs[i].active) {
            jobs[i].jobNumber = nextJobNumber++;
            jobs[i].pid = pid;
            jobs[i].commandLine = commandLine; // Remember to free it later!
            jobs[i].active = true;
            printf("[%d] %d\n", jobs[i].jobNumber, pid); // Displaying the job number and PID
            break;
        }
    }
}

void checkJobs() {
    Job jobs[MAX_JOBS];
    bool anyjobs = false;
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs[i].active) {
            anyjobs = true;
            if (waitpid(jobs[i].pid, NULL, WNOHANG) != 0)
            { // This means the process has finished
                printf("[%d] + done %s\n", jobs[i].jobNumber, jobs[i].commandLine);
                //free(jobs[i].commandLine); // Freeing the duplicated command line
                jobs[i].active = false;
            }
            else
            {
                printf("[%d] + running %s\n", jobs[i].jobNumber, jobs[i].commandLine);
            }
        }
    }
    if (anyjobs == false)
    {
        printf("No background jobs\n");
    }
}
