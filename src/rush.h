#ifndef __rush_h__
#define __rush_h__

#include <sys/time.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

// Macros definitions

#define MAX_INPUT 255
#define MAX_ARGS 64
#define MAX_PATHS 64
#define DELIMITERS " \t\r\n\a"
#define ERROR_MESSAGE "An error has occurred\n"

// function definitions
void shell();
char* read_input();
char** parse_input(char* line);

int execute_command(char **args);
int execute_parallel_commands(char **args);

void change_directory(char **args);
void update_path(char **args);

int exit_shell(char **args);
int redirect_output(char **args);

int builtin_command(char **args);
void redirect_output(char **args);

#endif