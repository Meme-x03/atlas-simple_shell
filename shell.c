#include "main.h"

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;   /* This will store the command we type */
	size_t len = 0;      /* This will store the size of the buffer */
	ssize_t nread;       /* This will store the number of characters read by getline */
	char *argv[10];      /* This will store the command and its arguments */
	int argc;            /* This will store the number of arguments */

	while (1)  /* This loop will run forever until we tell it to stop */
	{
		prompt();   /* Print the prompt to the screen */

		nread = getline(&line, &len, stdin);   /* Read the command from the user */

		if (nread == -1)   /* If we get an error or EOF (Ctrl+D), we exit the loop */
		{
			free(line);   /* Free the memory we allocated for the command */
			exit(EXIT_SUCCESS);   /* Exit the program successfully */
		}

		line[nread - 1] = '\0';   /* Remove the newline character at the end */

		argc = 0;   /* Initialize the argument count */
		argv[argc] = strtok(line, " ");   /* Split the command into words */

		while (argv[argc] != NULL)   /* Split the rest of the command */
			argv[++argc] = strtok(NULL, " ");

		if (fork() == 0)   /* Create a child process */
		{
			execve(argv[0], argv, NULL);   /* Execute the command in the child process */
			perror("execve");   /* If execve fails, print an error message */
			exit(EXIT_FAILURE);   /* Exit the child process if execve fails */
		}
		else   /* Parent process waits for the child to finish */
		{
			wait(NULL);   /* Wait for the child process to finish */
		}
	}

	free(line);   /* Free the memory we allocated for the command */
	return (0);     /* Return 0 to indicate the program ended successfully */
}

/**
 * prompt - Prints the prompt to the screen
 */
void prompt(void)
{
	printf("#cisfun$ ");   /* Print the prompt to the screen */
}

