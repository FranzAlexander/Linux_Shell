// command.c - defines command caller and basic commands
// Connor Nicholson
// 19 Sep 20

#include "command.h"

static void ls(void);		// prints file names of current directory
static void show(void);		// runs the show program found in test files

void command_caller(char *input)
{
	if(strcmp(input, "exit") == 0)
		exit(0);
	else if(strcmp(input, "ls") == 0)
		ls();
	else if(strcmp(input, "./show") == 0)
		show();
	else
		printf("'%s' not recognised\n", input);
}

static void ls(void)
{
	DIR *dp;
	struct dirent *dir;
	dp = opendir(".");
	if(dp)
	{
		while((dir = readdir(dp)) != NULL)	//read all in directory
		{
			if(dir->d_type == DT_DIR)
			{
				// disregard '..' and '.' files and colour dir blue
				if(strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") != 0)
					printf(BLU "%s " RESET, dir->d_name);	
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
	
	if((pid = fork()) < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	if(pid == 0)	//if child
		execvp(args[0], args);
	if(pid > 0)	//if parent
		wait(NULL);
}
