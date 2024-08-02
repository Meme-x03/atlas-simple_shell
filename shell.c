#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_LINE 80

extern char **environ;

void handle_command(char *args[]);
char *find_command(char *command);

int main(void)
{
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    char input[MAX_LINE];         /* user input */
    int should_run = 1;           /* flag to determine when to exit program */
    size_t length;
    int i;

    while (should_run)
    {
        printf("simple_shell> ");
        fflush(stdout);

        if (!fgets(input, MAX_LINE, stdin))
            break;

        length = strlen(input);
        if (input[length - 1] == '\n')
            input[length - 1] = '\0';

        i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL)
        {
            i++;
            args[i] = strtok(NULL, " ");
        }

        if (args[0] == NULL)
            continue;

        if (strcmp(args[0], "exit") == 0)
            should_run = 0;
        else
            handle_command(args);
    }
    return (0);
}

void handle_command(char *args[])
{
    pid_t pid;
    char *command_path;

    command_path = find_command(args[0]);
    if (command_path == NULL)
    {
        fprintf(stderr, "%s: Command not found\n", args[0]);
        return;
    }

    pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execve(command_path, args, environ) == -1)
        {
            perror("Command execution failed");
        }
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
    }
    free(command_path);
}

char *find_command(char *command)
{
    char *path = getenv("PATH");
    char *path_dup = strdup(path);
    char *dir = strtok(path_dup, ":");
    struct stat buffer;

    if (stat(command, &buffer) == 0)
    {
        free(path_dup);
        return strdup(command);
    }

    while (dir != NULL)
    {
        char *full_path = malloc(strlen(dir) + strlen(command) + 2);
        sprintf(full_path, "%s/%s", dir, command);

        if (stat(full_path, &buffer) == 0)
        {
            free(path_dup);
            return full_path;
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_dup);
    return NULL;
}

