#include "main.h"

char *builtin_str[] = {"exit", "cd","path"};
int (*builtin_func[])(char **) = {&exit_shell, &change_directory, &update_path};

int execute_command(char **args){
    if (builtin_command(args)){
        ;
    }
    else{
        pid_t pid;
        int status;
        pid = fork();
        if (pid == 0){
            if (redirect_output(args)){
                execv(args[0], args);
            }
            else{
                print_error();
            }
            exit(0);
        }
        else if (pid < 0){
            print_error();
        }
        else{
            do{
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    
        }
    }
    return 1;
}

int builtin_command(char **args){
    int flag = 0;
    for (int i = 0; i <sizeof(builtin_str) / sizeof(char * ); i++){
        if (strcmp(args[0], builtin_str[i]) == 0){
            (*builtin_func[i])(args);
            flag = 1;
        }
    }
    return flag;
}