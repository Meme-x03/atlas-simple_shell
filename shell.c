#include "main.h"
#include <errno.h>

/**
 * main - Entry point for the shell
 *
 * Return: Always 0 on success, or an error code on failure
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *argv[2];

    while (1)
    {
        display_prompt();
        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (errno == EINTR)
            {
                continue;  /* Ignore interrupted system calls */
            }
            free(line);
            exit(0);  /* Exit on EOF or error */
        }

        /* Remove newline character */
        line[nread - 1] = '\0';

        /* Check for exit command */
        if (strcmp(line, "exit") == 0)
        {
            free(line);
            exit(0);
        }

        argv[0] = line;
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
    }

    free(line);
    return (0);
}

