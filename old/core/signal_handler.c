#include "signal_handler.h"

void handle_signals(void)
{
	signal(SIGINT, sigint_handler);
}

void sigint_handler(int sig)
{
	printf("%d\n", sig);
	signal(SIGINT, sigint_handler);
	fflush(stdout);
}
