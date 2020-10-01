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

static const char *built_in[] = {"exit", "ls", "cd"};

typedef struct Command
{
	int first;
	int last;
	char *sep;
}Command;

void execute_command(char *input);

//static int check_build_in(char *input);

// calls the relevant command for user input
void command_caller(char *input);

#endif // COMMAND_H
