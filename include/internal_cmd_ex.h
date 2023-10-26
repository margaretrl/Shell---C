#pragma once
#include "internal_cmd_ex.h"
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

bool isInternal(char *command);
void executeInternalCommand(char* input, tokenlist *tokens, char* cmd_history[], int history_count);
