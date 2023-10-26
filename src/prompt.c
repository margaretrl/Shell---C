#include "prompt.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 

// Part 1 - Prompt
void printPrompt(){
	
    const char* user = getenv("USER");
	char* machine = getenv("MACHINE");
	//char* pwd = getenv("PWD");
    char cwd[1024]; // Changed for cd cmd use

	char hostname[256]; // Needed if getenv("MACHINE") or getenv("HOSTNAME") return NULL

    if (user == NULL){
        printf("Unable to get user\n");
    }

    if (machine == NULL){
        machine = getenv("HOSTNAME"); // Use HOSTNAME if MACHINE is null
        if (machine == NULL){
            if (gethostname(hostname, sizeof(hostname)) == -1){
                printf("Unable to get hostname\n");
            }
            machine = hostname;  // Use hostname if MACHINE and HOSTNAME are NULL
        }
    }

    if (!getcwd(cwd, sizeof(cwd))){
        printf("Unable to get current working directory\n");
    }

    // Prompt will still be printed even if incomplete as to allow user to use shell anyway
    printf("%s@%s:%s>", user, machine, cwd);
}
