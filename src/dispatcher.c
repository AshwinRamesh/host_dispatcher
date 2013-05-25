#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../inc/dispatcher.h"

int clock_time;

PcbPtr running_processes(PcbPtr queue) {
	//printf("%s\n", "Checking running processes");
	PcbPtr queue_head = queue;
	while(queue != NULL) {
		//printf("The current head is ID: %d\n",queue_head->id );
		//printf("Process %d is available with Time: %d\n", queue->id,queue->remaining_cpu_time);
		if (queue->status == RUNNING) {
			queue->remaining_cpu_time = queue->remaining_cpu_time - 1;
			//printf("Process %d is running with Time: %d\n", queue->id,queue->remaining_cpu_time);
			if (queue->remaining_cpu_time <= 0) {
				PcbPtr temp_pcb;
				temp_pcb = queue;
				queue = queue->next;
				temp_pcb = pcb_terminate(temp_pcb);
				temp_pcb = pcb_dequeue(&queue_head,&temp_pcb);
				pcb_free(temp_pcb);
			}
			else {
				queue = queue->next;
			}
		}
		else {
			queue = queue->next;
		}
	}
	return queue_head;
}

void start_processes(PcbPtr queue) {
	while(queue != NULL) {
		//printf("Process: %d Status: %d Time:%d\n", queue->id,queue->status,queue->remaining_cpu_time);
		if (queue->status == WAITING && (queue->arrival_time <= clock_time)) {
			PcbPtr process = queue;
			pcb_start(process);
		}
		queue = queue->next;
	}
}

void dispatcher(PcbPtr queue) {
	clock_time = 0;
	while (queue != NULL) {
		//printf("\nClock Time: %d\n", clock_time);
		//pcb_printList(queue);
		queue = running_processes(queue); //check running processes and decrement time
		start_processes(queue); // start all processes for arrival_time
		sleep(1);
		clock_time = clock_time+1;
	}
}
