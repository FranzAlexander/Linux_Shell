#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include "macros.h"
#include "parser.h"
#include "command_handler.h"

static void handle_signals(void);
static void handler(int sig_no);
static void az_loop(void);

static void handler(int sig_no)
{
    switch (sig_no)
    {
    case SIGINT:
        printf("\nType exit to quit program! \n");
        break;
    case SIGTSTP:
        printf("\nCan not pause program! \n");
        break;
    case SIGQUIT:
        printf("\nCan not quit program, type exit!\n");
        break;

    default:
        fprintf(stderr, "Caught wrong signal: %d\n", signal);
        break;
    }
}

static void handle_signals(void)
{
    struct sigaction action;
    action.sa_handler = &handler;
    action.sa_flags = SA_RESTART;
    sigfillset(&action.sa_mask);

    if (sigaction(SIGINT, &action, NULL) == -1)
    {
        perror("Failed to set signal handlers!\n");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGTSTP, &action, NULL) == -1)
    {
        perror("Failed to set signal handlers!\n");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGQUIT, &action, NULL) == -1)
    {
        perror("Failed to set signal handlers!\n");
        exit(EXIT_FAILURE);
    }
}

static void az_loop(void)
{
    handle_signals();

    char *prompt = (char *)malloc(MAX_PROMPT_SIZE);
    char *cwd = (char *)malloc(MAX_PATH_SIZE); //current working directory
    strcpy(prompt, "azshell>  ");

    while (1)
    {
        int again = 1;
        char *cmd;
        int lc = 0;
        char *c;
        command **cl;

        printf("%s%s:%s%s%s", BLUE, getcwd(cwd, MAX_PATH_SIZE), GREEN, prompt, RESET);

        cmd = (char *)malloc(CMD_LENGTH);

        while (again)
        {
            again = 0;
            cmd = fgets(cmd, CMD_LENGTH, stdin);
            if (cmd == NULL)
            {
                if (errno == EINTR)
                    again = 1;
            }
        }
        c = index(cmd, '\n');
        *c = '\0';

        cl = process_cmd_line(cmd, 1);

        while (cl[lc] != NULL) //while command array not null
        {
            command_handler(cl[lc], &prompt);
            //print_human_readable(cl[lc], lc);
            lc++;
        }

        while (wait(NULL) != -1)
            ; //zombie preventer
        clean_up(cl);
        free(cmd);
    }
    free(prompt);
    free(cwd);
}

int main(void)
{
    az_loop();
    return EXIT_SUCCESS;
}
