#include "environment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Part 2 & 3: Environment Variables and Tilde Expansion

// CONSIDER -> edge case $USER$HOME does not work, needs fixing
void expandEnvironmentVariables(tokenlist *tokens) {
    for (int i = 0; i < tokens->size; i++) {  //loop through each token on list
        if (tokens->items[i][0] == '$') { 
            char* envValue = getenv(tokens->items[i] + 1); // Skip $
            if (envValue != NULL) { // Check if its exists
                free(tokens->items[i]);  // Free old token
                tokens->items[i] = strdup(envValue);  // Allocate new value
            }
        }
    }
}

void expandTilde(tokenlist *tokens) { //function to expand tilde to user home directory path
    for(int i = 0; i < tokens->size; i++) { //loop through token list 
        char *token = tokens->items[i];
        

        if(token[0] == '~') { 
            //get user's home directory path 
            const char *homeDir = getenv("HOME");
            if(homeDir != NULL) {
                char *expandedToken = NULL;
                // Check if tilde is has a slash after or is standalone 
                if(token[1] == '/' || token[1] == '\0') { 
                    //allocate memory and expand token
                    expandedToken = malloc(strlen(homeDir) + strlen(token));
                    //copy home directory path
                    strcpy(expandedToken, homeDir);
                    //append the rest of the token skipping the tilde
                    strcat(expandedToken, token + 1); 
                }

                //replace old token with new onw if new expanded token was formed
                if(expandedToken != NULL) {
                    free(tokens->items[i]);
                    tokens->items[i] = expandedToken;
                }
            }
        }
    }
}

