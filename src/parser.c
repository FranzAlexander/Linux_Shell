#include "parser.h"

static int token_helper(char *line, char *cmd_name, char **args);
static struct Command *new_command(char *line);

static int token_helper(char *line, char *cmd_name, char **args)
{
    const char *dlim = " \t\r\n\a";

    char *token = strtok(line, dlim);

    int size = 0;
    int flags = 0;
    glob_t glob_buffer;
    int glob_counter = 0;

    while (token != NULL)
    {
        if (strchr(token, '*') != NULL || strchr(token, '?') != NULL)
        {
            flags |= (glob_counter > 1 ? GLOB_APPEND : 0);
            glob(token, flags, NULL, &glob_buffer);
            glob_counter = (int)glob_buffer.gl_pathc;
        }

        if (glob_counter > 0)
        {
            for (int i = 0; i < glob_counter; i += 1)
            {
                args[size += 1] = strdup(glob_buffer.gl_pathv[i]);
            }
            globfree(&glob_buffer);
        }
        else
        {
            args[size] = (char *)malloc(sizeof(char) * 50);
            strcpy(args[size], token);

            args[size] = (char *)realloc(args[size], strlen(args[size]));
        }
        token = strtok(NULL, dlim);

        size += 1;
    }

    // Means no arguments.
    if (args[0] == NULL)
    {
        args[0] = strdup(cmd_name);
    }

    free(token);

    return size;
}

static Command *new_command(char *line)
{
    Command *cmd = (Command *)malloc(sizeof(Command));
    cmd->cmd_name = (char *)malloc(sizeof(char) * 25);
    cmd->cmd_name = strtok(line, " ");

    cmd->argv = (char **)malloc(sizeof(char *) * 25);
    if (cmd->argv == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    cmd->argc = token_helper(line, cmd->cmd_name, cmd->argv);

    cmd->argv = (char **)realloc(cmd->argv, sizeof(char *) * (size_t)cmd->argc);

    cmd->input_path = NULL;
    cmd->output_path = NULL;

    // Loop through the arguments to check for redirection.
    for (int i = 0; i < cmd->argc; i += 1)
    {
        // Check for input.
        if (cmd->argv[i][0] == '>')
        {
            cmd->input_path = (char *)malloc(sizeof(char) * strlen(cmd->argv[i + 1]));
            strcpy(cmd->input_path, cmd->argv[i + 1]);
        }
        // Check for output.
        else if (cmd->argv[i][0] == '<')
        {
            cmd->output_path = (char *)malloc(sizeof(char) * strlen(cmd->argv[i + 1]));
            strcpy(cmd->output_path, cmd->argv[i + 1]);
        }
    }

    cmd->mode = 0;
    cmd->next = NULL;

    return cmd;
}

Command *parse_command(char *line)
{
    Command *current_command = (Command *)malloc(sizeof(Command));
    Command *root_command = NULL;

    // Get the size of the line entered by user.
    size_t line_size = strlen(line);

    int first_command = 1;
    char *line_pos = line;
    size_t counter = 0;

    //int mode = (line[line_size - 1] == '&') ? BACKGROUND : FOREGROUND;

    // Loop through the line.
    for (size_t i = 0; i < line_size; i += 1)
    {
        /* If the current character in the string is equal to 
        * |, & or the end of the line brake up the string. */
        if (*line == '|' || *line == '&' || *line == '\n')
        {
            int mode = 0;
            if (*line == '|')
            {
                mode = PIPEPLINE;
            }
            else if (*line == '&')
            {
                mode = CONCURRENT;
            }

            char *line_seg = (char *)malloc(sizeof(char) * counter);
            strncpy(line_seg, line_pos, counter);

            Command *new_cmd = new_command(line_seg);

            if (first_command == 1)
            {
                root_command = new_cmd;
                //root_command->mode = mode;
                current_command = root_command;
                first_command = 0;
            }
            else
            {
                current_command->next = new_cmd;
                current_command = new_cmd;
            }

            current_command->mode = mode;

            if (*line != '\n')
            {
                line += 1;
                line_pos = line;
                counter = 0;
            }
        }
        else
        {
            counter += 1;
            line += 1;
        }
    }

    return root_command;
}
