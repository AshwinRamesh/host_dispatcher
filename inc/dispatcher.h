#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include  "pcb.h"
#include <stdio.h>

PcbPtr running_processes();
PcbPtr start_process();
void dispatcher(PcbPtr queue);

#endif
