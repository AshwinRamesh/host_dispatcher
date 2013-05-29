#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../inc/dispatcher.h"
#include "../inc/mab.h"
#include "../inc/resources.h"

int clock_time;

PcbPtr input_queue = NULL; // queue from reading file
PcbPtr realtime_queue = NULL; // real time queue
PcbPtr user_queue = NULL; // user job queue;
// Below are feedback queues. 1 is highest priority
PcbPtr p1_queue = NULL;
PcbPtr p2_queue = NULL;
PcbPtr p3_queue = NULL;

PcbPtr current_process = NULL; // current process pointer

RsrcPtr io_resources = NULL; // resources for the dispatcher.

void print_queues() {
	printf("Printing INPUT QUEUE\n"); 	pcb_printList_forward(input_queue);
	printf("Printing USER QUEUE\n");		pcb_printList_forward(user_queue);
	printf("Printing REAL TIME QUEUE \n");	pcb_printList_forward(realtime_queue);
	printf("Printing P1 QUEUE\n");		pcb_printList_forward(p1_queue);
	printf("Printing P2 QUEUE\n");		pcb_printList_forward(p2_queue);
	printf("Printing P3 QUEUE\n");		pcb_printList_forward(p3_queue);
}

PcbPtr running_processes() {
	//printf("Process %d is running with Time: %d\n", queue->id,queue->remaining_cpu_time);
	if (current_process) { // if there is a process running
		//printf("At clock: %d Process Running: %d with Seconds Remaining: %d -> %d\n", clock_time,current_process->id,current_process->remaining_cpu_time, current_process->remaining_cpu_time-1);
		current_process->remaining_cpu_time = current_process->remaining_cpu_time -1;
		if (current_process->remaining_cpu_time <= 0) { // processing time is completed
			pcb_terminate(current_process);
			// free resources
			if (current_process->priority > 0) { // not real time
				io_resources = free_resource(io_resources,current_process);
			}
			//TODO:: FREE MAB HERE
			pcb_free(current_process);
			//print_queues();
			current_process = NULL;
		}
		else if (realtime_queue || p1_queue || p2_queue || p3_queue){ // suspend and enqueue process back to roundrobin if other waiting processes
			if (current_process->priority == 0) { //real time process
				return current_process;
			}
			current_process = pcb_suspend(current_process);
			if (current_process-> priority < 3 && current_process->priority != 0){ // reduce priority
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
	if (current_process == NULL && (realtime_queue || p1_queue || p2_queue || p3_queue)) {
		if (realtime_queue) {
			current_process = pcb_dequeue(&realtime_queue);
		}
		else if (p1_queue) {
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

/* Move head of userqueue to feedback queues */
void enqueue_roundrobin() {
	PcbPtr process;
	while (user_queue) { //TODO:: check if memory can be allocated here
		if (check_resource(io_resources,user_queue) == 1){ // if resources can be allocated for the given process
			process = pcb_dequeue(&user_queue);
			io_resources = allocate_resource(io_resources,process);
			switch (process->priority) {
				case 0:
					break;
				case 1:
					p1_queue = pcb_enqueue(p1_queue,process);
					break;
				case 2:
					p2_queue = pcb_enqueue(p2_queue,process);
					break;
				case 3:
					p3_queue = pcb_enqueue(p3_queue,process);
					break;
				default:
					fprintf(stderr, "Error. Priority not correctly set. Process ID: %d Priority: %d\n",process->id,process->priority);
					break;
			}
		}
		else {
			//printf(" %d resources cannot be allocated for Process %d\n",user_queue->arrival_time, user_queue->id);
			break;
		}
	}
}

/* Move input->head of queue to user queue */
void enqueue_user_real_queues(){
	PcbPtr process;
	while(input_queue && input_queue->arrival_time <= clock_time) {
		//printf("Enqueue from input id: %d arrival %d clock %d\n",input_queue->id,input_queue->arrival_time,clock_time);
		process = pcb_dequeue(&input_queue);
		if (process->priority == 0) { // real time queue
			realtime_queue = pcb_enqueue(realtime_queue,process);
		}
		else {
			user_queue = pcb_enqueue(user_queue,process);
		}
	}
}

void dispatcher(PcbPtr queue) {
	clock_time = 0;
	input_queue = queue;
	pcb_printList(queue);
	io_resources = create_resource(PRINTERS,SCANNERS,MODEMS,CDS);
	while (input_queue || user_queue || realtime_queue || current_process || p1_queue || p2_queue || p3_queue) {
		//printf("CLOCK TIME : %d \n .================.\n", clock_time);
		enqueue_user_real_queues(); // add items to user queue and real time queue
		enqueue_roundrobin(); // add items to feedback queues if memory can be allocated
		current_process = running_processes(); //check running process and decrement time / suspend
		start_process(); // start next process in RR queue
		sleep(1);
		clock_time = clock_time+1;
	}
	destroy_resource(io_resources); // free memory for resources
	//printf("%s\n", "dispatcher complete");
}
