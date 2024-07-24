#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>    /* This lets us use printf to print things on the screen */
#include <stdlib.h>   /* This lets us use functions like malloc and free */
#include <unistd.h>   /* This lets us use system calls like execve */
#include <string.h>   /* This lets us use functions like strtok to split strings */
#include <sys/types.h>/* This lets us use various data types */
#include <sys/wait.h> /* This lets us use the wait function to wait for child processes */

void prompt(void);

#endif /* MAIN_H */

