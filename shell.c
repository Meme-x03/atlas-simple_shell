#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80

int main(void)
{
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    char input[MAX_LINE];         /* user input */
    int should_run = 1;           /* flag to determine when to exit program */

    while (should_run)
    {
        printf("simple_shell> ");
        fflush(stdout);

        if (!fgets(input, MAX_LINE, stdin))
            break;

        size_t length = strlen(input);
        if (input[length - 1] == '\n')
            input[length - 1] = '\0';

        int i = 0;
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

        pid_t pid = fork();
        if (pid < 0)
        {
            fprintf(stderr, "Fork Failed\n");
            return 1;
        }
        else if (pid == 0)
        {
            if (execvp(args[0], args) == -1)
            {
                fprintf(stderr, "Command not found\n");
            }
            exit(0);
        }
        else
        {
            wait(NULL);
        }
    }
    return 0;
}

