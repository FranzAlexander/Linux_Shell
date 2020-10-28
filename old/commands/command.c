#include "command.h"

static int token_helper(char *line, char **args);
static CmdProcess *create_process(char *line);

Command *parse_command(char *line)
{
    size_t size = strlen(line);
    CmdProcess *root_process = NULL;
    CmdProcess *process = NULL;

    for (size_t i = 0; i <= size; i += 1)
    {
        if (*line == '|')
        {
            char *cmd_seg = NULL;
            strncpy(cmd_seg, line, i);
            CmdProcess *new_process = create_process(cmd_seg);

            if (root_process == NULL)
            {
                printf("Hello\n");
                root_process = new_process;
                process = root_process;
            }
            else
            {
                process->next = new_process;
                process = new_process;
            }
        }
        else if (*line == '\0')
        {
            CmdProcess *new_process = create_process(line);
            printf("This is cmd: %s\n", new_process->cmd);
            if (root_process == NULL)
            {
                printf("Hello\n");
                root_process = new_process;
                process = root_process;
            }
            else
            {
                process->next = new_process;
                process = new_process;
            }
        }

        line += 1;
    }

    int mode = (line[size - 1] == '&') ? BACKGROUND : FOREGROUND;

    Command *cmd = (Command *)malloc(sizeof(Command));
    cmd->root = root_process;
    cmd->mode = mode;
    return cmd;
}

static int token_helper(char *line, char **args)
{
    const char *dlim = " \t\r\n\a";

    char *token = strtok(line, dlim);

    int size = 0;

    while (token != NULL)
    {
        glob_t glob_buffer;
        if (args[size] == NULL)
        {
            args[size] = (char *)malloc(sizeof(char) * 50);
        }

        if (strchr(token, '*') == 0)
        {
            glob(token, 0, NULL, &glob_buffer);
        }

        if (glob_buffer.gl_pathc > 0)
        {
            for (size_t i = 0; i < glob_buffer.gl_pathc; i += 1)
            {
                strcpy(args[size], glob_buffer.gl_pathv[i]);
                //  args[size] = strdup(glob_buffer.gl_pathv[i]);
            }
            globfree(&glob_buffer);
        }
        else
        {
            strcpy(args[size], token);

            args[size] = (char *)realloc(args[size], strlen(args[size]));

            token = strtok(NULL, dlim);

            size += 1;
        }
    }

    free(token);

    return size;
}

static CmdProcess *create_process(char *line)
{
    char **args = (char **)malloc(sizeof(char *) * 10);
    if (args == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    int args_num = token_helper(line, args);

    for (int i = 0; i < args_num; i += 1)
    {
        printf("test: %s\n", args[i]);
    }

    args = (char **)realloc(args, (size_t)args_num);

    char *input_path = NULL;
    char *output_path = NULL;

    for (int size = 0; size < args_num; size += 1)
    {
        if (args[size][0] == '<')
        {
            input_path = (char *)malloc((strlen(args[size + 1] + 1) * sizeof(char)));
            strcpy(input_path, args[size + 1]);
        }
        else if (args[size][0] == '>')
        {
            output_path = (char *)malloc((strlen(args[size + 1] + 1) * sizeof(char)));
            strcpy(output_path, args[size + 1]);
        }
    }

    printf("args_num: %d\n", args_num);
    CmdProcess *cmd_process = (CmdProcess *)malloc(sizeof(CmdProcess));
    cmd_process->cmd = line;
    cmd_process->argc = args_num;
    cmd_process->argv = args;
    cmd_process->input_path = input_path;
    cmd_process->output_path = output_path;
    cmd_process->next = NULL;
    return cmd_process;
}

// static int command_type(char **args, int arg_num)
// {
//     const char *types[5] = {">", ">>", "<", "|", "&"};

//     for (int i = 0; i < 5; i += 1)
//     {
//         for (int ii = 0; ii < arg_num; ii += 1)
//         {
//             if (strcmp(args[ii], types[i]) == 0)
//             {
//                 return i + 1;
//             }
//         }
//     }
//     return 0;
// }