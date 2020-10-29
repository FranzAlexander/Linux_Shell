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

		cl = process_cmd_line(cmd, 1);
		
		while (cl[lc] != NULL)		//while command array not null
	       	{
			command_handler(cl[lc], &prompt);
			//print_human_readable(cl[lc], lc);
			lc++;
		}
		
	
		while(wait(NULL) != -1);	//zombie preventer
		clean_up(cl);
		free(cmd);		
		
	}
	free(prompt);
	free(cwd);
}
