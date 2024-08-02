#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* Function declarations */
void display_prompt(void);
int execute_command(char *cmd);

extern char **environ;

#endif /* MAIN_H */

