#include "main.h"

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	while (1) /* Infinite loop until exit */
	{
		char *line = read_input();
		if (line == NULL)
			break;
		
		char **argv = split_line(line);
		if (argv == NULL)
		{
			free(line);
			continue;
		}

		execute_command(argv);
		
		free(line);
		free(argv);
	}
	return (0); /* Return success */
}

/**
 * prompt - Prints the prompt
 */
void prompt(void)
{
	printf("#cisfun$ "); /* Print prompt */
}

/**
 * read_input - Reads input from the user
 *
 * Return: The input line or NULL on EOF
 */
char *read_input(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	prompt(); /* Print the prompt */
	nread = getline(&line, &len, stdin); /* Read user input */

	if (nread == -1) /* Check for error or EOF (Ctrl+D) */
	{
		free(line); /* Free memory */
		return (NULL);
	}

	line[nread - 1] = '\0'; /* Remove newline char */
	return (line);
}

/**
 * split_line - Splits a line into arguments
 * @line: The input line
 *
 * Return: An array of arguments
 */
char **split_line(char *line)
{
	int argc = 0;
	char **argv = malloc(10 * sizeof(char *)); /* Command and args */

	if (!argv)
		return (NULL);

	argv[argc] = strtok(line, " "); /* Split command into words */
	while (argv[argc] != NULL) /* Split remaining command */
	{
		argv[++argc] = strtok(NULL, " ");
	}
	return (argv);
}

/**
 * execute_command - Executes a command
 * @argv: An array of arguments
 */
void execute_command(char **argv)
{
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

