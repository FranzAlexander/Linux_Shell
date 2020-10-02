#ifndef MACROS_H
#define MACROS_H

#define array_size(x) (sizeof (*x) / sizeof (x[0]))

#define MAX_ARGS 50
#define ARG_SIZE 150

#define MAX_PATH_SIZE 256
#define MAX_PROMPT_SIZE 100

#define TRUE 1
#define FALSE 0

#define BLUE "\x1B[34m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

#endif
