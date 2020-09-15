#include "core.h"

void az_loop(void)
{
	while(1)
	{
		printf("azshell> ");
	}
}

char *read_line(void)
{
	char *buffer = NULL;
	size_t size = 0;

	if((getline(&buffer, &size, stdin)) != -1)
	{
		return buffer;
	}

	free(buffer);
	return "";
}

void tokenize(char* line, char *args[])
{
	char dlim[2] = "-";
	char *token = strtok(line, dlim);

	for(size_t i = 0; i < array_size(token); i++)
	{
		args[i] = strtok(NULL, dlim);
	}
}

void signal_handler(int *s)
{
	printf("Caught singal %ls, coming out...\n", s);
	exit(1);
}
