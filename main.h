#ifndef MAIN_H
#define MAIN_H

#include <stdio.h> /* For printf */
#include <stdlib.h> /* For malloc, free */
#include <unistd.h> /* For execve */
#include <string.h> /* For strtok */
#include <sys/types.h> /* For data types */
#include <sys/wait.h> /* For wait */

/* Function prototypes */
void prompt(void);
int main(void);
char *read_input(void);
char **split_line(char *line);
void execute_command(char **argv);

#endif /* MAIN_H */

