// command_handler.c - executes commands

#include "command_handler.h"

static void execute(char* path, char *argv[]);

void command_handler(command * c)
{
	pid_t pid = 0;

	if(c->background == 1)
	{
		if ((pid = fork()) < 0)
		{
			perror("Fork failed");
			exit(1);
		}
	}

	if(pid == 0)
	{


		if(strcmp(c->com_name, "exit") == 0)
			_exit(0);
		if(strcmp(c->com_name, "ls") == 0)
			execute("/bin/ls", c->argv);
		if(strcmp(c->com_name, "ps") == 0)
			execute("/bin/ps", c->argv);
		if(strcmp(c->com_name, "./show") == 0)
			execute("src/commands/tests/./show", c->argv);
	}
		
	if(pid == 0 && c->background == 1)
		kill(getpid(), SIGKILL);
}

static void execute(char* path, char *argv[])
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
