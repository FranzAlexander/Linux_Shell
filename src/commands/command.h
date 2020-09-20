// command.h - describes command caller and basic command functions
// connor nicholson
// Sep 19 20

#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include "macros.h"

static void ls(void);
static void show(void);

// calls the relevant command for user input
void command_caller(char *input);

#endif // COMMAND_H
