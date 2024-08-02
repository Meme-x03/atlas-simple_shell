#ifndef MAIN_H
#define MAIN_H

/**
 * File: main.h
 * Author: Your Name
 * Description: Header file containing function prototypes for simple shell.
 */

extern char **environ;

/**
 * handle_command - Handles execution of a command.
 * @args: Array of arguments.
 */
void handle_command(char *args[]);

/**
 * find_command - Finds the full path of a command.
 * @command: The command to find.
 *
 * Return: The full path of the command, or NULL if not found.
 */
char *find_command(char *command);

#endif /* MAIN_H */

