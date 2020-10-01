#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct ProcessQueue
{
	pid_t id;
	char *p_name;

} ProcessQueue;

ProcessQueue *create_queue(void);

void add_to_queue(pid_t id, char *name);

void delete_from_queue(pid_t id);

void delete_queue(ProcessQueue *queue);

#endif // QUEUE_H_INCLUDED
