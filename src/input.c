#include "main.h"
#include <ctype.h>

char **read_input(char *input) {
    int bufsize = MAX_ARGS;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
    char *rest = input;

    if (!tokens) {
        print_error();
        exit(EXIT_FAILURE);
    }

    while ((token = strtok_r(rest, " \t\r\n", &rest))) {
        tokens[position] = strdup(token);
        position++;

        if (position >= bufsize) {
            bufsize += MAX_ARGS;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                print_error();
                exit(EXIT_FAILURE);
            }
        }
    }
    tokens[position] = NULL;
    return tokens;
}