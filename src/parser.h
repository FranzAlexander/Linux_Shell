#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

#define MAX_PROMPT_SIZE 100
#define MAX_PATH_SIZE 256

enum EXECUTION
{
    BACKGROUND,
    FOREGROUND,
    PIPEPLINE,
    CONCURRENT,
};

typedef struct Command
{
    char *cmd_name;
    int argc;
    char **argv;
    char *input_path;
    char *output_path;
    int mode;
    struct Command *next;
} Command;

Command *parse_command(char *line);

#endif // PARSER_H_INCLUDED
