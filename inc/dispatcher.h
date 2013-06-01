#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include  "pcb.h"
#include <stdio.h>

PcbPtr running_processes();
PcbPtr start_process();
void enqueue_roundrobin();
void dispatcher(PcbPtr queue);
void enqueue_userqueue();
#endif
