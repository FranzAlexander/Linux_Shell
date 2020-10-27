// command_handler.h - executes commands

#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <glob.h>
#include "macros.h"
#include "parser.h"

void command_handler(command * c);

#endif // COMMAND_HANDLER_H
