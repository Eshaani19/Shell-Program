#include "rush.h"

char *get_input(){
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

char **parse_input(char *line){
    int bufsize = MAX_ARGS, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens){
        print_error();
        exit(1);
    }

    token = strtok(line, DELIMITERS);
    while (token != NULL){
        tokens[position] = token;
        position++;

        if (position >= bufsize){
            bufsize += MAX_ARGS;
            tokens = realloc(token, bufsize * sizeof(char*));
            if (!tokens){
                print_error();
                exit(1);
            }
        }
        token = strtok(NULL, DELIMITERS);
    }
    tokens[position] = NULL;
    return tokens;
}
