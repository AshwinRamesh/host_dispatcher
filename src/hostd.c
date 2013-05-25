#include "../inc/pcb.h"
#include "../inc/readinput.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


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
	process_queue = read_file(file);
	fclose(file);
	file = NULL;
	if (process_queue == NULL) { // error in reading
		return EXIT_FAILURE;
	}
	/* TODO */
	return 0;
}
