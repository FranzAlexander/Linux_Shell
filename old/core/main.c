#include <stdlib.h>
#include <stdio.h>
#include "core.h"

int main(int argc, char **argv)
{
	printf("%d", argc);
	printf("%s", *argv);
	az_loop();
	return EXIT_SUCCESS;
}
