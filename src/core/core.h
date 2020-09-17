#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include "macros.h"


void az_loop(void);

char *read_line(void);

char **tokenize(char *line);

void signal_handler(int *s);
