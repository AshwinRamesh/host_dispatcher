#ifndef PCB_H_
#define PCB_H_

#include <unistd.h>

#define MAX_ARGS	3
#define MAX_INPUT_SIZE 1024
#define PROCESS_NAME "./sigtrap"

/* List of Status for PCB */
#define RUNNING	1
#define WAITING	2
#define SUSPENDED	3
#define STOPPED	4
#define ERROR		-1
#define OTHER		0

struct pcb {
	//int id; // personal identifier
	pid_t pid; // process id given by machine
	int id; // identifier
	int status; // status of the process
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

PcbPtr pcb_get_tail(PcbPtr head);
PcbPtr pcb_dequeue(PcbPtr *head);
PcbPtr pcb_enqueue_tail(PcbPtr tail, PcbPtr child);
PcbPtr pcb_enqueue(PcbPtr head, PcbPtr child);
PcbPtr pcb_create(int arrival_time, int priority, int processor_time, int mbytes, int num_printers, int num_scanners, int num_modems, int num_cds);
void pcb_free(PcbPtr process);
PcbPtr pcb_free_all(PcbPtr pcb_head);
PcbPtr pcb_start(PcbPtr process);
PcbPtr pcb_terminate(PcbPtr process);
PcbPtr pcb_suspend(PcbPtr process);
void pcb_printList(PcbPtr queue) ;
#endif
