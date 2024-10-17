#include "main.h"
#include <unistd.h>

char **path = NULL;
int path_size = 0;

char *builtin_str[] = {"exit", "cd", "path"};
int (*builtin_func[])(char **) = {&exit_shell, &change_directory, &update_path};

int exit_shell(char **args) {
    if (args[1] != NULL) {
        print_error();
        return 1;
    }
    exit(0);
}

int change_directory(char **args) {
    if (args[1] == NULL || args[2] != NULL) {
        print_error();
    } else if (chdir(args[1]) != 0) {
        print_error();
    }
    return 1;
}

int update_path(char **args) {
    // Free existing path
    free_path();
    
    // Count new paths
    path_size = 0;
    for (int i = 1; args[i] != NULL; i++) {
        path_size++;
    }
    
    // If no paths provided, clear the path
    if (path_size == 0) {
        path = malloc(sizeof(char*));
        path[0] = NULL;
        return 1;
    }
    
    // Allocate new path array
    path = malloc(sizeof(char*) * (path_size + 1));
    if (!path) {
        print_error();
        return 1;
    }
    
    // Copy new paths
    for (int i = 0; i < path_size; i++) {
        path[i] = strdup(args[i+1]);
        if (!path[i]) {
            print_error();
            // Clean up allocated paths
            for (int j = 0; j < i; j++) {
                free(path[j]);
            }
            free(path);
            return 1;
        }
    }
    path[path_size] = NULL;
    return 1;
}

void free_path() {
    if (path != NULL) {
        for (int i = 0; i < path_size; i++) {
            free(path[i]);
        }
        free(path);
        path = NULL;
    }
}

void initialize_path() {
    path_size = 1;
    path = malloc(sizeof(char*) * 2);
    path[0] = strdup("/bin");
    path[1] = NULL;
}