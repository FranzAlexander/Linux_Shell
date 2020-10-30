#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include "macros.h"
#include "parser.h"
#include "command_handler.h"
static void handle_signals();
static void sigint_handler(int sig_no);
static void sigstp_handler(int sig_no);

static void sigint_handler(int sig_no)
{
    printf("\nType exit to quite program! \n");
}

static void sigstp_handler(int sig_no)
{
    pause();
}

static void handle_signals()
{
    struct sigaction action, tstp_action;
    action.sa_handler = &sigint_handler;
    action.sa_flags = SA_RESTART;
    sigaction(SIGINT, &action, NULL);

    tstp_action.sa_handler = &sigstp_handler;
    sigaction(SIGTSTP, &tstp_action, NULL);
}

void az_loop(void)
{
    handle_signals();

    char *prompt = (char *)malloc(MAX_PROMPT_SIZE);
    char *cwd = (char *)malloc(MAX_PATH_SIZE); //current working directory
    strcpy(prompt, "azshell>  ");

    while (1)
    {
        char *cmd;
        int lc = 0;
        char *c;
        command **cl;

        printf("%s%s:%s%s%s", BLUE, getcwd(cwd, MAX_PATH_SIZE), GREEN, prompt, RESET);

        cmd = (char *)malloc(CMD_LENGTH);

        cmd = fgets(cmd, CMD_LENGTH, stdin);
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
