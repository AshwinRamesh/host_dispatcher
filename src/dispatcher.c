#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../inc/dispatcher.h"

int clock_time;
PcbPtr input_queue = NULL; // queue from reading file
PcbPtr p1_queue = NULL;
PcbPtr p2_queue = NULL;
PcbPtr p3_queue = NULL;

PcbPtr current_process = NULL;

PcbPtr running_processes() {
	//printf("Process %d is running with Time: %d\n", queue->id,queue->remaining_cpu_time);
	if (current_process) { // if there is a process running
		current_process->remaining_cpu_time = current_process->remaining_cpu_time -1;
		if (current_process->remaining_cpu_time <= 0) { // processing time is completed
			pcb_terminate(current_process);
			pcb_free(current_process);
			current_process = NULL;
		}
		else if (p1_queue || p2_queue || p3_queue){ // suspend and enqueue process back to roundrobin if other waiting processes
			current_process = pcb_suspend(current_process);
			if (current_process-> priority < 3){ // reduce priority
				current_process->priority = current_process->priority +1 ;
			}
			switch (current_process->priority) {
				case 1:
					p1_queue = pcb_enqueue(p1_queue,current_process);
					break;
				case 2:
					p2_queue = pcb_enqueue(p2_queue,current_process);
					break;
				case 3:
					p3_queue = pcb_enqueue(p3_queue,current_process);
					break;
				default:
					fprintf(stderr, "Error. Priority is out of bounds\n");
			}
			current_process = NULL;
		}
	}
	return current_process;
}

/* Start next process in p*_queue. return current process */
PcbPtr start_process() {
	//printf("Process: %d Status: %d Time:%d\n", queue->id,queue->status,queue->remaining_cpu_time);
	if (current_process == NULL && (p1_queue || p2_queue || p3_queue)) {
		if (p1_queue) {
			current_process = pcb_dequeue(&p1_queue);
		}
		else if (p2_queue) {
			current_process = pcb_dequeue(&p2_queue);
		}
		else if (p3_queue) {
			current_process = pcb_dequeue(&p3_queue);
		}
		else {
			fprintf(stderr, "Error. Priority Queues all null\n");
		}
		pcb_start(current_process);
		return current_process;
	}
	return NULL;
}

/* Move head of queue to round robin queue */
void enqueue_roundrobin() {
	PcbPtr process;
	while(input_queue && input_queue->arrival_time <= clock_time) {
		//printf("ENQUEUE FROM INPUT STARTING. Printing P1\n");
		process = pcb_dequeue(&input_queue);
		p1_queue = pcb_enqueue(p1_queue,process);
		//pcb_printList_forward(p1_queue);
	}
}

void dispatcher(PcbPtr queue) {
	clock_time = 0;
	input_queue = queue;
	pcb_printList(queue);
	while (input_queue || current_process || p1_queue || p2_queue || p3_queue) {
		//printf("\nClock Time: %d\n", clock_time);
		enqueue_roundrobin(); // add items to round robin
		current_process = running_processes(); //check running process and decrement time / suspend
		start_process(); // start next process in RR queue
		sleep(1);
		clock_time = clock_time+1;
	}
	//printf("%s\n", "dispatcher complete");
}
