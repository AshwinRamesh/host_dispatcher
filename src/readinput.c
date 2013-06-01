#include "../inc/readinput.h"
#include "../inc/pcb.h"
#include "../inc/mab.h"
#include "../inc/resources.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Count number of lines in file */
int count_file_lines(char* file_name) {
	FILE *file;
	if (!(file = fopen(file_name,"r"))) {
		printf("%s\n", "File does not exist. Exiting");
		exit(1);
	}
	int ch;
	int count=0;
	do {
		ch = fgetc(file);
		if (ch == '\n') {
			count++;
		}
	}while(ch != EOF);
	fclose(file);
	return count;
}

/* Runs all validation on each line of input ensuring that it is correctly formatted and does not follow incorrect logic */
int validate_input_line(int arrival_time, int priority, int processor_time, int mbytes, int num_printers, int num_scanners, int num_modems, int num_cds) {
	// check that priorities are between 0-3
	if (priority < 0 || priority > 3) {
		return 0;
	}
	// check that real time has 64 memory
	if (priority == 0 && mbytes != 64) {
		return 0;
	}
	// check that resources are not less than 0
	if (num_printers < 0 || num_cds < 0 || num_modems < 0 || num_scanners < 0) {
		return 0;
	}
	// check that real time has no resources
	if (priority == 0 && (num_printers != 0 || num_cds != 0 || num_modems != 0 || num_scanners != 0)) {
		return 0;
	}
	// check that memory is not over allocated or negative
	if (priority != 0 && (mbytes < 0  || mbytes > USER_TIME_MEMORY)) {
		return 0;
	}
	// check that resources are not overallocated
	if (priority > 0 && (num_printers > PRINTERS || num_cds > CDS || num_modems > MODEMS || num_scanners > SCANNERS)) {
		return 0;
	}
	// check that arrival time is not negative
	if (arrival_time < 0) {
		return 0;
	}
	// check that processor time is not negative
	if (processor_time < 0) {
		return 0;
	}
	return 1; // Proper input
}

/* Read Input */
PcbPtr read_file(char * file_name) {
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
	FILE *file;

	/*Check that there are not too many lines in file*/
	int lines = count_file_lines(file_name);
	if (lines > MAX_INPUT_LINES) {
		fprintf(stderr, "Error. Too many lines in file. Maximum %d File has %d. Exiting\n", MAX_INPUT_LINES,lines);
		exit(1);
	}
	/* Read each line of the file */
	if (!(file = fopen(file_name,"r"))) {
		printf("%s\n", "File does not exist. Exiting");
		exit(1);
	}
	int line = 0;
	while(fgets(buffer,sizeof(buffer),file) != NULL) {
		line++;
		int arg_count = sscanf(buffer,"%d, %d, %d, %d, %d, %d, %d, %d", &arrival_time, &priority, &processor_time, &mbytes, &num_printers, &num_scanners, &num_modems, &num_cds);
		/* Error in the file input line itself*/
		if (arg_count != 8) {
			printf("%s\n", "Error: File format is incorrect.");
			return pcb_free_all(process_queue_head); // returns NULL
		}
		/* Checks to see that input is correct with format of dispatcher */
		int correct_input = validate_input_line(arrival_time,priority,processor_time,mbytes,num_printers,num_scanners,num_modems,num_cds);
		if (correct_input == 1) {
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
			fprintf(stderr, "Input line [%d] is illegally formatted. Ignoring line...\n",line);
		}
	}
	fclose(file);
	return process_queue_head;
}
