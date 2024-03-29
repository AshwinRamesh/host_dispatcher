#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "../inc/pcb.h"

/*Global Variables*/
int id_count = 0;

/* Get last node in queue*/
PcbPtr pcb_get_tail(PcbPtr head) {
	while (head->next != NULL) {
		head = head->next;
	}
	return head;
}

/* Remove pcb in queue and return it */
PcbPtr pcb_dequeue(PcbPtr *head){
	if((*head) == NULL) {
		fprintf(stderr, "Head is null. Cannot Dequeue.\n");
		return NULL;
	}
	PcbPtr temp_pcb = *head;
	*head = (*head)->next;
	if ((*head) != NULL) {
		(*head)->prev = NULL; // new head will have null before
	}
	temp_pcb->next = NULL;
	temp_pcb->prev = NULL;
	return temp_pcb;
}

/*Similar to pcb_enqueue, except tail of queue is given instead of head */
PcbPtr pcb_enqueue_tail(PcbPtr tail, PcbPtr child) {
	child->next = NULL;
	tail->next = child;
	child->prev = tail;
	return child; // returns new tail
}

/* link new pcb to end of queue. Params: head of queue, new pcb*/
PcbPtr pcb_enqueue(PcbPtr head, PcbPtr child){
	if (head == NULL) { // head is null. nothing in queue
		child->next = NULL;
		child->prev = NULL;
		head = child;
	}
	else if (head->next == NULL) { // head is only node in queue or is tail of queue
		pcb_enqueue_tail(head,child);
	}
	else { // inner node
		PcbPtr tail = pcb_get_tail(head);
		pcb_enqueue_tail(tail,child);
	}
	return head;
}

/* Create new pcb and return its address */
PcbPtr pcb_create(int arrival_time, int priority, int processor_time, int mbytes, int num_printers, int num_scanners, int num_modems, int num_cds){
	id_count = id_count + 1; // increment ID count
	PcbPtr temp_pcb = (PcbPtr)malloc(sizeof(Pcb));
	// set process args
	temp_pcb->args[0] = (char *)malloc(MAX_INPUT_SIZE);
	strcpy(temp_pcb->args[0],PROCESS_NAME);
	temp_pcb->args[1] = (char *)malloc(MAX_INPUT_SIZE);
	sprintf(temp_pcb->args[1],"%d",processor_time);
	temp_pcb->args[2] = NULL;
	// set other numerical variable values
	temp_pcb->id = id_count;
	temp_pcb->arrival_time = arrival_time;
	temp_pcb->remaining_cpu_time = processor_time;
	temp_pcb->processor_time = processor_time;
	temp_pcb->priority = priority;
	temp_pcb->mbytes = mbytes;
	temp_pcb->num_printers = num_printers;
	temp_pcb->num_scanners = num_scanners;
	temp_pcb->num_modems = num_modems;
	temp_pcb->num_cds = num_cds;
	// set defaults for other variables
	temp_pcb->pid = 0;
	temp_pcb->status = WAITING;
	temp_pcb->prev = NULL;
	temp_pcb->next = NULL;
	return temp_pcb;
}

/* Free single PCB */
void pcb_free(PcbPtr process) {
	if (process != NULL) {
		free(process->args[0]);
		free(process->args[1]);
		free(process);
	}
}

/* Free all memory in the pcb linked list. Returns NULL */
PcbPtr pcb_free_all(PcbPtr pcb_head) {
	if (pcb_head == NULL) {
		return pcb_head;
	}
	PcbPtr pcb_temp;
	while (1) {
		pcb_temp = pcb_head->next;
		pcb_free(pcb_head);
		if (pcb_temp == NULL) {
			return pcb_temp;
		}
		pcb_head = pcb_temp;
	}
}

/* Start process of the given PCB */
PcbPtr pcb_start(PcbPtr process) {
	if (process->status == WAITING) { // process is currently waiting
		process->status = RUNNING;
		switch(process->pid = fork()) {
			case -1:
				printf("%s\n", "Error starting process");
				return NULL;
				break;
			case 0:
				process->status = RUNNING;
				printf("ID: %d pid: %d priority: %d arrival: %d remaining time: %d offset: %d mbytes: %d prn: %d scn: %d modem: %d cd: %d \n",process->id, getpid(),process->priority,process->arrival_time,process->remaining_cpu_time,process->memory->offset,process->mbytes,process->num_printers,process->num_scanners,process->num_modems,process->num_cds);
				execvp(process->args[0],process->args);
				break;
			default:
				break;
		}
		return process;
	}
	else if (process->status == SUSPENDED) { // process is currently suspended
		if (kill(process->pid, SIGCONT)) {
       			fprintf(stderr, "Restart of process:%dfailed\n",process->id);
        			return NULL;
    		}
		process->status = RUNNING;
		return process;
	}
	else {
		fprintf(stderr, "An error occured during start. proccess: %d has status %d\n", process->id,process->status);
	}
	return NULL; // null if error
}

/* Terminate the PCB */
PcbPtr pcb_terminate(PcbPtr process) {
	if(kill(process->pid,SIGINT) != 0) { // error
		fprintf(stderr, "Termination failed for pid: %d\n", process->pid);
		return NULL;
	}
	int status;
	process->status = STOPPED;
	waitpid(process->pid,&status,WUNTRACED);
	return process;
}

/* Suspend the PCB */
PcbPtr pcb_suspend(PcbPtr process) {
	if(kill(process->pid,SIGTSTP)) {
		fprintf(stderr, "Suspending Process:%d failed\n",process->id );
	}
	int status;
	process->status = SUSPENDED;
	waitpid(process->pid,&status,WUNTRACED);
	return process;
}

/* Function to check if the linked list is correct */
void pcb_printList(PcbPtr queue) {
	if (queue == NULL) {
		printf("\n%s\n", "QUEUE IS NULL");
	}
	PcbPtr last;
	int temp;
	printf("%s\n", "Testing Forwards:");
	while (queue != NULL) {
		if (queue->next == NULL) {
			temp = 8888;
		}
		else {
			temp = queue->next->id;
		}
		printf("Current Process: %d Next Process: %d\n",queue->id,temp );
		last = queue;
		queue = queue->next;
	}
	printf("%s\n", "Testing Backwards");
	queue = last;
	while(queue != NULL) {
		if (queue->prev == NULL) {
			temp = 9999;
		}
		else {
			temp = queue->prev->id;
		}
		printf("Current Process: %d Prev Process: %d\n",queue->id,temp );
		last = queue;
		queue = queue->prev;
	}
	printf("%s\n", "Finished Testing");
}

/* Function to check if the linked list is correct */
void pcb_printList_forward(PcbPtr queue) {
	if (queue == NULL) {
		printf("\n%s\n", "QUEUE IS NULL");
	}
	int temp;
	printf("%s\n", "Testing Forwards:");
	while (queue != NULL) {
		if (queue->next == NULL) {
			temp = 8888;
		}
		else {
			temp = queue->next->id;
		}
		printf("Current Process: %d Next Process: %d\n",queue->id,temp );
		queue = queue->next;
	}
	printf("%s\n", "Finished Testing");
}
