// command_handler.c - executes commands

#include "command_handler.h"

static void execute(char *path, char *argv[]);
static void execute_wildcard(char *path, char **argv);

void command_handler(command *c)
{
	pid_t pid = 0;

	if (c->background == 1)
	{
		if ((pid = fork()) < 0)
		{
			perror("Fork failed");
			exit(1);
		}
	}

	if (pid == 0)
	{

		if (strcmp(c->com_name, "exit") == 0)
			_exit(0);
		if (strcmp(c->com_name, "ls") == 0)
		{
			if (strcmp(c->argv[1], "*") == 0)
			{
				execute_wildcard(c->com_name, c->argv);
			}
			else
			{
				execute("/bin/ls", c->argv);
			}
		}
		if (strcmp(c->com_name, "ps") == 0)
			execute("/bin/ps", c->argv);
		if (strcmp(c->com_name, "./show") == 0)
			execute("src/commands/tests/./show", c->argv);
	}

	if (pid == 0 && c->background == 1)
		kill(getpid(), SIGKILL);
}

static void execute(char *path, char *argv[])
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

static void execute_wildcard(char *path, char **argv)
{
	pid_t pd;

	if ((pd = fork()) < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	if (pd == 0)
	{
		printf("%s\n", path);
		glob_t glob_buffer;
		int flags = 0;
		for (int i = 1; i < 2; i += 1)
		{
			flags |= (i > 1 ? GLOB_APPEND : 0);
			int result = glob(argv[i], flags, NULL, &glob_buffer);

			if (result != 0)
			{
				fprintf(stderr, "%s: problem with %s (%s), stopping early!\n",
						argv[0], argv[i],
						(result == GLOB_ABORTED ? "filesystem problem"
												: result == GLOB_NOMATCH ? "no match of pattern"
																		 : result == GLOB_NOSPACE ? "no dynamic memory"
																								  : "unknown problem"));
				break;
			}
		}

		for (size_t i = 0; i < glob_buffer.gl_pathc; i += 1)
		{
			printf("%s\n", glob_buffer.gl_pathv[i]);
		}
		// execvp(argv[0], &glob_buffer.gl_pathv[0]);
		globfree(&glob_buffer);
	}
	else if (pd > 0)
	{
		wait(NULL);
	}
}