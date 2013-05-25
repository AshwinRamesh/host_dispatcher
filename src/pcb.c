#include "../inc/pcb.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

/* Get last node in queue*/
PcbPtr pcb_get_tail(PcbPtr head) {
	while (head->next != NULL) {
		head = head->next;
	}
	return head;
}

/* Remove head of queue and return it */
PcbPtr pcb_dequeue(PcbPtr *head){
	if(head == NULL) {
		return NULL; // no more processes left
	}
	PcbPtr temp_pcb = *head;
	*head = (*head)->next;
	temp_pcb->next = NULL;
	return temp_pcb;
}

/*Similar to pcb_enqueue, except tail of queue is given instead of head */
PcbPtr pcb_enqueue_tail(PcbPtr tail, PcbPtr child) {
	tail->next = child;
	child->prev = tail;
	return child; // returns new tail
}

/* link new pcb to end of queue. Params: head of queue, new pcb*/
PcbPtr pcb_enqueue(PcbPtr head, PcbPtr child){
	if (head == NULL) {
		head = child;
	}
	else if (head->next == NULL) {
		pcb_enqueue_tail(head,child);
	}
	else {
		PcbPtr tail = pcb_get_tail(head);
		pcb_enqueue_tail(tail,child);
	}
	return head;
}

/* Create mew pcb and return its address */
PcbPtr pcb_create(int arrival_time, int priority, int processor_time, int mbytes, int num_printers, int num_scanners, int num_modems, int num_cds){
	PcbPtr temp_pcb = (PcbPtr)malloc(sizeof(Pcb));
	// set process args
	temp_pcb->args[0] = PROCESS_NAME;
	char temp[5];
	sprintf(temp,"%d",processor_time);
	temp_pcb->args[1] = temp;
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
PcbPtr pcb_free_memory(PcbPtr pcb_head) {
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

PcbPtr pcb_start(PcbPtr process) {
	switch(process->pid = fork()) {
		case -1:
			printf("%s\n", "Error starting process");
			return NULL;
			break;
		case 0:
			execvp(process->args[0],process->args);
			break;
		default:
			break;
	}
	return process;
}

PcbPtr pcb_terminate(PcbPtr process) {
	//if(kill(process->pid,SIGINT) != 0) { // error
	//	printf("%s\n", "Error Terminating PID");
	//	return NULL;
	//}
	return process
}
