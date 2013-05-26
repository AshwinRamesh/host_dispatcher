#include "../inc/pcb.h"
#include "../inc/readinput.h"
#include "../inc/dispatcher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


int main(int argc, char const *argv[]){

	/*Initialise Variables*/
	FILE *file; // input file
	PcbPtr process_queue; // the pcb queue

	if (argc != 2) {
		printf("%s\n", "Usage: hostd <filename>");
		return EXIT_FAILURE;
	}
	else if (!(file = fopen(argv[1],"r"))) {
		printf("%s\n", "File does not exist.");
		return EXIT_FAILURE;
	}

	/* Get process queue */
	printf("%s\n", "being reading file");
	process_queue = read_file(file);
	fclose(file);
	file = NULL;
	if (process_queue == NULL) { // error in reading
		return EXIT_FAILURE;
	}
	/* TODO */
	//pcb_printList(process_queue);
	printf("Begin Dispatcher\n");
	dispatcher(process_queue);
	return 0;
}
