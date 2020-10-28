#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "command.h"

#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

static char *read_line(void);

static char *read_line(void)
{
    size_t size = 0;
    char *line = (char *)malloc(sizeof(char));

    if ((getline(&line, &size, stdin)) == -1)
    {
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("Failed to read line input!\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        return line;
    }
}

int main(void)
{
    Command *cmd;
    while (1)
    {
        printf(BLUE "$: " RESET);

        char *line = read_line();
        if (*line == '\0' || strlen(line) == 0)
        {
            continue;
        }

        cmd = parse_command(line);
        for (int i = 0; i < cmd->argc; i += 1)
        {
            printf("Hello: %s\n", cmd->argv[i]);
        }
        execute_command(cmd);
    }
}