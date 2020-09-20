#ifndef HISTORY_H
#define HISTORY_H

#include "stdio.h"
#include "stdlib.h"

typedef struct History
{
	int test;
//	char command_file_history[];
//	char command_history[];	
} History;

History *create_history(size_t f_size, size_t hist_size);

void add_to_command_history(const char *command);

#endif // HISTORY_H
