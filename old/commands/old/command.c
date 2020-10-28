// command.c - defines command caller and basic commands
// Connor Nicholson
// 19 Sep 20

#include "command.h"

static void ls(void);						   // prints file names of current directory
static void show(void);						   // runs the show program found in test files
static int check_built_in(char *input);		   // Check to see if the command is built in.
static void execute_built_in(char *input);	   // Executes a command that is built in.
static void execute_non_built_in(char *input); // Executes a non built in command.

void execute_command(char *input)
{
	if (check_built_in(input) == 0)
	{
		execute_built_in(input);
	}
	else
	{
		execute_non_built_in(input);
	}
}

static int check_built_in(char *input)
{
	int result = -1;

	for (size_t i = 0; i < (sizeof(built_in) / sizeof(built_in[0])); i += 1)
	{
		if (strcmp(input, built_in[i]) == 0)
		{
			result = 0;
			return result;
		}
		else
		{
			result = 1;
			return result;
		}
	}

	return result;
}

static void execute_built_in(char *input)
{
	if (strcmp(input, built_in[0]) == 0)
	{
		exit(0);
	}
	else if (strcmp(input, built_in[1]) == 0)
	{
		ls();
	}
}

static void execute_non_built_in(char *input)
{
	int pipe_fds[2];
	
	if(pipe(pipe_fds) == -1)
	{
		perror("Could not initialize pipe!\n");
		exit(EXIT_FAILURE);
	}

	pid_t p1 = fork();
	if(p1 == -1)
	{
		perror("Could not create child process!\n");
		exit(EXIT_FAILURE);
	}	
}

// void command_caller(char *input)
// {
// 	if (strcmp(input, "exit") == 0)
// 		exit(0);
// 	else if (strcmp(input, "ls") == 0)
// 		ls();
// 	else if (strcmp(input, "./show") == 0)
// 		show();
// 	else
// 		printf("'%s' not recognised\n", input);
// }

static void ls(void)
{
	DIR *dp;
	struct dirent *dir;
	dp = opendir(".");
	if (dp)
	{
		while ((dir = readdir(dp)) != NULL) //read all in directory
		{
			if (dir->d_type == DT_DIR)
			{
				// disregard '..' and '.' files and colour dir blue
				if (strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") != 0)
					printf(BLUE "%s " RESET, dir->d_name);
			}
			else
				printf("%s ", dir->d_name);
		}
		printf("\n");
		closedir(dp);
	}
}

static void show(void)
{
	char *args[] = {"src/commands/tests/./show", NULL};
	pid_t pid;

	if ((pid = fork()) < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	if (pid == 0) //if child
		execvp(args[0], args);
	if (pid > 0) //if parent
		wait(NULL);
}
