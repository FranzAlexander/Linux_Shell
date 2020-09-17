#include "core.h"

void az_loop(void)
{
	while (1)
	{
		printf("azshell> ");
		
		char *line = read_line();

		char **args = tokenize(line);

		printf("%s\n", args[0]);

		free(line);
		free(args);
	}
}

/*
 * Reads a line from the command line using the getline function.
 * */
char* read_line(void)
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

char** tokenize(char *line)
{
	const char dlim[2] = "-";
	char **args = malloc(sizeof(char) * 50);
	if(args == NULL)
	{
		perror("Failed to allocate memory!\n");
		exit(EXIT_FAILURE);
	}

	char *token = strtok(line, dlim);

	size_t size = 0;

	while(token != NULL)
	{
		args[size] = token;
		token = strtok(NULL, dlim);
		size++;
	}

	return args;
}

void signal_handler(int *s)
{
	printf("Caught singal %ls, coming out...\n", s);
	exit(1);
}
