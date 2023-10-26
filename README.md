# Shell

The purpose of this project is to design and develop a comprehensive shell interface that enhances process control, user interaction, and error handling mechanisms.

## Group Members
- **Margaret Rivas**: mer20c@fsu.edu
- **Sophia Quinoa**: saq20a@fsu.edu
- **Hannah Housand**: hjh21a@fsu.edu

## Division of Labor

### Part 1: Prompt
- **Responsibilities**:
    - [X] Implement a user-friendly prompt that displays the user's name, machine name, and the absolute working directory.
    - [X] Ensure that the prompt is dynamically updated to reflect the current working directory.
    - Handled in prompt.h/c
    - Completed by Margaret Rivas
- **Assigned to**: Margaret Rivas, Sophia Quinoa

### Part 2: Environment Variables
- **Responsibilities**:
  - [X] Create a mechanism to automatically expand tokens prefixed with the dollar sign into their respective environment variable values.
  - Handled in environment.h/c
  - Completed by Margaret Rivas
- **Assigned to**: Margaret Rivas, Hannah Housand

### Part 3: Tilde Expansion
- **Responsibilities**:
    - [X] Implement the tilde expansion functionality to automatically replace the tilde symbol with the value of the $HOME environment variable.
    - [X] Ensure this expansion only applies when the tilde is standalone or at the beginning of a path.
  - Handled in environment.h/c
  - Completed by Margaret Rivas
- **Assigned to**: Margaret Rivas, Sophia Quinoa

### Part 4: $PATH Search
- **Responsibilities**:
    - [X] Create a mechanism to search for commands in the directories specified in the $PATH environment variable.
    - [X] Implement error handling.
  - Handled in path_search.h/c
  - Completed Margaret Rivas
- **Assigned to**: Margaret Rivas, Hannah Housand

### Part 5: External Command Execution
- **Responsibilities**:
    - [X] Implement a system for executing external commands by creating a child process using fork().
    - [X] Ensure that commands with arguments are processed and executed correctly in the child process.
    - [X] Implement error handling and feedback mechanisms to inform the user of the status of the command execution.
  - Handled in external_cmd_ex.h/c
  - Completed Hannah Housand
- **Assigned to**: Sophia Quinoa, Hannah Housand

### Part 6: I/O Redirection
- **Responsibilities**:
    - [X] Implementing the ability to redirect standard output to a specified file.
    - [X] Handling the creation of a new file if it does not exist or overwriting an existing one.
    - [X] Implementing the ability to redirect standard input from a specified file, handling errors if the file does not exist or is not a regular file.
    - Handled in redirection.h/c
    - Completed by Margaret Rivas, Hannah Housand
- **Assigned to**: Margaret Rivas, Hannah Housand

### Part 7: Piping
- **Responsibilities**:
    - [X] Implementing the piping mechanism to redirect the output of one command as the input to another.
    - [X] Ensuring that multiple pipes work seamlessly, handling up to two pipes concurrently.
    - [X] Ensuring compatibility and functional integrity with I/O redirection features.
    - [X] Implementing error handling.
    - Handled in piping.h/c
    - Completed by Hannah Housand, Margaret Rivas
- **Assigned to**: Sophia Quinoa, Hannah Housand

### Part 8: Background Processing
- **Responsibilities**:
    - [X] Implementing the ability for the shell to execute commands in the background, allowing the user to continue with other operations.
    - [X] Ensuring that background processing is integrated with I/O redirection and piping functionalities.
    - Hanlded in background.h/c
    - Completed by Sophia Quinoa, Hannah Housand 
- **Assigned to**: Sophia Quinoa, Hannah Housand

### Part 9: Internal Command Execution
- **Responsibilities**:
    - [X] Implementing the 'exit' command to properly terminate the shell and displaying the last three valid commands executed.
    - [X] Implementing the 'cd' command to change the current working directory.
    - [X] Implementing the 'jobs' command to display a list of active background processes.
    - [ ] I/O Redirection fix
    - Handled in internal_cmd_ex.c/h
    - Completed by: Margaret Rivas
- **Assigned to**:  Margaret Rivas, Sophia Quinoa

### Part 10: External Timeout Executable
- **Responsibilities**:
    - [X] Creating the "mytimeout" executable that initiates a specified command and allows it to run for up to a number of seconds.
    - [X] Implementing a mechanism to terminate the "cmd" process after the elapsed time, sending a TERM signal to ensure termination.
    - [X] Integrating the "mytimeout" command into the shell.
    - Handled in mytimeout.c
    - Completed by: Margaret Rivas
- **Assigned to**:  Margaret Rivas, Hannah Housand

### Extra Credit
- **Responsibilities**:
    - [ ] Support unlimited number of pipes
    - [ ] Support piping and I/O redirection in a single command
    - [ ] Shell-ception: Execute your shell from within a running shell process repeatedly
    - We didnt do it :(
- **Assigned to**: Margaret Rivas, Hannah Housand, Sophia Quinoa

## File Listing
```
shell/
├── Makefile
├── README.md
├── include
│   ├── background.h
│   ├── environment.h
│   ├── external_cmd_ex.h
│   ├── internal_cmd_ex.h
│   ├── lexer.h
│   ├── path_search.h
│   ├── piping.h
│   ├── prompt.h
│   └── redirection.h
└── src
    ├── background.c
    ├── environment.c
    ├── external_cmd_ex.c
    ├── internal_cmd_ex.c
    ├── lexer.c
    ├── main.c
    ├── mytimeout.c
    ├── path_search.c
    ├── piping.c
    ├── prompt.c
    └── redirection.c
```
## How to Compile & Execute

### Requirements
- **Compiler**: gcc
- **Dependencies**: No dependencies other than standard C libraries

### Compilation
```bash
make
```
This will build the executables in /bin/
### Execution
For shell:
```bash
make run
```
For mytimeout:
```bash
make run_mytimeout [seconds] [cmd] [args]
# or within our shell:
.timeout [seconds] [cmd] [args]
```
This will run the program ...

## Bugs
- **Bug 1**: Edge case $USER$HOME does not work, needs fixing -> modify if necessary
- **Bug 2**: I/O redirection doesnt work for internal_cmd_ex.h
- **Bug 3**: Piping does not work for more than 2 pipes.

## Extra Credit
- **Extra Credit 1**: Not completed
- **Extra Credit 2**: Not completed
- **Extra Credit 3**: Not completed

## Considerations
- Shell only uses fork() and execv() to spawn new processes.
