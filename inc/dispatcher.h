#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include  "pcb.h"
#include <stdio.h>

void running_processes(PcbPtr queue);
void start_processes(PcbPtr queue);
void dispatcher(PcbPtr queue);

#endif
