// command.c - defines command caller and basic commands
// Connor Nicholson
// 19 Sep 20

#include "command.h"

static void ls(void);	// prints file names of current directory

void command_caller(char *input)
{
	if(strcmp(input, "exit") == 0)
	{
		exit(0);
	}
	else if(strcmp(input, "ls") == 0)
	{
		ls();
	}
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
			if(dir->d_type == DT_REG)	//excludes hidden files such as "." & ".."
				printf("%s ", dir->d_name);
		}
		printf("\n");
		closedir(dp);
	}
}
