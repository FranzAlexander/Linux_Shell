#include "core.h"

void az_loop(void)
{
	char **cmd_hist = malloc(sizeof(char) * 1000);
	for (int i = 0; i < 1000; i+=1)
	{
		cmd_hist[i] = malloc(sizeof(char) * 255);
	}

	handle_signals();

	char *prompt = malloc(MAX_PROMPT_SIZE);
	char *cwd = malloc(MAX_PATH_SIZE);	//current working directory
	strcpy(prompt, "azshell>  ");

	while (1)
	{
		char *cmd;
		int lc = 0;
		char *c;
		command **cl;
		
		printf("%s%s:%s%s%s", BLUE, getcwd(cwd, MAX_PATH_SIZE), GREEN, prompt, RESET);

		cmd = (char *) malloc(CMD_LENGTH);

		cmd = fgets(cmd, CMD_LENGTH, stdin);
		c = index(cmd, '\n');
		*c = '\0';
		//printf("Command Line : [%s] [%ld]\n", cmd, strlen(cmd));

		cl = process_cmd_line(cmd, 1);
		
		while (cl[lc] != NULL)		//while command array not null
	       	{
			command_handler(cl[lc], &prompt);
			lc++;
		}
	
		while(wait(NULL) != -1);	//zombie preventer
		clean_up(cl);
		free(cmd);

		/*char *line = read_line();
		char **args = malloc(sizeof(char) * MAX_ARGS);
		if (args == NULL)
		{
			perror("Failed to allocate memory!\n");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < MAX_ARGS; i+=1)
		{
			args[i] = malloc(sizeof(char) * ARG_SIZE);
		}

		if (*line == '\n')
		{
			continue;
		}

		int arg_num = tokenize(line, args);

		for (int i = 0; i < arg_num; i+=1)
		{
			//printf("%s\n", args[i]);
			execute_command(args[i]);
		}

		for (int i = 0; i < MAX_ARGS; i+=1)
		{
			free(args[i]);
		}
		free(args);
		free(line);*/
		
		
	}
	free(prompt);
	free(cwd);
}

/*
 * Reads a line from the command line using the getline function.
 * 
char *read_line(void)
{
	size_t size = 0;
	char *line = malloc(sizeof(char));

	if (line == NULL)
	{
		perror("Failed to allocate memory!\n");
		exit(EXIT_FAILURE);
	}

	if ((getline(&line, &size, stdin)) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("Failed to read line input!\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		return line;
	}
}

int tokenize(char *line, char **args)
{
	const char *dlim = " -\t\n";

	char *token = strtok(line, dlim);

	int size = 0;

	while (token != NULL)
	{
		args[size] = token;
		token = strtok(NULL, dlim);
		size++;
	}

	return size;
}*/
