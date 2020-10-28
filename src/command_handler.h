#ifndef COMMAND_HANDLER_H_INCLUDED
#define COMMAND_HANDLER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>
#include "parser.h"

void command_handler(Command *cmd, char **prompt);

#endif // COMMAND_HANDLER_H_INCLUDED