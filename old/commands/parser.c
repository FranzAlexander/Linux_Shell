#include "parser.h"

char *read_line(void)
{
    size_t size = 0;
    char *line = malloc(sizeof(char));

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

// int tokenize(char *line, char **args)
// {
//     const char const *dlim = " \t\r\n\a";

//     char *token = strtok(line, dlim);

//     int size = 0;
// }