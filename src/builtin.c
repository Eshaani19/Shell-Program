#include "rush.h"

void exit_shell(){
    exit(0);
}

void change_directory(char **args){
    if (args[1] == NULL || args[2] != NULL){
        print_error();
    }
    else{
        if (chdir(args[1]) != 0){
            print_error();
        }
    }
}

void update_path(char **args){
    for (int i = 0; i < MAX_PATH_DIRS; i++){
        if(path_dirs[i] != NULL){
            free(path_dirs[i]);
            path_dirs[i] = NULL;
        }
    }
    int i = 0;
    while (args[i+1] != NULL && i < MAX_PATH_DIRS){
        path_dirs[i] = strdup(args[i+1]);
        i++;
    }
    return 1;
}