// command.h - describes command caller and basic command functions
// connor nicholson
// Sep 19 20

#ifndef COMMAND_H
#define COMMAND_H

#define BLU "\x1B[34m"
#define RESET "\x1B[0m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>

//unsure the purpose of this struct.
/*typedef struct Command
{
	const char *built_in[1];
} Command;*/


// calls the relevant command for user input
void command_caller(char *input);

#endif // COMMAND_H
