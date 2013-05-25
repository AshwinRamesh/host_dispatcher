#ifndef PCB_H_
#define PCB_H_

#include <unistd.h>

#define MAX_ARGS	3
#define MAX_INPUT_SIZE 1024
#define PROCESS_NAME "./sigtrap"

struct pcb {
	//int id; // personal identifier
	pid_t pid; // process id given by machine
	char * args[MAX_ARGS]; // process args for exec

	/* List of items for process */
	int arrival_time;
	int priority;
	int processor_time;
	int mbytes;
	int num_printers;
	int num_scanners;
	int num_modems;
	int num_cds;
	/* End List */

	int remaining_cpu_time; // remaining time for process

	/* Linked List Elements */
	struct pcb * prev;
	struct pcb * next;
	/* End Linked List Elements*/
};
typedef struct pcb Pcb;
typedef Pcb * PcbPtr;

PcbPtr pcb_queue();
PcbPtr pcb_enqueue();
PcbPtr pcb_create(int arrival_time, int priority, int processor_time, int mbytes, int num_printers, int num_scanners, int num_modems, int num_cds);
PcbPtr pcb_free_memory(PcbPtr pcb_head);
#endif
