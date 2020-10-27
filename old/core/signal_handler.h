#ifndef SIGNAL_HANDLER_H
#define SINGAL_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_signals(void);

void sigint_handler(int sig);

#endif
