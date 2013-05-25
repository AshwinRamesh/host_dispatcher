#include "../inc/pcb.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

PcbPtr pcb_queue(){
	Pcb * newPCB;
	return newPCB;
}

PcbPtr pcb_enqueue(){
	Pcb * newPCB;
	return newPCB;
}

/* Create mew pcb and return its address */
PcbPtr pcb_create(int arrival_time, int priority, int processor_time, int mbytes, int num_printers, int num_scanners, int num_modems, int num_cds){
	PcbPtr temp_pcb = (PcbPtr)malloc(sizeof(Pcb));

	// set process args
	temp_pcb->args[0] = PROCESS_NAME;
	temp_pcb->args[1] = processor_time;
	temp_pcb->args[2] = "\0";

	// set other numerical variable values
	temp_pcb->arrival_time = arrival_time;
	temp_pcb->priority = priority;
	temp_pcb->mbytes = mbytes;
	temp_pcb->num_printers = num_printers;
	temp_pcb->num_scanners = num_scanners;
	temp_pcb->num_modems = num_modems;
	temp_pcb->num_cds = num_cds;

	// set defaults for other variables
	temp_pcb->pid = 0;
	temp_pcb->remaining_cpu_time = 0;
	temp_pcb->prev = NULL;
	temp_pcb->next = NULL;

	return temp_pcb;
}

/* Free all memory in the pcb linked list. Returns NULL */
void pcb_free_memory(PcbPtr pcb_head) {
	if (pcb_head == NULL) {
		return pcb_head;
	}
	PcbPtr pcb_temp;
	while (1) {
		pcb_temp = pcb_head->next;
		free(pcb_head);
		if (pcb_temp == NULL) {
			return pcb_temp;
		}
		pcb_head = pcb_temp;
	}
}
