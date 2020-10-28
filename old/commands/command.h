#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include "parser.h"

enum COMMAND_TYPE
{
    EXTERNAL,
};

enum EXECUTION
{
    BACKGROUND,
    FOREGROUND,
    PIPEPLINE,
};

enum STATUS
{
    RUNNING,
    DONE,
    SUSPENDED,
    CONTINUED,
    TERMINATED,
};

typedef struct CmdProcess
{
    char *cmd;
    int argc;
    char **argv;
    char *input_path;
    char *output_path;
    //   int type;
    int status;
    struct CmdProcess *next;
} CmdProcess;

typedef struct Command
{
    int id;
    CmdProcess *root;
    int mode;
} Command;

Command *parse_command(char *line);

int command_type(char **args, int arg_num);

#endif // COMMAND_H_INCLUDED