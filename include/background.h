#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>






bool IsBackground(char ** tokens);
void addJob(pid_t pid, char *commandLine);
void checkJobs();
char *joinTokens(char **tokens);