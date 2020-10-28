#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "command_handler.h"

#define BLUE "\x1B[34m"
#define GREEN "\x1B[32m"
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

    char *prompt = (char *)malloc(sizeof(char) * MAX_PROMPT_SIZE);
    char *cwd = (char *)malloc(sizeof(char) * MAX_PATH_SIZE); // Current working directory
    strcpy(prompt, "azshell>");

    while (1)
    {
        printf("%s%s:%s%s%s", BLUE, getcwd(cwd, MAX_PATH_SIZE), GREEN, prompt, RESET);

        char *line = read_line();
        if (*line == '\0' || strlen(line) == 0)
        {
            continue;
        }

        cmd = parse_command(line);

        command_handler(cmd, &prompt);
    }
}