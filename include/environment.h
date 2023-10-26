#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"

// Part 2 & 3: Environment Variables and Tilde Expansion

void expandEnvironmentVariables(tokenlist *tokens);
void expandTilde(tokenlist *tokens);