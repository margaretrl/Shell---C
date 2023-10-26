#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Part 5 - External Command Execution

void executeExternalCommand(const char *command, char **args);
