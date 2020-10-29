// command_handler.c - executes commands

#include <pwd.h>
#include "command_handler.h"

static void execute(char* path, char *argv[]);
static void change_directory(char *path);
static void change_prompt(char **prompt, char *argv[]);

void command_handler(command * c, char **prompt)
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
	
		//int saved_stdout = 0;
		FILE * saved_stdout = stdout;
		
		if(c->redirect_out != NULL)			
			stdout = fopen(c->redirect_out, "w+");	// output writes to file
		
		if(strcmp(c->com_name, "exit") == 0)		// exit
			_exit(0);
		else if(strcmp(c->com_name, "ls") == 0)	// ls
			execute("/bin/ls", c->argv);
		else if(strcmp(c->com_name, "ps") == 0)	// ps
			execute("/bin/ps", c->argv);
		else if(strcmp(c->com_name, "pwd") == 0)	// pwd
                        execute("/bin/pwd", c->argv);
                else if(strcmp(c->com_name, "cd") == 0)       // cd
                        change_directory(c->argv[1]);
		else if(strcmp(c->com_name, "prompt") == 0)	// prompt
			change_prompt(prompt, c->argv);
		else if(strcmp(c->com_name, "./show") == 0 || strcmp(c->com_name, "show") == 0)
			execute("src/commands/tests/./show", c->argv);
		else if(strcmp(c->com_name, "sleep") == 0)	// sleep
			execute("/bin/sleep", c->argv);
		else if(strcmp(c->com_name, "echo") == 0)	// echo
                        execute("/bin/echo", c->argv);
		else
		{
			printf("'%s' not recognised\n", c->com_name);
			prompt = prompt; 	// unused parameter
		}
		
		if(c->redirect_out != NULL)		// output writes back to terminal
		{
			fclose(stdout);
			stdout = saved_stdout;
		}
	}
		
	if(pid == 0 && c->background == 1)	//kills child if not dead
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

// changes working directory to the parameter path
static void change_directory(char *path)
{
	int error = 0;
	if(path == NULL)
	{
		struct passwd *pw =  getpwuid(getuid());
		error = chdir(pw->pw_dir);
	}
	else
		error = chdir(path);

	if(error < 0)
		printf("Cannot change directory\n");
}

// changes prompt to user input
static void change_prompt(char **prompt, char *argv[])
{
	if(argv[1] == NULL)
		printf("Invalid. Try: prompt <new prompt>\n");
	else
	{
		char *temp = malloc(MAX_PROMPT_SIZE -1);
		strcpy(temp, argv[1]);
		int i=2;
		while(argv[i] != NULL)
		{
			strcat(temp, " ");
			strcat(temp, argv[i]);
		       	++i;
		}
		strcat(temp, " \0");
		strcpy(*prompt, temp);
	}
}
