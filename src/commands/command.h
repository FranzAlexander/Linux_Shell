// command.h - describes command caller and basic command functions
// connor nicholson
// Sep 19 20

#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

//unsure the purpose of this struct.
/*typedef struct Command
{
	const char *built_in[1];
} Command;*/


// calls the relevant command for user input
void command_caller(char *input);

#endif // COMMAND_H
