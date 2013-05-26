#include "../inc/pcb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PcbPtr read_file(FILE *file) {

	PcbPtr process_queue_head = NULL;
	PcbPtr process_queue_tail = NULL;
	PcbPtr temp_pcb = NULL;

	char buffer[MAX_INPUT_SIZE];

	int arrival_time;
	int priority;
	int processor_time;
	int mbytes;
	int num_printers;
	int num_scanners;
	int num_modems;
	int num_cds;
	/* Read each line of the file */
	while(fgets(buffer,sizeof(buffer),file) != NULL) {
		int arg_count = sscanf(buffer,"%d, %d, %d, %d, %d, %d, %d, %d", &arrival_time, &priority, &processor_time, &mbytes, &num_printers, &num_scanners, &num_modems, &num_cds);
		/* Error in the file input */
		if (arg_count != 8) {
			printf("%s\n", "Error: File format is incorrect.");
			return pcb_free_all(process_queue_head); // returns NULL
		}
		//printf("%s %d\n", "Creating pcb with arrival time",arrival_time); // remove later
		temp_pcb = pcb_create(arrival_time,priority,processor_time,mbytes,num_printers,num_scanners,num_modems,num_cds);

		//TODO - other checks for process / real time etc.
		//printf("%d\n", arrival_time);
		if (process_queue_head == NULL){
			process_queue_head = pcb_enqueue(process_queue_head,temp_pcb);
		}
		else if (process_queue_tail == NULL) {
			process_queue_tail = pcb_enqueue(process_queue_head,temp_pcb)->next;
		}
		else {
			process_queue_tail = pcb_enqueue_tail(process_queue_tail,temp_pcb);
		}
	}
	return process_queue_head;
}
