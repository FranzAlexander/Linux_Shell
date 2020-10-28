#include "command_handler.h"

static void execute(char *path, char **argv);
static void change_directory(char *path);
static void change_prompt(char **prompt, char **argv);

void command_handler(Command *cmd, char **prompt)
{
    Command *current;

    pid_t pid = 0;

    for (current = cmd; current != NULL; current = current->next)
    {
        if (cmd->mode == BACKGROUND)
        {
            if ((pid = fork()) < 0)
            {
                perror("Fork failed!");
                exit(EXIT_FAILURE);
            }
        }

        if (pid == 0)
        {
            if (strcmp(cmd->cmd_name, "exit") == 0) // exit
            {
                _exit(0);
            }
            else if (strcmp(cmd->cmd_name, "ls") == 0) // ls
            {
                execute("/bin/ls", cmd->argv);
            }
            else if (strcmp(cmd->cmd_name, "ps") == 0) // ps
            {
                execute("/bin/ps", cmd->argv);
            }
            else if (strcmp(cmd->cmd_name, "pwd") == 0) // pwd
            {
                execute("/bin/pwd", cmd->argv);
            }
            else if (strcmp(cmd->cmd_name, "cd") == 0) // cd
            {
                change_directory(cmd->argv[1]);
            }
            else if (strcmp(cmd->cmd_name, "prompt") == 0) // prompt
            {
                change_prompt(prompt, cmd->argv);
            }
            else if (strcmp(cmd->cmd_name, "./show") == 0 || strcmp(cmd->cmd_name, "show") == 0)
            {
                execute("src/commands/tests/./show", cmd->argv);
            }
            else
            {
                printf("'%s' not recognised\n", cmd->cmd_name);
                prompt = prompt; // unused parameter
            }
        }

        if (pid == 0 && cmd->mode == BACKGROUND) //kills child if not dead
            kill(getpid(), SIGKILL);
    }
}

static void execute(char *path, char **argv)
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) //if child
        execv(path, argv);
    if (pid > 0) //if parent
        wait(NULL);
}

// changes working directory to the parameter path
static void change_directory(char *path)
{
    int error = 0;
    if (path == NULL)
    {
        struct passwd *pw = getpwuid(getuid());
        error = chdir(pw->pw_dir);
    }
    else
        error = chdir(path);

    if (error < 0)
        printf("Cannot change directory\n");
}

// changes prompt to user input
static void change_prompt(char **prompt, char **argv)
{
    if (argv[1] == NULL)
        printf("Invalid. Try: prompt <new prompt>\n");
    else
    {
        char *temp = malloc(MAX_PROMPT_SIZE - 1);
        strcpy(temp, argv[1]);
        int i = 2;
        while (argv[i] != NULL)
        {
            strcat(temp, " ");
            strcat(temp, argv[i]);
            ++i;
        }
        strcat(temp, " \0");
        strcpy(*prompt, temp);
    }
}