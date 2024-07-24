#include "main.h"

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL; /* Command input */
	size_t len = 0; /* Size of buffer */
	ssize_t nread; /* Number of chars read by getline */
	char *argv[10]; /* Command and args */
	int argc; /* Number of args */

	while (1) /* Infinite loop until exit */
	{
		prompt(); /* Print the prompt */

		nread = getline(&line, &len, stdin); /* Read user input */

		if (nread == -1) /* Check for error or EOF (Ctrl+D) */
		{
			printf("\n"); /* Print newline */
			free(line); /* Free memory */
			exit(EXIT_SUCCESS); /* Exit program */
		}

		line[nread - 1] = '\0'; /* Remove newline char */

		argc = 0; /* Init arg count */
		argv[argc] = strtok(line, " "); /* Split command into words */

		while (argv[argc] != NULL) /* Split remaining command */
		{
			argv[++argc] = strtok(NULL, " ");
		}

		if (fork() == 0) /* Create child process */
		{
			execve(argv[0], argv, NULL); /* Execute command */
			perror("execve"); /* Print error if execve fails */
			exit(EXIT_FAILURE); /* Exit child process */
		}
		else /* Parent process waits */
		{
			wait(NULL); /* Wait for child to finish */
		}
	}

	free(line); /* Free memory */
	return (0); /* Return success */
}

/**
 * prompt - Prints the prompt
 */
void prompt(void)
{
	printf("#cisfun$ "); /* Print prompt */
}

