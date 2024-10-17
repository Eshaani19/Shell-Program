#include "main.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int execute_command(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    for (int i = 0; i < NUM_BUILTINS; i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return launch_external_command(args);
}

int launch_external_command(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (handle_redirection(args) == -1) {
            exit(EXIT_FAILURE);
        }

        // Search for the command in the path
        int command_found = 0;
        for (int i = 0; i < path_size; i++) {
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", path[i], args[0]);
            
            if (access(full_path, X_OK) == 0) {
                command_found = 1;
                execv(full_path, args);
                // If execv returns, there was an error
                print_error();
                exit(EXIT_FAILURE);
            }
        }

        // If command not found in any path
        if (!command_found) {
            print_error();
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        // Error forking
        print_error();
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int handle_redirection(char **args) {
    int out_file = -1;
    char *out_filename = NULL;
    int redirect_pos = -1;
    
    // Find redirection symbol
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0) {
            // Check if this is a second redirection
            if (out_filename != NULL) {
                print_error();
                return -1;
            }
            if (args[i+1] == NULL) {
                print_error();
                return -1;
            }
            out_filename = args[i+1];
            redirect_pos = i;
            i++;  // Skip the filename
        }
    }
    
    // If no redirection found
    if (out_filename == NULL) {
        return 0;
    }
    
    // Check if there's content after the redirection filename
    if (redirect_pos >= 0 && args[redirect_pos + 2] != NULL) {
        print_error();
        return -1;
    }
    
    // Open output file
    out_file = open(out_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_file == -1) {
        print_error();
        return -1;
    }
    
    // Redirect stdout
    if (dup2(out_file, STDOUT_FILENO) == -1) {
        close(out_file);
        print_error();
        return -1;
    }
    
    close(out_file);
    
    // Null terminate the command before the redirection
    args[redirect_pos] = NULL;
    
    return 0;
}

void execute_parallel_commands(char **args) {
    int i = 0;
    int cmd_start = 0;
    pid_t *pids = malloc(sizeof(pid_t) * MAX_ARGS);
    int pid_count = 0;
    
    while (args[i] != NULL) {
        if (strcmp(args[i], "&") == 0 || args[i + 1] == NULL) {
            // Temporarily store the current token
            char *current = args[i];
            
            // Null terminate the current command
            if (strcmp(args[i], "&") == 0) {
                args[i] = NULL;
            }
            
            // Only fork if there are commands to execute
            if (args[cmd_start] != NULL) {
                pid_t pid = fork();
                if (pid == 0) {
                    // Child process
                    execute_command(&args[cmd_start]);
                    exit(0);
                } else if (pid > 0) {
                    pids[pid_count++] = pid;
                } else {
                    print_error();
                }
            }
            
            // If this was the last command, break
            if (args[i + 1] == NULL) {
                break;
            }
            
            // Restore the token and continue
            if (current != NULL && strcmp(current, "&") == 0) {
                args[i] = current;
            }
            cmd_start = i + 1;
        }
        i++;
    }
    
    // Wait for all child processes
    for (i = 0; i < pid_count; i++) {
        waitpid(pids[i], NULL, 0);
    }
    
    free(pids);
}