// Eshaani Arvind U88155472
// This file contains the main function and the function to run the shell

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 1) {
        print_error();
        exit(1);
    }
    
    initialize_path();
    shell();
    return 0;
}

void shell() {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t characters;

    while (1) {
        printf("rush> ");
        fflush(stdout);
        
        characters = getline(&input, &bufsize, stdin);
        
        if (characters == -1) {
            break;  // End of file (ctrl-d)
        }
        
        // Remove newline character
        if (input[characters - 1] == '\n') {
            input[characters - 1] = '\0';
        }
        
        if (strlen(input) == 0) {
            continue;  // Empty line, just reprompt
        }
        
        char **args = read_input(input);
        if (args[0] == NULL) {
            for (int i = 0; args[i] != NULL; i++) {
                free(args[i]);
            }
            free(args);
            continue;  // Empty command, just reprompt
        }
        
        int has_parallel = 0;
        for (int i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], "&") == 0) {
                has_parallel = 1;
                break;
            }
        }
        
        if (has_parallel) {
            execute_parallel_commands(args);
        } else {
            execute_command(args);
        }
        
        // Free the arguments
        for (int i = 0; args[i] != NULL; i++) {
            free(args[i]);
        }
        free(args);
    }
    
    free(input);
}