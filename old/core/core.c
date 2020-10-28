#include "core.h"

void az_loop(void)
{
	while (1)
	{
		printf(BLUE "$: " RESET);

		char *line = read_line();
		if (*line == '\n' || strlen(line) == 0)
		{
			continue;
		}
		Command *cmd_process = parse_command(line);
		if (cmd_process->root == NULL)
		{
			printf("Root Empty");
		}
		else
		{
			printf("%d", cmd_process->root->argc);
		}

		// for (int i = 0; i < cmd_process->root->argc; i += 1)
		// {
		// 	printf("%s\n", cmd_process->root->argv[i]);
		// }
	}
}
