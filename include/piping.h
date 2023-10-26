#pragma once
#include "lexer.h"
#include <stdbool.h>

struct command
{
    char **argv;  // Command and its arguments
};

//void executePiping(char** tokens);
int needsPiping(char ** tokens);
//int spawn_proc (int in, int out, struct command *cmd);
int fork_pipes (int n, struct command *cmd);
//int pipeCounter(char** tokens, int size);
void getCmdArr(char **tokens, char **cmd, int start, int end);
void execPipeCmds(tokenlist *tokens, int pipeIndex1);
