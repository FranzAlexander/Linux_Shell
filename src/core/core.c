#include "core.h"

void az_loop(void)
{
	while (1)
	{
		printf("azshell> ");
		
		char *line = read_line();
		char **args = malloc(sizeof(char) * 50);
		if(args == NULL)
		{
			perror("Failed to allocate memory!\n");
			return;
		}

		if(*line == '\n')
		{
			continue;
		}

		int arg_num = tokenize(line, args);
	
		for(int i = 0; i < arg_num; i++)
		{
			printf("%s\n", args[i]);
		}
	
		free(line);
		free(args);
	}
}

/*
 * Reads a line from the command line using the getline function.
 * */
char *read_line(void)
{
	size_t size = 0;
	char *line = malloc(sizeof(char));

	if ((getline(&line, &size, stdin)) == -1)
	{
		if(feof(stdin))
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

	while(token != NULL)
	{
		args[size] = token;
		token = strtok(NULL, dlim);
		size++;
	}

	return size;
}

void signal_handler(int *s)
{
	printf("Caught singal %ls, coming out...\n", s);
	exit(1);
}

