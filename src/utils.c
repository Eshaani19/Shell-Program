#include "main.h"

void print_error(){
    write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
}

int redirect_output(char **args){
    for (int i = 0; args[i] != NULL; i++){
        if (args[i+1] == NULL){
            print_error();
            return 0;
        }
        int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
        if (fd < 0){
            print_error();
            return 0;
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        args[i] = NULL;
    }
    return 1;
}