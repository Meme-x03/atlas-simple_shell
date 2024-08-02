#include "main.h"

/**
 * execute_command - Executes the given command
 * @cmd: Command to execute
 *
 * Return: Always returns -1 on failure
 */
int execute_command(char *cmd)
{
    char *argv[2];

    argv[0] = cmd;
    argv[1] = NULL;

    if (fork() == 0)
    {
        /* Child process */
        execve(argv[0], argv, environ);
        perror("./hsh");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        wait(NULL);
    }

    return (-1);
}

