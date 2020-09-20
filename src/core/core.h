#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include "macros.h"
#include "command.h"
#include "signal_handler.h"
#include "history.h"

void az_loop(void);

char *read_line(void);

int tokenize(char *line, char **args);

#endif // CORE_H
