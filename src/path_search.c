#include "path_search.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

// Part 4 -$PATH Search

char* findInPATH(const char* command) {
    char* PATH = getenv("PATH");    // Get $PATH env variable
    if (PATH == NULL) {
        fprintf(stderr, "Error: PATH environment variable not found.\n");
        return NULL;
    }

    char* PATH_copy = strdup(PATH); // Make a copy of PATH bc strtok() modifies original str
    if (PATH_copy == NULL) {
        fprintf(stderr, "Error: Failed to duplicate PATH string.\n");
        return NULL;
    }

    char* cmd_path = NULL;

    //split the PATH string into its constituent directories using ':' for delimiter 
    char* dir = strtok(PATH_copy, ":"); //split by :
    while (dir != NULL) {
        //calculate lenght needed for the command's full path
        // +1 for slash btwn directory and comand, +1 for null
        size_t len = strlen(dir) + strlen(command) + 2;  
        //allocate/re-allocate memory for cmd_path
        cmd_path = (char*) realloc(cmd_path, len * sizeof(char));
        if (cmd_path == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            free(PATH_copy);
            return NULL;
        }
        //construct full path to command in cd
        snprintf(cmd_path, len, "%s/%s", dir, command); // Full path construction

        // Check if cmd exists & executable
        struct stat stat_buf;
        if (stat(cmd_path, &stat_buf) == 0 && (stat_buf.st_mode & S_IXUSR)) {
            break;  // Command found
        }

        //move to PATH next dir
        dir = strtok(NULL, ":");    // Move to next directory in PATH
    }

    //release memory allocated for duplicate
    free(PATH_copy);

    // If not found case: free cmd_path and return NULL
    if (dir == NULL) {
        free(cmd_path);
        cmd_path = NULL;
    }
    
    //return full path
    return cmd_path;
}
