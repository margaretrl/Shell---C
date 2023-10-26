#include "lexer.h"
#include "prompt.h"
#include "environment.h"
#include "path_search.h"
#include "redirection.h"
#include "internal_cmd_ex.h"
#include "external_cmd_ex.h"
#include "piping.h"
#include "background.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

int main()
{
    char* cmd_history[3];
    int history_count = 0;
	while (1) {
		printPrompt();  // ## Part 1 - Prompt ##

		/* input contains the whole command
		 * tokens contains substrings from input split by spaces
		 */

		char *input = get_input();
		printf("whole input: %s\n", input); // For testing

		tokenlist *tokens = get_tokens(input);
        expandEnvironmentVariables(tokens); // ## Part 2 - Env. Variables ##
        expandTilde(tokens); // ## Part 3 - Tilde Expansion ##

        // ## Part 4 - $PATH Search ## 
        // Check command for / & if it is internal 
        if (tokens->size > 0 && !isInternal(tokens->items[0]) 
        && strchr(tokens->items[0], '/') == NULL) {
            char *fullPath = findInPATH(tokens->items[0]);
            if (fullPath != NULL) {
                //printf("Full path of executable: %s\n", fullPath);
                // Replace the command name with its full path
                free(tokens->items[0]);
                tokens->items[0] = fullPath;
                //test = fullPath;

            } else {
                //fprintf(stderr, "Command not found.\n");
                free(input);
                free_tokens(tokens);
                continue; // Skip curr iteration if command is not found
            }
        }

        int pipe1 = needsPiping(tokens->items);
        
        if (tokens->size > 0 && pipe1 != -1){
            execPipeCmds(tokens,pipe1);
        } // piping done
        else if  (tokens->size > 0 && isInternal(tokens->items[0])) {
            // Part 6 - Internal Command Execution
            executeInternalCommand(input, tokens, cmd_history,history_count);
        }
        else if (tokens->size > 0 && !isInternal(tokens->items[0])){
            // Part 5 - External Command Execution
            char *command = tokens->items[0];
            executeExternalCommand(command, tokens->items);
        }


        // ## Storing valid commands for exit - Part 9 ##
        if (history_count < 3 && strcmp(input, "exit") != 0) {
            // CHECK -> Not sure if should store input or just cmd!!
            cmd_history[history_count] = strdup(input);  // Store cmd in history    
            history_count++;
        }
        else if (strcmp(input, "exit") != 0){
            free(cmd_history[0]); // Free memory of oldest cmd
            // Shift history array left
            for (int i = 1; i < 3; i++) {
                cmd_history[i - 1] = cmd_history[i];
            }
            cmd_history[2] = strdup(input); // Add new cmd to array
        }



		for (int i = 0; i < tokens->size; i++) { // For testing
			printf("token %d: (%s)\n", i, tokens->items[i]);
		}

        // Free allocated memory
        if(input != NULL){
            free(input);
        }
		if (tokens != NULL) {
            free_tokens(tokens);
        }
	}

	return 0;
}
