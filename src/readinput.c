#include "../inc/pcb.h"
#include "../inc/resources.h"
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
		/* Checks to see that input is correct with format of dispatcher */
		int correct_input = 0;
		if (priority == 0 && num_printers == 0 && num_scanners == 0 && num_modems == 0 && num_cds == 0) { // ensuring real time has no IO
			correct_input = 1;
		}
		if ( correct_input == 1 || (priority > 0 && priority <= 3 && num_printers <= PRINTERS && num_scanners <= SCANNERS && num_modems <= MODEMS && num_cds <= CDS)) { //ensuring user ps doesnt have too many IOs
			temp_pcb = pcb_create(arrival_time,priority,processor_time,mbytes,num_printers,num_scanners,num_modems,num_cds);
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
		else { // error in input row
			fprintf(stderr, "Input line given has incorrect parameters and does not fit with the dispatcher specs. Ignoring line...\n");
		}
	}
	return process_queue_head;
}
