#include "rush.h"

int main(int argc, char *argv[])
{
    if (argc != 1){
        print_error();
        exit(1);
    }
    shell();
    return 0;
}

void shell(){
    char *input;
    char **args;
    int status = 1:

    do {
        printf("rush> ");
        fflush(stdout);
        input = get_input();
        if (strlen(input) == 0){
            continue;
        }
        args = read_input(input);
        if (args[0] != NULL){
            status = execute_command(args);
        }
        free(input);
        free(args);
    } while (status);
}