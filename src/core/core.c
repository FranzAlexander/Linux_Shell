#include "core.h"

void az_loop(void)
{
	while(1)
	{
		printf("azshell> ");
	}
}

void signal_handler(int *s)
{
	printf("Caught singal %ls, coming out...\n", s);
	exit(1);
}
