#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <glob.h>

#define TOKEN_BUFFER 1024

enum EXECUTION
{
    BACKGROUND,
    FOREGROUND,
    PIPEPLINE,
};

typedef struct Command
{
    char* cmd;
    int argc;
    char **argv;
    char *input_path;
    char *output_path;
    int mode;
    struct Command *next;
} Command;

Command *parse_command(char *line);
void execute_command(Command *cmd);
//void drop_command(Command *cmd);

#endif // COMMAND_H_INCLUDED