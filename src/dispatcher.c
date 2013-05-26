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
		current_process->remaining_cpu_time = current_process->remaining_cpu_time -1;
		if (current_process->remaining_cpu_time <= 0) { // processing time is completed
			pcb_terminate(current_process);
			pcb_dequeue(&rr_queue,&current_process);
			pcb_free(current_process);
			current_process = NULL;
		}
		else { // suspend and enqueue process back to roundrobin
			pcb_suspend(current_process);
			pcb_enqueue(rr_queue,current_process);
		}
	}
	return current_process;
}

/* Start next process in rr_queue. return current process */
PcbPtr start_process() {
	//printf("Process: %d Status: %d Time:%d\n", queue->id,queue->status,queue->remaining_cpu_time);
	if (current_process == NULL && rr_queue) {
		PcbPtr process = queue;
		pcb_start(process);
	}
}

/* Move head of queue to round robin queue */
void enqueue_roundrobin(PcbPtr queue, PcbPtr rr_queue) {
	PcbPtr process;
	while(queue->arrival_time <= clock_time) {
		process = pcb_dequeue(queue,queue);
		pcb_enqueue(rr_queue,process);
	}
}

void dispatcher(PcbPtr queue) {
	clock_time = 0;
	while (queue || rr_queue || current_process) {
		//printf("\nClock Time: %d\n", clock_time);
		//pcb_printList(queue);
		enqueue_roundrobin(queue,rr_queue); // add items to round robin
		current_process = running_processes(); //check running process and decrement time / suspend
		start_process(); // start next process in RR queue
		sleep(1);
		clock_time = clock_time+1;
	}
	//printf("%s\n", "dispatcher complete");
}
