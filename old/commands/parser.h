#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Reads a line from the command line using the getline function.    
*/
char *read_line(void);

/*
* Breaks the string pass in into seperate parts, returns the number of arguments.
*/
//int tokenize(char *line, char **args);

#endif // PARSER_H_INCLUDED