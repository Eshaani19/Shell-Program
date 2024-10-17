#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_BUILTINS 3
#define MAX_ARGS 255

// Global variables
extern char **path;
extern int path_size;
extern char *builtin_str[];
extern int (*builtin_func[])(char **);

// Function prototypes
void shell();
char **read_input(char *input);
int execute_command(char **args);
void execute_parallel_commands(char **args);
int launch_external_command(char **args);
int handle_redirection(char **args);
int exit_shell(char **args);
int change_directory(char **args);
int update_path(char **args);
void print_error();
void free_path();
void initialize_path();

#endif // MAIN_H