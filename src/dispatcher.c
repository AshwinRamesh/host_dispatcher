#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../inc/dispatcher.h"

int clock_time;
PcbPtr input_queue = NULL;
PcbPtr rr_queue = NULL;
PcbPtr current_process = NULL;

PcbPtr running_processes() {
	//printf("Process %d is running with Time: %d\n", queue->id,queue->remaining_cpu_time);
	if (current_process) { // if there is a process running
		printf("At clock %d current process id:%d \n",clock_time,current_process->id );
		current_process->remaining_cpu_time = current_process->remaining_cpu_time -1;
		if (current_process->remaining_cpu_time <= 0) { // processing time is completed
			printf("Terminating %d\n", current_process->id);
			pcb_terminate(current_process);
			pcb_free(current_process);
			current_process = NULL;
		}
		else { // suspend and enqueue process back to roundrobin
			printf("process exists\n");
			pcb_printList(rr_queue); // PROBLEM
			current_process = pcb_suspend(current_process);

			printf("%s\n", "suspended");
			rr_queue = pcb_enqueue(rr_queue,current_process);
			current_process = NULL;
		}
	}
	else {
		printf("current process does not exist\n");
	}
	return current_process;
}

/* Start next process in rr_queue. return current process */
PcbPtr start_process() {
	//printf("Process: %d Status: %d Time:%d\n", queue->id,queue->status,queue->remaining_cpu_time);
	if (current_process == NULL && rr_queue) {
		printf("In here\n");
		current_process = pcb_dequeue(&rr_queue);
		pcb_printList(rr_queue);
		pcb_start(current_process);
		return current_process;
	}
	return NULL;
}

/* Move head of queue to round robin queue */
void enqueue_roundrobin() {
	PcbPtr process;
	while(input_queue && input_queue->arrival_time <= clock_time) {
		process = pcb_dequeue(&input_queue);
		rr_queue = pcb_enqueue(rr_queue,process);
		printf("ENQUED RR\n");
		pcb_printList(rr_queue);
	}
}

void dispatcher(PcbPtr queue) {
	clock_time = 0;
	input_queue = queue;
	pcb_printList(queue);
	while (input_queue || rr_queue || current_process) {
		/*Testing Conditions */
		if (input_queue) {
			printf("Queue exists\n");
		}
		else {
			printf("Queue empty\n");
		}
		if (rr_queue) {
			printf("RR Queue exists\n");
		}
		else {
			printf("RR Queue empty\n");
		}
		if (current_process) {
			printf("Current Process exists\n");
		}
		else {
			printf("Current Process empty\n");
		}
		/* Remove Above*/
		printf("\nClock Time: %d\n", clock_time);
		enqueue_roundrobin(); // add items to round robin
		if (rr_queue == NULL) {
			printf("At clock: %d rr_queue is null\n",clock_time);
		}
		else {
			printf("At clock: %d rr_queue head id: %d\n",clock_time,rr_queue->id);
		}
		pcb_printList(rr_queue);
		current_process = running_processes(); //check running process and decrement time / suspend
		printf("RRQUEUE AGAIN:\n");
		pcb_printList(rr_queue);
		start_process(); // start next process in RR queue
		if (current_process) {
			printf("Current Process Running: %d\n",  current_process->id);
		}
		else {
			printf("Current Process does not exist yet.\n");
		}
		sleep(1);
		clock_time = clock_time+1;
	}
	//printf("%s\n", "dispatcher complete");
}
