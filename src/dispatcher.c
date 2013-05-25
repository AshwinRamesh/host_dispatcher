#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../inc/dispatcher.h"

int clock_time;

void running_processes(PcbPtr queue) {
	printf("%s\n", "Checking running processes");
	while(queue != NULL) {
		if (queue->status == RUNNING) {
			queue->remaining_cpu_time = queue->remaining_cpu_time - 1;
			printf("Process %d is running with Time: %d\n", queue->id,queue->remaining_cpu_time);
			if (queue->remaining_cpu_time <= 0) {
				PcbPtr temp_pcb;
				temp_pcb = queue;
				queue = queue->next;
				pcb_terminate(temp_pcb);
			}
			else {
				queue = queue->next;
			}
		}
		else {
			queue = queue->next;
		}
	}
}

void start_processes(PcbPtr queue) {
	printf("%s\n", "Starting new processes");
	while(queue != NULL) {
		printf("Process: %d Status: %d Time:%d\n", queue->id,queue->status,queue->remaining_cpu_time);
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
		printf("\nClock Time: %d\n", clock_time);
		printf("%s\n", "running dispatcher");
		if (queue == NULL) {
			printf("%d %s\n", clock_time,"queue is null");
		}
		running_processes(queue); //check running processes and decrement time
		if (queue == NULL) {
			printf("%s\n", "queue is null");
		}
		start_processes(queue); // start all processes for arrival_time
		sleep(1);
		clock_time = clock_time+1;
	}
}
