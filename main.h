#ifndef MAIN_H
#define MAIN_H

extern char **environ;

void handle_command(char *args[]);
char *find_command(char *command);

#endif /* MAIN_H */

