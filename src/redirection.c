#include "redirection.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//I/O redirection

void handleIORedirection(char **tokens){
    for (int i = 0; tokens[i] != NULL; i++){ //loop through each token
        if (strcmp(tokens[i], ">") == 0){  
            //check for redirection token ">"
            if (tokens[i + 1] == NULL){
                //check if no file name following token; if so print error 
                fprintf(stderr, "Output redirection has no file.\n");
                exit(EXIT_FAILURE);
            }

            // open specified file, if doesnt exist -> create new
            //if file exists -> empty it
            int fd = open(tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            
            //check for any errors when opening or creating file
            if (fd == -1) {
                printf("Error in open\n");
                exit(EXIT_FAILURE); //exit
            }
            
            dup2(fd, 1);  // Duplicate file descriptor fd to stdout
            close(fd);  // Close the original file descriptor
            tokens[i] = NULL; //removes from further processing 
        }

        else if (strcmp(tokens[i], "<") == 0){  // Input redirection
            if (tokens[i + 1] == NULL){
                fprintf(stderr, "Input redirection has no file.\n");
                exit(EXIT_FAILURE);
            }
            int fd = open(tokens[i + 1], O_RDONLY); // Open in read only
            if (fd == -1){
                printf("Error in open\n");
                exit(EXIT_FAILURE);
            }
            dup2(fd, 0);  // Duplicate file descriptor fd to stdin
            close(fd);  // Close original file descriptor
            tokens[i] = NULL;
        }
    }
}


