#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "macros.h"


void az_loop(void);

char *read_line(void);

void tokenize(char *line, char *args[]);

void signal_handler(int *s);
